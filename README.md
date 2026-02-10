# WorkMate 桌面工作助手

一款基于 Python + PyQt5 开发的轻量级桌面工作助手，以悬浮窗形式常驻桌面，集成待办管理、提醒闹钟、快捷启动、番茄钟等高效工具，助力日常办公效率提升。

---

## 功能特性

### 核心功能

| 模块 | 说明 |
|------|------|
| **待办事项** | 新增/编辑/删除/标记完成，支持优先级（高/中/低）、分类标签、截止日期，多维度筛选（全部/进行中/已完成/已过期） |
| **提醒事项** | 定时提醒 + 系统通知弹窗，支持单次/每日/每周/每月重复提醒，到时自动弹窗 + 音效提醒 |
| **闹钟** | 设定闹钟时间，到时系统通知 + 铃声提醒，支持贪睡功能（自定义推迟分钟数），支持多个闹钟并行 |
| **快捷启动** | 内置 Edge 浏览器、记事本、计算器、资源管理器等常用工具一键启动，支持自定义添加任意程序（配置可执行路径 + 启动参数），网格化展示，右键编辑/删除 |
| **全局快捷键** | `Alt+Space` 显示/隐藏主窗口，`Alt+T` 新建待办，`Alt+R` 新建提醒，`Alt+L` 打开启动面板，所有快捷键均可自定义 |
| **悬浮窗口** | 无边框置顶悬浮窗，支持鼠标拖拽移动，迷你模式（显示时间 + 待办数）↔ 展开模式一键切换 |
| **系统托盘** | 最小化到系统托盘常驻运行，托盘右键菜单快捷操作，双击托盘图标唤起窗口 |
| **设置中心** | 深色/浅色主题切换，窗口透明度调节（30%~100%），开机自启动，快捷键自定义绑定，数据导出/导入备份 |

### 创意扩展功能

| 模块 | 说明 |
|------|------|
| **🍅 番茄钟** | 25 分钟专注 + 5 分钟休息（可配置），圆环进度动画实时展示，自动切换工作/休息/长休息阶段，每日番茄完成统计 |
| **📝 桌面便签** | 独立悬浮便签窗口，支持多张便签同时显示，6 种颜色可选，自动记忆位置和大小，关闭后可再次恢复 |
| **📋 剪贴板历史** | 实时监控系统剪贴板，自动记录最近 200 条文本复制历史，支持关键词搜索，双击即可重新复制，一键清空 |
| **📊 系统监控** | 状态栏实时显示 CPU / 内存占用率，3 秒刷新，轻量无感 |

---

## 技术架构

```
Python 3.8+ / PyQt5
├── 数据持久化 ──── SQLite (WAL 模式)
├── 定时调度 ────── QTimer + APScheduler
├── 全局热键 ────── pynput
├── 系统监控 ────── psutil
├── 系统通知 ────── QSystemTrayIcon + winsound
└── 打包分发 ────── PyInstaller / Nuitka + Inno Setup
```

---

## 项目结构

```
chatBot/
├── main.py                    # 程序入口
├── requirements.txt           # Python 依赖
├── config.json                # 用户配置文件
├── workmate.db                # SQLite 数据库（运行后自动生成）
├── resources/
│   ├── icons/                 # 图标资源
│   └── sounds/                # 铃声资源
└── src/
    ├── db/
    │   └── database.py        # 数据库封装（建表 + 全部 CRUD）
    ├── core/
    │   ├── todo_manager.py    # 待办事项业务逻辑
    │   ├── reminder_manager.py# 提醒事项 + 定时检查
    │   ├── alarm_manager.py   # 闹钟 + 秒级检查
    │   ├── launcher_manager.py# 外部程序启动器
    │   ├── hotkey_manager.py  # 全局快捷键管理
    │   └── pomodoro_manager.py# 番茄钟状态机
    ├── utils/
    │   ├── config.py          # JSON 配置读写
    │   ├── autostart.py       # Windows 注册表自启动
    │   └── notification.py    # 系统通知 + 音效
    └── ui/
        ├── main_window.py     # 主窗口（迷你/展开模式）
        ├── tray_icon.py       # 系统托盘
        ├── todo_panel.py      # 待办事项面板
        ├── reminder_panel.py  # 提醒事项面板
        ├── alarm_panel.py     # 闹钟面板
        ├── launcher_panel.py  # 快捷启动面板
        ├── pomodoro_panel.py  # 番茄钟面板（含圆环动画）
        ├── clipboard_panel.py # 剪贴板历史面板
        ├── sticky_note.py     # 桌面便签窗口
        ├── settings_panel.py  # 设置面板
        └── styles.py          # QSS 主题样式表（深色/浅色）
```

---

## 快速开始

### 环境要求

- Python >= 3.8
- Windows 10 / 11

### 安装依赖

```bash
pip install -r requirements.txt
```

### 运行

```bash
python main.py
```

启动后桌面左上角出现迷你悬浮窗（显示当前时间和待办数量），双击展开完整面板。

### 默认快捷键

| 快捷键 | 功能 |
|--------|------|
| `Alt + Space` | 显示 / 隐藏主窗口 |
| `Alt + T` | 新建待办事项 |
| `Alt + R` | 新建提醒事项 |
| `Alt + L` | 打开快捷启动面板 |

---

## 打包为安装程序

### 使用 PyInstaller 打包

```bash
pip install pyinstaller
pyinstaller --noconfirm --onefile --windowed --name WorkMate --icon resources/icons/app.ico --add-data "config.json;." --add-data "resources;resources" main.py
```

### 使用 Inno Setup 生成安装包

打包后的 `dist/WorkMate.exe` 可配合 Inno Setup 制作 Windows 安装向导，支持：
- 桌面快捷方式
- 开始菜单项
- 卸载程序

---

## 数据说明

所有数据存储在项目根目录的 `workmate.db` SQLite 数据库中，包含以下数据表：

| 表名 | 说明 |
|------|------|
| `todos` | 待办事项（标题、内容、优先级、分类、截止时间、完成状态） |
| `reminders` | 提醒事项（标题、提醒时间、重复类型、启用状态） |
| `alarms` | 闹钟（时间、标签、铃声路径、贪睡分钟数） |
| `app_shortcuts` | 快捷启动应用（名称、路径、参数、图标） |
| `sticky_notes` | 桌面便签（内容、位置、大小、颜色） |
| `clipboard_history` | 剪贴板历史（内容、类型、时间） |
| `pomodoro_records` | 番茄钟记录（阶段、时长） |
| `settings` | 键值对设置存储 |

---

## 配置文件

`config.json` 存储应用配置，支持以下选项：

```json
{
    "theme": "dark",
    "opacity": 0.95,
    "autostart": false,
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
```

---

## 许可证

MIT License
