#ifndef INVOICEDATA_H
#define INVOICEDATA_H

#include "invoiceitem.h"
#include "batypes.h"
#include <QList>
#include <QString>

class InvoiceData
{
public:
    InvoiceData();
    InvoiceData(QString name, quint32 id, bool isLast = true);

    void customerName(QString name) { m_customerName = name; }
    const QString& customerName() const { return m_customerName; }

    void invoiceID(quint32 id) { m_invoiceID = id; }
    quint32 invoiceID() const { return m_invoiceID; }

    void setLast(bool last) { m_isLast = last; }
    bool isLast() const { return m_isLast; }

    void addItem(const InvoiceItem &item) { m_items.append(item); }
    const InvoiceDataList& getGoodsList() const { return m_items; }

    double getTotalSummary();

private:
    InvoiceDataList m_items;
    QString m_customerName;
    quint32 m_invoiceID;
    bool m_isLast;
};

#endif // INVOICEDATA_H
