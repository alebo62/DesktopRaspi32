#ifndef DATABASEWRITER_H
#define DATABASEWRITER_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDateTime>
#include "mainwindow.h" //  for Record struct

struct Record;
/*
    QDateTime m_date;
    int m_who;
    int m_whoom;
    int m_type;
 */

class DataBaseWriter : public QObject
{
	Q_OBJECT

	QSqlQuery  query;

	QSqlDatabase  db;

	QDateTime dtime;

	void addDataToDb(const Record& rec);

public:
	explicit DataBaseWriter(QObject *parent = nullptr);

	static bool createConnection();
signals:
};

#endif // DATABASEWRITER_H
