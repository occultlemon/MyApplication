/*
══════════════════════════════════════╗
	@filename:		kbtnshowgrouptodo.h
	@describe:		自定义按钮 - 单击侧边分组展示该分组的待办事项
	@editor:		wangjie
	@time:			2023/5/23
══════════════════════════════════════╣
*/
#ifndef __KBTNSHOWGROUPTODO_H__
#define __KBTNSHOWGROUPTODO_H__
#define IN
#define OUT
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kbtnshowgrouptodo.h"
#include<qstring.h>
#include<qvector.h>
#include<qaction.h>
#include<qmenu.h>
#include<qmessagebox.h>
#include<qevent.h>
#include<qpainter.h>

class KBtnShowGroupTodo : public QWidget
{
	Q_OBJECT

public:
	KBtnShowGroupTodo(QString name, int groupId, int groupCount, QWidget* parent = Q_NULLPTR);
	~KBtnShowGroupTodo();
	void enterEvent(IN QEvent* event) override; //鼠标进入事件
	void leaveEvent(IN QEvent* event) override;//鼠标离开事件
	void mousePressEvent(IN QMouseEvent* event) override;//鼠标点击事件
	void initDisplay();		//显示（）内数字初始化
	void changePress();		//互斥事件 - 按下
	void changeRelease();	//互斥 - 松开
	//getter setter
	int getGroupId() const;
	void setGroupId(int groupId);
	QString getGroupName() const;
	void setGroupName(QString groupName);
	int getGroupCount() const;
	void setGroupCount(int groupCount);
signals:
	void signalBtnClicked(KBtnShowGroupTodo* btnShowGroup);	//通知其他按钮该按钮的信号
private:
	Ui::KBtnShowGroupTodo ui;
	int m_mouseStatus;	//鼠标状态
	QString m_groupName;	//组名
	int m_groupId;		//组别id
	int m_groupCount;	//该分组下todo事件的计数
};

#endif // !__KBTNSHOWGROUPTODO_H__
