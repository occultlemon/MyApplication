/*
══════════════════════════════════════╗
	@filename:		ktodomainwindow.h
	@describe:		主窗口
	@editor:		wangjie
	@time:			2023/5/25
══════════════════════════════════════╣
*/
#ifndef __KTODOMAINWINDOW_H__
#define __KTODOMAINWINDOW_H__
#define IN
#define OUT
#define INOUT

#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include "ui_ktodomainwindow.h"

#include<qmap.h>
#include<qstring.h>
#include<qvector.h>
#include<QMouseEvent>
#include<qevent.h>
#include<qdebug.h>
#include<qmessagebox.h>
#include<qpoint.h>
#include<qvariant.h>
#include<qdatetime.h>
#include<qmenu.h>
#include<qaction.h>
#include<qicon.h>
#include<qpushbutton.h>
#include<qcursor.h>
#include<qurl.h>
#include<qtimer.h>
#include<qdesktopservices.h>
#include<qpropertyanimation.h>
#include<qtextedit.h>
#include<qshareddata.h>

#include"kdbconnect.h"
#include"klearnmore.h"
#include"ktodoitems.h"
#include"kbtnshowgrouptodo.h"
#include"kaddgroupdialog.h"
#include"ktimerbox.h"

class KTodoItems;
class KTodoMainWindow : public QWidget
{
	Q_OBJECT

public:
	KTodoMainWindow(IN QWidget* parent, IN KDBConnect* db, QMap<QString, QString> user);
	~KTodoMainWindow();
	//鼠标事件
	void mouseMoveEvent(INOUT QMouseEvent* event) override;//移动
	void mouseReleaseEvent(IN QMouseEvent* event) override;//移动
	void mousePressEvent(INOUT QMouseEvent* event) override;//按下
	//初始化
	void initModuleTop();	//顶部模块
	void initModuleLeft();	//左侧模块
	void initModuleMain();	//主模块
	void initModuleRight();	//右侧模块
	void initTodoList();	//事项列表
	void initTodoGroup();	//事项分组
	//功能函数
	void showMessage(QString message);//消息提示
	bool msgConfirmed(QString title, QString message);//确认信息
	void initMyHomePage(IN KTodoItems* items);	//初始化我的主页 -- 单击我的主页按钮以后这里进行刷新
	void initMyTodo(IN QList<KTodoItems*> listItems, IN KTodoItems* items);	//初始化我的待办 -- 单击我的待办按钮后这里进行刷新
	void initItemsDetail(IN KTodoItems* items);		//初始化右侧的todo事项的细节
	void addOneTodoHomePage(IN KTodoItems* items);		//新增一条todo事项 触发 我的首页变化
	void addOneTodoMyTodoPage(IN KTodoItems* items);	//新增一条todo事项，触发 我的待办页面的变化
	void deleteLayout(IN QLayout* currentLayout);	//清除布局
	void addGroup(QString name);	//添加新分组
	void sortTodos(QString sqlString, int sort);	//排序方法
	//日期函数
	void closeTimerBoxDeadTime();	//关闭到期时间日期选择器弹窗
	void getDeadTime(QDate date, QTime time, int again);		//获取todo到期时间
	void closeTimerBoxNoticeTime();	//关闭提醒时间日期选择器弹窗
	void getNoticeTime(QDate date, QTime time, int again);		//获取todo提醒时间

//按钮触发事件
public slots:
	//顶部
	void onPbnMainPageLearnMoreClicked();//须知
	void onPbnMainPageExitClicked();//注销
	void onPbnMainPageMinClicked();//最小化
	void onPbnMainPageMaxClicked();//最大化
	void onPbnMainPageCloseAllClicked();//关闭

	//中部
	void onPbnRefreshClicked();//刷新按钮
	void onPbnShowFinishedClicked();//显示已完成
	void addTodoReturnPress();	//回车键新建待办
	void onPbnOverTimeSortClicked();//结束时间排序
	void onPbnCreateTimeSortClicked();//创建时间排序
	void onPbnFirstSortClicked();//优先级排序
	void onCheckBoxChanged(IN KTodoItems* item);	//勾选框
	//左侧
	void onGroupTodoClicked(IN KBtnShowGroupTodo* pBtnShowGroup);//组别单击，实现main区域的todo事件切换
	void onPbnAddOneGroupClicked();			//新建一个分组的触发事件
	//右侧
	void onPbnDeadTimeRightClicked();	//设置到期时间
	void onPbnSetNoticeRightClicked();	//设置提醒时间
	void onPbnAddIntroRightClicked();	//描述
	void onPbnAddLocalRightClicked();	//地点
	void onPbnAddOtherRightClicked();	//备注
	void onPbnSaveChangeRightClicked();		//保存修改

signals:
	//注销信号
	void signalCloseMainWindow();

private:
	Ui::KTodoMainWindowClass ui;
	//数据库
	KDBConnect* m_pDatabase;

	//鼠标位置变量
	QPoint m_mousePoint;
	bool m_isMousePressed;
	//日期是否更新	
	bool m_ifNewAdd;	//新建了一个todo
	bool m_ifNoticeTime;	//提醒日期
	bool m_ifOverTime;	//超时日期
	//组件
	QPushButton* m_pPbnAddGroup;			//添加分组
	KAddGroupDialog* m_pAddGroupDialog;		//新建分组的弹窗
	//右侧日期设置组件对象
	KTimerBox* m_pTimerBoxDeadTime;		//到期时间
	KTimerBox* m_pTimerBoxNoticeTime;		//提醒时间
	KTimerBox* m_pTimerBoxNewAdd;		//新建一个todo事项的时间
	QTextEdit* m_pIntro;	//描述
	QTextEdit* m_pLocal;	//地点
	QTextEdit* m_pOther;	//备注

	//todoItems的存储容器
	KTodoItems* m_pCurrentItems;	//当前操作的todoItems
	QList<KTodoItems*> m_listTodoLists;		//所有的todoItems用list存储
	QMap<int, KTodoItems*> m_mapTodoItems;		//存储todoItems的id和对象指针 用于排序
	QMap<int, QList<KTodoItems*>> m_mapListTodoItems;		//根据id存储todoItems，用map+list	获取到的是	种类[size]	也就是一种分类下有几个todo

	//todoGroups的存储容器
	int m_groupId;		//当前选中的组别的id
	KBtnShowGroupTodo* m_pCurrentGroups;	//当前操作的todoGroups
	QList<int> m_listGroupIds;		//将选中的组别的id存为一个list
	QList<KBtnShowGroupTodo*> m_listTodoGroups;		//所有的todoGroups用list存储
	QMap<int, KBtnShowGroupTodo*> m_mapTodoGroups;	//根据id存储todoGroups，在新增时保存todoItems的id和todoGroups的关系			//存储组别的种类

	//排序
	QAction* m_pOverTimeSort;
	QAction* m_pCreateTimeSort;
	QAction* m_pFirstSort;
	//动画
	QPropertyAnimation* m_pAddGroupAnimation;	//添加分组时的动画
};

#endif // !__KTODOMAINWINDOW_H__
