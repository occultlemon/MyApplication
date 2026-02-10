import json
import os


_DEFAULT_CONFIG = {
    "theme": "dark",
    "opacity": 0.95,
    "autostart": False,
    "hotkeys": {
        "toggle_window": "<alt>+<space>",
        "new_todo": "<alt>+t",
        "new_reminder": "<alt>+r",
        "launcher_panel": "<alt>+l"
    },
    "pomodoro": {
        "work_duration": 25,
        "break_duration": 5,
        "long_break_duration": 15,
        "sessions_before_long_break": 4
    }
}


class Config:
    """应用配置读写管理"""

    def __init__(self, config_path=None):
        if config_path is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            config_path = os.path.join(base_dir, "config.json")
        self.path = config_path
        self.data = {}
        self.load()

    def load(self):
        if os.path.exists(self.path):
            with open(self.path, 'r', encoding='utf-8') as f:
                self.data = json.load(f)
        else:
            self.data = _DEFAULT_CONFIG.copy()
            self.save()

    def save(self):
        with open(self.path, 'w', encoding='utf-8') as f:
            json.dump(self.data, f, ensure_ascii=False, indent=4)

    def get(self, key, default=None):
        keys = key.split('.')
        val = self.data
        for k in keys:
            if isinstance(val, dict):
                val = val.get(k)
            else:
                return default
            if val is None:
                return default
        return val

    def set(self, key, value):
        keys = key.split('.')
        d = self.data
        for k in keys[:-1]:
            d = d.setdefault(k, {})
        d[keys[-1]] = value
        self.save()
