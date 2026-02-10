from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QLabel, QComboBox, QSlider, QCheckBox,
    QGroupBox, QFormLayout, QLineEdit, QFrame,
    QFileDialog, QMessageBox
)
from PyQt5.QtCore import Qt, pyqtSignal
from src.utils.autostart import is_autostart_enabled, enable_autostart, disable_autostart


class SettingsPanel(QWidget):
    """设置面板"""
    theme_changed = pyqtSignal(str)
    opacity_changed = pyqtSignal(float)

    def __init__(self, config):
        super().__init__()
        self.config = config
        self._init_ui()
        self._load_values()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(14)

        title = QLabel("⚙ 设置")
        title.setObjectName("panelTitle")
        layout.addWidget(title)

        # ── 外观设置 ──
        appearance_group = QGroupBox("外观")
        appearance_layout = QFormLayout(appearance_group)

        self.theme_combo = QComboBox()
        self.theme_combo.addItems(["深色主题", "浅色主题"])
        self.theme_combo.currentIndexChanged.connect(self._on_theme)
        appearance_layout.addRow("主题:", self.theme_combo)

        opacity_row = QHBoxLayout()
        self.opacity_slider = QSlider(Qt.Horizontal)
        self.opacity_slider.setRange(30, 100)
        self.opacity_slider.setValue(95)
        self.opacity_slider.valueChanged.connect(self._on_opacity)
        opacity_row.addWidget(self.opacity_slider)
        self.opacity_label = QLabel("95%")
        self.opacity_label.setFixedWidth(40)
        opacity_row.addWidget(self.opacity_label)
        appearance_layout.addRow("透明度:", opacity_row)

        layout.addWidget(appearance_group)

        # ── 快捷键设置 ──
        hotkey_group = QGroupBox("全局快捷键")
        hotkey_layout = QFormLayout(hotkey_group)

        self.hk_toggle = QLineEdit()
        self.hk_toggle.setPlaceholderText("如: <alt>+<space>")
        hotkey_layout.addRow("显示/隐藏:", self.hk_toggle)

        self.hk_todo = QLineEdit()
        self.hk_todo.setPlaceholderText("如: <alt>+t")
        hotkey_layout.addRow("新建待办:", self.hk_todo)

        self.hk_reminder = QLineEdit()
        self.hk_reminder.setPlaceholderText("如: <alt>+r")
        hotkey_layout.addRow("新建提醒:", self.hk_reminder)

        self.hk_launcher = QLineEdit()
        self.hk_launcher.setPlaceholderText("如: <alt>+l")
        hotkey_layout.addRow("启动面板:", self.hk_launcher)

        self.hk_minimize = QLineEdit()
        self.hk_minimize.setPlaceholderText("如: <alt>+<shift>+m")
        hotkey_layout.addRow("最小化:", self.hk_minimize)

        self.hk_maximize = QLineEdit()
        self.hk_maximize.setPlaceholderText("如: <alt>+<shift>+x")
        hotkey_layout.addRow("最大化:", self.hk_maximize)

        save_hk_btn = QPushButton("保存快捷键")
        save_hk_btn.setObjectName("primaryBtn")
        save_hk_btn.clicked.connect(self._save_hotkeys)
        hotkey_layout.addRow("", save_hk_btn)

        layout.addWidget(hotkey_group)

        # ── 系统设置 ──
        system_group = QGroupBox("系统")
        system_layout = QFormLayout(system_group)

        self.autostart_check = QCheckBox("开机自启动")
        self.autostart_check.toggled.connect(self._on_autostart)
        system_layout.addRow(self.autostart_check)

        layout.addWidget(system_group)

        # ── 数据管理 ──
        data_group = QGroupBox("数据管理")
        data_layout = QHBoxLayout(data_group)

        export_btn = QPushButton("导出数据")
        export_btn.clicked.connect(self._export)
        data_layout.addWidget(export_btn)

        import_btn = QPushButton("导入数据")
        import_btn.clicked.connect(self._import)
        data_layout.addWidget(import_btn)

        layout.addWidget(data_group)

        # ── 关于 ──
        about_group = QGroupBox("关于")
        about_layout = QVBoxLayout(about_group)
        about_layout.addWidget(QLabel("WorkMate 桌面工作助手  v1.0.0"))
        about_layout.addWidget(QLabel("基于 PyQt5 开发"))
        layout.addWidget(about_group)

        layout.addStretch()

    def _load_values(self):
        theme = self.config.get('theme', 'dark')
        self.theme_combo.setCurrentIndex(0 if theme == 'dark' else 1)

        opacity = self.config.get('opacity', 0.95)
        self.opacity_slider.setValue(int(opacity * 100))

        hk = self.config.get('hotkeys', {})
        self.hk_toggle.setText(hk.get('toggle_window', '<alt>+<space>'))
        self.hk_todo.setText(hk.get('new_todo', '<alt>+t'))
        self.hk_reminder.setText(hk.get('new_reminder', '<alt>+r'))
        self.hk_launcher.setText(hk.get('launcher_panel', '<alt>+l'))
        self.hk_minimize.setText(hk.get('minimize_window', '<alt>+<shift>+m'))
        self.hk_maximize.setText(hk.get('maximize_window', '<alt>+<shift>+x'))

        self.autostart_check.setChecked(is_autostart_enabled())

    def _on_theme(self, idx):
        theme = 'dark' if idx == 0 else 'light'
        self.config.set('theme', theme)
        self.theme_changed.emit(theme)

    def _on_opacity(self, val):
        self.opacity_label.setText(f"{val}%")
        opacity = val / 100.0
        self.config.set('opacity', opacity)
        self.opacity_changed.emit(opacity)

    def _save_hotkeys(self):
        self.config.set('hotkeys.toggle_window', self.hk_toggle.text().strip())
        self.config.set('hotkeys.new_todo', self.hk_todo.text().strip())
        self.config.set('hotkeys.new_reminder', self.hk_reminder.text().strip())
        self.config.set('hotkeys.launcher_panel', self.hk_launcher.text().strip())
        self.config.set('hotkeys.minimize_window', self.hk_minimize.text().strip())
        self.config.set('hotkeys.maximize_window', self.hk_maximize.text().strip())
        QMessageBox.information(self, "提示", "快捷键已保存，重启后生效。")

    def _on_autostart(self, checked):
        if checked:
            enable_autostart()
        else:
            disable_autostart()

    def _export(self):
        import json
        import shutil
        path, _ = QFileDialog.getSaveFileName(self, "导出数据", "workmate_backup.db", "数据库 (*.db)")
        if path:
            import os
            db_path = os.path.join(
                os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                "workmate.db"
            )
            try:
                shutil.copy2(db_path, path)
                QMessageBox.information(self, "成功", "数据导出成功！")
            except Exception as e:
                QMessageBox.warning(self, "失败", f"导出失败：{e}")

    def _import(self):
        path, _ = QFileDialog.getOpenFileName(self, "导入数据", "", "数据库 (*.db)")
        if path:
            QMessageBox.information(self, "提示", "请将导入文件替换 workmate.db 后重启应用。")
