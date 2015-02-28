#include "generalinvoicedata.h"

GeneralInvoiceData::GeneralInvoiceData()
    : m_type(IT_NONE), m_invoiceId(0)
{
}

GeneralInvoiceData::GeneralInvoiceData(const QDate &date, InvoiceType type, quint32 id, const QString &company,
                                       const QString &name, const QString &secondName)
    : m_date(date), m_type(type), m_invoiceId(id), m_companyName(company), m_traderName(name),
      m_traderSecondName(secondName)
{
}
