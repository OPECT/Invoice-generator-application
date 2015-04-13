#ifndef DOCINVOICEHANDLER_H
#define DOCINVOICEHANDLER_H

#include <QObject>
#include <QString>

class QDate;
class ErrorReport;

class DocInvoiceBuilder : public QObject
{
    Q_OBJECT
public:
    explicit DocInvoiceBuilder(ErrorReport &errorReporter, QObject *parent = 0);
    virtual ~DocInvoiceBuilder() {}

    virtual bool createDocument(const QString &outputFileName) = 0;
    virtual bool addInvoicePage(const QString &supplier, const QString &recipient, const QString &client, quint32 id,
                                const QDate &date) = 0;
    virtual bool addInvoiceItem(const QString &name, const QString &type, double quantity, double price,
                                double summary) = 0;
    virtual bool addInvoideSummary() = 0;
    virtual bool saveDocument(bool overwrite = false) = 0;

    const QString& outputFile() const { return m_outputFile; }
    void outputFile(const QString& file) { m_outputFile = file; }

protected:
    void reportError(const QString &msg);

protected:
    ErrorReport &m_reporter;
    QString m_outputFile;
};

#endif // DOCINVOICEHANDLER_H
