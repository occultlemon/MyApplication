import winsound
from PyQt5.QtWidgets import QSystemTrayIcon


def show_notification(tray_icon, title, message, icon_type=QSystemTrayIcon.Information, duration=5000):
    """通过系统托盘显示桌面通知"""
    if tray_icon and tray_icon.isSystemTrayAvailable():
        tray_icon.showMessage(title, message, icon_type, duration)


def play_alert_sound(sound_path=None):
    """播放提醒音效"""
    try:
        if sound_path:
            winsound.PlaySound(sound_path, winsound.SND_FILENAME | winsound.SND_ASYNC)
        else:
            winsound.PlaySound("SystemExclamation", winsound.SND_ALIAS | winsound.SND_ASYNC)
    except Exception:
        try:
            winsound.MessageBeep(winsound.MB_ICONEXCLAMATION)
        except Exception:
            pass
