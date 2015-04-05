#ifndef INVOICEDOCUMENTWRAPPER_H
#define INVOICEDOCUMENTWRAPPER_H

#include <QString>
#include <QVariant>

class InvoiceDocumentWrapper
{
public:
    InvoiceDocumentWrapper(const QString &templateFile) : m_template(templateFile) { }
    virtual ~InvoiceDocumentWrapper() { }

    virtual bool create(bool overwrite = false) = 0;
    virtual bool copySheetFromSource(const QString &srcName, const QString &dstName) = 0;
    virtual bool changeCurrentSheet(const QString &sheetName) = 0;
    virtual bool deleteSheet(const QString &name) = 0;
    virtual bool save(const QString& name, bool overwrite = false) = 0;

    virtual bool writeString(quint32 row, quint32 col, const QString &data) = 0;
    virtual bool writeDouble(quint32 row, quint32 col, double data) = 0;
    virtual QVariant readData(quint32 row, quint32 col) = 0;

    virtual bool isDocumentCreated() = 0;

protected:
    QString m_template;
};

#endif // INVOICEDOCUMENTWRAPPER_H
