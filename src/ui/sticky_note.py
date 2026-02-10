from PyQt5.QtWidgets import (
    QWidget, QVBoxLayout, QHBoxLayout, QPushButton,
    QTextEdit, QLabel, QColorDialog, QMenu
)
from PyQt5.QtCore import Qt, QPoint
from PyQt5.QtGui import QFont, QColor


STICKY_COLORS = ['#fef3c7', '#d1fae5', '#dbeafe', '#fce7f3', '#e0e7ff', '#fecaca']


class StickyNoteWindow(QWidget):
    """独立悬浮便签窗口"""

    def __init__(self, db, note_id=None, content='', color='#fef3c7',
                 pos_x=200, pos_y=200, width=220, height=220):
        super().__init__()
        self.db = db
        self.note_id = note_id
        self.bg_color = color
        self._drag_pos = None

        self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        self.setAttribute(Qt.WA_TranslucentBackground)
        self.setGeometry(pos_x, pos_y, width, height)
        self.setMinimumSize(160, 120)

        self._init_ui(content)
        self._apply_color()

    def _init_ui(self, content):
        self.container = QWidget(self)
        layout = QVBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.addWidget(self.container)

        inner = QVBoxLayout(self.container)
        inner.setContentsMargins(8, 4, 8, 8)
        inner.setSpacing(4)

        # 标题栏
        header = QHBoxLayout()
        header.setSpacing(4)
        title = QLabel("📌 便签")
        title.setFont(QFont("Microsoft YaHei", 9))
        title.setStyleSheet("color: #78716c;")
        header.addWidget(title)
        header.addStretch()

        color_btn = QPushButton("🎨")
        color_btn.setFixedSize(22, 22)
        color_btn.setStyleSheet("border:none; font-size:12px;")
        color_btn.setToolTip("更换颜色")
        color_btn.clicked.connect(self._pick_color)
        header.addWidget(color_btn)

        close_btn = QPushButton("✕")
        close_btn.setFixedSize(22, 22)
        close_btn.setStyleSheet("border:none; color:#a8a29e; font-size:12px;")
        close_btn.setToolTip("关闭便签")
        close_btn.clicked.connect(self._close_note)
        header.addWidget(close_btn)
        inner.addLayout(header)

        # 内容编辑区
        self.editor = QTextEdit()
        self.editor.setPlainText(content)
        self.editor.setFont(QFont("Microsoft YaHei", 11))
        self.editor.setFrameShape(QTextEdit.NoFrame)
        self.editor.setStyleSheet("background: transparent; color: #44403c;")
        self.editor.textChanged.connect(self._save_content)
        inner.addWidget(self.editor)

    def _apply_color(self):
        self.container.setStyleSheet(f"""
            QWidget {{
                background: {self.bg_color};
                border-radius: 10px;
                border: 1px solid rgba(0,0,0,0.08);
            }}
        """)

    def _pick_color(self):
        menu = QMenu(self)
        for c in STICKY_COLORS:
            act = menu.addAction(f"  ● ")
            act.setData(c)
            # 用样式着色
            act.setIcon(self._color_icon(c))
        act = menu.exec_(self.cursor().pos())
        if act and act.data():
            self.bg_color = act.data()
            self._apply_color()
            if self.note_id:
                self.db.update_sticky_note(self.note_id, color=self.bg_color)

    def _color_icon(self, color_hex):
        from PyQt5.QtGui import QPixmap, QIcon
        pm = QPixmap(16, 16)
        pm.fill(QColor(color_hex))
        return QIcon(pm)

    def _save_content(self):
        if self.note_id:
            self.db.update_sticky_note(self.note_id, content=self.editor.toPlainText())

    def _close_note(self):
        if self.note_id:
            self.db.update_sticky_note(self.note_id, is_visible=0)
        self.close()

    def _save_geometry(self):
        if self.note_id:
            g = self.geometry()
            self.db.update_sticky_note(
                self.note_id, pos_x=g.x(), pos_y=g.y(),
                width=g.width(), height=g.height()
            )

    # ── 拖拽移动 ──
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton and event.y() < 30:
            self._drag_pos = event.globalPos() - self.pos()
            event.accept()

    def mouseMoveEvent(self, event):
        if self._drag_pos and event.buttons() & Qt.LeftButton:
            self.move(event.globalPos() - self._drag_pos)
            event.accept()

    def mouseReleaseEvent(self, event):
        self._drag_pos = None
        self._save_geometry()

    def resizeEvent(self, event):
        super().resizeEvent(event)

    def closeEvent(self, event):
        self._save_geometry()
        super().closeEvent(event)


class StickyNoteManager:
    """便签管理器：管理所有便签窗口的创建和恢复"""

    def __init__(self, db):
        self.db = db
        self.windows = []

    def restore_all(self):
        """恢复所有可见便签"""
        notes = self.db.get_sticky_notes(visible_only=True)
        for n in notes:
            self._open_window(dict(n))

    def create_new(self):
        """新建便签"""
        nid = self.db.add_sticky_note()
        note = {'id': nid, 'content': '', 'color': '#fef3c7',
                'pos_x': 200, 'pos_y': 200, 'width': 220, 'height': 220}
        self._open_window(note)

    def _open_window(self, note):
        w = StickyNoteWindow(
            self.db, note_id=note['id'], content=note.get('content', ''),
            color=note.get('color', '#fef3c7'),
            pos_x=note.get('pos_x', 200), pos_y=note.get('pos_y', 200),
            width=note.get('width', 220), height=note.get('height', 220)
        )
        w.show()
        self.windows.append(w)

    def close_all(self):
        for w in self.windows:
            w.close()
        self.windows.clear()
