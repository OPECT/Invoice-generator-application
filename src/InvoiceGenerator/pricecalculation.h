#ifndef PRICECALCULATION_H
#define PRICECALCULATION_H

#include <QString>

class TableHandler;

class PriceCalculation
{
public:
    PriceCalculation(const TableHandler& goods);
    virtual ~PriceCalculation() { }

    virtual bool calculate(quint32 goodId, quint32 customerId, double& price) const = 0;

protected:
    bool getGoodPrice(quint32 goodId, double &price) const;

protected:
    const TableHandler& m_goodsTable;

    QString m_goodPriceColumn;
    QString m_goodIdColumn;
};

#endif // PRICECALCULATION_H
