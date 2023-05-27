#include "kloginpage.h"

const static int WPX = 700;
const static int HPX = 500;


KLoginPage::KLoginPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(WPX, HPX);
	this->setMaximumSize(WPX, HPX);
	this->setWindowFlags(Qt::FramelessWindowHint);
	ui.pbnLoginPageLogin->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnLoginPageRegister->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnLoginPageExit->setCursor(QCursor(Qt::PointingHandCursor));
	//连库
	this->m_pLoginDB = KDBConnect::getInstance(this);
	(void)connect(ui.pbnLoginPageRegister, &QPushButton::clicked, this, &KLoginPage::onPbnLoginPageRegisterClicked);
	(void)connect(ui.pbnLoginPageExit, &QPushButton::clicked, this, &KLoginPage::onPbnLoginPageExitClicked);
	(void)connect(ui.pbnLoginPageLogin, &QPushButton::clicked, this, &KLoginPage::onPbnLoginPageLoginClicked);
}

KLoginPage::~KLoginPage()
{
}

//重载鼠标
void KLoginPage::mousePressEvent(IN QMouseEvent* event)	//点击
{
	if (event->button() == Qt::LeftButton)
	{
		m_position = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void KLoginPage::mouseMoveEvent(IN QMouseEvent* event)	//移动
{
	if (event->button() & Qt::LeftButton)
	{
		move(event->globalPos() - m_position);
		event->accept();
	}
}

void KLoginPage::onPbnLoginPageLoginClicked()		//登录键
{
	//合法性
	ui.labelLoginPageId->clear();
	ui.labelLoginPagePwd->clear();
	if (ui.lineEditLoginPageId->text().size() == 0)
	{
		ui.labelLoginPageId->setText("不可空");
		return;
	}
	if (ui.lineEditLoginPagePwd->text().size() == 0)
	{
		ui.labelLoginPagePwd->setText("不可空");
		return;
	}

	//获取账号密码
	QString username = ui.lineEditLoginPageId->text();
	QString password = ui.lineEditLoginPagePwd->text();

	//sql
	QString loginSql = "select count(*) from user where username = ?";
	//用户是否存在
	QVector<QVariant> vecUser;
	vecUser.push_back(username);
	QSqlQuery query = this->m_pLoginDB->execQuery(loginSql, vecUser);	//匹配数据库
	query.next();

	if (query.value(0).toInt() > 0)		//如果用户存在，则查询密码
	{
		//loginSql.append(" and password = ?");
		QString loginAllSql = "select count(*) from user where username = ? and password = ?";
		QVector<QVariant> vecPwd;
		vecPwd.push_back(username);
		vecPwd.push_back(password);
		query = this->m_pLoginDB->execQuery(loginAllSql, vecPwd);
		query.next();

		if (query.value(0).toInt() > 0)	//核验密码
		{
			//传入主页面
			this->m_mUser["username"] = username;
			this->m_pTodoMainWindow = new KTodoMainWindow(nullptr, this->m_pLoginDB, this->m_mUser);

			//绑定信号
			(void)connect(this->m_pTodoMainWindow, &KTodoMainWindow::signalCloseMainWindow, this, &KLoginPage::show);
			this->m_pTodoMainWindow->show();
			this->hide();
		}
		else //密码错误
		{
			QMessageBox::information(NULL, "提示！", "请输入正确的密码！");
		}
	}
	else //用户不存在
	{
		QMessageBox::information(NULL, "提示！", "用户不存在！");
	}
}

void KLoginPage::onPbnLoginPageRegisterClicked()	//注册键
{
	m_pRegisterPage = new KRegisterPage();
	m_pRegisterPage->show();
}

void KLoginPage::onPbnLoginPageExitClicked()		//退出键
{
	this->close();
}