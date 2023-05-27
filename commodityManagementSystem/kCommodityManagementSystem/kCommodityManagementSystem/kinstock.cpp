#include "kinstock.h"

KInStock::KInStock(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//刷新入库页面的数据
	this->getTableViewData();
	this->setTableViewData();
	//加载下拉框类别
	this->setCombBoxType();
	//未点击时不显示类别
	ui.comboBoxStockPageCategory->setCurrentIndex(-1);

	int row = this->m_pStockPageTableModel->rowCount();//总行数
	if (row == 0)//没有商品，不能清仓
	{
		ui.btnStockPageClear->setEnabled(false);
	}

	(void)connect(ui.tableViewStockPage, &QTableView::clicked, this, &KInStock::tableViewPressedShow);
	(void)connect(ui.btnStockPageInStock, &QPushButton::clicked, this, &KInStock::onBtnStockPageInStockClicked);
	(void)connect(ui.btnStockPageClear, &QPushButton::clicked, this, &KInStock::onBtnStockPageClearClicked);
	(void)connect(ui.btnStockPagePicture, &QPushButton::clicked, this, &KInStock::onBtnStockPagePictureClicked);
}

KInStock::~KInStock()
{
	delete m_pStockPageDatebase;
	delete m_pStockPageTableModel;
}

//获取数据表
void KInStock::getTableViewData()
{
	this->m_pStockPageTableModel = new QSqlTableModel(this);
	this->m_pStockPageTableModel->setTable("good");
	this->m_pStockPageTableModel->select();

	//设置数据提交方式和数据名称	
	this->m_pStockPageTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);	//手动提交
	//只需要展示这些列
	this->m_pStockPageTableModel->setHeaderData(3, Qt::Horizontal, "商品名称");
	this->m_pStockPageTableModel->setHeaderData(4, Qt::Horizontal, "进价");
	this->m_pStockPageTableModel->setHeaderData(5, Qt::Horizontal, "售价");
	this->m_pStockPageTableModel->setHeaderData(6, Qt::Horizontal, "库存");
	this->m_pStockPageTableModel->setHeaderData(7, Qt::Horizontal, "描述");

}

