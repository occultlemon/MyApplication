#include "kmainwindow.h"

const static int WPX = 1000;
const static int HPX = 600;

KMainWindow::KMainWindow(QWidget* parent, DBUtil* db, QMap<QString, QString> user)
//KMainWindow::KMainWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//设置窗口大小
	this->setMinimumSize(WPX, HPX);
	this->setMaximumSize(WPX, HPX);

	ui.labelLoginUser->setText(QString("当前用户：") + (user["username"]));

	//初始化
	//widget页面
	//ui.stackedWidgetMain->addWidget(&m_stockWindow);
	ui.stackedWidgetMain->addWidget(&m_stockWindow);
	ui.stackedWidgetMain->addWidget(&m_orderWindow);
	ui.stackedWidgetMain->addWidget(&m_historyOrderWindow);

	//设置按钮组
	m_btnGroup.addButton(ui.btnInStock, 0);
	m_btnGroup.addButton(ui.btnOutOrder, 1);
	m_btnGroup.addButton(ui.btnHistoryOrder, 2);

	//初始状态	侧边栏不隐藏
	m_sideWidgetFlag = false;
	//ui.widgetSideBar->move(0, ui.widgetTopBar->height() + 10);
	m_pPropertyAnimation = new QPropertyAnimation(ui.widgetSideBar, "geometry");
	m_pPropertyAnimation->setEasingCurve(QEasingCurve::InOutQuint);
	m_pPropertyAnimation->setDuration(1000);

	(void)connect(&m_btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), ui.stackedWidgetMain, &QStackedWidget::setCurrentIndex);
	(void)connect(ui.btnMenu, &QPushButton::clicked, this, &KMainWindow::onBtnMenuClicked);
	(void)connect(ui.btnLogOff, &QPushButton::clicked, this, &KMainWindow::onBtnLogOffClicked);
	(void)connect(ui.btnClose, &QPushButton::clicked, this, &KMainWindow::onBtnCloseClicked);
	(void)connect(ui.btnLearnMore, &QPushButton::clicked, this, &KMainWindow::onBtnLearnMoreClicked);
	(void)connect(ui.btnMinst, &QPushButton::clicked, this, &KMainWindow::onBtnMinstClicked);



	//默认选中的页面
	m_btnGroup.button(0)->setChecked(true);
	ui.stackedWidgetMain->setCurrentIndex(0);
}

void KMainWindow::onBtnMenuClicked()
{
	if (m_sideWidgetFlag)
	{
		m_pPropertyAnimation->setStartValue(QRect(-this->rect().width(), 0, ui.widgetSideBar->width(), ui.widgetSideBar->height()));
		//这里ui.widgetTopBar->height() / 200是因为我发现若不对这个值进行限制,当单击时，侧边栏的位置会发生变化，但是我目前找不到原因，只能采用这种方式尽量降低视觉上的影响，希望老师可以告知真正的原因
		m_pPropertyAnimation->setEndValue(QRect(0, ui.widgetTopBar->height() / 200, ui.widgetSideBar->width(), ui.widgetSideBar->height()));
		m_pPropertyAnimation->start();

		m_sideWidgetFlag = !m_sideWidgetFlag;
	}
	else
	{
		m_pPropertyAnimation->setStartValue(QRect(0, ui.widgetTopBar->height() / 200, ui.widgetSideBar->width(), ui.widgetSideBar->height()));
		m_pPropertyAnimation->setEndValue(QRect(-this->rect().width(), 0, ui.widgetSideBar->width(), ui.widgetSideBar->height()));
		m_pPropertyAnimation->start();

		m_sideWidgetFlag = !m_sideWidgetFlag;
	}
}


void KMainWindow::onBtnLogOffClicked()
{
	emit signalCloseMainWindow();
	this->close();

}

//learnMore
void KMainWindow::onBtnLearnMoreClicked()
{
	KReadme* readme = new KReadme();
	readme->show();
}
//最小化
void KMainWindow::onBtnMinstClicked()
{
	this->showMinimized();
}
//关闭
void KMainWindow::onBtnCloseClicked()
{
	this->close();


}