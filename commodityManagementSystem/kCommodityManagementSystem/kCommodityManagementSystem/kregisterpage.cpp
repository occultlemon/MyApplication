#include "kregisterpage.h"

KRegisterPage::KRegisterPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	(void)connect(ui.btnRegisterPageRegister, &QPushButton::clicked, this, &KRegisterPage::onBtnRegisterPageRegister);
	(void)connect(ui.btnRegisterPageClear, &QPushButton::clicked, this, &KRegisterPage::onBtnRegisterPageClear);
}

KRegisterPage::~KRegisterPage()
{
}

//注册
void KRegisterPage::onBtnRegisterPageRegister()
{
	ui.labelRegisterPageUser->clear();
	ui.labelRegisterPagePwd->clear();
	ui.labelRegisterPagePwdAgain->clear();
	ui.labelRegisterPagePhone->clear();
	ui.labelRegisterPageMail->clear();

	QSqlQuery sql;
	QString username = ui.lineEditRegisterPageUser->text();
	QString password = ui.lineEditRegisterPagePwd->text();
	QString pwdAgain = ui.lineEditRegisterPagePwdAgain->text();
	QString phone = ui.lineEditRegisterPagePhone->text();
	QString mail = ui.lineEditRegisterPageMail->text();

	//合法性
	bool flag = true;
	//用户名
	if (username.size() == 0)
	{
		ui.labelRegisterPageUser->setText("不可空！");
		flag = false;
	}
	else
	{
		sql.prepare("select count(*) from user where username = ?");
		sql.bindValue(0, username);
		if (sql.exec())
		{
			sql.next();
			if (sql.value(0).toInt() > 0)
			{
				ui.labelRegisterPageUser->setText("重复！");
				flag = false;
			}
		}
	}

	//密码
	if (password.size() == 0)
	{
		ui.labelRegisterPagePwd->setText("不可空！");
		flag = false;
	}
	if (pwdAgain.size() == 0)
	{
		ui.labelRegisterPagePwdAgain->setText("不可空！");
	}
	else
	{
		if (pwdAgain != password)
		{
			ui.labelRegisterPagePwdAgain->setText("两次输入密码不一致");
			flag = false;
		}
	}

	//电话
	if (phone.size() == 0)
	{
		ui.labelRegisterPagePhone->setText("不可空！");
		flag = false;
	}
	else
	{
		QRegExp rx("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
		if (!rx.exactMatch(phone))
		{
			ui.labelRegisterPagePhone->setText("格式错误");
			flag = false;
		}
	}
	//邮箱
	if (mail.size() == 0)
	{
		ui.labelRegisterPageMail->setText("不可空！");
		flag = false;
	}
	else
	{
		QRegExp rx("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
		if (!rx.exactMatch(mail))
		{
			ui.labelRegisterPageMail->setText("格式错误");
			flag = false;
		}
	}
	if (!flag)
	{
		return;
	}

	//注册时间
	QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString insertSql = QString("insert into user(username,password,regsiter_time,phone,email) values('%1','%2','%3','%4','%5')").arg(username).arg(password).arg(date).arg(phone).arg(mail);

	bool exec = this->m_pRegSqldb->execSql(insertSql);	//连接数据库

	if (exec)
	{
		//QMessageBox* box = new QMessageBox(QMessageBox::Information, tr("提示！"), tr("注册成功！"));
		QMessageBox::information(NULL, "提示！", "注册成功！");
		this->onBtnRegisterPageClear();


	}
}
//取消
void KRegisterPage::onBtnRegisterPageClear()
{
	ui.lineEditRegisterPageUser->clear();
	ui.lineEditRegisterPagePwd->clear();
	ui.lineEditRegisterPagePwdAgain->clear();
	ui.lineEditRegisterPagePhone->clear();
	ui.lineEditRegisterPageMail->clear();

	ui.labelRegisterPageUser->clear();
	ui.labelRegisterPagePwd->clear();
	ui.labelRegisterPagePwdAgain->clear();
	ui.labelRegisterPagePhone->clear();
	ui.labelRegisterPageMail->clear();

}
