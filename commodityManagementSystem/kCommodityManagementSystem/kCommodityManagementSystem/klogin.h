/*
══════════════════════════════════════╗
	filename:	KLOGIN_H
	describe:	登录主页面
	editor:		wangjie
	time:		2023/5/9
══════════════════════════════════════╣
*/
#ifndef KLOGIN_H
#define KLOGIN_H
#define IN
#define OUT

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_klogin.h"
#include<qbuttongroup.h>
#include<qstackedwidget.h>
#include<qpropertyanimation.h>
#include<qeasingcurve.h>
#include<qdebug.h>

#include"kloginpage.h"
#include"kregisterpage.h"

class KLogin : public QWidget
{
	Q_OBJECT

public:
	KLogin(QWidget* parent = Q_NULLPTR);
	~KLogin();

private:
	Ui::KLogin ui;

	QButtonGroup m_btnGroup;
	KLoginPage m_loginPageWindow;
	KRegisterPage m_registerPageWindow;
};

#endif // !KLOGIN_H