from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QListWidget, QListWidgetItem, QLabel,
    QTimeEdit, QLineEdit, QDialog, QFormLayout, QDialogButtonBox
)
from PyQt5.QtCore import Qt, QTime
from PyQt5.QtGui import QFont


class AlarmEditDialog(QDialog):
    """闹钟编辑对话框"""
    def __init__(self, parent=None, alarm=None):
        super().__init__(parent)
        self.setWindowTitle("编辑闹钟" if alarm else "新建闹钟")
        self.setMinimumWidth(300)
        layout = QFormLayout(self)

        self.time_edit = QTimeEdit()
        self.time_edit.setDisplayFormat("HH:mm")
        if alarm:
            h, m = alarm['alarm_time'].split(':')
            self.time_edit.setTime(QTime(int(h), int(m)))
        else:
            self.time_edit.setTime(QTime.currentTime().addSecs(3600))
        layout.addRow("时间:", self.time_edit)

        self.label_input = QLineEdit()
        self.label_input.setPlaceholderText("闹钟备注（可选）")
        if alarm:
            self.label_input.setText(alarm.get('label', '') or '')
        layout.addRow("备注:", self.label_input)

        self.snooze_input = QLineEdit("5")
        self.snooze_input.setPlaceholderText("贪睡分钟数")
        if alarm:
            self.snooze_input.setText(str(alarm.get('snooze_minutes', 5)))
        layout.addRow("贪睡(分钟):", self.snooze_input)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addRow(buttons)

    def get_data(self):
        try:
            snooze = int(self.snooze_input.text())
        except ValueError:
            snooze = 5
        return {
            'alarm_time': self.time_edit.time().toString("HH:mm"),
            'label': self.label_input.text().strip(),
            'snooze_minutes': snooze
        }


class AlarmItemWidget(QWidget):
    """单条闹钟项"""
    def __init__(self, alarm, db, reload_cb, parent=None):
        super().__init__(parent)
        self.aid = alarm['id']
        self.data = alarm
        self.db = db
        self.reload_cb = reload_cb

        self.setMinimumHeight(52)

        layout = QHBoxLayout(self)
        layout.setContentsMargins(10, 8, 10, 8)
        layout.setSpacing(12)

        time_label = QLabel(alarm['alarm_time'])
        time_label.setFont(QFont("Consolas", 18, QFont.Bold))
        if not alarm['is_active']:
            time_label.setStyleSheet("color: #585b70;")
        layout.addWidget(time_label)

        info = QVBoxLayout()
        info.setSpacing(2)
        label = QLabel(alarm.get('label', '') or '闹钟')
        label.setWordWrap(True)
        if not alarm['is_active']:
            label.setStyleSheet("color: #585b70;")
        info.addWidget(label)

        snooze = QLabel(f"贪睡 {alarm.get('snooze_minutes', 5)} 分钟")
        snooze.setObjectName("statLabel")
        info.addWidget(snooze)
        layout.addLayout(info, 1)

        toggle_btn = QPushButton("开" if alarm['is_active'] else "关")
        toggle_btn.setFixedSize(40, 28)
        if alarm['is_active']:
            toggle_btn.setObjectName("successBtn")
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
        self.db.update_alarm(self.aid, is_active=new_val)
        self.reload_cb()

    def _edit(self):
        dlg = AlarmEditDialog(self, self.data)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            self.db.update_alarm(self.aid, **data)
            self.reload_cb()

    def _delete(self):
        self.db.delete_alarm(self.aid)
        self.reload_cb()


class AlarmPanel(QWidget):
    """闹钟面板"""

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
        title = QLabel("⏰ 闹钟")
        title.setObjectName("panelTitle")
        header.addWidget(title)
        header.addStretch()

        add_btn = QPushButton("+ 新建闹钟")
        add_btn.setObjectName("primaryBtn")
        add_btn.clicked.connect(self._add)
        header.addWidget(add_btn)
        layout.addLayout(header)

        self.list_widget = QListWidget()
        layout.addWidget(self.list_widget, 1)

    def _add(self):
        dlg = AlarmEditDialog(self)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            self.db.add_alarm(**data)
            self.load()

    def load(self):
        self.list_widget.clear()
        alarms = self.db.get_alarms()
        for a in alarms:
            item = QListWidgetItem()
            w = AlarmItemWidget(dict(a), self.db, self.load)
            hint = w.sizeHint()
            hint.setHeight(max(hint.height(), 58))
            item.setSizeHint(hint)
            self.list_widget.addItem(item)
            self.list_widget.setItemWidget(item, w)
