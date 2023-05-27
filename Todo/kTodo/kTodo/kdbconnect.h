/*
══════════════════════════════════════╗
	@filename:		kdbconnect.h
	@describe:		数据库
	@editor:		wangjie
	@time:			2023/5/16
══════════════════════════════════════╣
*/
#ifndef __KDBCONNECT_H__
#define __KDBCONNECT_H__

#pragma execution_character_set("utf-8")
#include <QObject>
#include<qsqlquery.h>
#include<qsqldatabase.h>
#include<qstring.h>
#include<qvector.h>
#include<qlist.h>
#include<qdebug.h>
#include<qsqlerror.h>
#include<qlogging.h>
#include<qmessagebox.h>
#include<qvariant.h>

class KDBConnect : public QObject
{
	Q_OBJECT

public:
	//静态局部变量的懒汉单例
	static KDBConnect* getInstance(QObject*);

	bool connectDB(QString dbName);	//连接数据库
	bool execSql(QString sql);	//执行sql语句
	QSqlQuery execQuery(QString sql, QVector<QVariant> args);	//组合条件查询
	QSqlDatabase getDB();	//获取到sqldatabase

	//表格初始化
	void createUserTable();	//用户表
	void createTodoTable();	//待办表
	void createGroupTable();	//组别表

	//常用
	void msgShow(QString message);	//消息提示
	bool msgConfirmed(QString title, QString message);	//弹出窗口确认消息

private:
	//禁止外部构造
	KDBConnect(QString, QObject*);
	KDBConnect(QObject*);
	//禁止外部析构
	~KDBConnect();
	static KDBConnect* m_pInstance;		//单例模式静态局部变量
	QSqlDatabase m_database;	//数据库
};

#endif // !__KDBCONNECT_H__
