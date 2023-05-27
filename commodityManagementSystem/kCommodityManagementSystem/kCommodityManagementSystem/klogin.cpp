#include "klogin.h"
const static int WPX = 900;
const static int HPX = 600;

KLogin::KLogin(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//设置窗口大小
	this->setMinimumSize(WPX, HPX);
	this->setMaximumSize(WPX, HPX);

	//初始化
	//widget页面
	ui.stackedWidgetPages->addWidget(&m_loginPageWindow);
	ui.stackedWidgetPages->addWidget(&m_registerPageWindow);

	//按钮组
	m_btnGroup.addButton(ui.m_btnWelcomePageLogin, 0);
	m_btnGroup.addButton(ui.m_btnWelcomePageRegister, 1);

	(void)connect(&m_btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), ui.stackedWidgetPages, &QStackedWidget::setCurrentIndex);

	m_btnGroup.button(0)->setChecked(true);
	ui.stackedWidgetPages->setCurrentIndex(0);


}

KLogin::~KLogin()
{
}
