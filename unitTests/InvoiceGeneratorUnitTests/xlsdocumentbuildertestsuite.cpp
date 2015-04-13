#include "xlsdocumentbuildertestsuite.h"
#include "xlstandardinvoiceformatbuilder.h"
#include "xlsdocumentwrapper.h"
#include "xlsstandardinvoicevalidator.h"
#include "unittestpurposeerrorreport.h"

#include <cppunit/TestCaller.h>
#include <QVariant>

XLSDocumentBuilderTestSuite::XLSDocumentBuilderTestSuite() : m_correctTemplateFile("../standardInvoice.xlsx"),
    m_wrongTemplateFile("../brokenTemplate.xlsx"), m_wrongData("Incorrect Data"), m_templateSheet("Invoice"),
    m_invoiceSheet("Invoice 111"), m_newInvoiceSheet("Invoice 4321"), m_supplier("Suuplier"), m_customer("Customer"),
    m_payer("Payer"), m_invoiceID(111), m_newIinvoiceID(4321), m_goodName1("Item One"), m_goodType1("items"),
    m_goodQuantity1(1.2), m_goodPrice1(0.111), m_goodName2("Item Two"), m_goodType2("items"), m_goodQuantity2(100),
    m_goodPrice2(2.78), m_resultFile("../resultFile.xlsx"),
    m_creationError("Create Document Error: Invoice template is invalid"),
    m_savingErrorDocumentIsNotReady("Save Document Error: Document is not ready"),
    m_savingErrorEmptyFileName("Save Document Error: No output file name provided"),
    m_savingErrorSheetIsNotReady("Save Document Error: Can't delete Invoice Sheet Template"),
    m_savingErrorCantSaveFile("Save Document Error: Can't save invoice file"),
    m_addPageErrorDocIsNotReady("Add Invoice Page Error: Document is not ready"),
    m_addPageErrorCantCreateNewSheet("Add Invoice Page Error: Can't create invoice sheet"),
    m_addPageErrorCantUpdateSheet("Add Invoice Page Error: Can't update date"),
    m_addItemErrorSheetIsNotReady("Add Item Error: Sheet is not ready"),
    m_addItemErrorInvoiceIsFull("Add Item Error: Invoice is Full"),
    m_addSummaryErrorSheetIsNotReady("Add Invoice Summary Error: Sheet is not ready")
{
}

bool XLSDocumentBuilderTestSuite::readAndVerify(const XLSDocumentWrapper &doc, quint32 row, quint32 col,
                                                const QVariant &ethalon) const
{
    QVariant data = doc.readData(row, col);
    if (!data.isValid() && data != ethalon)
    {
        return false;
    }
    return true;
}

void XLSDocumentBuilderTestSuite::documentOperations()
{
    CPPUNIT_ASSERT(createDocument_OK());
    CPPUNIT_ASSERT(createDocument_BAD());
    CPPUNIT_ASSERT(saveDocument_OK());
    CPPUNIT_ASSERT(saveDocument_BAD());
}

void XLSDocumentBuilderTestSuite::itemOperations()
{
    CPPUNIT_ASSERT(addPage_OK());
    CPPUNIT_ASSERT(addPage_BAD1());
    CPPUNIT_ASSERT(addPage_BAD2());
    CPPUNIT_ASSERT(addItem_OK());
    CPPUNIT_ASSERT(addItem_BAD());
    CPPUNIT_ASSERT(addSummary_OK());
}

bool XLSDocumentBuilderTestSuite::createDocument_OK()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!error.getErrorList().empty())
    {
        return false;
    }

    return true;
}

