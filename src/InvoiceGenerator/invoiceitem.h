#ifndef INVOICEITEM_H
#define INVOICEITEM_H

#include <QString>
#include "batypes.h"

class InvoiceItem
{
public:
    InvoiceItem();
    InvoiceItem(QString, quint32, GOOT_TYPE, double);

    void name(QString name) { m_name = name; }
    const QString& name() const { return m_name; }

    void quantity(quint32 qaunt) { m_quantity = qaunt; }
    quint32 quantity() const { return m_quantity; }

    void quantityType(GOOT_TYPE type) { m_quantType = type; }
    GOOT_TYPE quantityType() const { return m_quantType; }

    void goodPrice(double price) { m_goodPrice = price; }
    double goodPrice() const { return m_goodPrice; }

    double totalPrice() const { return m_goodPrice * m_quantity; }

private:
    QString m_name;
    quint32 m_quantity;
    GOOT_TYPE m_quantType;
    double m_goodPrice;
};

#endif // INVOICEITEM_H
