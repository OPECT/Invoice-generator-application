#include "databasemanager.h"
#include "tablehandler.h"

#include <QStringList>
#include <QSqlQuery>
#include <QString>

DataBaseManager::DataBaseManager() : m_isDBReady(false)
{
}

DataBaseManager::~DataBaseManager()
{
}

bool DataBaseManager::openDB(const QString& type, const QString& host, const QString& name,const QString& user,
              const QString& password)
{
    if (m_isDBReady)
    {
        return false;
    }

    m_db = QSqlDatabase::addDatabase(type);
    m_db.setHostName(host);
    m_db.setDatabaseName(name);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open())
    {
        return false;
    }

    m_isDBReady = true;
    return true;
}

bool DataBaseManager::createTable(const QString& table, const QStringList &tableAttr)
{
    if (!m_isDBReady)
    {
        return false;
    }

    QSqlQuery query(m_db);
    return query.exec(QObject::tr("create table %1 (%2)").arg(table).arg(tableAttr.join(", ")));
}

bool DataBaseManager::isTableExist(const QString& table) const
{
    if (!m_isDBReady)
    {
        return false;
    }

    return TableHandler(table, m_db).isTableExist();
}
