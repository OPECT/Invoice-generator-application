#ifndef DOCSTANDARDXLFORMATHANDLER_H
#define DOCSTANDARDXLFORMATHANDLER_H

#include "docinvoicebuilder.h"
#include "invoicedocumentwrapper.h"

class XLStandardInvoiceFormatBuilder : public DocInvoiceBuilder
{
public:
    enum ItemColumnValue { ICV_GOOD_ID = 1, ICV_GOOD_NAME = 2, ICV_GOOD_TYPE = 6, ICV_GOOD_QUANTITY = 7,
                           ICV_GOOD_PRICE = 8, ICV_GOOD_TOTAL = 9 };
    enum GeneralDataRow { GDR_SUPPLIER = 4, GDR_RECIPIENT = 5, GDR_INVOICE_ID = 6, GDR_DATE = 7 };
    enum GeneralDataColumn { GDC_GENERAL = 4, GDC_INVOICE_ID = 7, GDC_DATE = 4 };

public:
    XLStandardInvoiceFormatBuilder(InvoiceDocumentWrapper &document, ErrorReport &errorReporter,
                                   QString templateSheetName = "Invoice", QObject *parent = 0);
    virtual ~XLStandardInvoiceFormatBuilder();

    virtual bool createDocument(const QString &outputFileName);
    virtual bool addInvoicePage(const QString &supplier, const QString &recipient, quint32 id, const QDate &date);
    virtual bool addInvoiceItem(const QString &name, const QString &type, double quantity, double price,
                                double summary);
    virtual bool addInvoideSummary();
    virtual bool saveDocument(bool overwrite);

    quint32 maxItemsCount() { return m_maxItemNumber; }
    quint32 currentItemsCount() { return m_itemCount; }

private:
    quint32 toDocumentRowIndex(quint32 itemCount) const;
    bool isTemplateValid() const;

    bool createNewSheet(const QString &srcName, const QString &dstName);
    bool updateDate(const QDate &date);
    bool writeCellString(quint32 row, quint32 col, const QString &data);
    bool writeCellDouble(quint32 row, quint32 col, double data);

private:
    // XXX Check that selected sheet in m_document was not chagned outside of the builder
    InvoiceDocumentWrapper &m_document;
    bool m_isDocumentReady;
    bool m_isSheetReady;

    quint32 m_itemCount;
    quint32 m_maxItemNumber;
    quint32 m_rowOffset;

    QString m_templateSheetName;
};

#endif // DOCSTANDARDXLFORMATHANDLER_H
