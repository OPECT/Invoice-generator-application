#include "pricecalculationwithdiscount.h"
#include "tablehandler.h"

#include <QList>
#include <QVariant>

PriceCalculationWithDiscount::PriceCalculationWithDiscount(const TableHandler &goods, const TableHandler &customers)
    : PriceCalculation(goods), m_customersTable(customers), m_customerDiscountColumn("discount"),
      m_customerIdColumn("id")
{
}

bool PriceCalculationWithDiscount::calculate(quint32 goodId, quint32 customerId, double& price) const
{
    double goodPrice = 0;
    if (!getGoodPrice(goodId, goodPrice))
    {
        return false;
    }

    QString customerFilter = m_customerIdColumn + " = \"" + QString::number(customerId) + "\"";

    QList<QVariant> discountList;
    if (!m_customersTable.select(m_customerDiscountColumn, customerFilter, false, discountList))
    {
        return false;
    }
    if (discountList.count() != 1)
    {
        return false;
    }

    bool convertionResult = false;
    quint32 customerDiscount = discountList.first().toUInt(&convertionResult);

    if (!convertionResult)
    {
        return false;
    }

    if (!checkDiscount(customerDiscount))
    {
        return false;
    }


    double customerDiscountValue = goodPrice * customerDiscount / 100;
    price = goodPrice - customerDiscountValue;

    return true;
}

bool PriceCalculationWithDiscount::checkDiscount(quint32 discount) const
{
    return discount <= 100;
}
