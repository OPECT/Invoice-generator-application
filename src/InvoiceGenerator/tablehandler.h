#ifndef TABLEHANDLER_H
#define TABLEHANDLER_H

#include <QString>
#include <QVariant>
#include <QList>

class QSqlDatabase;

class TableHandler : public QObject
{
    Q_OBJECT
public:
    explicit TableHandler(const QString& table, const QSqlDatabase &db, QObject *parent = 0);

    bool isTableExist() const;
    bool select(const QString& column, const QString& filter, bool showUnique, QList<QVariant> &result) const;

private:
    QString m_tableName;
    const QSqlDatabase &m_db;
};

#endif // TABLEHANDLER_H
