/*
══════════════════════════════════════╗
	@filename:		kregisterpage.h
	@describe:		注册页面
	@editor:		wangjie
	@time:			2023/5/17
══════════════════════════════════════╣
*/
#ifndef __KREGISTERPAGE_H__
#define __KREGISTERPAGE_H__
#define IN
#define OUT
#include <QWidget>
#include "ui_kregisterpage.h"
#include<QMouseEvent>
#include<qsqlquery.h>
#include<qmessagebox.h>
#include<qdebug.h>
#include<qstring.h>
#include"qtimer.h"

#include"kdbconnect.h"

class KRegisterPage : public QWidget
{
	Q_OBJECT

public:
	KRegisterPage(QWidget* parent = Q_NULLPTR);
	~KRegisterPage();

protected:
	//重载鼠标方法
	void mousePressEvent(IN QMouseEvent* event);
	void mouseMoveEvent(IN QMouseEvent* event);

private slots:
	void onPbnRegisterPageRegisterSureClicked();	//确认注册
	void onPbnRegisterPageRegisterCancelClicked();	//取消注册

private:
	Ui::KRegisterPage ui;
	QPoint m_position;

	KDBConnect* m_pRegSqldb;
};
#endif // !__KREGISTERPAGE_H__