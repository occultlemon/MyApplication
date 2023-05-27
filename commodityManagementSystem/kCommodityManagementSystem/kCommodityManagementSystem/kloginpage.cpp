#include "kloginpage.h"

const static QString DB_NAME = "shop";
KLoginPage::KLoginPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//连接数据库
	this->m_pSqldb = new DBUtil(DB_NAME);
	//初始化表格
	this->createUserTable();	//用户表
	this->createCategoryTable();	//类别表
	this->createGoodsTable();	//商品表
	this->createRecordTable();	//销售记录表

	(void)connect(ui.btnLoginPageClear, &QPushButton::clicked, this, &KLoginPage::onBtnLoginPageClearClicked);
	(void)connect(ui.btnLoginPageLogin, &QPushButton::clicked, this, &KLoginPage::onBtnLoginPageLoginClicked);

}

KLoginPage::~KLoginPage()
{
	//回滚数据库
	delete this->m_pSqldb;

}


//建立用户表
bool KLoginPage::createUserTable()
{
	QSqlQuery sql;
	if (sql.exec(QString("select count(*) from sqlite_master  where type='table' and name='user'")))
	{
		sql.next();
		if (sql.value(0).toInt() == 0)
		{
			bool cr = this->m_pSqldb->execSql("create table if not exists user(userid  INTEGER PRIMARY KEY ,username varchar(12) UNIQUE,password varchar(40),phone varchar(40),email varchar(40),regsiter_time datetime)");//时间格式  '2010-08-05'
			this->m_pSqldb->execSql("insert into user(username,password,phone,email,regsiter_time) values('user1','1','18790115022','wj5022@qq.com','2023-05-09 12:22')");
			return(cr);
		}
	}
	else
	{
		qDebug() << sql.lastError();
	}
}

//建立类别表
bool KLoginPage::createCategoryTable()
{
	QSqlQuery sql;
	if (sql.exec(QString("select count(*) from sqlite_master  where type='table' and name='category'")))
	{
		sql.next();
		if (sql.value(0).toInt() == 0)
		{
			bool cr = this->m_pSqldb->execSql("create table if not exists category(categoryid  INTEGER PRIMARY KEY ,category_name varchar(10))");
			this->m_pSqldb->execSql("insert into category(category_name) values('服装')");
			this->m_pSqldb->execSql("insert into category(category_name) values('食品')");
			this->m_pSqldb->execSql("insert into category(category_name) values('电子产品')");
			this->m_pSqldb->execSql("insert into category(category_name) values('其他')");
			return(cr);
		}
	}
	else
	{
		qDebug() << sql.lastError();
	}
}

