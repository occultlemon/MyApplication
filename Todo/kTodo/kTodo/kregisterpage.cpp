#include "kregisterpage.h"
const static int WPX = 700;
const static int HPX = 500;

KRegisterPage::KRegisterPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(WPX, HPX);
	this->setMaximumSize(WPX, HPX);
	this->setWindowFlags(Qt::FramelessWindowHint);
	ui.pbnRegisterPageRegisterCancel->setCursor(QCursor(Qt::PointingHandCursor));
	ui.pbnRegisterPageRegisterSure->setCursor(QCursor(Qt::PointingHandCursor));
	(void)connect(ui.pbnRegisterPageRegisterSure, &QPushButton::clicked, this, &KRegisterPage::onPbnRegisterPageRegisterSureClicked);
	(void)connect(ui.pbnRegisterPageRegisterCancel, &QPushButton::clicked, this, &KRegisterPage::onPbnRegisterPageRegisterCancelClicked);
}

KRegisterPage::~KRegisterPage()
{
}

//重载鼠标方法
void KRegisterPage::mousePressEvent(IN QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_position = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void KRegisterPage::mouseMoveEvent(IN QMouseEvent* event)
{
	if (event->button() & Qt::LeftButton)
	{
		move(event->globalPos() - m_position);
		event->accept();
	}
}

void KRegisterPage::onPbnRegisterPageRegisterSureClicked()	//确认注册
{
	ui.labelRegisterPageID->clear();
	ui.labelRegisterPagePwd->clear();
	ui.labelRegisterPagePwdAgain->clear();

	QSqlQuery query;
	QString username = ui.lineEditRegisterPageId->text();
	QString password = ui.lineEditRegisterPagePwd->text();
	QString pwdAgain = ui.lineEditRegisterPagePwdAgain->text();

	bool flag = true;
	//合法性
	//用户名
	if (username.size() == 0)
	{
		ui.labelRegisterPageID->setText("不可空");
		flag = false;
	}
	else
	{
		query.prepare("select count(*) from user where username = ?");
		query.bindValue(0, username);
		if (query.exec())
		{
			query.next();
			if (query.value(0).toInt() > 0)
			{
				ui.labelRegisterPageID->setText("重复！");
				flag = false;
			}
		}
	}

	//密码
	if (password.size() == 0)
	{
		ui.labelRegisterPagePwd->setText("不可空");
		flag = false;
	}
	if (pwdAgain.size() == 0)
	{
		ui.labelRegisterPagePwdAgain->setText("不可空");
		flag = false;
	}
	else
	{
		if (pwdAgain != password)
		{
			ui.labelRegisterPagePwdAgain->setText("不一致");
			flag = false;
		}
	}
	if (!flag)
	{
		return;
	}

	//注册数据 插库
	QString insertSql = QString("insert into user(username, password) values('%1','%2')").arg(username).arg(password);
	bool exec = this->m_pRegSqldb->execSql(insertSql);
	if (exec)
	{
		QMessageBox* box = new QMessageBox(QMessageBox::Information, tr("提示！"), tr("注册成功！"));
		//QMessageBox::information(NULL, "提示！", "注册成功！");
		QTimer::singleShot(1000, box, SLOT(accept())); //也可将accept改为close
		box->exec();
		this->close();
	}
}

void KRegisterPage::onPbnRegisterPageRegisterCancelClicked()	//取消注册
{
	this->close();
}