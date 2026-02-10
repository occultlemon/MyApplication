from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QListWidget, QListWidgetItem, QLabel, QApplication, QLineEdit
)
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QFont


class ClipboardPanel(QWidget):
    """剪贴板历史面板"""

    def __init__(self, db):
        super().__init__()
        self.db = db
        self._last_text = ''
        self._init_ui()
        self.load()
        self._start_monitor()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(10)

        header = QHBoxLayout()
        title = QLabel("📋 剪贴板历史")
        title.setObjectName("panelTitle")
        header.addWidget(title)
        header.addStretch()

        clear_btn = QPushButton("清空")
        clear_btn.setObjectName("dangerBtn")
        clear_btn.setFixedWidth(60)
        clear_btn.clicked.connect(self._clear)
        header.addWidget(clear_btn)
        layout.addLayout(header)

        # 搜索
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("搜索剪贴板内容...")
        self.search_input.textChanged.connect(self._filter)
        layout.addWidget(self.search_input)

        self.list_widget = QListWidget()
        self.list_widget.setWordWrap(True)
        self.list_widget.itemDoubleClicked.connect(self._copy_item)
        layout.addWidget(self.list_widget, 1)

        hint = QLabel("双击条目可复制到剪贴板")
        hint.setObjectName("statLabel")
        hint.setAlignment(Qt.AlignCenter)
        layout.addWidget(hint)

    def _start_monitor(self):
        """监控系统剪贴板变化"""
        self._timer = QTimer(self)
        self._timer.setInterval(1000)
        self._timer.timeout.connect(self._check_clipboard)
        self._timer.start()
        clipboard = QApplication.clipboard()
        self._last_text = clipboard.text() or ''

    def _check_clipboard(self):
        clipboard = QApplication.clipboard()
        text = clipboard.text()
        if text and text != self._last_text and text.strip():
            self._last_text = text
            self.db.add_clipboard_entry(text.strip())
            self.load()

    def _copy_item(self, item):
        text = item.data(Qt.UserRole)
        if text:
            QApplication.clipboard().setText(text)
            self._last_text = text  # 避免重复记录

    def _clear(self):
        self.db.clear_clipboard_history()
        self.load()

    def _filter(self, keyword):
        for i in range(self.list_widget.count()):
            item = self.list_widget.item(i)
            text = item.data(Qt.UserRole) or ''
            item.setHidden(keyword.lower() not in text.lower())

    def load(self):
        self.list_widget.clear()
        entries = self.db.get_clipboard_history(100)
        for e in entries:
            content = e['content']
            preview = content[:120].replace('\n', ' ')
            if len(content) > 120:
                preview += '...'
            item = QListWidgetItem()
            item.setText(f"[{e['created_at'][11:16]}]  {preview}")
            item.setData(Qt.UserRole, content)
            item.setToolTip(content[:500])
            self.list_widget.addItem(item)
