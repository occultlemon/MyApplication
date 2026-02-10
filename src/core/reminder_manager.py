from datetime import datetime, timedelta
from PyQt5.QtCore import QObject, QTimer, pyqtSignal


class ReminderManager(QObject):
    """提醒事项管理 + 定时检查"""
    reminder_fired = pyqtSignal(dict)  # 触发时发射提醒数据

    def __init__(self, db):
        super().__init__()
        self.db = db
        self._timer = QTimer(self)
        self._timer.setInterval(15000)  # 每15秒检查一次
        self._timer.timeout.connect(self._check)
        self._timer.start()

    def add(self, title, remind_time, content='', repeat_type='once'):
        return self.db.add_reminder(title, remind_time, content, repeat_type)

    def get_all(self, active_only=False):
        return self.db.get_reminders(active_only)

    def update(self, rid, **kw):
        self.db.update_reminder(rid, **kw)

    def delete(self, rid):
        self.db.delete_reminder(rid)

    def _check(self):
        now = datetime.now()
        reminders = self.db.get_reminders(active_only=True)
        for r in reminders:
            try:
                rt = datetime.strptime(r['remind_time'], '%Y-%m-%d %H:%M:%S')
            except (ValueError, TypeError):
                try:
                    rt = datetime.strptime(r['remind_time'], '%Y-%m-%d %H:%M')
                except (ValueError, TypeError):
                    continue
            if rt <= now:
                self.reminder_fired.emit(dict(r))
                repeat = r['repeat_type']
                if repeat == 'once':
                    self.db.update_reminder(r['id'], is_active=0)
                elif repeat == 'daily':
                    new_time = (rt + timedelta(days=1)).strftime('%Y-%m-%d %H:%M:%S')
                    self.db.update_reminder(r['id'], remind_time=new_time)
                elif repeat == 'weekly':
                    new_time = (rt + timedelta(weeks=1)).strftime('%Y-%m-%d %H:%M:%S')
                    self.db.update_reminder(r['id'], remind_time=new_time)
                elif repeat == 'monthly':
                    month = rt.month + 1
                    year = rt.year + (month - 1) // 12
                    month = (month - 1) % 12 + 1
                    new_time = rt.replace(year=year, month=month).strftime('%Y-%m-%d %H:%M:%S')
                    self.db.update_reminder(r['id'], remind_time=new_time)
