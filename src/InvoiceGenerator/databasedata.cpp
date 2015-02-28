#include "databasedata.h"

DataBaseData::DataBaseData()
{
}

DataBaseData::DataBaseData(const QString& customersTableName, const QString& goodsTableName, const QString& userName,
             const QString& password, const QString& file)
    : m_customersTableName(customersTableName), m_goodsTableName(goodsTableName), m_userName(userName),
      m_password(password), m_dataBaseFile(file)
{
}
