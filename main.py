"""
WorkMate 桌面工作助手
=====================
入口文件：初始化 Qt 应用并启动主窗口。
"""
import sys
import os

# ── 高 DPI 环境变量（必须在 QApplication 实例化之前设置） ──
os.environ["QT_ENABLE_HIGHDPI_SCALING"] = "1"
os.environ["QT_SCALE_FACTOR_ROUNDING_POLICY"] = "PassThrough"

# 确保项目根目录在 sys.path 中
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QFont

from src.ui.main_window import MainWindow


def main():
    # ── Per-Monitor 高 DPI 支持 ──
    QApplication.setAttribute(Qt.AA_EnableHighDpiScaling, True)
    QApplication.setAttribute(Qt.AA_UseHighDpiPixmaps, True)
    # PyQt5 >= 5.14 支持非整数缩放因子（1.25x / 1.5x 等）
    try:
        QApplication.setHighDpiScaleFactorRoundingPolicy(
            Qt.HighDpiScaleFactorRoundingPolicy.PassThrough
        )
    except AttributeError:
        pass  # PyQt5 < 5.14 忽略

    app = QApplication(sys.argv)
    app.setQuitOnLastWindowClosed(False)  # 关闭窗口时不退出，托盘保持
    app.setFont(QFont("Microsoft YaHei", 10))

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