bool XLSDocumentBuilderTestSuite::createDocument_BAD()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    if (!document.create() || !document.isDocumentCreated())
    {
        return false;
    }
    if (!document.writeString(XLStandardInvoiceFormatBuilder::GDR_SUPPLIER, XLSStandardInvoiceValidator::GDC_GENERAL,
                              m_wrongData))
    {
        return false;
    }
    if (!document.save(m_wrongTemplateFile, true))
    {
        return false;
    }
    if (!QFile::exists(m_wrongTemplateFile))
    {
        return false;
    }

    XLSDocumentWrapper badDocument(m_wrongTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(badDocument, error);

    if (builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (error.getErrorList().count() != 1)
    {
        return false;
    }
    if (error.getErrorList().at(0) != m_creationError)
    {
        return false;
    }
    if (QFile::exists(m_wrongTemplateFile))
    {
        QFile::remove(m_wrongTemplateFile);
    }

    return true;
}

bool XLSDocumentBuilderTestSuite::saveDocument_OK()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }

    if (!error.getErrorList().empty())
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::saveDocument_BAD()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (builder.saveDocument(true))
    {
        return false;
    }
    if (!builder.createDocument(QString()))
    {
        return false;
    }
    if (builder.saveDocument(true))
    {
        return false;
    }

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (builder.saveDocument(true))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }

    if (!builder.createDocument(m_correctTemplateFile))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (builder.saveDocument(false))
    {
        return false;
    }

    QStringList errors = error.getErrorList();
    if (errors.count() != 4)
    {
        return false;
    }
    if (errors.at(0) != m_savingErrorDocumentIsNotReady || errors.at(1) != m_savingErrorEmptyFileName ||
        errors.at(2) != m_savingErrorSheetIsNotReady || errors.at(3) != m_savingErrorCantSaveFile)
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::addPage_OK()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }

    if (!error.getErrorList().empty())
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    XLSDocumentWrapper verifyDoc(m_resultFile);

    if (!verifyDoc.create() && !verifyDoc.isDocumentCreated())
    {
        return false;
    }
    if (verifyDoc.changeCurrentSheet(m_templateSheet))
    {
        return false;
    }
    if (!verifyDoc.changeCurrentSheet(m_invoiceSheet))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLStandardInvoiceFormatBuilder::GDR_SUPPLIER,
                       XLStandardInvoiceFormatBuilder::GDC_GENERAL, m_supplier))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLStandardInvoiceFormatBuilder::GDR_RECIPIENT,
                       XLStandardInvoiceFormatBuilder::GDC_GENERAL, m_customer))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLStandardInvoiceFormatBuilder::GDR_PAYER,
                       XLStandardInvoiceFormatBuilder::GDC_GENERAL, m_payer))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLStandardInvoiceFormatBuilder::GDR_INVOICE_ID,
                       XLStandardInvoiceFormatBuilder::GDC_INVOICE_ID, m_invoiceID))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::addPage_BAD1()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!document.copySheetFromSource(m_templateSheet, m_invoiceSheet) || !document.deleteSheet(m_templateSheet))
    {
        return false;
    }
    if (builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (builder.saveDocument(true))
    {
        return false;
    }

    if (error.getErrorList().count() != 3)
    {
        return false;
    }
    if (error.getErrorList().at(0) != m_addPageErrorDocIsNotReady)
    {
        return false;
    }
    if (error.getErrorList().at(1) != m_addPageErrorCantCreateNewSheet)
    {
        return false;
    }
    if (error.getErrorList().at(2) != m_savingErrorSheetIsNotReady)
    {
        return false;
    }

    if (QFile::exists(m_resultFile))
    {
        return false;
    }

    return true;
}

