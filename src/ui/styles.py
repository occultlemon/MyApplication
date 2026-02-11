# ──────────────────────────────────────────
# WorkMate 全局 QSS 样式表（深色 / 浅色主题）
# ──────────────────────────────────────────

DARK_THEME = """
/* ── 全局 ── */
* {
    font-family: "Microsoft YaHei", "Segoe UI", sans-serif;
    font-size: 13px;
    color: #cdd6f4;
}
QWidget#mainWindow {
    background: #1e1e2e;
    border-radius: 12px;
}
QWidget#miniWidget {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #1e1e2e, stop:1 #313244);
    border-radius: 28px;
}

/* ── 侧边栏 ── */
QWidget#sidebar {
    background: #181825;
    border-top-left-radius: 12px;
    border-bottom-left-radius: 12px;
}
QPushButton[class="navBtn"] {
    background: transparent;
    border: none;
    padding: 10px;
    font-size: 18px;
    border-radius: 8px;
    min-width: 42px;
    min-height: 42px;
}
QPushButton[class="navBtn"]:hover {
    background: #313244;
}
QPushButton[class="navBtn"]:checked {
    background: #45475a;
    color: #89b4fa;
}

/* ── 内容区 ── */
QWidget#contentArea {
    background: #1e1e2e;
    border-top-right-radius: 12px;
    border-bottom-right-radius: 12px;
}

/* ── 标题栏 ── */
QWidget#titleBar {
    background: transparent;
}
QLabel#titleLabel {
    font-size: 13px;
    font-weight: bold;
    color: #cdd6f4;
}
QPushButton#minimizeBtn, QPushButton#closeBtn, QPushButton#miniModeBtn {
    background: transparent;
    border: none;
    font-size: 14px;
    padding: 4px 8px;
    border-radius: 6px;
    min-width: 28px;
}
QPushButton#minimizeBtn:hover { background: #313244; }
QPushButton#closeBtn:hover { background: #f38ba8; color: #1e1e2e; }
QPushButton#miniModeBtn:hover { background: #313244; }

/* ── 输入框 ── */
QLineEdit, QTextEdit {
    background: #313244;
    border: 1px solid #45475a;
    border-radius: 8px;
    padding: 6px 10px;
    color: #cdd6f4;
    selection-background-color: #89b4fa;
}
QLineEdit:focus, QTextEdit:focus {
    border: 1px solid #89b4fa;
}

/* ── 下拉框 ── */
QComboBox {
    background: #313244;
    border: 1px solid #45475a;
    border-radius: 8px;
    padding: 5px 10px;
    min-width: 60px;
}
QComboBox::drop-down {
    border: none;
    width: 24px;
}
QComboBox::down-arrow {
    image: none;
    border-left: 4px solid transparent;
    border-right: 4px solid transparent;
    border-top: 6px solid #cdd6f4;
    margin-right: 8px;
}
QComboBox QAbstractItemView {
    background: #313244;
    border: 1px solid #45475a;
    selection-background-color: #45475a;
    outline: none;
}

/* ── 日期时间选择 ── */
QDateTimeEdit, QTimeEdit {
    background: #313244;
    border: 1px solid #45475a;
    border-radius: 8px;
    padding: 5px 10px;
}
QDateTimeEdit::drop-down, QTimeEdit::drop-down {
    border: none;
    width: 20px;
}

/* ── 按钮 ── */
QPushButton {
    background: #313244;
    border: 1px solid #45475a;
    border-radius: 8px;
    padding: 6px 14px;
    color: #cdd6f4;
}
QPushButton:hover {
    background: #45475a;
    border-color: #585b70;
}
QPushButton:pressed {
    background: #585b70;
}
QPushButton#primaryBtn {
    background: #89b4fa;
    color: #1e1e2e;
    border: none;
    font-weight: bold;
}
QPushButton#primaryBtn:hover {
    background: #74c7ec;
}
QPushButton#dangerBtn {
    background: #f38ba8;
    color: #1e1e2e;
    border: none;
}
QPushButton#dangerBtn:hover {
    background: #eba0ac;
}
QPushButton#successBtn {
    background: #a6e3a1;
    color: #1e1e2e;
    border: none;
}
QPushButton#successBtn:hover {
    background: #94e2d5;
}
QPushButton#deleteBtn {
    background: transparent;
    border: none;
    color: #f38ba8;
    font-size: 13px;
    padding: 2px;
    min-width: 24px;
    max-width: 24px;
}
QPushButton#deleteBtn:hover {
    background: rgba(243,139,168,0.2);
    border-radius: 12px;
}

/* ── 列表 ── */
QListWidget {
    background: transparent;
    border: none;
    outline: none;
}
QListWidget::item {
    background: #313244;
    border-radius: 8px;
    margin: 2px 0;
    padding: 4px;
}
QListWidget::item:hover {
    background: #45475a;
}
QListWidget::item:selected {
    background: #45475a;
    color: #cdd6f4;
}

/* ── 滚动条 ── */
QScrollBar:vertical {
    background: transparent;
    width: 8px;
    margin: 0;
}
QScrollBar::handle:vertical {
    background: #45475a;
    border-radius: 4px;
    min-height: 30px;
}
QScrollBar::handle:vertical:hover {
    background: #585b70;
}
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0;
}
QScrollBar:horizontal {
    height: 8px;
}
QScrollBar::handle:horizontal {
    background: #45475a;
    border-radius: 4px;
}

/* ── 复选框 ── */
QCheckBox {
    spacing: 6px;
}
QCheckBox::indicator {
    width: 18px;
    height: 18px;
    border-radius: 4px;
    border: 2px solid #585b70;
    background: transparent;
}
QCheckBox::indicator:checked {
    background: #89b4fa;
    border-color: #89b4fa;
}

/* ── 标签页 ── */
QLabel#panelTitle {
    font-size: 16px;
    font-weight: bold;
    color: #cdd6f4;
    padding: 4px 0;
}
QLabel#statLabel {
    color: #a6adc8;
    font-size: 12px;
}
QLabel#accentLabel {
    color: #89b4fa;
    font-weight: bold;
}

/* ── 状态栏 ── */
QWidget#statusBar {
    background: #181825;
    border-bottom-left-radius: 12px;
    border-bottom-right-radius: 12px;
}
QLabel#statusText {
    color: #a6adc8;
    font-size: 11px;
}

/* ── 分隔线 ── */
QFrame#separator {
    background: #313244;
    max-height: 1px;
}

/* ── 滑块 ── */
QSlider::groove:horizontal {
    height: 4px;
    background: #45475a;
    border-radius: 2px;
}
QSlider::handle:horizontal {
    width: 16px;
    height: 16px;
    margin: -6px 0;
    background: #89b4fa;
    border-radius: 8px;
}
QSlider::sub-page:horizontal {
    background: #89b4fa;
    border-radius: 2px;
}

/* ── 工具提示 ── */
QToolTip {
    background: #313244;
    color: #cdd6f4;
    border: 1px solid #45475a;
    border-radius: 6px;
    padding: 4px 8px;
}

/* ── 菜单 ── */
QMenu {
    background: #313244;
    border: 1px solid #45475a;
    border-radius: 8px;
    padding: 4px;
}
QMenu::item {
    padding: 6px 24px;
    border-radius: 4px;
}
QMenu::item:selected {
    background: #45475a;
}

/* ── 分组框 ── */
QGroupBox {
    background: #252535;
    border: 1px solid #45475a;
    border-radius: 8px;
    margin-top: 12px;
    padding: 16px 10px 10px 10px;
    font-weight: bold;
    color: #cdd6f4;
}
QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    left: 12px;
    padding: 0 6px;
    color: #89b4fa;
}

/* ── 滚动区域 ── */
QScrollArea {
    background: transparent;
    border: none;
}
QScrollArea > QWidget > QWidget {
    background: transparent;
}
"""

