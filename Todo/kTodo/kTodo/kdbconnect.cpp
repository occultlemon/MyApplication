#include "kdbconnect.h"


//静态成员变量在类外初始化
KDBConnect* KDBConnect::m_pInstance = nullptr;

const static QString DB_NAME = "KTodoDB";
//默认构造
KDBConnect::KDBConnect(QObject* parent)
	: QObject(parent)
{
}

KDBConnect::~KDBConnect()
{
	this->m_database.close();
	qDebug() << "Disconnect to database";
}

//有参构造
KDBConnect::KDBConnect(QString dbName, QObject* parent) :QObject(parent)
{
	Q_UNUSED(parent);
	this->connectDB(dbName);
	//新建用户表
	this->createUserTable();
	//新建待办列表
	this->createTodoTable();
	//新建组别
	this->createGroupTable();

}

//连接数据库
bool KDBConnect::connectDB(QString dbName)
{
	//新建数据库
	this->m_database = QSqlDatabase::addDatabase("QSQLITE");
	//this->m_database.setDatabaseName("./KTodoDB.db");
	this->m_database.setDatabaseName(dbName.append(".db"));

	if (!m_database.open())
	{
		//日志：严重错误：数据库连接失败
		qCritical("Can't open database: %s(%s)", this->m_database.lastError().text().toLocal8Bit().data(), qt_error_string().toLocal8Bit().data());
		return false;
	}
	else
	{
		qDebug() << "Succeed to connect database";
	}
}

//执行sql语句
bool KDBConnect::execSql(QString sql)
{
	QSqlQuery query;

	if (!query.exec(sql))
	{
		qDebug() << "Failed to execSql: " << sql << ";" << query.lastError();	//debug已解决：Failed to execSql : "create table if not exists user(userid  INTEGER PRIMARY KEY ,username varchar(12) UNIQUE,password varchar(40),)"; QSqlError("1", "Unable to execute statement", "near \")\": syntax error")
		return false;
	}
	else
	{
		qDebug() << "sql execed !" << "(" << sql << ")";
		return true;
	}
}

//组合条件查询	--QVariant 可以保存很多Qt的数据类型
QSqlQuery KDBConnect::execQuery(QString sql, QVector<QVariant> args)
{
	QSqlQuery query;
	query.prepare(sql);
	for (int i = 0; i < args.size(); i++)
	{
		query.bindValue(i, args[i]);
	}
	if (!query.exec())
	{
		qDebug() << "Failed to execSql: " << sql << ";" << query.lastError();
		this->msgShow(query.lastError().text());
	}
	else
	{
		qDebug() << "sql execed !" << "(" << sql << ")";
	}
	return query;
}

QSqlDatabase KDBConnect::getDB()	//获取到sqldatabase
{
	return this->m_database;
}


//表格初始化
//用户表
void KDBConnect::createUserTable()
{
	QSqlQuery query;
	if (query.exec(QString("select count(*) from sqlite_master  where type='table' and name='user'")))
	{
		query.next();
		if (query.value(0).toInt() == 0)
		{
			this->execSql("create table if not exists user(userid  INTEGER PRIMARY KEY ,username varchar(12) UNIQUE, password varchar(40))");
			this->execSql("insert into user(username,password) values('wj','111')");
		}
	}
	else
	{
		this->msgShow(query.lastError().text());
		qDebug() << query.lastError();
	}
}

//消息提示
void KDBConnect::msgShow(QString message)
{
	QMessageBox* box = new QMessageBox(QMessageBox::Information, "消息！", message);
	box->exec();
}

//弹出窗口确认消息
bool KDBConnect::msgConfirmed(QString title, QString message)
{
	QMessageBox::StandardButton result = QMessageBox::question(NULL, title, message, QMessageBox::Yes | QMessageBox::No);
	switch (result)
	{
	case QMessageBox::Yes:
		qDebug() << "Yes";
		return true;
	case QMessageBox::No:
		qDebug() << "NO";
		return false;
	default:
		return false;
		break;
	}
}

//待办表
void KDBConnect::createTodoTable()
{
	QSqlQuery query;
	if (query.exec(QString("select count(*) from sqlite_master  where type='table' and name='todoList' ")))
	{
		query.next();
		if (query.value(0).toInt() == 0)
		{
			//待办事件id，组别id，创建时间（时间格式  '2010-08-05'），待办事件名称，级别，超时时间，设置重复，提醒时间，描述，地点，备注，完成人，是否完成，所属组）
			this->execSql("create table if not exists todoList(id  INTEGER PRIMARY KEY ,groupId INTEGER,createTime datetime,todoName varchar(20),todoLevel INTEGER,overTime datetime,again INTEGER,noticeTime datetime,intro varchar(20),local varchar(20),other varchar(20),finishPerson varchar(10),ifFinish INTEGER,groupName varchar(20))");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(1,2,'2023-05-15 8:00','第七周上课',2,'2023-05-15 18:00',2,'2023-05-15 7:00','学校','湖北大学','无','wj',1,'作业')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(2,1,'2023-05-20 12:20','出去约会',3,'2023-05-21 24:00',2,'2023-05-20 11:20','私人','小吃街','无','wj',1,'我的待办')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(3,3,'2023-06-30 15:00','实习',4,'2023-08-30 24:00',2,'2023-06-30 08:00','工作','光谷金山办公园区','无','wj',0,'工作')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(4,2,'2023-05-15 16:40','完成大作业',4,'2023-05-26 24:00',2,'2023-05-15 12:40','学校','湖北大学','无','wj',0,'作业')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(5,1,'2023-05-18 00:00','过生日',1,'2023-05-18 24:00',2,'2023-05-17 07:32','私人','家里','无','wj',0,'我的待办')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(6,1,'2023-05-25 00:00','这是一条以后的事项',2,'2023-07-18 24:00',1,'2023-06-17 07:32','测试','实验室','无','wj',0,'我的待办')");
			this->execSql("insert into todoList(id,groupId,createTime,todoName,todoLevel,overTime,again ,noticeTime ,intro ,local,other,finishPerson,ifFinish,groupName) values(7,1,'2023-05-25 00:00','七天内（根据系统时间判断）',3,'2023-06-02 24:00',1,'2023-06-01 07:32','测试','家里','无','wj',0,'我的待办')");
		}
	}
	else
	{
		this->msgShow(query.lastError().text());
		qDebug() << query.lastError();	//debug已解决：QSqlError("1", "Unable to execute statement", "unrecognized token: \"'user\"")		
	}
}
//组别表
void KDBConnect::createGroupTable()
{
	QSqlQuery query;
	if (query.exec(QString("select count(*) from sqlite_master where type='table' and name='groupList'")))
	{
		query.next();
		if (query.value(0).toInt() == 0)
		{
			//组别id，分组名称，该组内待办事项数量
			this->execSql("create table if not exists groupList(groupId  INTEGER PRIMARY KEY ,groupName varchar(20),groupCount INTEGER)");
			this->execSql("insert into groupList(groupId,groupName,groupCount) values(1,'我的待办',4)");
			this->execSql("insert into groupList(groupId,groupName,groupCount) values(2,'作业',2)");
			this->execSql("insert into groupList(groupId,groupName,groupCount) values(3,'工作',1)");
		}
	}
	else
	{
		this->msgShow(query.lastError().text());
		qDebug() << query.lastError();
	}
}

KDBConnect* KDBConnect::getInstance(QObject* parent)
{
	if (KDBConnect::m_pInstance == nullptr)
	{
		KDBConnect::m_pInstance = new KDBConnect(DB_NAME, parent);
	}
	return KDBConnect::m_pInstance;
}
