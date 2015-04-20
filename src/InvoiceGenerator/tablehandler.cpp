#include "tablehandler.h"
#include <QSqlQuery>
#include <QSqlDatabase>

TableHandler::TableHandler(const QString &table, QSqlDatabase& db, QObject *parent) :
    QObject(parent), m_tableName(table), m_db(db)
{
}

bool TableHandler::select(const QString& criteria, const QString& filter, bool showUnique,
                          QList<QVariant> &result)
{
    QSqlQuery query(m_db);
    QString selectPart = "SELECT" + showUnique ? " DISTINCT " : " ";
    QString criteriaPart = criteria + " FROM " + m_tableName;
    QString filterPart = filter.isEmpty() ? "" : " WHERE " + filter;
    QString message = selectPart + criteriaPart + filterPart;
    bool bRes = query.exec(message);

    while (query.next()) {
        result.append(query.value(0));
    }
    return bRes;
}