LIGHT_THEME = """
* {
    font-family: "Microsoft YaHei", "Segoe UI", sans-serif;
    font-size: 13px;
    color: #4c4f69;
}
QWidget#mainWindow {
    background: #eff1f5;
    border-radius: 12px;
}
QWidget#miniWidget {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:1, stop:0 #eff1f5, stop:1 #dce0e8);
    border-radius: 28px;
}
QWidget#sidebar {
    background: #e6e9ef;
    border-top-left-radius: 12px;
    border-bottom-left-radius: 12px;
}
QPushButton[class="navBtn"] {
    background: transparent;
    border: none;
    padding: 10px;
    font-size: 18px;
    border-radius: 8px;
    min-width: 42px;
    min-height: 42px;
}
QPushButton[class="navBtn"]:hover { background: #ccd0da; }
QPushButton[class="navBtn"]:checked {
    background: #bcc0cc;
    color: #1e66f5;
}
QWidget#contentArea {
    background: #eff1f5;
    border-top-right-radius: 12px;
    border-bottom-right-radius: 12px;
}
QWidget#titleBar { background: transparent; }
QLabel#titleLabel { font-size: 13px; font-weight: bold; color: #4c4f69; }
QPushButton#minimizeBtn, QPushButton#closeBtn, QPushButton#miniModeBtn {
    background: transparent; border: none; font-size: 14px;
    padding: 4px 8px; border-radius: 6px; min-width: 28px;
}
QPushButton#minimizeBtn:hover { background: #ccd0da; }
QPushButton#closeBtn:hover { background: #d20f39; color: #fff; }
QPushButton#miniModeBtn:hover { background: #ccd0da; }
QLineEdit, QTextEdit {
    background: #fff; border: 1px solid #ccd0da;
    border-radius: 8px; padding: 6px 10px; color: #4c4f69;
    selection-background-color: #1e66f5;
}
QLineEdit:focus, QTextEdit:focus { border: 1px solid #1e66f5; }
QComboBox {
    background: #fff; border: 1px solid #ccd0da;
    border-radius: 8px; padding: 5px 10px; min-width: 60px;
}
QComboBox::drop-down { border: none; width: 24px; }
QComboBox::down-arrow {
    image: none; border-left: 4px solid transparent;
    border-right: 4px solid transparent; border-top: 6px solid #4c4f69;
    margin-right: 8px;
}
QComboBox QAbstractItemView {
    background: #fff; border: 1px solid #ccd0da;
    selection-background-color: #e6e9ef; outline: none;
}
QDateTimeEdit, QTimeEdit {
    background: #fff; border: 1px solid #ccd0da;
    border-radius: 8px; padding: 5px 10px;
}
QDateTimeEdit::drop-down, QTimeEdit::drop-down { border: none; width: 20px; }
QPushButton {
    background: #fff; border: 1px solid #ccd0da;
    border-radius: 8px; padding: 6px 14px; color: #4c4f69;
}
QPushButton:hover { background: #e6e9ef; }
QPushButton:pressed { background: #ccd0da; }
QPushButton#primaryBtn {
    background: #1e66f5; color: #fff; border: none; font-weight: bold;
}
QPushButton#primaryBtn:hover { background: #2a7bff; }
QPushButton#dangerBtn { background: #d20f39; color: #fff; border: none; }
QPushButton#dangerBtn:hover { background: #e64560; }
QPushButton#successBtn { background: #40a02b; color: #fff; border: none; }
QPushButton#successBtn:hover { background: #50b83b; }
QPushButton#deleteBtn {
    background: transparent; border: none; color: #d20f39;
    font-size: 13px; padding: 2px; min-width: 24px; max-width: 24px;
}
QPushButton#deleteBtn:hover {
    background: rgba(210,15,57,0.15); border-radius: 12px;
}
QListWidget { background: transparent; border: none; outline: none; }
QListWidget::item {
    background: #fff; border-radius: 8px; margin: 2px 0; padding: 4px;
}
QListWidget::item:hover { background: #e6e9ef; }
QListWidget::item:selected { background: #dce0e8; color: #4c4f69; }
QScrollBar:vertical { background: transparent; width: 8px; }
QScrollBar::handle:vertical { background: #ccd0da; border-radius: 4px; min-height: 30px; }
QScrollBar::handle:vertical:hover { background: #bcc0cc; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
QCheckBox { spacing: 6px; }
QCheckBox::indicator {
    width: 18px; height: 18px; border-radius: 4px;
    border: 2px solid #bcc0cc; background: transparent;
}
QCheckBox::indicator:checked { background: #1e66f5; border-color: #1e66f5; }
QLabel#panelTitle { font-size: 16px; font-weight: bold; color: #4c4f69; padding: 4px 0; }
QLabel#statLabel { color: #8c8fa1; font-size: 12px; }
QLabel#accentLabel { color: #1e66f5; font-weight: bold; }
QWidget#statusBar {
    background: #e6e9ef; border-bottom-left-radius: 12px;
    border-bottom-right-radius: 12px;
}
QLabel#statusText { color: #8c8fa1; font-size: 11px; }
QFrame#separator { background: #ccd0da; max-height: 1px; }
QSlider::groove:horizontal { height: 4px; background: #ccd0da; border-radius: 2px; }
QSlider::handle:horizontal {
    width: 16px; height: 16px; margin: -6px 0;
    background: #1e66f5; border-radius: 8px;
}
QSlider::sub-page:horizontal { background: #1e66f5; border-radius: 2px; }
QToolTip {
    background: #fff; color: #4c4f69; border: 1px solid #ccd0da;
    border-radius: 6px; padding: 4px 8px;
}
QMenu {
    background: #fff; border: 1px solid #ccd0da; border-radius: 8px; padding: 4px;
}
QMenu::item { padding: 6px 24px; border-radius: 4px; }
QMenu::item:selected { background: #e6e9ef; }

/* ── 分组框 ── */
QGroupBox {
    background: #fff;
    border: 1px solid #ccd0da;
    border-radius: 8px;
    margin-top: 12px;
    padding: 16px 10px 10px 10px;
    font-weight: bold;
    color: #4c4f69;
}
QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    left: 12px;
    padding: 0 6px;
    color: #1e66f5;
}

/* ── 滚动区域 ── */
QScrollArea {
    background: transparent;
    border: none;
}
QScrollArea > QWidget > QWidget {
    background: transparent;
}
"""


def get_theme(name='dark'):
    return DARK_THEME if name == 'dark' else LIGHT_THEME
