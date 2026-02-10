import sqlite3
import os
from datetime import datetime


class Database:
    """SQLite 数据库封装，管理所有数据持久化操作"""

    def __init__(self, db_path=None):
        if db_path is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            db_path = os.path.join(base_dir, "workmate.db")
        self.db_path = db_path
        self.conn = sqlite3.connect(db_path, check_same_thread=False)
        self.conn.row_factory = sqlite3.Row
        self.conn.execute("PRAGMA journal_mode=WAL")
        self._create_tables()

    def _create_tables(self):
        self.conn.executescript('''
            CREATE TABLE IF NOT EXISTS todos (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                content TEXT DEFAULT '',
                priority INTEGER DEFAULT 1,
                category TEXT DEFAULT '',
                due_date TEXT,
                is_done INTEGER DEFAULT 0,
                created_at TEXT DEFAULT (datetime('now','localtime')),
                updated_at TEXT DEFAULT (datetime('now','localtime'))
            );
            CREATE TABLE IF NOT EXISTS reminders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                content TEXT DEFAULT '',
                remind_time TEXT NOT NULL,
                repeat_type TEXT DEFAULT 'once',
                is_active INTEGER DEFAULT 1,
                created_at TEXT DEFAULT (datetime('now','localtime'))
            );
            CREATE TABLE IF NOT EXISTS alarms (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                alarm_time TEXT NOT NULL,
                label TEXT DEFAULT '',
                sound_path TEXT DEFAULT '',
                is_active INTEGER DEFAULT 1,
                snooze_minutes INTEGER DEFAULT 5
            );
            CREATE TABLE IF NOT EXISTS app_shortcuts (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                exe_path TEXT NOT NULL,
                arguments TEXT DEFAULT '',
                icon_path TEXT DEFAULT '',
                sort_order INTEGER DEFAULT 0
            );
            CREATE TABLE IF NOT EXISTS sticky_notes (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                content TEXT DEFAULT '',
                pos_x INTEGER DEFAULT 200,
                pos_y INTEGER DEFAULT 200,
                width INTEGER DEFAULT 220,
                height INTEGER DEFAULT 220,
                color TEXT DEFAULT '#fef3c7',
                is_visible INTEGER DEFAULT 1,
                created_at TEXT DEFAULT (datetime('now','localtime'))
            );
            CREATE TABLE IF NOT EXISTS clipboard_history (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                content TEXT NOT NULL,
                content_type TEXT DEFAULT 'text',
                created_at TEXT DEFAULT (datetime('now','localtime'))
            );
            CREATE TABLE IF NOT EXISTS pomodoro_records (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                phase TEXT NOT NULL,
                duration INTEGER NOT NULL,
                completed_at TEXT DEFAULT (datetime('now','localtime'))
            );
            CREATE TABLE IF NOT EXISTS settings (
                key TEXT PRIMARY KEY,
                value TEXT
            );
        ''')
        self.conn.commit()

    # ──────────── Todo CRUD ────────────
    def add_todo(self, title, content='', priority=1, category='', due_date=None):
        cur = self.conn.execute(
            'INSERT INTO todos (title,content,priority,category,due_date) VALUES (?,?,?,?,?)',
            (title, content, priority, category, due_date)
        )
        self.conn.commit()
        return cur.lastrowid

    def get_todos(self, filter_type='all'):
        sql_map = {
            'active': 'SELECT * FROM todos WHERE is_done=0 ORDER BY priority DESC, created_at DESC',
            'done': 'SELECT * FROM todos WHERE is_done=1 ORDER BY updated_at DESC',
            'overdue': "SELECT * FROM todos WHERE is_done=0 AND due_date IS NOT NULL AND due_date<datetime('now','localtime') ORDER BY due_date",
        }
        sql = sql_map.get(filter_type, 'SELECT * FROM todos ORDER BY is_done ASC, priority DESC, created_at DESC')
        return self.conn.execute(sql).fetchall()

    def update_todo(self, todo_id, **kw):
        kw['updated_at'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        sets = ','.join(f'{k}=?' for k in kw)
        self.conn.execute(f'UPDATE todos SET {sets} WHERE id=?', list(kw.values()) + [todo_id])
        self.conn.commit()

    def delete_todo(self, todo_id):
        self.conn.execute('DELETE FROM todos WHERE id=?', (todo_id,))
        self.conn.commit()

    def get_active_todo_count(self):
        return self.conn.execute('SELECT COUNT(*) FROM todos WHERE is_done=0').fetchone()[0]

    # ──────────── Reminder CRUD ────────────
    def add_reminder(self, title, remind_time, content='', repeat_type='once'):
        cur = self.conn.execute(
            'INSERT INTO reminders (title,content,remind_time,repeat_type) VALUES (?,?,?,?)',
            (title, content, remind_time, repeat_type)
        )
        self.conn.commit()
        return cur.lastrowid

    def get_reminders(self, active_only=False):
        if active_only:
            return self.conn.execute('SELECT * FROM reminders WHERE is_active=1 ORDER BY remind_time').fetchall()
        return self.conn.execute('SELECT * FROM reminders ORDER BY remind_time DESC').fetchall()

    def update_reminder(self, rid, **kw):
        sets = ','.join(f'{k}=?' for k in kw)
        self.conn.execute(f'UPDATE reminders SET {sets} WHERE id=?', list(kw.values()) + [rid])
        self.conn.commit()

    def delete_reminder(self, rid):
        self.conn.execute('DELETE FROM reminders WHERE id=?', (rid,))
        self.conn.commit()

    # ──────────── Alarm CRUD ────────────
    def add_alarm(self, alarm_time, label='', sound_path='', snooze_minutes=5):
        cur = self.conn.execute(
            'INSERT INTO alarms (alarm_time,label,sound_path,snooze_minutes) VALUES (?,?,?,?)',
            (alarm_time, label, sound_path, snooze_minutes)
        )
        self.conn.commit()
        return cur.lastrowid

    def get_alarms(self):
        return self.conn.execute('SELECT * FROM alarms ORDER BY alarm_time').fetchall()

    def update_alarm(self, aid, **kw):
        sets = ','.join(f'{k}=?' for k in kw)
        self.conn.execute(f'UPDATE alarms SET {sets} WHERE id=?', list(kw.values()) + [aid])
        self.conn.commit()

    def delete_alarm(self, aid):
        self.conn.execute('DELETE FROM alarms WHERE id=?', (aid,))
        self.conn.commit()

    # ──────────── App Shortcuts CRUD ────────────
    def add_shortcut(self, name, exe_path, arguments='', icon_path='', sort_order=0):
        cur = self.conn.execute(
            'INSERT INTO app_shortcuts (name,exe_path,arguments,icon_path,sort_order) VALUES (?,?,?,?,?)',
            (name, exe_path, arguments, icon_path, sort_order)
        )
        self.conn.commit()
        return cur.lastrowid

    def get_shortcuts(self):
        return self.conn.execute('SELECT * FROM app_shortcuts ORDER BY sort_order, id').fetchall()

    def update_shortcut(self, sid, **kw):
        sets = ','.join(f'{k}=?' for k in kw)
        self.conn.execute(f'UPDATE app_shortcuts SET {sets} WHERE id=?', list(kw.values()) + [sid])
        self.conn.commit()

    def delete_shortcut(self, sid):
        self.conn.execute('DELETE FROM app_shortcuts WHERE id=?', (sid,))
        self.conn.commit()

    # ──────────── Sticky Notes CRUD ────────────
    def add_sticky_note(self, content='', color='#fef3c7', pos_x=200, pos_y=200):
        cur = self.conn.execute(
            'INSERT INTO sticky_notes (content,color,pos_x,pos_y) VALUES (?,?,?,?)',
            (content, color, pos_x, pos_y)
        )
        self.conn.commit()
        return cur.lastrowid

    def get_sticky_notes(self, visible_only=True):
        if visible_only:
            return self.conn.execute('SELECT * FROM sticky_notes WHERE is_visible=1').fetchall()
        return self.conn.execute('SELECT * FROM sticky_notes').fetchall()

    def update_sticky_note(self, nid, **kw):
        sets = ','.join(f'{k}=?' for k in kw)
        self.conn.execute(f'UPDATE sticky_notes SET {sets} WHERE id=?', list(kw.values()) + [nid])
        self.conn.commit()

    def delete_sticky_note(self, nid):
        self.conn.execute('DELETE FROM sticky_notes WHERE id=?', (nid,))
        self.conn.commit()

    # ──────────── Clipboard History ────────────
    def add_clipboard_entry(self, content, content_type='text'):
        cur = self.conn.execute(
            'INSERT INTO clipboard_history (content,content_type) VALUES (?,?)',
            (content, content_type)
        )
        self.conn.execute(
            'DELETE FROM clipboard_history WHERE id NOT IN '
            '(SELECT id FROM clipboard_history ORDER BY created_at DESC LIMIT 200)'
        )
        self.conn.commit()
        return cur.lastrowid

    def get_clipboard_history(self, limit=50):
        return self.conn.execute(
            'SELECT * FROM clipboard_history ORDER BY created_at DESC LIMIT ?', (limit,)
        ).fetchall()

    def clear_clipboard_history(self):
        self.conn.execute('DELETE FROM clipboard_history')
        self.conn.commit()

    # ──────────── Pomodoro Records ────────────
    def add_pomodoro_record(self, phase, duration):
        self.conn.execute(
            'INSERT INTO pomodoro_records (phase,duration) VALUES (?,?)', (phase, duration)
        )
        self.conn.commit()

    def get_today_pomodoro_stats(self):
        row = self.conn.execute(
            "SELECT COUNT(*) as cnt, COALESCE(SUM(duration),0) as total "
            "FROM pomodoro_records WHERE phase='work' AND date(completed_at)=date('now','localtime')"
        ).fetchone()
        return {'count': row['cnt'], 'total_minutes': row['total'] // 60}

    # ──────────── Settings ────────────
    def get_setting(self, key, default=None):
        row = self.conn.execute('SELECT value FROM settings WHERE key=?', (key,)).fetchone()
        return row['value'] if row else default

    def set_setting(self, key, value):
        self.conn.execute('INSERT OR REPLACE INTO settings (key,value) VALUES (?,?)', (key, str(value)))
        self.conn.commit()

    def close(self):
        self.conn.close()