//将数据放入tableView
void KInStock::setTableViewData()
{
	//放入数据
	ui.tableViewStockPage->setModel(this->m_pStockPageTableModel);
	ui.tableViewStockPage->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//将不需要展示的列隐藏
	ui.tableViewStockPage->hideColumn(0);
	ui.tableViewStockPage->hideColumn(1);
	ui.tableViewStockPage->hideColumn(2);
	ui.tableViewStockPage->hideColumn(8);
	//设置宽度
	ui.tableViewStockPage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

//设置下拉框
void KInStock::setCombBoxType()
{
	QSqlQuery query;
	QVector<QString> vector;
	query = this->m_pStockPageDatebase->execQuery("select category_name from category order by categoryid", vector);
	while (query.next())
	{
		QString types = query.value("category_name").toString();
		ui.comboBoxStockPageCategory->addItem(types);
	}
}

//单击tableView  显示入库页面的各种组件信息
void KInStock::tableViewPressedShow(const QModelIndex& index)
{
	//根据tableView中的行内容显示
	int row = index.row();
	QAbstractItemModel* model = ui.tableViewStockPage->model();	//设置模型
	ui.comboBoxStockPageCategory->setCurrentText(model->data(model->index(row, 2)).toString());
	ui.lineEditStockPageName->setText(model->data(model->index(row, 3)).toString());
	ui.lineEditStockPageSellIn->setText(model->data(model->index(row, 4)).toString());
	ui.lineEditStockPageSellOut->setText(model->data(model->index(row, 5)).toString());
	ui.spinBoxStockPageNum->setValue(0);//model->data(model->index(row,6)).toInt());
	//展示图片
	QString url = "border-image: url(" + model->data(model->index(row, 8)).toString() + ")";//拉伸填充
	ui.btnStockPagePicture->setStyleSheet(url);
	//ui.btnStockPagePicture->setText(model->data(model->index(row, 8)).toString());	//设置按钮文本

	ui.textEditStockPageInfo->setText(model->data(model->index(row, 7)).toString());
	ui.labelStockPageId->setText(model->data(model->index(row, 0)).toString());
	//隐藏id
	ui.labelStockPageId->hide();

}


//按钮单击事件的消息弹窗的封装
bool KInStock::btnClickedConfirm(QString title, QString message)
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

//消息提示的封装
void KInStock::showMessage(QString message)
{
	QMessageBox* box = new QMessageBox(QMessageBox::Information, "提示：", message);
}


//入库
void KInStock::onBtnStockPageInStockClicked()
{
	//获取下拉框的种类文本
	QString types = ui.comboBoxStockPageCategory->currentText();
	//读取页面的展示信息
	QString name = ui.lineEditStockPageName->text();
	double inPrice = ui.lineEditStockPageSellIn->text().toDouble();
	double outPrice = ui.lineEditStockPageSellOut->text().toDouble();
	int count = ui.spinBoxStockPageNum->text().toInt();
	int goodsId = ui.labelStockPageId->text().toInt();
	if (ui.labelStockPageId->text().size() == 0)
	{
		this->showMessage("仓库没有该商品");
		return;
	}
	QString info = ui.textEditStockPageInfo->document()->toPlainText();
	QString goodPictUrl = ui.btnStockPagePicture->text();

	if (types.size() == 0 || name.size() == 0 || ui.lineEditStockPageSellIn->text().size() == 0 ||
		ui.lineEditStockPageSellOut->text().size() == 0 || ui.spinBoxStockPageNum->text().size() == 0)
	{
		this->showMessage("信息未填完整");
		return;
	}

	//通过类别查询id
	QVector<QString> vec1;
	vec1.push_back(types);
	QSqlQuery sqlQuery;
	//通过类别的名称获取到类别的id
	sqlQuery = this->m_pStockPageDatebase->execQuery("select categoryid from category where category_name = ?", vec1);
	vec1.pop_back();
	sqlQuery.next();
	QString typeId = sqlQuery.value("categoryid").toString();
	//获取到当前的库存，入库出库直接追加
	sqlQuery.prepare("select good_numb from good where goodid = ?");
	sqlQuery.bindValue(0, goodsId);
	int numAdd = 0;		//新增的数量
	if (sqlQuery.exec())
	{
		sqlQuery.next();
		numAdd = sqlQuery.value(0).toInt();
		qDebug() << "sql execed!";
	}
	else
	{
		qDebug() << "Error: Fail to exec sql." << sqlQuery.lastError();
	}

	QString msg;
	if (count == 0)
	{
		//确认数据信息
		msg = "没有选择入库数量\n类别：" + types + "\n名称：" + name + "\n进价：" + QString::number(inPrice) + "\n售价：" + QString::number(outPrice);
	}
	else
	{
		//确认数据信息
		msg = "确认入库？\n类别：" + types + "\n名称：" + name + "\n进价：" + QString::number(inPrice) + "\n售价：" +
			QString::number(outPrice) + "\n新增数量：" + QString::number(count) + "\n最终数量：" + QString::number(count + numAdd);
	}
	if (!this->btnClickedConfirm("修改货品信息", msg))
	{
		return;
	}

	//数据更新
	//sqlQuery.prepare("update good set categoryid = ?, category_name = ?, good_name = ?, sell_in = ?, sell_out = ?, good_numb = ?, good_intro = ?, good_pict = ? where goodid = ? ");
	sqlQuery.prepare("update good set categoryid = ?, category_name = ?, good_name = ?, sell_in = ?, sell_out = ?, good_numb = ?, good_intro = ? where goodid = ? ");
	sqlQuery.bindValue(0, typeId);
	sqlQuery.bindValue(1, types);
	sqlQuery.bindValue(2, name);
	sqlQuery.bindValue(3, inPrice);
	sqlQuery.bindValue(4, outPrice);
	sqlQuery.bindValue(5, count + numAdd);
	sqlQuery.bindValue(6, info);
	//sqlQuery.bindValue(7, goodPictUrl);	//图片丢失
	//sqlQuery.bindValue(7, ":/KMainWindow/images/yifu1.png");	//图片丢失
	sqlQuery.bindValue(7, goodsId);


	if (!sqlQuery.exec())
	{
		qDebug() << "Error: Fail to exec sql." << sqlQuery.lastError();
		this->showMessage("入库更新失败！");
	}
	else
	{
		qDebug() << "sql execed !";
		//定时退出
		this->showMessage("入库更新成功！");
	}
	//刷新数据
	this->m_pStockPageTableModel->select();
	ui.tableViewStockPage->setModel(this->m_pStockPageTableModel);

}
//清仓
void KInStock::onBtnStockPageClearClicked()
{
	//获取商品总行数
	int row = this->m_pStockPageTableModel->rowCount();
	int goodsCount = 0;
	for (int i = 0; i < row; i++)
	{
		goodsCount += this->m_pStockPageTableModel->data(this->m_pStockPageTableModel->index(i, 6)).toInt();
	}
	QString message = "确认清仓？\t商品种类：" + QString::number(row) + "种\n商品总数：" + QString::number(goodsCount) + "个单位";
	if (this->btnClickedConfirm("提示", message))
	{
		//数据库操作
		if (this->m_pStockPageDatebase->execSql("delete from good"))
		{
			this->showMessage("已全部清仓");
			this->getTableViewData();
			this->setTableViewData();
		}
		else
		{
			this->showMessage("清仓失败");
		}
	}
}
//图片按钮
void KInStock::onBtnStockPagePictureClicked()
{
	//添加图片
	//获取文件名和路径，同时加入筛选功能
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("open iamge"),//对话框名称
		":/KMainWindow/",	//默认打开文件位置“.”文件目录"/"根目录
		tr("image files(*.jpg *.png *.bmp)"));//筛选器
	if (!fileName.size() == 0) {
		//设置图片位置
		//ui.btnStockPagePicture->setText(fileName);
		//设置图片显示
		QString url = "border-image: url(" + fileName + ")";//拉伸填充
		ui.btnStockPagePicture->setStyleSheet(url);

		//ui.btnStockPagePicture->setText(fileName).toString();	//设置按钮文本
		QString goodPictUrl = ui.btnStockPagePicture->text();
	}
}

