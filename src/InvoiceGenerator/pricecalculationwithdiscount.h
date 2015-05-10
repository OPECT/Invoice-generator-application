#ifndef PRICECALCULATIONWITHDISCOUNT_H
#define PRICECALCULATIONWITHDISCOUNT_H

#include "pricecalculation.h"

class PriceCalculationWithDiscount : public PriceCalculation
{
public:
    PriceCalculationWithDiscount(const TableHandler& goods, const TableHandler& customers);
    virtual ~PriceCalculationWithDiscount() { }

    virtual bool calculate(quint32 goodId, quint32 customerId, double& price) const;

private:
    bool checkDiscount(quint32 discount) const;

private:
    const TableHandler& m_customersTable;

    QString m_customerDiscountColumn;
    QString m_customerIdColumn;
};

#endif // PRICECALCULATIONWITHDISCOUNT_H
