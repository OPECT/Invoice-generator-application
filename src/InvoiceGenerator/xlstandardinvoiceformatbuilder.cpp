#include "xlstandardinvoiceformatbuilder.h"
#include "xlsstandardinvoicevalidator.h"
#include "errorreport.h"
#include "badefines.h"

#include <QDate>
#include <QStringList>

// XXX handle template file usage(make it hidden)
XLStandardInvoiceFormatBuilder::XLStandardInvoiceFormatBuilder(InvoiceDocumentWrapper &document,
                                                               ErrorReport &errorReporter, QString templateSheetName,
                                                               QObject *parent)
    : DocInvoiceBuilder(errorReporter, parent), m_document(document), m_isDocumentReady(false),
      m_isSheetReady(false), m_itemCount(0), m_rowOffset(XLSStandardInvoiceValidator::IIR_HEADER + 3),
      m_templateSheetName(templateSheetName)
{
}

XLStandardInvoiceFormatBuilder::~XLStandardInvoiceFormatBuilder()
{
}

bool XLStandardInvoiceFormatBuilder::createDocument(const QString &outputFileName)
{
    m_isSheetReady = false;
    m_isDocumentReady = m_document.create(true);
    if (!m_isDocumentReady)
    {
        reportError("Create Document Error: Can't create  document");
        return false;
    }

    if (!isTemplateValid())
    {
        m_isDocumentReady = false;
        reportError("Create Document Error: Invoice template is invalid");
        return false;
    }
    m_outputFile = outputFileName;
    return true;
}

bool XLStandardInvoiceFormatBuilder::addInvoicePage(const QString &supplier, const QString &recipient, quint32 id,
                                                    const QDate &date)
{
    QString invoiceSheetName = QString("Invoice %1").arg(id);

    if (!m_isDocumentReady)
    {
        reportError("Add Invoice Page Error: Document is not ready");
        return false;
    }

    if (!m_document.copySheetFromSource(m_templateSheetName, invoiceSheetName))
    {
        reportError("Add Invoice Page Error: Can't create invoice sheet");
        return false;
    }

    if (!m_document.changeCurrentSheet(invoiceSheetName))
    {
        m_document.deleteSheet(invoiceSheetName);
        reportError("Add Invoice Page Error: Can't switch to new invoice sheet");
        return false;
    }

    m_isSheetReady = false;
    if (!writeCellString(GDR_RECIPIENT, GDC_GENERAL, recipient) ||
        !writeCellDouble(GDR_INVOICE_ID, GDC_INVOICE_ID, id))
    {
        m_document.deleteSheet(invoiceSheetName);
        reportError("Add Invoice Page Error: Can't update new invoice with general data");
        return false;
    }

    if (!updateDate(date))
    {
        m_document.deleteSheet(invoiceSheetName);
        reportError("Add Invoice Page Error: Can't update date");
        return false;
    }

    m_itemCount = 0;
    m_isSheetReady = true;
    return true;
}

bool XLStandardInvoiceFormatBuilder::addInvoiceItem(const QString &name, const QString &type, double quantity,
                                                    double price, double summary)
{
    if (!m_isSheetReady)
    {
        reportError("Add Item Error: Sheet is not ready");
        return false;
    }

    if (m_itemCount >= MAX_INVOICE_ITEMS)
    {
        reportError("Add Item Error: Invoice is Full");
        return false;
    }

    if (!writeCellDouble(toDocumentRowIndex(m_itemCount), ICV_GOOD_ID, m_itemCount + 1) ||
        !writeCellString(toDocumentRowIndex(m_itemCount), ICV_GOOD_NAME, name) ||
        !writeCellString(toDocumentRowIndex(m_itemCount), ICV_GOOD_TYPE, type) ||
        !writeCellDouble(toDocumentRowIndex(m_itemCount), ICV_GOOD_QUANTITY, quantity) ||
        !writeCellDouble(toDocumentRowIndex(m_itemCount), ICV_GOOD_PRICE, price) ||
        !writeCellDouble(toDocumentRowIndex(m_itemCount), ICV_GOOD_TOTAL, summary))
    {
        return false;
    }

    m_itemCount++;
    return true;
}

bool XLStandardInvoiceFormatBuilder::addInvoideSummary()
{
    if (!m_isSheetReady)
    {
        reportError("Add Invoice Summary Error: Sheet is not ready");
        return false;
    }
    return true;
}

bool XLStandardInvoiceFormatBuilder::saveDocument(bool overwrite)
{
    if (!m_isDocumentReady)
    {
        reportError("Save Document Error: Document is not ready");
        return false;
    }

    if (m_outputFile.isEmpty())
    {
        reportError("Save Document Error: No output file name provided");
        return false;
    }

    if (!m_document.deleteSheet(m_templateSheetName))
    {
        reportError("Save Document Error: Can't delete Invoice Sheet Template");
        return false;
    }

    if (!m_document.save(m_outputFile, overwrite))
    {
        reportError("Save Document Error: Can't save invoice file");
        return false;
    }

    m_isDocumentReady = false;
    m_isSheetReady = false;
    return true;
}

bool XLStandardInvoiceFormatBuilder::updateDate(const QDate &date)
{
    QVariant data = m_document.readData(GDR_DATE, GDC_DATE);
    if (!data.isValid())
    {
        return false;
    }

    QString dateField = data.toString();
    quint32 dayStartIdx = dateField.indexOf("\"") + 1;
    quint32 dayEndIdx = dateField.indexOf("\"", dayStartIdx) - 1;

    dateField.replace(dayStartIdx, dayEndIdx - dayStartIdx + 1, QString::number(date.day()));

    quint32 monStartIdx = dateField.indexOf("_", 0);
    quint32 monEndIdx = dateField.indexOf(" ", monStartIdx);

    // XXX translate it!!!
    dateField.replace(monStartIdx, monEndIdx - monStartIdx, QDate::longMonthName(date.month()));

    quint32 yearStartIdx = dateField.indexOf("200", 0);
    quint32 yearEndIdx = dateField.indexOf("_", yearStartIdx);

    dateField.replace(yearStartIdx, yearEndIdx - yearStartIdx + 1, QString::number(date.year()));

    return writeCellString(GDR_DATE, GDC_DATE, dateField);
}

bool XLStandardInvoiceFormatBuilder::writeCellString(quint32 row, quint32 col, const QString &data)
{
    if (!m_isDocumentReady || !m_document.writeString(row, col, data))
    {
        reportError("Error while writing " + data);
        return false;
    }
    return true;
}

bool XLStandardInvoiceFormatBuilder::writeCellDouble(quint32 row, quint32 col, double data)
{
    if (!m_isDocumentReady || !m_document.writeDouble(row, col, data))
    {
        reportError("Error while writing " + QString::number(data));
        return false;
    }
    return true;
}

quint32 XLStandardInvoiceFormatBuilder::toDocumentRowIndex(quint32 itemCount) const
{
    return itemCount + m_rowOffset;
}

bool XLStandardInvoiceFormatBuilder::isTemplateValid() const
{
    XLSStandardInvoiceValidator templateValidator(m_document.templateFile());
    return templateValidator.validateSheet(m_templateSheetName);
}
