from PyQt5.QtCore import QObject, pyqtSignal


class TodoManager(QObject):
    """待办事项业务管理"""
    count_changed = pyqtSignal(int)

    def __init__(self, db):
        super().__init__()
        self.db = db

    def add(self, title, content='', priority=1, category='', due_date=None):
        rid = self.db.add_todo(title, content, priority, category, due_date)
        self.count_changed.emit(self.active_count())
        return rid

    def get_all(self, filter_type='all'):
        return self.db.get_todos(filter_type)

    def update(self, todo_id, **kw):
        self.db.update_todo(todo_id, **kw)
        self.count_changed.emit(self.active_count())

    def toggle(self, todo_id, is_done):
        self.db.update_todo(todo_id, is_done=int(is_done))
        self.count_changed.emit(self.active_count())

    def delete(self, todo_id):
        self.db.delete_todo(todo_id)
        self.count_changed.emit(self.active_count())

    def active_count(self):
        return self.db.get_active_todo_count()
