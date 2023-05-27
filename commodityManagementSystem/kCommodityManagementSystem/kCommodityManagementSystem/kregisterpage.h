/*
══════════════════════════════════════╗
	filename:	KREGISTERPAGE_H
	describe:	分页-注册页面
	editor:		wangjie
	time:		2023/5/11
══════════════════════════════════════╣
*/
#ifndef KREGISTERPAGE_H
#define KREGISTERPAGE_H
#define IN
#define OUT

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kregisterpage.h"
#include"dbutil.h"
#include<qsqldatabase.h>
#include<qsqlerror.h>
#include<qsqlquery.h>
#include<qdatetime.h>
#include<qmessagebox.h>
#include<qtimer.h>

class KRegisterPage : public QWidget
{
	Q_OBJECT

public:
	KRegisterPage(QWidget* parent = Q_NULLPTR);
	~KRegisterPage();

private slots:
	//注册
	void onBtnRegisterPageRegister();
	//取消
	void onBtnRegisterPageClear();



private:
	Ui::KRegisterPage ui;
	DBUtil* m_pRegSqldb;

};
#endif // !KREGISTERPAGE_H