#include "invoicedata.h"
#include <QListIterator>

InvoiceData::InvoiceData() :
    m_customerName(""), m_invoiceID(0), m_isLast(true)
{
}

InvoiceData::InvoiceData(QString name, quint32 id, bool isLast) :
    m_customerName(name), m_invoiceID(id), m_isLast(isLast)
{
}

double InvoiceData::getTotalSummary()
{
    QListIterator<InvoiceItem> iter(m_items);
    double sum = 0;

    while (iter.hasNext())
    {
        sum += iter.next().totalPrice();
    }
    return sum;
}
