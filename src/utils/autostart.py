import os
import sys
import winreg


APP_NAME = "WorkMate"
REG_PATH = r"Software\Microsoft\Windows\CurrentVersion\Run"


def is_autostart_enabled():
    """检查是否已设置开机自启"""
    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, REG_PATH, 0, winreg.KEY_READ)
        value, _ = winreg.QueryValueEx(key, APP_NAME)
        winreg.CloseKey(key)
        return bool(value)
    except (FileNotFoundError, OSError):
        return False


def enable_autostart():
    """设置开机自启动"""
    exe_path = sys.executable
    if getattr(sys, 'frozen', False):
        exe_path = sys.executable
    else:
        exe_path = f'"{sys.executable}" "{os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "main.py"))}"'
    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, REG_PATH, 0, winreg.KEY_SET_VALUE)
        winreg.SetValueEx(key, APP_NAME, 0, winreg.REG_SZ, exe_path)
        winreg.CloseKey(key)
        return True
    except OSError:
        return False


def disable_autostart():
    """取消开机自启动"""
    try:
        key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, REG_PATH, 0, winreg.KEY_SET_VALUE)
        winreg.DeleteValue(key, APP_NAME)
        winreg.CloseKey(key)
        return True
    except (FileNotFoundError, OSError):
        return False
