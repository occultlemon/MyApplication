#include "koutorder.h"

KOutOrder::KOutOrder(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setCombBoxType();
	//未点击时不显示
	ui.comboBoxOrderPageCategory->setCurrentIndex(-1);


	(void)connect(ui.comboBoxOrderPageCategory, &QComboBox::currentTextChanged, this, &KOutOrder::setComboBoxCategory);
	(void)connect(ui.comboBoxOrderPageName, &QComboBox::currentTextChanged, this, &KOutOrder::setComboBoxName);
	(void)connect(ui.btnOrderPageSellOff, &QPushButton::clicked, this, &KOutOrder::onBtnOrderPageSellOff);
	(void)connect(ui.btnOrderPageUnderOrder, &QPushButton::clicked, this, &KOutOrder::onBtnOrderPageUnderOrder);

	//写信号槽的时候出现问题：无法确定需要哪个重载函数 实例&QSpinBox::valueChanged ，使用QOverload<int>::of()解决
	(void)connect(ui.spinBoxOrderPageNum, QOverload<int>::of(&QSpinBox::valueChanged), this, &KOutOrder::calculateTotalPrice);
}

KOutOrder::~KOutOrder()
{
	delete m_pOrderPageDatebase;
	delete m_pOrderPageTableModel;
}

//获取数据库
void KOutOrder::getTableData()
{
	this->m_pOrderPageTableModel = new QSqlTableModel(this);
	this->m_pOrderPageTableModel->setTable("sell");
	this->m_pOrderPageTableModel->select();

	this->m_pOrderPageTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	this->m_pOrderPageTableModel->setHeaderData(0, Qt::Horizontal, "订单ID");
	this->m_pOrderPageTableModel->setHeaderData(1, Qt::Horizontal, "销售时间");
	this->m_pOrderPageTableModel->setHeaderData(2, Qt::Horizontal, "销售总额");
	this->m_pOrderPageTableModel->setHeaderData(3, Qt::Horizontal, "操作人员");
}

//在textBrowserOrderPageOrderInfo中展示出售信息
void KOutOrder::showOrderInfo(QMap<QString, QString> orderInfoDate)
{
	this->m_orderInfoShow.append("___.___.___.___.___.___.___.___.___.___.");
	//this->m_OrderInfo.append("\n"+orderInfo["sellTime"])
	this->m_orderInfoShow.append("\n" + orderInfoDate["sellOffTime"] + " 售出：" + orderInfoDate["goodsName"]);
	this->m_orderInfoShow.append("\n数量：" + orderInfoDate["goodsNum"] + " 单价：" + orderInfoDate["unitPrice"] + "￥ 总价：" + orderInfoDate["totalPrice"] + "￥\n");
	ui.textBrowserOrderPageOrderInfo->setText(this->m_orderInfoShow);
}

//刷新页面
void KOutOrder::refreshOrderPage()
{
	//获取到id
	int goodsId = ui.comboBoxOrderPageName->currentText().split("-")[0].toInt();
	//获取其他的值
	QSqlQuery sqlQuery;
	sqlQuery.prepare("select * from good where goodid = ?");
	sqlQuery.bindValue(0, goodsId);

	if (sqlQuery.exec())
	{
		qDebug() << "sql execed";
		while (sqlQuery.next())
		{
			QString outPrice = sqlQuery.value("sell_out").toString();
			QString goodsNum = sqlQuery.value("good_numb").toString();
			QString goodsPicture = sqlQuery.value("good_pict").toString();
			ui.lineEditOrderPageUnitPrice->setText(outPrice);	//单价
			ui.lineEditOrderPageInventory->setText(goodsNum);	//库存
			//设置最大可出售的数量为库存量
			ui.spinBoxOrderPageNum->setMaximum(goodsNum.toInt());
			//设置总价
			ui.lineEditOrderPageTotalPrice->setText(QString::number(ui.spinBoxOrderPageNum->text().toDouble() * ui.lineEditOrderPageUnitPrice->text().toDouble()));
			//设置图片
			QString url = "border-image: url(" + goodsPicture + ")";
			ui.btnOrderPagePicture->setStyleSheet(url);
			ui.btnOrderPagePicture->setText(NULL);
			//设置简介
			ui.textEditOrderPageInfo->setText(sqlQuery.value("good_intro").toString());
		}
	}
	else
	{
		qDebug() << "Error: Fail to exec sql." << sqlQuery.lastError();
	}
}

//设置下拉框
void KOutOrder::setCombBoxType()
{
	QSqlQuery query;
	QVector<QString> vector;
	query = this->m_pOrderPageDatebase->execQuery("select category_name from category order by categoryid", vector);
	while (query.next())
	{
		QString types = query.value("category_name").toString();
		ui.comboBoxOrderPageCategory->addItem(types);
	}

}

