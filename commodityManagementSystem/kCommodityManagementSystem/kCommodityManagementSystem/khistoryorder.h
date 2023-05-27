/*
══════════════════════════════════════╗
	filename:	historyorder.h
	describe:	分页面-历史订单
	editor:		wangjie
	time:		2023/5/11
══════════════════════════════════════╣
*/
#ifndef KHISTORYORDER_H
#define KHISTORYORDER_H
#define IN
#define OUT

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_khistoryorder.h"
#include"dbutil.h"
#include<qsqltablemodel.h>

class KHistoryOrder : public QWidget
{
	Q_OBJECT

public:
	KHistoryOrder(QWidget* parent = Q_NULLPTR);
	~KHistoryOrder();

	//获取数据表
	void getTableViewData();
	//设置
	void setTableViewData();

	void onBtnRefreshClicked();


private:
	Ui::KHistoryOrder ui;
	QSqlTableModel* m_pHistoryPageTableModel;	//商品数据记录
	DBUtil* m_pHistoryPageDatebase;	//数据库

};
#endif // !KHISTORYORDER_H