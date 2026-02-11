import math
from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QLabel, QSizePolicy
)
from PyQt5.QtCore import Qt, QRectF
from PyQt5.QtGui import QPainter, QColor, QPen, QFont, QConicalGradient


class PomodoroRing(QWidget):
    """番茄钟圆环进度指示器（尺寸跟随父容器自适应）"""

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setMinimumSize(120, 120)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.progress = 1.0  # 0..1
        self.time_text = "25:00"
        self.phase_text = "专注"
        self.ring_color = QColor("#89b4fa")

    def set_progress(self, value):
        self.progress = max(0.0, min(1.0, value))
        self.update()

    def set_time_text(self, text):
        self.time_text = text
        self.update()

    def set_phase(self, phase):
        phase_map = {
            'work': ('专注', QColor("#89b4fa")),
            'break': ('休息', QColor("#a6e3a1")),
            'long_break': ('长休息', QColor("#f9e2af")),
        }
        self.phase_text, self.ring_color = phase_map.get(phase, ('专注', QColor("#89b4fa")))
        self.update()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        side = min(self.width(), self.height())
        x = (self.width() - side) / 2
        y = (self.height() - side) / 2
        margin = 12
        rect = QRectF(x + margin, y + margin, side - 2 * margin, side - 2 * margin)

        # 按圆环大小动态计算线宽和字号
        ring_pen_w = max(4, int(side * 0.05))
        time_font_size = max(14, int(side * 0.18))
        phase_font_size = max(9, int(side * 0.07))
        phase_offset = max(20, int(side * 0.22))

        # 背景环
        bg_pen = QPen(QColor("#313244"), ring_pen_w)
        bg_pen.setCapStyle(Qt.RoundCap)
        painter.setPen(bg_pen)
        painter.drawArc(rect, 0, 360 * 16)

        # 进度环
        fg_pen = QPen(self.ring_color, ring_pen_w)
        fg_pen.setCapStyle(Qt.RoundCap)
        painter.setPen(fg_pen)
        span = int(self.progress * 360 * 16)
        painter.drawArc(rect, 90 * 16, -span)

        # 中心文字
        painter.setPen(QColor("#cdd6f4"))
        painter.setFont(QFont("Consolas", time_font_size, QFont.Bold))
        painter.drawText(rect, Qt.AlignCenter, self.time_text)

        # 阶段文字
        sub_rect = QRectF(rect.x(), rect.y() + phase_offset, rect.width(), rect.height())
        painter.setFont(QFont("Microsoft YaHei", phase_font_size))
        painter.setPen(QColor("#a6adc8"))
        painter.drawText(sub_rect, Qt.AlignCenter, self.phase_text)

        painter.end()


class PomodoroPanel(QWidget):
    """番茄钟面板"""

    def __init__(self, pomodoro_mgr, db):
        super().__init__()
        self.mgr = pomodoro_mgr
        self.db = db
        self._init_ui()
        self._connect()
        self._update_stats()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(12)

        title = QLabel("🍅 番茄钟")
        title.setObjectName("panelTitle")
        layout.addWidget(title)

        # 圆环
        self.ring = PomodoroRing()
        layout.addWidget(self.ring, 1)

        # 控制按钮
        btn_row = QHBoxLayout()
        btn_row.setSpacing(12)

        self.start_btn = QPushButton("▶ 开始")
        self.start_btn.setObjectName("primaryBtn")
        self.start_btn.setFixedHeight(38)
        self.start_btn.clicked.connect(self._toggle)
        btn_row.addWidget(self.start_btn)

        self.skip_btn = QPushButton("⏭ 跳过")
        self.skip_btn.setFixedHeight(38)
        self.skip_btn.clicked.connect(self.mgr.skip)
        btn_row.addWidget(self.skip_btn)

        self.reset_btn = QPushButton("⟲ 重置")
        self.reset_btn.setFixedHeight(38)
        self.reset_btn.clicked.connect(self._reset)
        btn_row.addWidget(self.reset_btn)

        layout.addLayout(btn_row)

        # 统计信息
        self.stats_label = QLabel()
        self.stats_label.setObjectName("statLabel")
        self.stats_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.stats_label)

        self.session_label = QLabel(f"已完成: 0 个番茄  |  今日: 0 分钟")
        self.session_label.setObjectName("accentLabel")
        self.session_label.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.session_label)

    def _connect(self):
        self.mgr.tick.connect(self._on_tick)
        self.mgr.phase_changed.connect(self._on_phase)
        self.mgr.session_completed.connect(self._update_stats)

    def _toggle(self):
        if self.mgr.is_running:
            self.mgr.pause()
            self.start_btn.setText("▶ 继续")
        else:
            self.mgr.start()
            self.start_btn.setText("⏸ 暂停")

    def _reset(self):
        self.mgr.reset()
        self.start_btn.setText("▶ 开始")
        self.ring.set_phase('work')

    def _on_tick(self, remaining, total):
        m, s = divmod(remaining, 60)
        self.ring.set_time_text(f"{m:02d}:{s:02d}")
        progress = remaining / total if total > 0 else 0
        self.ring.set_progress(progress)

    def _on_phase(self, phase):
        self.ring.set_phase(phase)
        self.start_btn.setText("▶ 开始")
        self._update_stats()

    def _update_stats(self):
        stats = self.db.get_today_pomodoro_stats()
        sessions = self.mgr.completed_sessions
        self.session_label.setText(
            f"已完成: {sessions} 个番茄  |  今日: {stats['count']} 次 / {stats['total_minutes']} 分钟"
        )
