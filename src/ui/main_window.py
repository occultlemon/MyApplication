import psutil
from datetime import datetime
from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QLabel, QStackedWidget, QFrame, QApplication,
    QGraphicsDropShadowEffect, QSizePolicy, QMessageBox
)
from PyQt5.QtCore import (
    Qt, QTimer, QPropertyAnimation, QRect, QEasingCurve,
    pyqtSignal, QSize, QPoint
)
from PyQt5.QtGui import QFont, QColor, QPainter, QPixmap, QIcon, QCursor

from src.db.database import Database
from src.utils.config import Config
from src.utils.notification import show_notification, play_alert_sound
from src.core.todo_manager import TodoManager
from src.core.reminder_manager import ReminderManager
from src.core.alarm_manager import AlarmManager
from src.core.launcher_manager import LauncherManager
from src.core.hotkey_manager import HotkeyManager
from src.core.pomodoro_manager import PomodoroManager
from src.ui.tray_icon import TrayIcon
from src.ui.todo_panel import TodoPanel
from src.ui.reminder_panel import ReminderPanel
from src.ui.alarm_panel import AlarmPanel
from src.ui.launcher_panel import LauncherPanel
from src.ui.pomodoro_panel import PomodoroPanel
from src.ui.clipboard_panel import ClipboardPanel
from src.ui.sticky_note import StickyNoteManager
from src.ui.settings_panel import SettingsPanel
from src.ui.styles import get_theme


# ── 侧栏导航项配置 ──
NAV_ITEMS = [
    ("☑", "待办事项"),
    ("🔔", "提醒事项"),
    ("⏰", "闹钟"),
    ("🚀", "快捷启动"),
    ("🍅", "番茄钟"),
    ("📋", "剪贴板"),
    ("⚙", "设置"),
]

# ── 边框拖拽缩放常量 ──
RESIZE_MARGIN = 6
EDGE_NONE = 0
EDGE_LEFT = 1
EDGE_RIGHT = 2
EDGE_TOP = 4
EDGE_BOTTOM = 8

# ── 展开模式默认占屏幕的比例 ──
EXPAND_W_RATIO = 0.28          # 宽度 = 可用宽 × 28%
EXPAND_H_RATIO = 0.68          # 高度 = 可用高 × 68%
EXPAND_MIN_W_RATIO = 0.16      # 最小宽度比例
EXPAND_MIN_H_RATIO = 0.35      # 最小高度比例
# 绝对下限（逻辑像素），防止在超大屏上比例值太小
EXPAND_ABS_MIN_W = 300
EXPAND_ABS_MIN_H = 340


