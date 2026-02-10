from PyQt5.QtWidgets import QSystemTrayIcon, QMenu, QAction, QApplication
from PyQt5.QtGui import QIcon, QPixmap, QPainter, QColor, QFont
from PyQt5.QtCore import pyqtSignal, QObject


def create_default_icon():
    """生成默认托盘图标（蓝色圆底白字 W）"""
    pm = QPixmap(64, 64)
    pm.fill(QColor(0, 0, 0, 0))
    painter = QPainter(pm)
    painter.setRenderHint(QPainter.Antialiasing)
    painter.setBrush(QColor("#89b4fa"))
    painter.setPen(QColor("#89b4fa"))
    painter.drawEllipse(2, 2, 60, 60)
    painter.setPen(QColor("#1e1e2e"))
    painter.setFont(QFont("Arial", 30, QFont.Bold))
    painter.drawText(pm.rect(), 0x0084, "W")  # AlignCenter
    painter.end()
    return QIcon(pm)


class TrayIcon(QSystemTrayIcon):
    """系统托盘图标"""
    show_window = pyqtSignal()
    quit_app = pyqtSignal()
    new_todo = pyqtSignal()
    new_reminder = pyqtSignal()
    new_sticky = pyqtSignal()
    toggle_mini = pyqtSignal()

    def __init__(self, parent=None):
        super().__init__(create_default_icon(), parent)
        self.setToolTip("WorkMate 桌面工作助手")
        self._build_menu()
        self.activated.connect(self._on_activated)

    def _build_menu(self):
        menu = QMenu()

        show_act = menu.addAction("📌 显示主窗口")
        show_act.triggered.connect(self.show_window.emit)

        menu.addSeparator()

        todo_act = menu.addAction("☑ 新建待办")
        todo_act.triggered.connect(self.new_todo.emit)

        reminder_act = menu.addAction("🔔 新建提醒")
        reminder_act.triggered.connect(self.new_reminder.emit)

        sticky_act = menu.addAction("📝 新建便签")
        sticky_act.triggered.connect(self.new_sticky.emit)

        menu.addSeparator()

        mini_act = menu.addAction("🔄 迷你/展开模式")
        mini_act.triggered.connect(self.toggle_mini.emit)

        menu.addSeparator()

        quit_act = menu.addAction("❌ 退出")
        quit_act.triggered.connect(self.quit_app.emit)

        self.setContextMenu(menu)

    def _on_activated(self, reason):
        if reason == QSystemTrayIcon.DoubleClick:
            self.show_window.emit()
        elif reason == QSystemTrayIcon.Trigger:
            self.toggle_mini.emit()
