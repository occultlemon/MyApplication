/*
══════════════════════════════════════╗
	@filename:		kaddgroupdialog.h
	@describe:		添加分组的弹窗
	@editor:		wangjie
	@time:			2023/5/24
══════════════════════════════════════╣
*/

#ifndef __KADDGROUPDIALOG_H__
#define __KADDGROUPDIALOG_H__
#define IN
#define OUT

#include <QDialog>
#include "ui_kaddgroupdialog.h"
#include<qpushbutton.h>
#include<qstring.h>
#include<qevent.h>
#include<qpropertyanimation.h>
#include<qaction.h>

class KAddGroupDialog : public QDialog
{
	Q_OBJECT

public:
	KAddGroupDialog(QWidget* parent = Q_NULLPTR);
	~KAddGroupDialog();
	void closeEvent(IN QCloseEvent* event);	//关闭事件
	void signalHand();	//信号通信 传递信息

public slots:
	//关闭按钮	取消按钮
	void onPbnCloseClicked();
	//确定按钮
	void onPbnOKClicked();

signals:
	void addGroup(QString groupName);

private:
	Ui::KAddGroupDialog ui;
};



#endif // !__KADDGROUPDIALOG_H__