bool XLSDocumentBuilderTestSuite::addPage_BAD2()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (document.changeCurrentSheet(m_templateSheet) && !document.write(XLStandardInvoiceFormatBuilder::GDR_DATE,
                                                                        XLStandardInvoiceFormatBuilder::GDC_DATE,
                                                                        QVariant()))
    {
        return false;
    }
    if (builder.addInvoicePage(m_supplier, m_customer, m_payer, m_newIinvoiceID, m_date))
    {
        return false;
    }
    if (builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }

    if (error.getErrorList().count() != 2)
    {
        return false;
    }
    if (error.getErrorList().at(0) != m_addPageErrorCantUpdateSheet)
    {
        return false;
    }
    if (error.getErrorList().at(1) != m_addPageErrorCantCreateNewSheet)
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    XLSDocumentWrapper verifyDoc(m_resultFile);

    if (!verifyDoc.create() && !verifyDoc.isDocumentCreated())
    {
        return false;
    }
    if (!verifyDoc.changeCurrentSheet(m_invoiceSheet))
    {
        return false;
    }
    if (verifyDoc.changeCurrentSheet(m_templateSheet))
    {
        return false;
    }
    if (verifyDoc.changeCurrentSheet(m_newInvoiceSheet))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::addItem_OK()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.addInvoiceItem(m_goodName1, m_goodType1, m_goodQuantity1, m_goodPrice1,
                                m_goodQuantity1 * m_goodPrice1))
    {
        return false;
    }
    if (!builder.addInvoiceItem(m_goodName2, m_goodType2, m_goodQuantity2, m_goodPrice2,
                                m_goodQuantity2 * m_goodPrice2))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }
    if (!error.getErrorList().empty())
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    XLSDocumentWrapper verifyDoc(m_resultFile);

    if (!verifyDoc.create() && !verifyDoc.isDocumentCreated())
    {
        return false;
    }
    if (!verifyDoc.changeCurrentSheet(m_invoiceSheet))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_ID, 1))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME, m_goodName1))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_TYPE, m_goodType1))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_QUANTITY, m_goodQuantity1))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_PRICE, m_goodPrice1))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 3,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_TOTAL, m_goodQuantity1 * m_goodPrice1))
    {
        return false;
    }

    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_ID, 2))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME, m_goodName2))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_TYPE, m_goodType2))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_QUANTITY, m_goodQuantity2))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_PRICE, m_goodPrice2))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_HEADER + 4,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_TOTAL, m_goodQuantity2 * m_goodPrice2))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::addItem_BAD()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (builder.addInvoiceItem(m_goodName1, m_goodType1, m_goodQuantity1, m_goodPrice1,
                                m_goodQuantity1 * m_goodPrice1))
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    for (quint8 id = 0; id < builder.maxItemsCount(); id ++)
    {
        if (!builder.addInvoiceItem(m_goodName1, m_goodType1, m_goodQuantity1, m_goodPrice1,
                                    m_goodQuantity1 * m_goodPrice1))
        {
            return false;
        }
    }

    if (builder.addInvoiceItem(m_goodName1, m_goodType1, m_goodQuantity1, m_goodPrice1,
                                m_goodQuantity1 * m_goodPrice1))
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }
    if (error.getErrorList().count() != 2)
    {
        return false;
    }
    if (error.getErrorList().at(0) != m_addItemErrorSheetIsNotReady)
    {
        return false;
    }
    if (error.getErrorList().at(1) != m_addItemErrorInvoiceIsFull)
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    XLSDocumentWrapper verifyDoc(m_resultFile);

    if (!verifyDoc.create() && !verifyDoc.isDocumentCreated())
    {
        return false;
    }
    if (!verifyDoc.changeCurrentSheet(m_invoiceSheet))
    {
        return false;
    }
    if (!readAndVerify(verifyDoc, XLSStandardInvoiceValidator::IIR_LAST,
                       XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME, m_goodName1))
    {
        return false;
    }
    if (verifyDoc.readData(XLSStandardInvoiceValidator::IIR_LAST + 1,
                           XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME).isValid())
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

bool XLSDocumentBuilderTestSuite::addSummary_OK()
{
    XLSDocumentWrapper document(m_correctTemplateFile);
    UnitTestPurposeErrorReport error;
    XLStandardInvoiceFormatBuilder builder(document, error);

    if (!builder.createDocument(m_resultFile))
    {
        return false;
    }
    if (builder.addInvoideSummary())
    {
        return false;
    }
    if (!builder.addInvoicePage(m_supplier, m_customer, m_payer, m_invoiceID, m_date))
    {
        return false;
    }
    if (!builder.addInvoideSummary())
    {
        return false;
    }
    if (!builder.saveDocument(true))
    {
        return false;
    }

    if (error.getErrorList().count() != 1)
    {
        return false;
    }
    if (error.getErrorList().at(0) != m_addSummaryErrorSheetIsNotReady)
    {
        return false;
    }
    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return true;
}

CppUnit::Test *XLSDocumentBuilderTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<XLSDocumentBuilderTestSuite>("Test Document creation/storage by Builder",
                                                                    &XLSDocumentBuilderTestSuite::documentOperations));
    suiteOfTests->addTest(new CppUnit::TestCaller<XLSDocumentBuilderTestSuite>("Test Builder Add Page/Item oreations",
                                                                    &XLSDocumentBuilderTestSuite::itemOperations));
    return suiteOfTests;
}
