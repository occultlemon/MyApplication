
/*
══════════════════════════════════════╗
	filename:	KMAINWWINDOW_H
	describe:	主页面实现-具体实现侧边栏切换
	editor:		wangjie
	time:		2023/5/8
══════════════════════════════════════╣
*/
#ifndef KMAINWWINDOW_H
#define KMAINWWINDOW_H
#define IN
#define OUT
#pragma execution_character_set("utf-8")
#include <QtWidgets/QWidget>
#include "ui_kmainwindow.h"
#include<qbuttongroup.h>
#include<qstackedwidget.h>
#include<qdebug.h>
#include<qpropertyanimation.h>
#include<qeasingcurve.h>
#include<qicon.h>
#include"dbutil.h"
#include<qaction.h>

#include"kinstock.h"
#include"koutorder.h"
#include"khistoryorder.h"
#include"kreadme.h"



class KMainWindow : public QWidget
{
	Q_OBJECT

public:
	KMainWindow(QWidget* parent, DBUtil* db, QMap<QString, QString> user);
	//KMainWindow(QWidget* parent = Q_NULLPTR);

	//隐藏侧边栏
	void onBtnMenuClicked();
	//void mouseDoubleClickEvent(QMouseEvent* event);

	//注销
	void onBtnLogOffClicked();
	//learnMore
	void onBtnLearnMoreClicked();
	//最小化
	void onBtnMinstClicked();
	//关闭
	void onBtnCloseClicked();



signals:
	void signalCloseMainWindow();

private:
	Ui::KMainWindowClass ui;

	QButtonGroup m_btnGroup;	//按钮组
	KInStock m_stockWindow;		//仓库页
	KOutOrder m_orderWindow;	//订单页
	KHistoryOrder m_historyOrderWindow;	//历史订单页

	bool m_sideWidgetFlag;
	QPropertyAnimation* m_pPropertyAnimation;
};

#endif // !KMAINWWINDOW_H
