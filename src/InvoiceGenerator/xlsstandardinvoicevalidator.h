#ifndef XLSSTANDARDINVOICEVALIDATOR_H
#define XLSSTANDARDINVOICEVALIDATOR_H

#include "invoicetemplatevalidator.h"

class XLSStandardInvoiceValidator : public InvoiceTemplateValidator
{
public:
    enum GeneralDataColumn { GDC_GENERAL = 2, GDC_SUPPLIER_SIGNATURE = 2, GDC_INVOICE_ID = 3, GDC_DATE = 4,
                             GDC_TOTAL_COST = 7, GDC_RECIEVER_SIGNATURE = 7 };
    enum InvoiceItemRows { IIR_HEADER = 8, IIR_LAST = 52 };

public:
    XLSStandardInvoiceValidator(const QString &target);

    virtual bool validateSheet(const QString &sheetName);

private:
    const QString m_supplier;
    const QString m_reciever;
    const QString m_invoiceNumber;
    const QString m_date;

    const QString m_headerID;
    const QString m_headerGood;
    const QString m_headerType;
    const QString m_headerQuatity;
    const QString m_headerPrice;
    const QString m_headerSummary;
    const QString m_invoiceTotal;
    const QString m_supplierSignature;
    const QString m_recieverSignature;

    const quint32 m_maxID;
};

#endif // XLSSTANDARDINVOICEVALIDATOR_H
