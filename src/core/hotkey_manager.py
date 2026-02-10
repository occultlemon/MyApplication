from pynput import keyboard
from PyQt5.QtCore import QObject, pyqtSignal


class HotkeyManager(QObject):
    """全局快捷键管理"""
    toggle_window = pyqtSignal()
    new_todo = pyqtSignal()
    new_reminder = pyqtSignal()
    open_launcher = pyqtSignal()
    minimize_window = pyqtSignal()
    maximize_window = pyqtSignal()

    def __init__(self, config):
        super().__init__()
        self.config = config
        self._listener = None

    def start(self):
        hk = self.config.get('hotkeys', {})
        mapping = {}

        combo = hk.get('toggle_window', '<alt>+<space>')
        mapping[combo] = lambda: self.toggle_window.emit()

        combo = hk.get('new_todo', '<alt>+t')
        mapping[combo] = lambda: self.new_todo.emit()

        combo = hk.get('new_reminder', '<alt>+r')
        mapping[combo] = lambda: self.new_reminder.emit()

        combo = hk.get('launcher_panel', '<alt>+l')
        mapping[combo] = lambda: self.open_launcher.emit()

        combo = hk.get('minimize_window', '<alt>+<shift>+m')
        mapping[combo] = lambda: self.minimize_window.emit()

        combo = hk.get('maximize_window', '<alt>+<shift>+x')
        mapping[combo] = lambda: self.maximize_window.emit()

        try:
            self._listener = keyboard.GlobalHotKeys(mapping)
            self._listener.daemon = True
            self._listener.start()
        except Exception as e:
            print(f"[HotkeyManager] 注册快捷键失败: {e}")

    def stop(self):
        if self._listener:
            self._listener.stop()
            self._listener = None

    def restart(self):
        self.stop()
        self.start()
