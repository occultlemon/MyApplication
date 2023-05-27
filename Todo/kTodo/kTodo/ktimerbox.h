/*
══════════════════════════════════════╗
	@filename:		ktimernbox.h
	@describe:		时间选择器弹窗
	@editor:		wangjie
	@time:			2023/5/20
══════════════════════════════════════╣
*/
#ifndef __KTIMERBOX_H__
#define __KTIMERBOX_H__
#define IN
#define OUT
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_ktimerbox.h"
#include<qevent.h>
#include<qdatetime.h>
#include<QTime>
#include<QDate>

class KTimerBox : public QWidget
{
	Q_OBJECT

public:
	KTimerBox(QWidget* parent = Q_NULLPTR);
	~KTimerBox();

	//设置重复 隐藏
	void gboxSetAgainHide();
	//设置时间 隐藏
	void gboxSetTimeHide();
	//弹窗事件	重写父类基类函数
	bool event(IN QEvent* event) override;
	//设置日期（yyyy-MM-dd）、时间(hh:mm)、和重复【currentindex的值(0\1\2\3)】
	void setDateTimeAgain(QDate date, QTime time, int again);

	//getter 
	QDate getDate();
	QTime getTime();
	int getAgain();



signals:
	//获取到当前时间信息的信号
	void signalGetTime(QDate date, QTime time, int again);
	//关闭这个弹窗的信号
	void signalCloseThis();
	//单击确定按钮的信号
	void signalPbnOk();

public slots:
	void onPbnCancelClicked();
	void onPbnOKClicked();


private:
	Ui::KTimerBox ui;

};

#endif // !__KTIMERBOX_H__