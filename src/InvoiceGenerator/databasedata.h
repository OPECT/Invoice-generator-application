#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QString>

class DataBaseData
{
public:
    DataBaseData();
    DataBaseData(const QString& customersTableName, const QString& goodsTableName, const QString& userName,
                 const QString& password, const QString& file);

    const QString& customersTableName() const { return m_customersTableName; }
    void customersTableName(const QString& name) { m_customersTableName = name; }

    const QString& goodsTableName() const { return m_goodsTableName; }
    void goodsTableName(const QString& name) { m_goodsTableName = name; }

    const QString& userName() const { return m_userName; }
    void userName(const QString& name) { m_userName = name; }

    const QString& password() const { return m_password; }
    void password(const QString& pwd) { m_password = pwd; }

    const QString& dataBaseFile() const { return m_dataBaseFile; }
    void dataBaseFile(const QString& file) { m_dataBaseFile = file; }

    const QString& goodNameColumn() const { return m_goodsNameColumn; }
    const QString& goodCategoryColumn() const { return m_goodsCategoryColumn; }
    const QString& customerNameColumn() const { return m_customerNameColumn; }
    const QString& customerRegionColumn() const { return m_customerRegionColumn; }

private:
    QString m_customersTableName;
    QString m_goodsTableName;
    QString m_userName;
    QString m_password;
    QString m_dataBaseFile;

    QString m_goodsNameColumn;
    QString m_goodsCategoryColumn;
    QString m_customerNameColumn;
    QString m_customerRegionColumn;
};

#endif // DATABASEDATA_H
