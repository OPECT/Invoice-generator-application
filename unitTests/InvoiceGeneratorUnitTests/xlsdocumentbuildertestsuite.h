#ifndef XLSDOCUMENTBUILDERTESTSUITE_H
#define XLSDOCUMENTBUILDERTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>
#include <QDate>

class QVariant;
class XLSDocumentWrapper;

class XLSDocumentBuilderTestSuite : public CppUnit::TestFixture
{
public:
    XLSDocumentBuilderTestSuite();

    void documentOperations();
    void itemOperations();

    bool createDocument_OK();
    bool createDocument_BAD();

    bool saveDocument_OK();
    bool saveDocument_BAD();

    bool addPage_OK();
    bool addPage_BAD1();
    bool addPage_BAD2();

    bool addItem_OK();
    bool addItem_BAD();

    bool addSummary_OK();
    bool addSummary_BAD();

    static CppUnit::Test *suite();

private:
    bool readAndVerify(const XLSDocumentWrapper &doc, quint32 row, quint32 col, const QVariant &ethalon) const;

private:
    QString m_correctTemplateFile;
    QString m_wrongTemplateFile;
    QString m_wrongData;
    QString m_templateSheet;
    QString m_invoiceSheet;
    QString m_newInvoiceSheet;

    QString m_customer;
    quint32 m_invoiceID;
    quint32 m_newIinvoiceID;
    QDate m_date;

    QString m_goodName1;
    QString m_goodType1;
    double m_goodQuantity1;
    double m_goodPrice1;
    QString m_goodName2;
    QString m_goodType2;
    double m_goodQuantity2;
    double m_goodPrice2;

    QString m_resultFile;

    QString m_creationError;
    QString m_savingErrorDocumentIsNotReady;
    QString m_savingErrorEmptyFileName;
    QString m_savingErrorSheetIsNotReady;
    QString m_savingErrorCantSaveFile;
    QString m_addPageErrorDocIsNotReady;
    QString m_addPageErrorCantCreateNewSheet;
    QString m_addPageErrorCantUpdateSheet;
    QString m_addItemErrorSheetIsNotReady;
    QString m_addItemErrorInvoiceIsFull;
    QString m_addSummaryErrorSheetIsNotReady;
};

#endif // XLSDOCUMENTBUILDERTESTSUITE_H
