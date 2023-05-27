/*
══════════════════════════════════════╗
	filename:	dbutil.h
	describe:	数据库基类
	editor:		wangjie
	time:		2023/5/9
══════════════════════════════════════╣
*/
#ifndef DBUTIL_H
#define DBUTIL_H
#define IN
#define OUT

#include <QObject>
#include<qstring.h>
#include<qdebug.h>
#include<qmap.h>
#include<qsqldatabase.h>
#include<qsqlerror.h>
#include<qsqlquery.h>
#include<qvector.h>


class DBUtil
{
public:
	DBUtil(QString);
	//DBUtil();

	bool connectDB(QString);
	bool execSql(QString);

	QSqlQuery execQuery(QString sql, QVector<QString> args);
	QSqlDatabase getDB();
	~DBUtil();

private:
	QSqlDatabase m_database;
};
#endif // !DBUTIL_H