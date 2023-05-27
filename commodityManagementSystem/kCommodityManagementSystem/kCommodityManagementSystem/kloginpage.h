/*
══════════════════════════════════════╗
	filename:	KLOGINPAGE_H
	describe:	分页-登录页
	editor:		wangjie
	time:		2023/5/9
══════════════════════════════════════╣
*/
#ifndef KLOGINPAGE_H
#define KLOGINPAGE_H

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kloginpage.h"
#include<qsqldatabase.h>
#include"kmainwindow.h"
#include"dbutil.h"
#include<qstring.h>
#include<qdebug.h>
#include<qmessagebox.h>
#include<qtimer.h>


class KLoginPage : public QWidget
{
	Q_OBJECT

public:
	KLoginPage(QWidget* parent = Q_NULLPTR);
	~KLoginPage();

	//建立用户表
	bool createUserTable();
	//建立类别表
	bool createCategoryTable();
	//建立商品表
	bool createGoodsTable();
	//建立销售记录表
	bool createRecordTable();
	//设置登录图片
	void setIconLogin();

private slots:
	//登录按钮
	void onBtnLoginPageLoginClicked();
	//清除按钮
	void onBtnLoginPageClearClicked();


private:
	Ui::KLoginPage ui;
	DBUtil* m_pSqldb;	//数据库操作
	QMap<QString, QString> m_user;		//保存当前登录用户
	KMainWindow* m_pMainWindow;	//主页面
};

#endif // !KLOGINPAGE_H