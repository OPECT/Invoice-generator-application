#ifndef INVOICEITEM_H
#define INVOICEITEM_H

#include <QString>

class InvoiceItem
{
public:
    enum GOOD_QUANTITY_TYPE { GQT_NONE, GQT_KG, GQT_NUM };

public:
    InvoiceItem();
    InvoiceItem(QString, quint32, GOOD_QUANTITY_TYPE, double);

    void name(QString name) { m_name = name; }
    const QString& name() const { return m_name; }

    void quantity(quint32 qaunt) { m_quantity = qaunt; }
    quint32 quantity() const { return m_quantity; }

    void quantityType(GOOD_QUANTITY_TYPE type) { m_quantType = type; }
    GOOD_QUANTITY_TYPE quantityType() const { return m_quantType; }

    void goodPrice(double price) { m_goodPrice = price; }
    double goodPrice() const { return m_goodPrice; }

    double totalPrice() const { return m_goodPrice * m_quantity; }

private:
    QString m_name;
    quint32 m_quantity;
    GOOD_QUANTITY_TYPE m_quantType;
    double m_goodPrice;
};

#endif // INVOICEITEM_H
