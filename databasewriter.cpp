#include "databasewriter.h"
#include <QDebug>

DataBaseWriter::DataBaseWriter(QObject *parent) : QObject{parent} {
	QString str = "CREATE TABLE  IF NOT EXISTS addressbook("
	              "dt    DATETIME KEY NOT NULL,"
	              "who   INTEGER ,"
	              "whoom INTEGER , "
	              "type  INTEGER , "
	              "time  TEXT , "
	              "audio BLOB "
	              ");";

	if (!query.exec(str)) {
		qDebug() << "Unable to  create  à  tàblå";
	}
}

bool DataBaseWriter::createConnection() {
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	db.setDatabaseName("addressbook");
	db.setUserName("elton");
	db.setHostName("epica");
	db.setPassword("password");

	if (!db.open()) {
		qDebug() << "Cannot  open  database:" << db.lastError();
		return false;
	}
	else
		qDebug() << "OK!";

	//QStringList lst = db.tables();
	//qDebug() << lst.size();
	// foreach (QString str, lst) {
	//     qDebug() << "Òàblå:" << str;
	// }
	return true;
}

void DataBaseWriter::addDataToDb(const Record &rec) {
	query.prepare("INSERT  INTO  addressbook  ( dt, who, whoom, type, time, audio)  \
	               VALUES(:dt, :who,  :whoom,  :type, :time, :audio);");
	// compress();
	query.bindValue(":dt", rec.m_date.toString("yyyy-MM-dd hh:mm:ss"));
	query.bindValue(":who", rec.m_who);
	query.bindValue(":whoom", rec.m_whoom);
	query.bindValue(":type", rec.m_type);
	query.bindValue(":time", QString::number(rec.mic_buf.length() / 16000) + "sec.");
	query.bindValue(":audio", rec.mic_buf);

	if (!query.exec()) {
		qDebug() << "Unable to  make  insert  operation";
	}
}
