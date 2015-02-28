#ifndef GENERALINVOICEDATA_H
#define GENERALINVOICEDATA_H

#include <QDate>
#include <QString>

class GeneralInvoiceData
{
public:
    enum InvoiceType { IT_NONE, IT_SimpleInvoice };

public:
    GeneralInvoiceData();
    GeneralInvoiceData(const QDate &date, InvoiceType type, quint32 id, const QString &company, const QString &name,
                       const QString &secondName);

    const QDate& date() const { return m_date; }
    void date(const QDate& currentDate) { m_date = currentDate; }

    InvoiceType invoiceType() const { return m_type; }
    void invoiceType(InvoiceType type) { m_type = type; }

    quint32 invoiceId() const { return m_invoiceId; }
    void invoiceId(quint32 id) { m_invoiceId = id; }

    const QString& companyName() const { return m_companyName; }
    void companyName(const QString& name) { m_companyName = name; }

    const QString& traderName() const { return m_traderName; }
    void traderName(const QString& name) { m_traderName = name; }

    const QString& traderSecondName() const { return m_traderSecondName; }
    void traderSecondName(const QString& name) { m_traderSecondName = name; }

private:
    QDate m_date;
    InvoiceType m_type;
    quint32 m_invoiceId;
    QString m_companyName;
    QString m_traderName;
    QString m_traderSecondName;
};

#endif // GENERALINVOICEDATA_H
