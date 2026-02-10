from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QLineEdit, QListWidget, QListWidgetItem, QLabel,
    QComboBox, QCheckBox, QMenu, QDateTimeEdit,
    QDialog, QTextEdit, QFormLayout, QDialogButtonBox
)
from PyQt5.QtCore import Qt, pyqtSignal, QDateTime
from PyQt5.QtGui import QFont


class TodoEditDialog(QDialog):
    """待办事项编辑对话框"""
    def __init__(self, parent=None, todo=None):
        super().__init__(parent)
        self.setWindowTitle("编辑待办" if todo else "新建待办")
        self.setMinimumWidth(340)
        layout = QFormLayout(self)

        self.title_input = QLineEdit()
        self.title_input.setPlaceholderText("待办标题")
        if todo:
            self.title_input.setText(todo['title'])
        layout.addRow("标题:", self.title_input)

        self.content_input = QTextEdit()
        self.content_input.setPlaceholderText("详细内容（可选）")
        self.content_input.setMaximumHeight(80)
        if todo:
            self.content_input.setPlainText(todo['content'] or '')
        layout.addRow("内容:", self.content_input)

        self.priority_combo = QComboBox()
        self.priority_combo.addItems(["低", "中", "高"])
        if todo:
            self.priority_combo.setCurrentIndex(todo['priority'])
        else:
            self.priority_combo.setCurrentIndex(1)
        layout.addRow("优先级:", self.priority_combo)

        self.category_input = QLineEdit()
        self.category_input.setPlaceholderText("分类标签（可选）")
        if todo:
            self.category_input.setText(todo['category'] or '')
        layout.addRow("分类:", self.category_input)

        self.due_date = QDateTimeEdit()
        self.due_date.setCalendarPopup(True)
        self.due_date.setDateTime(QDateTime.currentDateTime().addDays(1))
        self.due_date.setDisplayFormat("yyyy-MM-dd HH:mm")
        if todo and todo['due_date']:
            self.due_date.setDateTime(QDateTime.fromString(todo['due_date'][:16], "yyyy-MM-dd HH:mm"))
        self.due_check = QCheckBox("设置截止时间")
        self.due_check.setChecked(bool(todo and todo['due_date']))
        self.due_date.setEnabled(self.due_check.isChecked())
        self.due_check.toggled.connect(self.due_date.setEnabled)
        due_layout = QHBoxLayout()
        due_layout.addWidget(self.due_check)
        due_layout.addWidget(self.due_date)
        layout.addRow("截止:", due_layout)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        layout.addRow(buttons)

    def get_data(self):
        due = None
        if self.due_check.isChecked():
            due = self.due_date.dateTime().toString("yyyy-MM-dd HH:mm:ss")
        return {
            'title': self.title_input.text().strip(),
            'content': self.content_input.toPlainText().strip(),
            'priority': self.priority_combo.currentIndex(),
            'category': self.category_input.text().strip(),
            'due_date': due
        }


class TodoItemWidget(QWidget):
    """单条待办项组件"""
    changed = pyqtSignal()

    def __init__(self, todo, db, parent=None):
        super().__init__(parent)
        self.todo_id = todo['id']
        self.todo_data = todo
        self.db = db

        layout = QHBoxLayout(self)
        layout.setContentsMargins(10, 6, 10, 6)
        layout.setSpacing(8)

        self.checkbox = QCheckBox()
        self.checkbox.setChecked(bool(todo['is_done']))
        self.checkbox.stateChanged.connect(self._toggle)
        layout.addWidget(self.checkbox)

        priority_colors = {0: '#a6e3a1', 1: '#f9e2af', 2: '#f38ba8'}
        dot = QLabel("●")
        dot.setStyleSheet(f"color: {priority_colors.get(todo['priority'], '#a6adc8')}; font-size: 10px;")
        dot.setFixedWidth(14)
        layout.addWidget(dot)

        info_layout = QVBoxLayout()
        info_layout.setSpacing(2)
        title = QLabel(todo['title'])
        title.setFont(QFont("Microsoft YaHei", 12))
        if todo['is_done']:
            title.setStyleSheet("text-decoration: line-through; color: #585b70;")
        info_layout.addWidget(title)

        meta_parts = []
        if todo['category']:
            meta_parts.append(f"[{todo['category']}]")
        if todo['due_date']:
            meta_parts.append(f"截止: {todo['due_date'][:16]}")
        if meta_parts:
            meta = QLabel(" · ".join(meta_parts))
            meta.setObjectName("statLabel")
            info_layout.addWidget(meta)

        layout.addLayout(info_layout, 1)

        edit_btn = QPushButton("✎")
        edit_btn.setFixedSize(28, 28)
        edit_btn.setToolTip("编辑")
        edit_btn.clicked.connect(self._edit)
        layout.addWidget(edit_btn)

        del_btn = QPushButton("✕")
        del_btn.setObjectName("deleteBtn")
        del_btn.setFixedSize(28, 28)
        del_btn.setToolTip("删除")
        del_btn.clicked.connect(self._delete)
        layout.addWidget(del_btn)

    def _toggle(self, state):
        self.db.update_todo(self.todo_id, is_done=int(state == Qt.Checked))
        self.changed.emit()

    def _edit(self):
        dlg = TodoEditDialog(self, self.todo_data)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            if data['title']:
                self.db.update_todo(self.todo_id, **data)
                self.changed.emit()

    def _delete(self):
        self.db.delete_todo(self.todo_id)
        self.changed.emit()


