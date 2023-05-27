/*
══════════════════════════════════════╗
	@filename:		kloginpage.h
	@describe:		登录页面
	@editor:		wangjie
	@time:			2023/5/17
══════════════════════════════════════╣
*/
#ifndef __KLOGINPAGE_H__
#define __KLOGINPAGE_H__
#define IN
#define OUT
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kloginpage.h"
#include<QMouseEvent>
#include<qevent.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qmessagebox.h>
#include<qsettings.h>
#include<qstring.h>
#include<qvector.h>

#include"kdbconnect.h"
#include"kregisterpage.h"
#include"ktodomainwindow.h"



class KLoginPage : public QWidget
{
	Q_OBJECT

public:
	KLoginPage(QWidget* parent = Q_NULLPTR);
	~KLoginPage();

protected:
	//重载鼠标
	void mousePressEvent(IN QMouseEvent* event);	//点击
	void mouseMoveEvent(IN QMouseEvent* event);	//移动

private slots:
	void onPbnLoginPageLoginClicked();		//登录键
	void onPbnLoginPageRegisterClicked();	//注册键
	void onPbnLoginPageExitClicked();		//退出键


private:
	Ui::KLoginPage ui;
	QPoint m_position;	//窗口的位置

	KDBConnect* m_pLoginDB;	//数据库操作
	QMap<QString, QString> m_mUser;	//保存当前登录用户

	KRegisterPage* m_pRegisterPage;		//注册页面
	KTodoMainWindow* m_pTodoMainWindow;		//主页面
};

#endif // !__KLOGINPAGE_H__