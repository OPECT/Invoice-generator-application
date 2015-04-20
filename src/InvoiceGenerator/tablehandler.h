#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QList>

class QSqlDatabase;

class TableHandler : public QObject
{
    Q_OBJECT
public:
    explicit TableHandler(const QString& table, QSqlDatabase &db, QObject *parent = 0);

    bool select(const QString& column, const QString& filter, bool showUnique, QList<QVariant> &result);
private:
    QString m_tableName;
    QSqlDatabase &m_db;
};

#endif // TABLEHANDLER_H
