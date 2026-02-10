import os
from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QGridLayout, QPushButton,
    QLabel, QLineEdit, QDialog, QFormLayout, QDialogButtonBox,
    QFileDialog, QScrollArea, QFrame
)
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont


class ShortcutEditDialog(QDialog):
    """快捷方式编辑对话框"""
    def __init__(self, parent=None, shortcut=None):
        super().__init__(parent)
        self.setWindowTitle("编辑快捷方式" if shortcut else "添加快捷方式")
        self.setMinimumWidth(400)
        layout = QFormLayout(self)

        self.name_input = QLineEdit()
        self.name_input.setPlaceholderText("应用名称")
        if shortcut:
            self.name_input.setText(shortcut['name'])
        layout.addRow("名称:", self.name_input)

        path_row = QHBoxLayout()
        self.path_input = QLineEdit()
        self.path_input.setPlaceholderText("可执行文件路径 (.exe)")
        if shortcut:
            self.path_input.setText(shortcut['exe_path'])
        path_row.addWidget(self.path_input)
        browse_btn = QPushButton("浏览")
        browse_btn.setFixedWidth(60)
        browse_btn.clicked.connect(self._browse)
        path_row.addWidget(browse_btn)
        layout.addRow("路径:", path_row)

        self.args_input = QLineEdit()
        self.args_input.setPlaceholderText("启动参数（可选）")
        if shortcut:
            self.args_input.setText(shortcut.get('arguments', '') or '')
        layout.addRow("参数:", self.args_input)

        self.icon_input = QLineEdit()
        self.icon_input.setPlaceholderText("显示图标（emoji 或文字）")
        if shortcut:
            self.icon_input.setText(shortcut.get('icon_path', '') or '🔧')
        else:
            self.icon_input.setText('🔧')
        layout.addRow("图标:", self.icon_input)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addRow(buttons)

    def _browse(self):
        path, _ = QFileDialog.getOpenFileName(self, "选择可执行文件", "", "可执行文件 (*.exe);;所有文件 (*)")
        if path:
            self.path_input.setText(path)
            if not self.name_input.text():
                self.name_input.setText(os.path.splitext(os.path.basename(path))[0])

    def get_data(self):
        return {
            'name': self.name_input.text().strip(),
            'exe_path': self.path_input.text().strip(),
            'arguments': self.args_input.text().strip(),
            'icon_path': self.icon_input.text().strip() or '🔧'
        }


class LauncherPanel(QWidget):
    """快捷启动面板"""

    def __init__(self, db, launcher_mgr):
        super().__init__()
        self.db = db
        self.launcher = launcher_mgr
        self._init_ui()
        self.load()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(10)

        header = QHBoxLayout()
        title = QLabel("🚀 快捷启动")
        title.setObjectName("panelTitle")
        header.addWidget(title)
        header.addStretch()

        add_btn = QPushButton("+ 添加应用")
        add_btn.setObjectName("primaryBtn")
        add_btn.clicked.connect(self._add)
        header.addWidget(add_btn)
        layout.addLayout(header)

        # 内置快捷
        builtin_label = QLabel("内置工具")
        builtin_label.setObjectName("statLabel")
        layout.addWidget(builtin_label)

        builtin_row = QHBoxLayout()
        builtin_row.setSpacing(10)
        for name, icon, cb in [
            ("Edge", "🌐", lambda: self.launcher.launch_edge()),
            ("记事本", "📝", lambda: self.launcher.launch_notepad()),
            ("计算器", "🔢", lambda: self.launcher.launch_by_path("calc.exe")),
            ("资源管理器", "📁", lambda: self.launcher.launch_by_path("explorer.exe")),
        ]:
            btn = self._make_tile(icon, name)
            btn.clicked.connect(cb)
            builtin_row.addWidget(btn)
        builtin_row.addStretch()
        layout.addLayout(builtin_row)

        sep = QFrame()
        sep.setObjectName("separator")
        sep.setFrameShape(QFrame.HLine)
        sep.setFixedHeight(1)
        layout.addWidget(sep)

        custom_label = QLabel("自定义应用")
        custom_label.setObjectName("statLabel")
        layout.addWidget(custom_label)

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setFrameShape(QFrame.NoFrame)
        self.grid_container = QWidget()
        self.grid_layout = QGridLayout(self.grid_container)
        self.grid_layout.setSpacing(10)
        self.grid_layout.setAlignment(Qt.AlignTop | Qt.AlignLeft)
        scroll.setWidget(self.grid_container)
        layout.addWidget(scroll, 1)

    def _make_tile(self, icon_text, name):
        btn = QPushButton(f"{icon_text}\n{name}")
        btn.setFixedSize(80, 72)
        btn.setFont(QFont("Segoe UI Emoji", 10))
        btn.setStyleSheet("""
            QPushButton {
                border-radius: 10px;
                padding: 6px;
            }
        """)
        btn.setToolTip(name)
        return btn

    def _add(self):
        dlg = ShortcutEditDialog(self)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            if data['name'] and data['exe_path']:
                self.db.add_shortcut(data['name'], data['exe_path'], data['arguments'], data['icon_path'])
                self.load()

    def load(self):
        # 清空网格
        while self.grid_layout.count():
            w = self.grid_layout.takeAt(0).widget()
            if w:
                w.deleteLater()

        shortcuts = self.db.get_shortcuts()
        cols = 4
        for i, s in enumerate(shortcuts):
            sid = s['id']
            icon = s['icon_path'] or '🔧'
            btn = self._make_tile(icon, s['name'])
            btn.clicked.connect(lambda checked, _id=sid: self.launcher.launch(_id))
            btn.setContextMenuPolicy(Qt.CustomContextMenu)
            btn.customContextMenuRequested.connect(lambda pos, _s=dict(s): self._ctx_menu(_s))
            self.grid_layout.addWidget(btn, i // cols, i % cols)

    def _ctx_menu(self, shortcut):
        from PyQt5.QtWidgets import QMenu
        menu = QMenu(self)
        edit_act = menu.addAction("编辑")
        del_act = menu.addAction("删除")
        act = menu.exec_(self.cursor().pos())
        if act == edit_act:
            dlg = ShortcutEditDialog(self, shortcut)
            if dlg.exec_() == QDialog.Accepted:
                data = dlg.get_data()
                if data['name'] and data['exe_path']:
                    self.db.update_shortcut(shortcut['id'], **data)
                    self.load()
        elif act == del_act:
            self.db.delete_shortcut(shortcut['id'])
            self.load()
