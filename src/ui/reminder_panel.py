from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QLineEdit, QListWidget, QListWidgetItem, QLabel,
    QComboBox, QDateTimeEdit, QDialog, QFormLayout, QDialogButtonBox
)
from PyQt5.QtCore import Qt, QDateTime
from PyQt5.QtGui import QFont


class ReminderEditDialog(QDialog):
    """提醒事项编辑对话框"""
    def __init__(self, parent=None, reminder=None):
        super().__init__(parent)
        self.setWindowTitle("编辑提醒" if reminder else "新建提醒")
        self.setMinimumWidth(340)
        layout = QFormLayout(self)

        self.title_input = QLineEdit()
        self.title_input.setPlaceholderText("提醒标题")
        if reminder:
            self.title_input.setText(reminder['title'])
        layout.addRow("标题:", self.title_input)

        self.content_input = QLineEdit()
        self.content_input.setPlaceholderText("提醒内容（可选）")
        if reminder:
            self.content_input.setText(reminder.get('content', '') or '')
        layout.addRow("内容:", self.content_input)

        self.datetime_edit = QDateTimeEdit()
        self.datetime_edit.setCalendarPopup(True)
        self.datetime_edit.setDisplayFormat("yyyy-MM-dd HH:mm")
        if reminder:
            self.datetime_edit.setDateTime(
                QDateTime.fromString(reminder['remind_time'][:16], "yyyy-MM-dd HH:mm"))
        else:
            self.datetime_edit.setDateTime(QDateTime.currentDateTime().addSecs(3600))
        layout.addRow("时间:", self.datetime_edit)

        self.repeat_combo = QComboBox()
        self.repeat_combo.addItems(["单次", "每天", "每周", "每月"])
        repeat_map = {'once': 0, 'daily': 1, 'weekly': 2, 'monthly': 3}
        if reminder:
            self.repeat_combo.setCurrentIndex(repeat_map.get(reminder['repeat_type'], 0))
        layout.addRow("重复:", self.repeat_combo)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addRow(buttons)

    def get_data(self):
        repeat_types = ['once', 'daily', 'weekly', 'monthly']
        return {
            'title': self.title_input.text().strip(),
            'content': self.content_input.text().strip(),
            'remind_time': self.datetime_edit.dateTime().toString("yyyy-MM-dd HH:mm:ss"),
            'repeat_type': repeat_types[self.repeat_combo.currentIndex()]
        }


class ReminderItemWidget(QWidget):
    """单条提醒项"""
    def __init__(self, reminder, db, reload_cb, parent=None):
        super().__init__(parent)
        self.rid = reminder['id']
        self.data = reminder
        self.db = db
        self.reload_cb = reload_cb

        self.setMinimumHeight(44)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(10, 6, 10, 6)
        layout.setSpacing(8)

        icon = QLabel("🔔")
        icon.setFont(QFont("Segoe UI Emoji", 14))
        layout.addWidget(icon)

        info = QVBoxLayout()
        info.setSpacing(2)
        title = QLabel(reminder['title'])
        title.setWordWrap(True)
        if not reminder['is_active']:
            title.setStyleSheet("color: #585b70; text-decoration: line-through;")
        info.addWidget(title)

        repeat_labels = {'once': '单次', 'daily': '每天', 'weekly': '每周', 'monthly': '每月'}
        meta = QLabel(f"{reminder['remind_time'][:16]}  ·  {repeat_labels.get(reminder['repeat_type'], '单次')}")
        meta.setObjectName("statLabel")
        info.addWidget(meta)
        layout.addLayout(info, 1)

        # 启用/禁用
        toggle_btn = QPushButton("✓" if reminder['is_active'] else "○")
        toggle_btn.setFixedSize(28, 28)
        toggle_btn.setToolTip("启用/禁用")
        toggle_btn.clicked.connect(self._toggle)
        layout.addWidget(toggle_btn)

        edit_btn = QPushButton("✎")
        edit_btn.setFixedSize(28, 28)
        edit_btn.clicked.connect(self._edit)
        layout.addWidget(edit_btn)

        del_btn = QPushButton("✕")
        del_btn.setObjectName("deleteBtn")
        del_btn.setFixedSize(28, 28)
        del_btn.clicked.connect(self._delete)
        layout.addWidget(del_btn)

    def _toggle(self):
        new_val = 0 if self.data['is_active'] else 1
        self.db.update_reminder(self.rid, is_active=new_val)
        self.reload_cb()

    def _edit(self):
        dlg = ReminderEditDialog(self, self.data)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            if data['title']:
                self.db.update_reminder(self.rid, **data)
                self.reload_cb()

    def _delete(self):
        self.db.delete_reminder(self.rid)
        self.reload_cb()


class ReminderPanel(QWidget):
    """提醒事项面板"""

    def __init__(self, db):
        super().__init__()
        self.db = db
        self._init_ui()
        self.load()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(10)

        header = QHBoxLayout()
        title = QLabel("🔔 提醒事项")
        title.setObjectName("panelTitle")
        header.addWidget(title)
        header.addStretch()

        add_btn = QPushButton("+ 新建提醒")
        add_btn.setObjectName("primaryBtn")
        add_btn.clicked.connect(self._add)
        header.addWidget(add_btn)
        layout.addLayout(header)

        self.list_widget = QListWidget()
        layout.addWidget(self.list_widget, 1)

        self.stats = QLabel()
        self.stats.setObjectName("statLabel")
        layout.addWidget(self.stats)

    def _add(self):
        dlg = ReminderEditDialog(self)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            if data['title']:
                self.db.add_reminder(**data)
                self.load()

    def focus_input(self):
        self._add()

    def load(self):
        self.list_widget.clear()
        reminders = self.db.get_reminders()
        for r in reminders:
            item = QListWidgetItem()
            w = ReminderItemWidget(dict(r), self.db, self.load)
            hint = w.sizeHint()
            hint.setHeight(max(hint.height(), 52))
            item.setSizeHint(hint)
            self.list_widget.addItem(item)
            self.list_widget.setItemWidget(item, w)
        active = len([r for r in reminders if r['is_active']])
        self.stats.setText(f"活跃: {active} 项  |  总计: {len(reminders)} 项")