//订单页的种类下拉栏点击事件
void KOutOrder::setComboBoxCategory(const QString& arg)
{
	ui.comboBoxOrderPageName->clear();
	ui.lineEditOrderPageUnitPrice->clear();
	ui.lineEditOrderPageTotalPrice->clear();
	ui.lineEditOrderPageInventory->clear();
	ui.textEditOrderPageInfo->clear();
	////设置图片
	QString url = "border-image: border)";
	ui.btnOrderPagePicture->setStyleSheet(url);
	ui.btnOrderPagePicture->setText("商品图片");

	QSqlQuery sqlQuery;
	sqlQuery.prepare("select goodid, good_name from good where category_name = ?");
	sqlQuery.bindValue(0, arg);
	if (sqlQuery.exec())
	{
		qDebug() << "sql execed";
		while (sqlQuery.next())
		{
			QString goodsName = sqlQuery.value("good_name").toString();
			QString goodsId = sqlQuery.value("goodid").toString();

			ui.comboBoxOrderPageName->addItem(goodsId + "-" + goodsName);
		}
	}
	else
	{
		qDebug() << "Error: Fail to exec sql." << sqlQuery.lastError();
	}
}

//订单页的商品名下拉栏点击事件	-- 当种类下拉栏改变时，这里相应改变
void KOutOrder::setComboBoxName(const QString& arg)
{
	//获取到id
	int goodsId = ui.comboBoxOrderPageName->currentText().split("-")[0].toInt();
	//获取其他的值
	QSqlQuery sqlQuery;
	sqlQuery.prepare("select * from good where goodid = ?");
	sqlQuery.bindValue(0, goodsId);

	if (sqlQuery.exec())
	{
		qDebug() << "sql execed";
		while (sqlQuery.next())
		{
			QString outPrice = sqlQuery.value("sell_out").toString();
			QString goodsNum = sqlQuery.value("good_numb").toString();
			QString goodsPicture = sqlQuery.value("good_pict").toString();
			ui.lineEditOrderPageUnitPrice->setText(outPrice);	//单价
			ui.lineEditOrderPageInventory->setText(goodsNum);	//库存
			//设置最大可出售的数量为库存量
			ui.spinBoxOrderPageNum->setMaximum(goodsNum.toInt());
			//设置总价
			ui.lineEditOrderPageTotalPrice->setText(QString::number(ui.spinBoxOrderPageNum->text().toDouble() * outPrice.toDouble()));
			//ui.lineEditOrderPageTotalPrice->setText(this->calculateTotalPrice());
			//设置图片
			QString url = "border-image: url(" + goodsPicture + ")";
			ui.btnOrderPagePicture->setStyleSheet(url);
			ui.btnOrderPagePicture->setText(NULL);
			//设置简介
			ui.textEditOrderPageInfo->setText(sqlQuery.value("good_intro").toString());
		}
	}
	else
	{
		qDebug() << "Error: Fail to exec sql." << sqlQuery.lastError();
	}
}

//计算总价
void KOutOrder::calculateTotalPrice(int arg)
{
	//库存为0
	if (ui.lineEditOrderPageInventory->text().size() == 0)
	{
		ui.spinBoxOrderPageNum->setValue(0);
		return;
	}
	//数量不能大于库存
	ui.spinBoxOrderPageNum->setMaximum(ui.lineEditOrderPageInventory->text().toInt());
	//最小值为1	,小于1不能下单
	ui.spinBoxOrderPageNum->setMinimum(1);
	//ui.lineEditOrderPageTotalPrice->setText(QString::number(ui.lineEditOrderPageUnitPrice->text().toDouble() * arg));
	ui.lineEditOrderPageTotalPrice->setText(QString::number(ui.lineEditOrderPageUnitPrice->text().toDouble() * ui.spinBoxOrderPageNum->text().toDouble()));
}

