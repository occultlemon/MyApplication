/*
══════════════════════════════════════╗
	filename:	KINSTOCK_H
	describe:	分页-入库页面
	editor:		wangjie
	time:		2023/5/11
══════════════════════════════════════╣
*/
#ifndef KINSTOCK_H
#define KINSTOCK_H
#define IN
#define OUT

#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_kinstock.h"
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

class KInStock : public QWidget
{
	Q_OBJECT

public:
	KInStock(QWidget* parent = Q_NULLPTR);
	//KInStock(QWidget* parent, DBUtil* db, QMap<QString, QString> user);
	~KInStock();


	//获取数据表
	void getTableViewData();
	//将数据放入tableView
	void setTableViewData();
	//设置下拉框
	void setCombBoxType();
	//单击tableView  显示入库页面的各种组件信息
	void tableViewPressedShow(const QModelIndex& index);
	//按钮单击事件的消息弹窗的封装
	bool btnClickedConfirm(QString title, QString message);
	//消息提示的封装
	void showMessage(QString message);

	//入库
	void onBtnStockPageInStockClicked();
	//清仓
	void onBtnStockPageClearClicked();
	//图片按钮
	void onBtnStockPagePictureClicked();




private:
	Ui::KInStock ui;

	DBUtil* m_pStockPageDatebase;	//数据库
	QSqlTableModel* m_pStockPageTableModel;	//商品数据记录
	//QMap<QString, QString> m_user;	//当前登录用户
};


#endif // !KINSTOCK_H