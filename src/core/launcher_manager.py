import subprocess
import os
from PyQt5.QtCore import QObject


class LauncherManager(QObject):
    """快捷启动管理：启动外部程序"""

    def __init__(self, db):
        super().__init__()
        self.db = db

    def add(self, name, exe_path, arguments='', icon_path='', sort_order=0):
        return self.db.add_shortcut(name, exe_path, arguments, icon_path, sort_order)

    def get_all(self):
        return self.db.get_shortcuts()

    def update(self, sid, **kw):
        self.db.update_shortcut(sid, **kw)

    def delete(self, sid):
        self.db.delete_shortcut(sid)

    def launch(self, shortcut_id):
        shortcuts = self.db.get_shortcuts()
        for s in shortcuts:
            if s['id'] == shortcut_id:
                self._run(s['exe_path'], s['arguments'])
                return True
        return False

    def launch_by_path(self, exe_path, arguments=''):
        return self._run(exe_path, arguments)

    def _run(self, exe_path, arguments=''):
        try:
            cmd = [exe_path]
            if arguments:
                cmd += arguments.split()
            subprocess.Popen(cmd, shell=False)
            return True
        except FileNotFoundError:
            # 回退到 os.startfile（适用于系统路径程序）
            try:
                os.startfile(exe_path)
                return True
            except Exception:
                return False
        except Exception:
            return False

    @staticmethod
    def launch_edge(url=''):
        paths = [
            r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
            r"C:\Program Files\Microsoft\Edge\Application\msedge.exe",
        ]
        for p in paths:
            if os.path.exists(p):
                cmd = [p]
                if url:
                    cmd.append(url)
                subprocess.Popen(cmd)
                return True
        try:
            os.startfile(f"microsoft-edge:{url}")
            return True
        except Exception:
            return False

    @staticmethod
    def launch_notepad(file_path=''):
        cmd = ['notepad.exe']
        if file_path:
            cmd.append(file_path)
        subprocess.Popen(cmd)
