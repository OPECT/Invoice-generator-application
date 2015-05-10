#include "pricecalculation.h"
#include "tablehandler.h"

#include <QList>
#include <QVariant>

PriceCalculation::PriceCalculation(const TableHandler& goods) : m_goodsTable(goods), m_goodPriceColumn("price"),
    m_goodIdColumn("id")
{
}

bool PriceCalculation::getGoodPrice(quint32 goodId, double &price) const
{
    QString goodFilter = m_goodIdColumn + " = \"" + QString::number(goodId) + "\"";

    price = 0;
    QList<QVariant> priceList;
    if (!m_goodsTable.select(m_goodPriceColumn, goodFilter, false, priceList))
    {
        return false;
    }
    if (priceList.count() != 1)
    {
        return false;
    }

    bool convertionResult = false;
    double goodPrice = priceList.first().toDouble(&convertionResult);

    if (!convertionResult)
    {
        return false;
    }
    price = goodPrice;
    return true;
}
