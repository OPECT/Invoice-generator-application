#include "invoiceitem.h"

InvoiceItem::InvoiceItem()
    : m_name("DefaultItem"), m_quantity(0), m_quantType(GT_KG), m_goodPrice(0)
{
}

InvoiceItem::InvoiceItem(QString name, quint32 quant, GOOT_TYPE quantType, double goodPrice)
    : m_name(name), m_quantity(quant), m_quantType(quantType), m_goodPrice(goodPrice)
{
}
