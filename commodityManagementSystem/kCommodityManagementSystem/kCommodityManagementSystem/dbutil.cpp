#include "dbutil.h"

bool DBUtil::connectDB(QString dbName)
{
	//建立并打开数据库
	this->m_database = QSqlDatabase::addDatabase("QSQLITE");
	this->m_database.setDatabaseName(dbName.append(".db"));
	bool ok = this->m_database.open();
	if (!ok)
	{
		qDebug() << "Error: Failed to connect database." << this->m_database.lastError();
	}
	else
	{
		qDebug() << "Success to connect database";
	}
	return ok;
}

DBUtil::DBUtil(QString dbName)
{
	this->connectDB(dbName);
}

bool DBUtil::execSql(QString sql)
{
	QSqlQuery sqlQuery;
	bool execFlag = sqlQuery.exec(sql);

	if (!execFlag)
	{
		qDebug() << "Error: Failed to execSql" << "(" << sql << ")" << sqlQuery.lastError();
	}
	else
	{
		qDebug() << "Sql execed !" << "(" << sql << ")";
	}
	return execFlag;
}

//数据库查询语句（parms: 查询语句，查询对象）
QSqlQuery DBUtil::execQuery(QString sql, QVector<QString> args)
{
	QSqlQuery sqlQuery;
	sqlQuery.prepare(sql);
	for (int i = 0; i < args.size(); i++)
	{
		sqlQuery.bindValue(i, args[i]);
	}
	if (!sqlQuery.exec())
	{
		qDebug() << "Error: failed to execSql" << "(" << sql << ")" << sqlQuery.lastError();
	}
	else
	{
		qDebug() << "Sql execed !" << "(" << sql << ")";
	}
	return sqlQuery;
}

QSqlDatabase DBUtil::getDB()
{
	return this->m_database;
}


DBUtil::~DBUtil()
{
	this->m_database.close();
	qDebug() << "Disconnect to database";
}