//建立商品表
bool KLoginPage::createGoodsTable()
{
	QSqlQuery sql;
	if (sql.exec(QString("select count(*) from sqlite_master  where type='table' and name='good'")))
	{
		sql.next();
		if (sql.value(0).toInt() == 0)
		{

			bool cr = this->m_pSqldb->execSql("create table if not exists good(goodid  INTEGER PRIMARY KEY ,categoryid int,category_name varchar(10),good_name varchar(40),sell_in real,sell_out real,good_numb int,good_intro varchar(50),good_pict varchar(30))");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('1','服装','MLB FOG外套',127.00,228.00,100,'MLB FOG官方夹克男士2023新款情侣宽松潮牌刺绣棒球服休闲外套',':/KMainWindow/images/yifu1.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('2','食品','桃酥',15.00,28.00,100,'南宋胡记吴山传统桃酥老式手工核桃酥杭州特产糕点心休闲零食小吃',':/KMainWindow/images/shipin1.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('3','电子产品','三星Galaxy S23+',5849.00,6999.00,100,'【至高赠Buds2 Pro耳机】Samsung/三星Galaxy S23+ 5G智能手机拍照游戏官方旗舰正品 第二代骁龙8超视觉夜拍',':/KMainWindow/images/dianzichanpin1.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('4','其他','帐篷',43.00,79.00,100,'帐篷户外黑胶便携式折叠自动野营野餐过夜沙滩帐露营帐篷用品装备',':/KMainWindow/images/qita1.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('1','服装','GAP卫衣',169.00,279.00,100,'Gap男女装春季美式复古LOGO卫衣853131运动连帽开衫户外外套',':/KMainWindow/images/yifu2.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('2','食品','蛋白棒',25.00,38.00,100,'乳清威化蛋白棒减低o0代餐饱腹健身能量棒解馋卡脂零食品夹心饼干',':/KMainWindow/images/shipin2.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('3','电子产品','联想拯救者Y7000P 2023',6798.00,7999.00,100,'【新品上市】联想拯救者Y7000P 2023 13代酷睿i5/i7 16英寸电竞游戏本笔记本电脑 大学生编程办公ps设计电脑',':/KMainWindow/images/dianzichanpin2.png')");
			this->m_pSqldb->execSql("insert into good(categoryid,category_name,good_name,sell_in,sell_out,good_numb,good_intro,good_pict) "
				"values('4','其他','按摩椅',4888.00,6666.00,100,'ROTAI/荣泰A36按摩椅家用全身揉捏全自动小型太空舱按摩沙发椅',':/KMainWindow/images/qita2.png')");
			return(cr);

		}
	}
	else
	{
		qDebug() << sql.lastError();
	}
}

//建立销售记录表
bool KLoginPage::createRecordTable()
{
	QSqlQuery sql;
	if (sql.exec(QString("select count(*) from sqlite_master  where type='table' and name='sell'")))
	{
		sql.next();
		if (sql.value(0).toInt() == 0)
		{
			bool cr = this->m_pSqldb->execSql("create table if not exists sell(sellid  varchar(40) PRIMARY KEY ,sell_time varchar(10),sell_money real,operator varchar(10))");
			this->m_pSqldb->execSql("insert into sell(sellid,sell_time,sell_money,operator) values('P230513-29cb-78sd','2023-05-09 12:22',228.00,'wangjie')");
			return(cr);
		}
	}
	else
	{
		qDebug() << sql.lastError();
	}
}

//设置登录图片
void KLoginPage::setIconLogin()
{
	QAction* userAction = new QAction(this);
	userAction->setIcon(QIcon(":/KMainWindow/images/login.png"));
	ui.lineEditLoginPageUser->addAction(userAction, QLineEdit::LeadingPosition);
	QAction* pwdAction = new QAction(this);
	pwdAction->setIcon(QIcon(":/KMainWindow/images/pwd.png"));
	ui.lineEditLoginPagePwd->addAction(pwdAction, QLineEdit::LeadingPosition);

}

//登录按钮
void KLoginPage::onBtnLoginPageLoginClicked()
{
	ui.labelLoginPageUser->clear();
	ui.labelLoginPagePwd->clear();
	if (ui.lineEditLoginPageUser->text().size() == 0)
	{
		ui.labelLoginPageUser->setText("不可空！");
		return;
	}
	if (ui.lineEditLoginPagePwd->text().size() == 0)
	{
		ui.labelLoginPagePwd->setText("不可空！");
		return;
	}
	//获取用户名和密码
	QString username = ui.lineEditLoginPageUser->text();
	QString pwd = ui.lineEditLoginPagePwd->text();


	//QSqlQuery query;
	//query.prepare("select count(*) from user where username = ? and password = ?;");
	//query.bindValue(0, username);
	//query.bindValue(1, pwd);
	//query.exec();
	//int rowCount = 0;
	//while (query.next())
	//{
	//	rowCount++;
	//}
	//if (rowCount > 0)
	//{
	//	if (rowCount == 1)
	//	{
	//		QString path = "./user.ini";
	//		QSettings* config = new QSettings(path, QSettings::IniFormat);
	//		config->beginGroup("config");
	//		config->setValue("uid", username);
	//		config->setValue("upw", pwd);
	//		config->endGroup();
	//
	//		//登录成功:进入下一页
	//		this->m_user["username"] = username;
	//		this->m_user["password"] = pwd;
	//		//这里进入管理系统主页面
	//		this->m_pMainWindow = new KMainWindow(nullptr, this->m_pSqldb, this->m_user);
	//		//绑定信号
	//		(void)connect(this->m_pMainWindow, &KMainWindow::signalCloseMainWindow, this, &KLoginPage::show);
	//		this->m_pMainWindow->show();
	//		this->hide();
	//	}
	//	else
	//	{
	//		QMessageBox msg;
	//		msg.setText("登录失败，异常查询结果");
	//		msg.exec();
	//	}
	//}
	//else
	//{
	//	//登录失败
	//	QMessageBox msg;
	//	msg.setText("登录失败，错误的用户名或密码！");
	//	msg.exec();
	//}

	//sql
	QString loginSql = "select count(*) from user where username = ?";
	//用户是否存在
	QVector<QString> argUser;
	argUser.push_back(username);
	qDebug() << argUser.size();
	QSqlQuery query = this->m_pSqldb->execQuery(loginSql, argUser);	//匹配数据库
	query.next();
	qDebug() << query.value(0);
	if (query.value(0).toInt() > 0)		//用户存在	则查询密码
	{
		//loginSql.append(" and password = ?");
		QString loginAllSql = "select count(*) from user where username = ? and password = ?";
		QVector<QString> argPwd;
		argPwd.push_back(username);
		argPwd.push_back(pwd);
		query = this->m_pSqldb->execQuery(loginAllSql, argPwd);
		query.next();
		if (query.value(0).toInt() > 0)	//检查密码
		{
			this->hide();
			//登录成功:进入下一页
			this->m_user["username"] = username;
			this->m_user["password"] = pwd;
			//这里进入管理系统主页面
			this->m_pMainWindow = new KMainWindow(nullptr, this->m_pSqldb, this->m_user);
			//绑定信号
			(void)connect(this->m_pMainWindow, &KMainWindow::signalCloseMainWindow, this, &KLoginPage::show);
			this->m_pMainWindow->show();
		}
		else   //密码错误，弹窗
		{
			QMessageBox::information(NULL, "提示！", "请输入正确的口令！");
		}
	}
	else  //用户不存在，弹窗
	{
		QMessageBox::information(NULL, "提示！", "用户不存在！");
	}
}

//清除按钮
void KLoginPage::onBtnLoginPageClearClicked()
{
	ui.lineEditLoginPagePwd->clear();
	ui.lineEditLoginPageUser->clear();
}