class MainWindow(QWidget):
    """主窗口：支持迷你模式 / 展开模式（可缩放、可最大化），无边框悬浮，多屏自适应"""

    def __init__(self):
        super().__init__()
        # ── 初始化基础设施 ──
        self.db = Database()
        self.config = Config()
        self.is_mini = True
        self._is_maximized = False
        self._normal_geo = None
        self._drag_pos = None
        self._resize_edge = EDGE_NONE
        self._resize_origin = None
        self._resize_origin_geo = None
        self._current_nav = 0
        self._current_screen = None      # 当前所在的 QScreen 对象

        # ── 根据当前屏幕计算尺寸 ──
        self._current_screen = QApplication.primaryScreen()
        self._calc_sizes(self._current_screen)

        # ── 窗口属性 ──
        self.setWindowFlags(
            Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool
        )
        self.setAttribute(Qt.WA_TranslucentBackground)
        self.setMouseTracking(True)
        self.setGeometry(100, 100, self.mini_w, self.mini_h)

        # ── 初始化管理器 ──
        self.todo_mgr = TodoManager(self.db)
        self.reminder_mgr = ReminderManager(self.db)
        self.alarm_mgr = AlarmManager(self.db)
        self.launcher_mgr = LauncherManager(self.db)
        self.pomodoro_mgr = PomodoroManager(self.db, self.config)
        self.sticky_mgr = StickyNoteManager(self.db)
        self.hotkey_mgr = HotkeyManager(self.config)

        # ── 构建UI ──
        self._build_ui()

        # ── 系统托盘 ──
        self.tray = TrayIcon(self)
        self.tray.show_window.connect(self._show_expanded)
        self.tray.quit_app.connect(self._quit)
        self.tray.new_todo.connect(lambda: self._show_panel(0, focus=True))
        self.tray.new_reminder.connect(lambda: self._show_panel(1, focus=True))
        self.tray.new_sticky.connect(self.sticky_mgr.create_new)
        self.tray.toggle_mini.connect(self.toggle_mode)
        self.tray.show()

        # ── 连接信号 ──
        self.reminder_mgr.reminder_fired.connect(self._on_reminder)
        self.alarm_mgr.alarm_fired.connect(self._on_alarm)

        # ── 时钟刷新 ──
        self._clock_timer = QTimer(self)
        self._clock_timer.setInterval(1000)
        self._clock_timer.timeout.connect(self._update_clock)
        self._clock_timer.start()

        # ── 系统监控 ──
        self._sys_timer = QTimer(self)
        self._sys_timer.setInterval(3000)
        self._sys_timer.timeout.connect(self._update_sys_info)
        self._sys_timer.start()

        # ── 加载配置 ──
        theme = self.config.get('theme', 'dark')
        self.setStyleSheet(get_theme(theme))
        opacity = self.config.get('opacity', 0.95)
        self.setWindowOpacity(opacity)

        # ── 初始加载默认快捷方式 ──
        self._init_default_shortcuts()

        # ── 恢复便签 ──
        self.sticky_mgr.restore_all()

        # ── 启动快捷键 ──
        self.hotkey_mgr.toggle_window.connect(self.toggle_mode)
        self.hotkey_mgr.new_todo.connect(lambda: self._show_panel(0, focus=True))
        self.hotkey_mgr.new_reminder.connect(lambda: self._show_panel(1, focus=True))
        self.hotkey_mgr.open_launcher.connect(lambda: self._show_panel(3))
        self.hotkey_mgr.minimize_window.connect(self._minimize_to_tray)
        self.hotkey_mgr.maximize_window.connect(self._toggle_maximize)
        self.hotkey_mgr.start()

        # 初始显示迷你模式
        self._show_mini()

    # ═════════════════════════════════════════
    #  屏幕检测 + 自适应尺寸计算
    # ═════════════════════════════════════════
    def _get_current_screen(self):
        """获取窗口中心点所在的 QScreen，多显示器场景下精确定位"""
        center = self.geometry().center()
        screen = QApplication.screenAt(center)
        return screen if screen else QApplication.primaryScreen()

    def _calc_sizes(self, screen):
        """根据指定 QScreen 的可用区域和 DPI 动态计算所有尺寸"""
        avail = screen.availableGeometry()
        dpr = screen.devicePixelRatio()            # 设备像素比（1.0 / 1.25 / 1.5 / 2.0 ...）
        logical_dpi = screen.logicalDotsPerInch()
        dpi_factor = max(1.0, logical_dpi / 96.0)  # DPI 缩放因子

        # ── 迷你模式 ──
        self.mini_w = max(56, int(64 * dpi_factor))
        self.mini_h = self.mini_w

        # ── 展开模式默认尺寸（纯比例，不设硬编码上限） ──
        self.expand_w = max(EXPAND_ABS_MIN_W, int(avail.width() * EXPAND_W_RATIO))
        self.expand_h = max(EXPAND_ABS_MIN_H, int(avail.height() * EXPAND_H_RATIO))

        # ── 缩放约束 ──
        self.expand_min_w = max(EXPAND_ABS_MIN_W, int(avail.width() * EXPAND_MIN_W_RATIO))
        self.expand_min_h = max(EXPAND_ABS_MIN_H, int(avail.height() * EXPAND_MIN_H_RATIO))
        self.expand_max_w = avail.width()
        self.expand_max_h = avail.height()

        # ── 侧边栏 ──
        self.sidebar_w = max(48, int(52 * dpi_factor))

    def _adapt_to_screen(self, new_screen):
        """窗口从一个屏幕拖到另一个屏幕时，按比例自适应尺寸"""
        old_screen = self._current_screen
        old_avail = old_screen.availableGeometry() if old_screen else None

        # 重新计算所有尺寸
        self._current_screen = new_screen
        self._calc_sizes(new_screen)

        # 更新迷你控件尺寸
        self.mini_widget.setFixedSize(self.mini_w - 12, self.mini_h - 12)
        # 更新侧边栏宽度
        self.sidebar.setFixedWidth(self.sidebar_w)

        if self.is_mini:
            # 迷你模式：直接更新固定尺寸
            self.setMinimumSize(0, 0)
            self.setMaximumSize(16777215, 16777215)
            self.setFixedSize(self.mini_w, self.mini_h)

        elif self._is_maximized:
            # 最大化模式：最大化到新屏幕
            new_avail = new_screen.availableGeometry()
            self.setGeometry(new_avail)

        else:
            # 展开模式：按旧屏幕→新屏幕的比例缩放
            new_avail = new_screen.availableGeometry()
            if old_avail and old_avail.width() > 0 and old_avail.height() > 0:
                w_ratio = new_avail.width() / old_avail.width()
                h_ratio = new_avail.height() / old_avail.height()
                new_w = max(self.expand_min_w, min(self.expand_max_w, int(self.width() * w_ratio)))
                new_h = max(self.expand_min_h, min(self.expand_max_h, int(self.height() * h_ratio)))
            else:
                new_w = self.expand_w
                new_h = self.expand_h

            self.setMinimumSize(self.expand_min_w, self.expand_min_h)
            self.setMaximumSize(self.expand_max_w, self.expand_max_h)
            self.resize(new_w, new_h)

    # ═════════════════════════════════════════
    #  UI 构建
    # ═════════════════════════════════════════
    def _build_ui(self):
        self.root_layout = QVBoxLayout(self)
        self.root_layout.setContentsMargins(6, 6, 6, 6)
        self.root_layout.setSpacing(0)

        # ── 迷你模式 Widget ──
        self.mini_widget = QWidget()
        self.mini_widget.setObjectName("miniWidget")
        self.mini_widget.setFixedSize(self.mini_w - 12, self.mini_h - 12)
        mini_layout = QVBoxLayout(self.mini_widget)
        mini_layout.setContentsMargins(0, 6, 0, 6)
        mini_layout.setAlignment(Qt.AlignCenter)

        self.mini_time = QLabel("00:00")
        self.mini_time.setAlignment(Qt.AlignCenter)
        self.mini_time.setFont(QFont("Consolas", 11, QFont.Bold))
        self.mini_time.setStyleSheet("color: #89b4fa;")
        mini_layout.addWidget(self.mini_time)

        self.mini_badge = QLabel("0")
        self.mini_badge.setAlignment(Qt.AlignCenter)
        self.mini_badge.setFont(QFont("Arial", 9))
        self.mini_badge.setStyleSheet(
            "background: #f38ba8; color: #1e1e2e; border-radius: 8px; "
            "min-width:16px; max-width:24px; padding:1px 4px; font-weight:bold;"
        )
        mini_layout.addWidget(self.mini_badge, 0, Qt.AlignCenter)

        self.root_layout.addWidget(self.mini_widget)

        # ── 展开模式 Widget ──
        self.expand_widget = QWidget()
        self.expand_widget.setObjectName("mainWindow")
        self.expand_widget.setVisible(False)
        expand_layout = QVBoxLayout(self.expand_widget)
        expand_layout.setContentsMargins(0, 0, 0, 0)
        expand_layout.setSpacing(0)

        # 标题栏
        self.title_bar = self._build_title_bar()
        expand_layout.addWidget(self.title_bar)

        # 内容区（侧栏 + 面板）
        body = QHBoxLayout()
        body.setContentsMargins(0, 0, 0, 0)
        body.setSpacing(0)

        self.sidebar = self._build_sidebar()
        body.addWidget(self.sidebar)

        self.stack = QStackedWidget()
        self.stack.setObjectName("contentArea")

        # 创建各面板
        self.todo_panel = TodoPanel(self.db)
        self.reminder_panel = ReminderPanel(self.db)
        self.alarm_panel = AlarmPanel(self.db)
        self.launcher_panel = LauncherPanel(self.db, self.launcher_mgr)
        self.pomodoro_panel = PomodoroPanel(self.pomodoro_mgr, self.db)
        self.clipboard_panel = ClipboardPanel(self.db)
        self.settings_panel = SettingsPanel(self.config)

        self.stack.addWidget(self.todo_panel)      # 0
        self.stack.addWidget(self.reminder_panel)   # 1
        self.stack.addWidget(self.alarm_panel)      # 2
        self.stack.addWidget(self.launcher_panel)   # 3
        self.stack.addWidget(self.pomodoro_panel)   # 4
        self.stack.addWidget(self.clipboard_panel)  # 5
        self.stack.addWidget(self.settings_panel)   # 6

        body.addWidget(self.stack, 1)

        body_widget = QWidget()
        body_widget.setLayout(body)
        expand_layout.addWidget(body_widget, 1)

        # 状态栏
        self.status_bar = self._build_status_bar()
        expand_layout.addWidget(self.status_bar)

        self.root_layout.addWidget(self.expand_widget)

        # ── 信号连接 ──
        self.todo_panel.todo_count_changed.connect(self._update_badge)
        self.settings_panel.theme_changed.connect(self._apply_theme)
        self.settings_panel.opacity_changed.connect(self.setWindowOpacity)

    def _build_title_bar(self):
        bar = QWidget()
        bar.setObjectName("titleBar")
        bar.setFixedHeight(36)
        layout = QHBoxLayout(bar)
        layout.setContentsMargins(12, 0, 6, 0)
        layout.setSpacing(6)

        icon = QLabel("💼")
        icon.setFont(QFont("Segoe UI Emoji", 14))
        layout.addWidget(icon)

        title = QLabel("WorkMate")
        title.setObjectName("titleLabel")
        layout.addWidget(title)
        layout.addStretch()

        mini_btn = QPushButton("🔽")
        mini_btn.setObjectName("miniModeBtn")
        mini_btn.setToolTip("迷你模式")
        mini_btn.clicked.connect(self._show_mini)
        layout.addWidget(mini_btn)

        min_btn = QPushButton("—")
        min_btn.setObjectName("minimizeBtn")
        min_btn.setToolTip("最小化到托盘")
        min_btn.clicked.connect(self._minimize_to_tray)
        layout.addWidget(min_btn)

        self.max_btn = QPushButton("□")
        self.max_btn.setObjectName("minimizeBtn")
        self.max_btn.setToolTip("最大化")
        self.max_btn.clicked.connect(self._toggle_maximize)
        layout.addWidget(self.max_btn)

        close_btn = QPushButton("✕")
        close_btn.setObjectName("closeBtn")
        close_btn.setToolTip("关闭")
        close_btn.clicked.connect(self._minimize_to_tray)
        layout.addWidget(close_btn)

        return bar

    def _build_sidebar(self):
        sidebar = QWidget()
        sidebar.setObjectName("sidebar")
        sidebar.setFixedWidth(self.sidebar_w)
        layout = QVBoxLayout(sidebar)
        layout.setContentsMargins(4, 8, 4, 8)
        layout.setSpacing(4)

        self.nav_buttons = []
        for i, (icon_text, tip) in enumerate(NAV_ITEMS):
            btn = QPushButton(icon_text)
            btn.setProperty("class", "navBtn")
            btn.setToolTip(tip)
            btn.setCheckable(True)
            btn.clicked.connect(lambda checked, idx=i: self._on_nav(idx))
            layout.addWidget(btn)
            self.nav_buttons.append(btn)

        layout.addStretch()

        sticky_btn = QPushButton("📝")
        sticky_btn.setProperty("class", "navBtn")
        sticky_btn.setToolTip("新建便签")
        sticky_btn.clicked.connect(self.sticky_mgr.create_new)
        layout.addWidget(sticky_btn)

        if self.nav_buttons:
            self.nav_buttons[0].setChecked(True)

        return sidebar

    def _build_status_bar(self):
        bar = QWidget()
        bar.setObjectName("statusBar")
        bar.setFixedHeight(28)
        layout = QHBoxLayout(bar)
        layout.setContentsMargins(12, 0, 12, 0)

        self.sys_label = QLabel("CPU: --%  RAM: --%")
        self.sys_label.setObjectName("statusText")
        layout.addWidget(self.sys_label)

        layout.addStretch()

        self.clock_label = QLabel()
        self.clock_label.setObjectName("statusText")
        layout.addWidget(self.clock_label)

        return bar

    # ═════════════════════════════════════════
    #  模式切换
    # ═════════════════════════════════════════
    def toggle_mode(self):
        if self.is_mini:
            self._show_expanded()
        else:
            self._show_mini()

    def _show_mini(self):
        self.is_mini = True
        self._is_maximized = False
        self.expand_widget.setVisible(False)
        self.mini_widget.setVisible(True)
        self.setMinimumSize(0, 0)
        self.setMaximumSize(16777215, 16777215)
        geo = self.geometry()
        self.setFixedSize(self.mini_w, self.mini_h)
        self.move(geo.x(), geo.y())
        self._update_clock()
        cnt = self.db.get_active_todo_count()
        self._update_badge(cnt)
        self.show()
        self.activateWindow()

    def _show_expanded(self):
        self.is_mini = False
        self.mini_widget.setVisible(False)
        self.expand_widget.setVisible(True)

        # 以当前所在屏幕为参照
        screen = self._get_current_screen()
        if screen != self._current_screen:
            self._current_screen = screen
            self._calc_sizes(screen)

        self.setMinimumSize(self.expand_min_w, self.expand_min_h)
        self.setMaximumSize(self.expand_max_w, self.expand_max_h)

        geo = self.geometry()
        if self._is_maximized:
            self._apply_maximized()
        else:
            self.resize(self.expand_w, self.expand_h)
            avail = screen.availableGeometry()
            x = min(geo.x(), avail.right() - self.expand_w)
            y = min(geo.y(), avail.bottom() - self.expand_h)
            self.move(max(avail.x(), x), max(avail.y(), y))

        self._update_max_btn()
        self.show()
        self.activateWindow()
        self.raise_()

    def _show_panel(self, idx, focus=False):
        if self.is_mini:
            self._show_expanded()
        self._on_nav(idx)
        if focus:
            panel = self.stack.widget(idx)
            if hasattr(panel, 'focus_input'):
                panel.focus_input()

    def _minimize_to_tray(self):
        self.hide()

    # ═════════════════════════════════════════
    #  最大化 / 还原
    # ═════════════════════════════════════════
    def _toggle_maximize(self):
        if self.is_mini:
            self._show_expanded()
            return
        if self._is_maximized:
            self._restore_normal()
        else:
            self._apply_maximized()
        self._update_max_btn()

    def _apply_maximized(self):
        if not self._is_maximized:
            self._normal_geo = self.geometry()
        self._is_maximized = True
        # 最大化到窗口当前所在的屏幕
        screen = self._get_current_screen()
        avail = screen.availableGeometry()
        self.setGeometry(avail)

    def _restore_normal(self):
        self._is_maximized = False
        if self._normal_geo:
            self.setGeometry(self._normal_geo)
        else:
            self.resize(self.expand_w, self.expand_h)

    def _update_max_btn(self):
        if self._is_maximized:
            self.max_btn.setText("❐")
            self.max_btn.setToolTip("还原")
        else:
            self.max_btn.setText("□")
            self.max_btn.setToolTip("最大化")

    # ═════════════════════════════════════════
    #  导航
    # ═════════════════════════════════════════
    def _on_nav(self, idx):
        self._current_nav = idx
        self.stack.setCurrentIndex(idx)
        for i, btn in enumerate(self.nav_buttons):
            btn.setChecked(i == idx)
        panel = self.stack.widget(idx)
        if hasattr(panel, 'load'):
            panel.load()

    # ═════════════════════════════════════════
    #  事件回调
    # ═════════════════════════════════════════
    def _on_reminder(self, data):
        show_notification(self.tray, "⏰ 提醒", data.get('title', '提醒时间到'))
        play_alert_sound()

    def _on_alarm(self, data):
        label = data.get('label', '') or '闹钟'
        show_notification(self.tray, "⏰ 闹钟", f"{label} - {data.get('alarm_time', '')}")
        play_alert_sound()
        ret = QMessageBox.question(
            self, "闹钟响铃",
            f"⏰ {label}\n时间: {data.get('alarm_time', '')}\n\n是否贪睡？",
            QMessageBox.Yes | QMessageBox.No
        )
        if ret == QMessageBox.Yes:
            self.alarm_mgr.snooze(data['id'])

    def _update_clock(self):
        now = datetime.now()
        if self.is_mini:
            self.mini_time.setText(now.strftime("%H:%M"))
        self.clock_label.setText(now.strftime("%Y-%m-%d %H:%M:%S"))

    def _update_badge(self, count):
        self.mini_badge.setText(str(count))
        self.mini_badge.setVisible(count > 0)

    def _update_sys_info(self):
        try:
            cpu = psutil.cpu_percent(interval=0)
            ram = psutil.virtual_memory().percent
            self.sys_label.setText(f"CPU: {cpu:.0f}%  RAM: {ram:.0f}%")
        except Exception:
            pass

    def _apply_theme(self, theme_name):
        self.setStyleSheet(get_theme(theme_name))

    def _init_default_shortcuts(self):
        existing = self.db.get_shortcuts()
        if not existing:
            defaults = self.config.get('default_shortcuts', [])
            if defaults:
                for i, s in enumerate(defaults):
                    self.db.add_shortcut(
                        s['name'], s['exe_path'],
                        s.get('arguments', ''), s.get('icon', '🔧'), i
                    )

    # ═════════════════════════════════════════
    #  边框缩放 — 辅助方法
    # ═════════════════════════════════════════
    def _detect_edge(self, pos):
        if self.is_mini or self._is_maximized:
            return EDGE_NONE
        rect = self.rect()
        edge = EDGE_NONE
        if pos.x() <= RESIZE_MARGIN:
            edge |= EDGE_LEFT
        if pos.x() >= rect.width() - RESIZE_MARGIN:
            edge |= EDGE_RIGHT
        if pos.y() <= RESIZE_MARGIN:
            edge |= EDGE_TOP
        if pos.y() >= rect.height() - RESIZE_MARGIN:
            edge |= EDGE_BOTTOM
        return edge

    def _update_cursor_for_edge(self, edge):
        if edge == EDGE_NONE:
            self.setCursor(Qt.ArrowCursor)
        elif edge in (EDGE_LEFT, EDGE_RIGHT):
            self.setCursor(Qt.SizeHorCursor)
        elif edge in (EDGE_TOP, EDGE_BOTTOM):
            self.setCursor(Qt.SizeVerCursor)
        elif edge in (EDGE_TOP | EDGE_LEFT, EDGE_BOTTOM | EDGE_RIGHT):
            self.setCursor(Qt.SizeFDiagCursor)
        elif edge in (EDGE_TOP | EDGE_RIGHT, EDGE_BOTTOM | EDGE_LEFT):
            self.setCursor(Qt.SizeBDiagCursor)
        else:
            self.setCursor(Qt.ArrowCursor)

    def _apply_resize(self, global_pos):
        dx = global_pos.x() - self._resize_origin.x()
        dy = global_pos.y() - self._resize_origin.y()
        geo = QRect(self._resize_origin_geo)

        if self._resize_edge & EDGE_LEFT:
            new_w = geo.width() - dx
            if self.expand_min_w <= new_w <= self.expand_max_w:
                geo.setLeft(geo.left() + dx)
        if self._resize_edge & EDGE_RIGHT:
            new_w = geo.width() + dx
            if self.expand_min_w <= new_w <= self.expand_max_w:
                geo.setRight(geo.right() + dx)
        if self._resize_edge & EDGE_TOP:
            new_h = geo.height() - dy
            if self.expand_min_h <= new_h <= self.expand_max_h:
                geo.setTop(geo.top() + dy)
        if self._resize_edge & EDGE_BOTTOM:
            new_h = geo.height() + dy
            if self.expand_min_h <= new_h <= self.expand_max_h:
                geo.setBottom(geo.bottom() + dy)

        self.setGeometry(geo)

    # ═════════════════════════════════════════
    #  鼠标事件 — 拖拽移动 + 边框缩放 + 跨屏检测
    # ═════════════════════════════════════════
    def mousePressEvent(self, event):
        if event.button() != Qt.LeftButton:
            return

        if not self.is_mini:
            edge = self._detect_edge(event.pos())
            if edge != EDGE_NONE:
                self._resize_edge = edge
                self._resize_origin = event.globalPos()
                self._resize_origin_geo = self.geometry()
                event.accept()
                return

        if self.is_mini or (not self.is_mini and event.y() < 40):
            self._drag_pos = event.globalPos() - self.pos()
            event.accept()

    def mouseMoveEvent(self, event):
        # 正在缩放
        if self._resize_edge != EDGE_NONE:
            self._apply_resize(event.globalPos())
            event.accept()
            return

        # 正在拖拽
        if self._drag_pos and event.buttons() & Qt.LeftButton:
            self.move(event.globalPos() - self._drag_pos)
            event.accept()
            return

        # 空闲时更新光标
        if not self.is_mini and not self._is_maximized:
            edge = self._detect_edge(event.pos())
            self._update_cursor_for_edge(edge)

    def mouseReleaseEvent(self, event):
        self._drag_pos = None
        self._resize_edge = EDGE_NONE
        self._resize_origin = None
        self._resize_origin_geo = None

    def mouseDoubleClickEvent(self, event):
        if self.is_mini:
            self.toggle_mode()
        elif event.y() < 40:
            self._toggle_maximize()

    def moveEvent(self, event):
        """窗口位置变化时检测是否跨越到不同屏幕，自动适配"""
        super().moveEvent(event)
        new_screen = self._get_current_screen()
        if new_screen and new_screen != self._current_screen:
            self._adapt_to_screen(new_screen)

    def closeEvent(self, event):
        event.ignore()
        self._minimize_to_tray()

    # ═════════════════════════════════════════
    #  退出
    # ═════════════════════════════════════════
    def _quit(self):
        self.hotkey_mgr.stop()
        self.sticky_mgr.close_all()
        self.tray.hide()
        self.db.close()
        QApplication.quit()
