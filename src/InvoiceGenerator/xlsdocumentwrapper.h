#ifndef XLSDOCUMENTWRAPPER_H
#define XLSDOCUMENTWRAPPER_H

#include "invoicedocumentwrapper.h"
#include <QtXlsx>
#include <QStringList>

class XLSDocumentWrapper : public InvoiceDocumentWrapper
{
public:
    XLSDocumentWrapper(const QString &templateFile);
    ~XLSDocumentWrapper();

    virtual bool create(bool overwrite = false);
    virtual bool copySheetFromSource(const QString &srcName, const QString &dstName);
    virtual bool changeCurrentSheet(const QString &sheetName);
    virtual bool deleteSheet(const QString &name);
    virtual bool save(const QString& name, bool overwrite = false);

    virtual bool writeString(quint32 row, quint32 col, const QString &data);
    virtual bool writeDouble(quint32 row, quint32 col, double data);
    virtual bool write(quint32 row, quint32 col, const QVariant &data);
    virtual QVariant readData(quint32 row, quint32 col);

    virtual bool isDocumentCreated() { return m_pInvoiceBook != 0 ? true : false; }
    QStringList documentSheetNames() { return m_pInvoiceBook != 0 ? m_pInvoiceBook->sheetNames() : QStringList(); }

private:
    void releaseDocument();

private:
    QXlsx::Document *m_pInvoiceBook;
    QXlsx::Worksheet *m_pCurrentSheet;
};

#endif // XLSDOCUMENTWRAPPER_H