class TodoPanel(QWidget):
    """待办事项面板"""
    todo_count_changed = pyqtSignal(int)

    def __init__(self, db):
        super().__init__()
        self.db = db
        self._init_ui()
        self.load()

    def _init_ui(self):
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 12, 16, 12)
        layout.setSpacing(10)

        # 标题行
        header = QHBoxLayout()
        title = QLabel("☑ 待办事项")
        title.setObjectName("panelTitle")
        header.addWidget(title)
        header.addStretch()
        self.filter_combo = QComboBox()
        self.filter_combo.addItems(["全部", "进行中", "已完成", "已过期"])
        self.filter_combo.currentIndexChanged.connect(self.load)
        header.addWidget(self.filter_combo)
        layout.addLayout(header)

        # 快捷输入行
        input_row = QHBoxLayout()
        self.input = QLineEdit()
        self.input.setPlaceholderText("快速添加待办，回车确认...")
        self.input.returnPressed.connect(self._quick_add)
        input_row.addWidget(self.input)

        self.pri_combo = QComboBox()
        self.pri_combo.addItems(["低", "中", "高"])
        self.pri_combo.setCurrentIndex(1)
        self.pri_combo.setFixedWidth(60)
        input_row.addWidget(self.pri_combo)

        add_btn = QPushButton("+ 添加")
        add_btn.setObjectName("primaryBtn")
        add_btn.setFixedWidth(70)
        add_btn.clicked.connect(self._quick_add)
        input_row.addWidget(add_btn)

        detail_btn = QPushButton("📝")
        detail_btn.setToolTip("详细添加")
        detail_btn.setFixedWidth(36)
        detail_btn.clicked.connect(self._detail_add)
        input_row.addWidget(detail_btn)

        layout.addLayout(input_row)

        # 列表
        self.list_widget = QListWidget()
        layout.addWidget(self.list_widget, 1)

        # 底部统计
        self.stats = QLabel()
        self.stats.setObjectName("statLabel")
        layout.addWidget(self.stats)

    def _quick_add(self):
        text = self.input.text().strip()
        if not text:
            return
        self.db.add_todo(text, priority=self.pri_combo.currentIndex())
        self.input.clear()
        self.load()

    def _detail_add(self):
        dlg = TodoEditDialog(self)
        if dlg.exec_() == QDialog.Accepted:
            data = dlg.get_data()
            if data['title']:
                self.db.add_todo(**data)
                self.load()

    def focus_input(self):
        self.input.setFocus()
        self.input.selectAll()

    def load(self):
        self.list_widget.clear()
        fmap = {0: 'all', 1: 'active', 2: 'done', 3: 'overdue'}
        ft = fmap.get(self.filter_combo.currentIndex(), 'all')
        todos = self.db.get_todos(ft)
        for t in todos:
            item = QListWidgetItem()
            w = TodoItemWidget(dict(t), self.db)
            w.changed.connect(self.load)
            item.setSizeHint(w.sizeHint())
            self.list_widget.addItem(item)
            self.list_widget.setItemWidget(item, w)
        cnt = self.db.get_active_todo_count()
        self.stats.setText(f"待完成: {cnt} 项  |  总计: {len(todos)} 项")
        self.todo_count_changed.emit(cnt)
