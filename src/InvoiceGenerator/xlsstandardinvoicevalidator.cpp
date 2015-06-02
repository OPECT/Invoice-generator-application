#include "xlsstandardinvoicevalidator.h"
#include "xlsdocumentwrapper.h"
#include "xlstandardinvoiceformatbuilder.h"
#include <QFile>

XLSStandardInvoiceValidator::XLSStandardInvoiceValidator(const QString &target) : InvoiceTemplateValidator(target),
    m_supplier("Постачальник"), m_reciever("Одержувач"), m_invoiceNumber("Видаткова накладна №"),
    m_date("від \"     \" _____________  200_ р."), m_headerID("№ п/п"), m_headerGood("Товар"), m_headerType("Од.вим."),
    m_headerQuatity("Кількість"), m_headerPrice("Ціна"), m_headerSummary("Сума"), m_invoiceTotal("Разом:"),
    m_supplierSignature("Відвантажив(ла)______________________"),
    m_recieverSignature("Отримав(ла) ______________________________"),
    m_maxID(42)
{
}

bool XLSStandardInvoiceValidator::validateSheet(const QString &sheetName)
{
    if (!QFile::exists(m_targetFile))
    {
        return false;
    }

    XLSDocumentWrapper doc(m_targetFile);

    if (!doc.create(true))
    {
        return false;
    }

    if (!doc.changeCurrentSheet(sheetName))
    {
        return false;
    }

    QVariant data = doc.readData(XLStandardInvoiceFormatBuilder::GDR_SUPPLIER, GDC_GENERAL);
    if (!data.isValid() || data.toString() != m_supplier)
    {
        return false;
    }

    data = doc.readData(XLStandardInvoiceFormatBuilder::GDR_RECIPIENT, GDC_GENERAL);
    if (!data.isValid() || data.toString() != m_reciever)
    {
        return false;
    }

    data = doc.readData(XLStandardInvoiceFormatBuilder::GDR_INVOICE_ID, GDC_INVOICE_ID);
    if (!data.isValid() || data.toString() != m_invoiceNumber)
    {
        return false;
    }

    data = doc.readData(XLStandardInvoiceFormatBuilder::GDR_DATE, GDC_DATE);
    if (!data.isValid() || data.toString() != m_date)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID);
    if (!data.isValid() || data.toString() != m_headerID)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME);
    if (!data.isValid() || data.toString() != m_headerGood)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TYPE);
    if (!data.isValid() || data.toString() != m_headerType)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_QUANTITY);
    if (!data.isValid() || data.toString() != m_headerQuatity)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_PRICE);
    if (!data.isValid() || data.toString() != m_headerPrice)
    {
        return false;
    }

    data = doc.readData(IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TOTAL);
    if (!data.isValid() || data.toString() != m_headerSummary)
    {
        return false;
    }

    data = doc.readData(IIR_LAST, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID);
    if (!data.isValid() || data.toUInt() != m_maxID)
    {
        return false;
    }

    data = doc.readData(IIR_LAST + 1, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID);
    if (data.isValid())
    {
        return false;
    }

    data = doc.readData(IIR_LAST + 1, GDC_TOTAL_COST);
    if (!data.isValid() || data.toString() != m_invoiceTotal)
    {
        return false;
    }

    data = doc.readData(IIR_LAST + 3, GDC_SUPPLIER_SIGNATURE);
    if (!data.isValid() || data.toString() != m_supplierSignature)
    {
        return false;
    }

    data = doc.readData(IIR_LAST + 3, GDC_RECIEVER_SIGNATURE);
    if (!data.isValid() || data.toString() != m_recieverSignature)
    {
        return false;
    }

    return true;
}
