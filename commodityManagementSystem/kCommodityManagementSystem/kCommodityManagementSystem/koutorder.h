/*
══════════════════════════════════════╗
	filename:	KOUTORDER_H
	describe:	分页-出库订单页
	editor:		wangjie
	time:		2023/5/11
══════════════════════════════════════╣
*/
#ifndef KOUTORDER_H
#define KOUTORDER_H
#define IN
#define OUT

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_koutorder.h"
#include"dbutil.h"
#include<qsqltablemodel.h>
#include<qstring.h>
#include<qmap.h>
#include<qsqlquery.h>
#include<qabstractitemview.h>
#include<qvector.h>
#include<qmessagebox.h>
#include<qabstractitemmodel.h>
#include<qfiledialog.h>
#include<qspinbox.h>
#include<qtimer.h>
#include<quuid.h>
#include<qdatetime.h>
#include"khistoryorder.h"
//#include"kinstock.h"

class KOutOrder : public QWidget
{
	Q_OBJECT

public:
	KOutOrder(QWidget* parent = Q_NULLPTR);
	~KOutOrder();

	//获取数据库
	void getTableData();

	//设置下拉框
	void setCombBoxType();

	//在textEditOrderPageInfo中展示订单信息
	void showOrderInfo(QMap<QString, QString> orderInfo);
	//刷新页面
	void refreshOrderPage();

	//订单页的种类下拉栏点击事件
	void setComboBoxCategory(const QString& arg);
	//订单页的商品名下拉栏点击事件
	void setComboBoxName(const QString& arg);
	//计算总价
	void calculateTotalPrice(int arg);
	//出售 - 加入订单，改变库存	出售的时候不会将记录加入到历史订单中
	void onBtnOrderPageSellOff();
	//下单 - 将订单信息加入到历史订单中
	void onBtnOrderPageUnderOrder();

	//消息提示的封装
	void showMessage(QString message);
	//按钮单击事件的消息弹窗的封装
	bool btnClickedConfirm(QString title, QString message);

private:
	Ui::KOutOrder ui;

	//订单信息
	QString m_orderInfoShow;
	//保存出售订单的容器
	QVector<QMap<QString, QString>> m_orderData;
	//当前登录用户
	QMap<QString, QString> m_user;

	DBUtil* m_pOrderPageDatebase;	//数据库
	QSqlTableModel* m_pOrderPageTableModel;	//商品数据记录
};


#endif // !KOUTORDER_H