//出售 - 加入订单，改变库存	出售的时候不会将记录加入到历史订单中
void KOutOrder::onBtnOrderPageSellOff()
{
	if (this->m_orderData.size() > 0)
	{
		ui.btnOrderPageUnderOrder->setEnabled(true);
	}
	else
	{
		ui.btnOrderPageUnderOrder->setEnabled(false);
	}

	//获取当前页信息
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString sellOffTime = currentDateTime.toString("hh:mm:ss");

	QString goodsNum = ui.spinBoxOrderPageNum->text();	//数量
	QString unitPrice = ui.lineEditOrderPageUnitPrice->text();	//单价
	QString totalPrice = ui.lineEditOrderPageTotalPrice->text();	//总价
	int inventoryChanged = ui.lineEditOrderPageInventory->text().toInt() - ui.spinBoxOrderPageNum->text().toInt();

	//合法性校验
	if (ui.comboBoxOrderPageName->currentText().size() == 0 || goodsNum.size() == 0 || unitPrice.size() == 0 || totalPrice.size() == 0)
	{
		this->showMessage("信息不全!");
		return;
	}
	else
	{
		//商品数量为0
		if (goodsNum.toDouble() == 0)
		{
			this->showMessage("商品数量：0");
			return;
		}
	}
	//超卖
	if (inventoryChanged < 0)
	{
		this->showMessage("超过商品总量！");
		return;
	}
	//如果下单数量超过库存
	if (goodsNum.toInt() > inventoryChanged)
	{
		ui.spinBoxOrderPageNum->setValue(0);
	}

	//商品名称
	QString goodsName = ui.comboBoxOrderPageName->currentText().split("-")[1];
	//商品id
	QString goodsid = ui.comboBoxOrderPageName->currentText().split("-")[0];


	QSqlQuery sql;
	sql.prepare("update good set good_numb=? where goodid=?");
	sql.bindValue(0, inventoryChanged);
	sql.bindValue(1, goodsid);
	if (sql.exec())
	{
		ui.lineEditOrderPageInventory->setText(QString::number(inventoryChanged));
		//单类商品下单
		QMap<QString, QString> sellOffData;
		sellOffData["goodsid"] = goodsid;
		sellOffData["sellOffTime"] = sellOffTime;
		sellOffData["goodsName"] = goodsName;
		sellOffData["goodsNum"] = goodsNum;
		sellOffData["unitPrice"] = unitPrice;
		sellOffData["totalPrice"] = totalPrice;
		//展示到界面
		this->showOrderInfo(sellOffData);
		//加入购物车
		this->m_orderData.push_back(sellOffData);
		//更新库存
		ui.lineEditOrderPageInventory->setText(QString::number(inventoryChanged));
		//刷新第一页面
		//KInStock* kin;
		//kin->getTableViewData();
		//kin->setTableViewData();

	}
	else
	{
		this->showMessage("出售失败！");
		qDebug() << "Error: Fail to exec sql." << sql.lastError();
		return;
	}
	//改变页面显示
	//改变下单按钮的状态
	if (this->m_orderData.size() > 0)
	{
		ui.btnOrderPageUnderOrder->setEnabled(true);
	}
}

//消息提示的封装
void KOutOrder::showMessage(QString message)
{
	QMessageBox* box = new QMessageBox(QMessageBox::Information, "提示：", message);
}

//按钮单击事件的消息弹窗的封装
bool KOutOrder::btnClickedConfirm(QString title, QString message)
{
	QMessageBox::StandardButton result = QMessageBox::question(NULL, title, message, QMessageBox::Yes | QMessageBox::No);
	switch (result)
	{
	case QMessageBox::Yes:
		qDebug() << "yes";
		return true;
	case QMessageBox::No:
		qDebug() << "no";
		return false;
	default:
		return false;
		break;
	}
}

//下单 - 将订单信息加入到历史订单中
void KOutOrder::onBtnOrderPageUnderOrder()
{
	if (!this->btnClickedConfirm("下单", "确认下单？")) {
		return;
	}
	//所有订单信息，要求展示日期，订单号，应付款总额，下单成功
	//先入库  insert into sell(sell_time,sell_money,operator) values(?,?,?)
	//总金额
	double totalPrice;
	for (int i = 0; i < this->m_orderData.size(); i++)
	{
		totalPrice += this->m_orderData[i]["totalPrice"].toDouble();
	}
	//当前用户m_user
	QString user = this->m_user["username"];
	qDebug() << "当前用户" << user;
	//时间
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString underOrderTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
	//订单号 : P + 日期 + QUuid的9位随机编码
	QString orderIdTime;
	orderIdTime = QString("P" + QDate::currentDate().toString("yyMMdd") + "-");
	QUuid id = QUuid::createUuid();
	QString strId = orderIdTime + id.toString().mid(5, 9);
	//加入表格
	QSqlQuery sql;
	sql.prepare("insert into sell(sellid,sell_time,sell_money,operator) values(?,?,?,?)");
	sql.bindValue(0, strId);
	sql.bindValue(1, underOrderTime);
	sql.bindValue(2, totalPrice);
	sql.bindValue(3, user);
	if (sql.exec())
	{
		sql.next();
		this->m_orderInfoShow.append("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.");
		this->m_orderInfoShow.append("\n日期：" + underOrderTime + "\n订单号:" + strId + "\n应付款总额：" + QString::number(totalPrice) + "￥" + "\n下单成功！");
		ui.textBrowserOrderPageOrderInfo->setText(this->m_orderInfoShow);
		//清空购物车
		this->m_orderData.clear();

		//更新历史订单页
		KHistoryOrder* history = new KHistoryOrder();
		history->getTableViewData();
		history->setTableViewData();
	}
	else
	{
		this->showMessage("下单失败！");
		qDebug() << "Error: Fail to exec sql." << sql.lastError();
		return;
	}

	//按钮不可点
	ui.btnOrderPageUnderOrder->setEnabled(false);

}
