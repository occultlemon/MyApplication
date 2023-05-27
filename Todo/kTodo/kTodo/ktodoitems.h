/*
══════════════════════════════════════╗
	@filename:		ktodoitems.h
	@describe:		自定义待办事项条目显示
	@editor:		wangjie
	@time:			2023/5/17
══════════════════════════════════════╣
*/
#pragma execution_character_set("utf-8")
#ifndef __KTODOITEMS_H__
#define __KTODOITEMS_H__
#define IN
#define OUT
#include <QWidget>
#include "ui_ktodoitems.h"
#include<qlayoutitem.h>
#include<qevent.h>
#include<qpainter.h>
#include<qstring.h>
#include<qcheckbox.h>

#include"ktodomainwindow.h"

class KTodoItems : public QWidget
{
	Q_OBJECT

public:
	KTodoItems(QString name, int id, QWidget* parent = Q_NULLPTR);
	KTodoItems(int id, int groupId, QString todoName, int todoLevel, QDate overTime, QDateTime noticeTime, int again, QString intro, QString local, QString other, QString finishPerson, bool ifFinish, QString groupName, QWidget* parent = Q_NULLPTR);
	~KTodoItems();

	//初始化页面
	void initItemsDisplay(bool itemsShow);
	//友元
	friend class KTodoMainWindow;
	//勾选
	void finishCheckBox();
	//鼠标操作
	void enterEvent(IN QEvent* event) override; //鼠标进入事件
	void leaveEvent(IN QEvent* event) override;//鼠标离开事件
	void mousePressEvent(IN QMouseEvent* event) override;//鼠标点击事件
	//互斥事件
	void changePress();//被按下的颜色
	void changeRelease();//松开的颜色

	//getter setter	用于后续的数据更新
	int getId() const;	//id
	void setId(int id);

	int getGroupId() const;	//组别id
	void setGroupId(int groupId);

	QString getTodoName() const;	//todo名
	void setTodoName(QString name);

	int getTodoLevel() const;	//优先级
	void setTodoLevel(int level);

	QDate getOverTime() const;	//结束时间
	void setOverTime(QDate overTime);

	int getAgain() const;	//重复
	void setAgain(int again);

	QDateTime getNoticeTime() const;	//提醒时间
	void setNoticeTime(QDateTime noticeTime);

	QString getIntro() const;	//描述
	void setIntro(QString intro);

	QString getLocal() const;	//地点
	void setLocal(QString local);

	QString getOther() const;	//备注
	void setOther(QString other);

	QString getFinishPerson() const;	//完成人
	void setFinishPerson(QString finishPerson);

	bool getIfFinish() const;	//是否完成
	void setIfFinish(bool ifFinish);

	QString getGroupName() const;	//组别名
	void setGroupName(QString groupName);

public slots:
	void onCheckBoxChanged();	//完成和未完成之间的切换


signals:
	void signalCurrentItem(KTodoItems*);
	void signalChangedCheckBox(KTodoItems*);	//选择框单击信号

private:
	Ui::KTodoItems ui;

	int m_id;	//待办ID
	int m_groupId;	//组别ID
	QDate m_createTime;	//创建时间
	QString m_todoName;	//代办名称
	int m_todoLevel;	//级别	1无/2低/3中/4高
	QDate m_overTime;	//结束时间
	int m_again;	//设置重复	无/天/周/月/自定义
	QDateTime m_noticeTime;	//提醒时间
	QString m_intro;	//描述
	QString m_local;	//地点
	QString m_other;	//备注
	QString m_finishPerson;	//完成人
	bool m_ifFinish;	//是否完成
	QString m_groupName;	//所属组群
	int m_mouseState = 0;	//状态

	//组件
	QHBoxLayout* m_pHBox;	//显示级别、是否重复等信息的下部分区域
	QLabel* m_pLabelOverTime;	//结束时间
	QLabel* m_pLabelAgain;	//重复
	QLabel* m_pLabelNoticeTime;	//提醒时间
	QLabel* m_pLabelGroupName;	//所属分组名称

};

#endif // !__KTODOITEMS_H__