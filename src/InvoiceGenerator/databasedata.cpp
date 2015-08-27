#include "databasedata.h"
#include <QObject>

DataBaseData::DataBaseData() : m_columndId(QObject::tr("id")), m_goodsNameColumn(QObject::tr("Name")),
    m_goodsTypeColumn(QObject::tr("Type")), m_goodsCategoryColumn(QObject::tr("Category")),
    m_goodsPriceColumn(QObject::tr("Price")), m_customerNameColumn(QObject::tr("Name")),
    m_customerRegionColumn(QObject::tr("Region")), m_customerMultiplierColumn(QObject::tr("Multiplier"))
{
}
