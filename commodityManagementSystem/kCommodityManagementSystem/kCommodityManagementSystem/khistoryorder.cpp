#include "khistoryorder.h"

KHistoryOrder::KHistoryOrder(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->getTableViewData();
	this->setTableViewData();

	//实现历史订单页面数据更新
	(void)connect(ui.btnHistoryPageRefresh, &QPushButton::clicked, this, &KHistoryOrder::onBtnRefreshClicked);
}

KHistoryOrder::~KHistoryOrder()
{
	delete m_pHistoryPageDatebase;
	delete m_pHistoryPageTableModel;
}


//获取数据表
void KHistoryOrder::getTableViewData()
{
	this->m_pHistoryPageTableModel = new QSqlTableModel(this);
	this->m_pHistoryPageTableModel->setTable("sell");
	this->m_pHistoryPageTableModel->select();

	//设置数据名称
	this->m_pHistoryPageTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	this->m_pHistoryPageTableModel->setHeaderData(0, Qt::Horizontal, "订单ID");
	this->m_pHistoryPageTableModel->setHeaderData(1, Qt::Horizontal, "销售时间");
	this->m_pHistoryPageTableModel->setHeaderData(2, Qt::Horizontal, "销售总金额");
	this->m_pHistoryPageTableModel->setHeaderData(3, Qt::Horizontal, "操作人员");

}

//设置
void KHistoryOrder::setTableViewData()
{
	ui.tableViewHistoryPage->setModel(this->m_pHistoryPageTableModel);
	ui.tableViewHistoryPage->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableViewHistoryPage->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void KHistoryOrder::onBtnRefreshClicked()
{

	this->m_pHistoryPageTableModel->select();
	ui.tableViewHistoryPage->setModel(this->m_pHistoryPageTableModel);

	this->getTableViewData();
	this->setTableViewData();
}