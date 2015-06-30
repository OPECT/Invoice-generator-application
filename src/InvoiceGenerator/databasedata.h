#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QString>

class DataBaseData
{
public:
    DataBaseData();

    const QString& userName() const { return m_userName; }
    void userName(const QString& name) { m_userName = name; }

    const QString& password() const { return m_password; }
    void password(const QString& pwd) { m_password = pwd; }

    const QString& dataBaseFile() const { return m_dataBaseFile; }
    void dataBaseFile(const QString& file) { m_dataBaseFile = file; }

    const QString& idColumn() const { return m_columndId; }
    const QString& goodNameColumn() const { return m_goodsNameColumn; }
    const QString& goodTypeColumn() const { return m_goodsTypeColumn; }
    const QString& goodCategoryColumn() const { return m_goodsCategoryColumn; }
    const QString& goodPriceColumn() const { return m_goodsPriceColumn; }
    const QString& customerNameColumn() const { return m_customerNameColumn; }
    const QString& customerRegionColumn() const { return m_customerRegionColumn; }
    const QString& customerMultiplierColumn() const { return m_customerMultiplierColumn; }

private:
    QString m_userName;
    QString m_password;
    QString m_dataBaseFile;

    QString m_columndId;
    QString m_goodsNameColumn;
    QString m_goodsTypeColumn;
    QString m_goodsCategoryColumn;
    QString m_goodsPriceColumn;
    QString m_customerNameColumn;
    QString m_customerRegionColumn;
    QString m_customerMultiplierColumn;
};

#endif // DATABASEDATA_H
