from PyQt5.QtCore import QObject, QTimer, pyqtSignal


class PomodoroManager(QObject):
    """番茄钟业务管理"""
    tick = pyqtSignal(int, int)         # (remaining_seconds, total_seconds)
    phase_changed = pyqtSignal(str)     # 'work' / 'break' / 'long_break'
    session_completed = pyqtSignal()    # 一个工作阶段完成

    PHASE_WORK = 'work'
    PHASE_BREAK = 'break'
    PHASE_LONG_BREAK = 'long_break'

    def __init__(self, db, config):
        super().__init__()
        self.db = db
        self.config = config

        pom_cfg = config.get('pomodoro', {})
        self.work_duration = pom_cfg.get('work_duration', 25) * 60
        self.break_duration = pom_cfg.get('break_duration', 5) * 60
        self.long_break_duration = pom_cfg.get('long_break_duration', 15) * 60
        self.sessions_before_long = pom_cfg.get('sessions_before_long_break', 4)

        self.current_phase = self.PHASE_WORK
        self.total_seconds = self.work_duration
        self.remaining = self.work_duration
        self.completed_sessions = 0
        self.is_running = False

        self._timer = QTimer(self)
        self._timer.setInterval(1000)
        self._timer.timeout.connect(self._on_tick)

    def start(self):
        self.is_running = True
        self._timer.start()

    def pause(self):
        self.is_running = False
        self._timer.stop()

    def reset(self):
        self.pause()
        self.current_phase = self.PHASE_WORK
        self.total_seconds = self.work_duration
        self.remaining = self.work_duration
        self.tick.emit(self.remaining, self.total_seconds)

    def skip(self):
        self._next_phase()

    def _on_tick(self):
        self.remaining -= 1
        self.tick.emit(self.remaining, self.total_seconds)
        if self.remaining <= 0:
            self._next_phase()

    def _next_phase(self):
        self._timer.stop()
        # 记录完成的阶段
        duration = self.total_seconds - self.remaining
        self.db.add_pomodoro_record(self.current_phase, duration)

        if self.current_phase == self.PHASE_WORK:
            self.completed_sessions += 1
            self.session_completed.emit()
            if self.completed_sessions % self.sessions_before_long == 0:
                self.current_phase = self.PHASE_LONG_BREAK
                self.total_seconds = self.long_break_duration
                self.remaining = self.long_break_duration
            else:
                self.current_phase = self.PHASE_BREAK
                self.total_seconds = self.break_duration
                self.remaining = self.break_duration
        else:
            self.current_phase = self.PHASE_WORK
            self.total_seconds = self.work_duration
            self.remaining = self.work_duration

        self.is_running = False
        self.phase_changed.emit(self.current_phase)
        self.tick.emit(self.remaining, self.total_seconds)
