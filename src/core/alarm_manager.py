from datetime import datetime, timedelta
from PyQt5.QtCore import QObject, QTimer, pyqtSignal


class AlarmManager(QObject):
    """闹钟管理 + 定时检查"""
    alarm_fired = pyqtSignal(dict)

    def __init__(self, db):
        super().__init__()
        self.db = db
        self._timer = QTimer(self)
        self._timer.setInterval(1000)  # 每秒检查
        self._timer.timeout.connect(self._check)
        self._timer.start()
        self._fired_ids = set()  # 防止同一闹钟在同一分钟内重复触发

    def add(self, alarm_time, label='', sound_path='', snooze_minutes=5):
        return self.db.add_alarm(alarm_time, label, sound_path, snooze_minutes)

    def get_all(self):
        return self.db.get_alarms()

    def update(self, aid, **kw):
        self.db.update_alarm(aid, **kw)

    def delete(self, aid):
        self.db.delete_alarm(aid)
        self._fired_ids.discard(aid)

    def snooze(self, aid, minutes=None):
        """贪睡：推迟闹钟"""
        alarms = self.db.get_alarms()
        for a in alarms:
            if a['id'] == aid:
                m = minutes or a['snooze_minutes'] or 5
                new_time = (datetime.now() + timedelta(minutes=m)).strftime('%H:%M')
                self.db.update_alarm(aid, alarm_time=new_time)
                self._fired_ids.discard(aid)
                break

    def _check(self):
        now_hm = datetime.now().strftime('%H:%M')
        alarms = self.db.get_alarms()
        for a in alarms:
            if not a['is_active']:
                continue
            if a['alarm_time'] == now_hm and a['id'] not in self._fired_ids:
                self._fired_ids.add(a['id'])
                self.alarm_fired.emit(dict(a))
        # 每过一分钟清除已触发标记
        if datetime.now().second == 0:
            self._fired_ids.clear()
