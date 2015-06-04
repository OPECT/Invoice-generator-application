#include "xlsinvoicevalidatortestsuite.h"
#include "xlsstandardinvoicevalidator.h"
#include "xlsdocumentwrapper.h"
#include "xlstandardinvoiceformatbuilder.h"

#include <cppunit/TestCaller.h>

XLSInvoiceValidatorTestsuite::XLSInvoiceValidatorTestsuite() : m_targetFile("../standardInvoice.xlsx"),
    m_targetSheet("Invoice"), m_updatedFile("../updatedInvoice.xlsx"), m_brokenData("Wrong Data"),
    m_wrongTargetFile("../nonExistingFile"), m_wrongTargetSheet("nonExistingSheet")
{
}

bool XLSInvoiceValidatorTestsuite::checkNeededField(quint32 row, quint32 col, QVariant data)
{
    XLSDocumentWrapper doc(m_targetFile);

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.write(row, col, data))
    {
        return false;
    }
    if (!doc.save(m_updatedFile, true))
    {
        return false;
    }
    if (!QFile::exists(m_updatedFile))
    {
        return false;
    }

    XLSStandardInvoiceValidator validator(m_updatedFile);

    if (validator.validateSheet(m_targetSheet))
    {
        return false;
    }

    QFile::remove(m_updatedFile);
    return true;
}

bool XLSInvoiceValidatorTestsuite::validateSheet_OK()
{
    XLSStandardInvoiceValidator validator(m_targetFile);

    if (!validator.validateSheet(m_targetSheet))
    {
        return false;
    }
    return true;
}

bool XLSInvoiceValidatorTestsuite::validateSheet_BAD()
{
    XLSStandardInvoiceValidator incorrectValidator(m_wrongTargetFile);

    if (incorrectValidator.validateSheet(m_targetSheet))
    {
        return false;
    }

    XLSStandardInvoiceValidator validator(m_targetFile);

    if (validator.validateSheet(m_wrongTargetSheet))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateRecieverField()
{
    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_RECIPIENT, XLSStandardInvoiceValidator::GDC_GENERAL,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_RECIPIENT, XLSStandardInvoiceValidator::GDC_GENERAL,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateInvoiceIDField()
{
    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_INVOICE_ID, XLSStandardInvoiceValidator::GDC_INVOICE_ID,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_INVOICE_ID, XLSStandardInvoiceValidator::GDC_INVOICE_ID,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateDateField()
{
    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_DATE, XLSStandardInvoiceValidator::GDC_DATE,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLStandardInvoiceFormatBuilder::GDR_DATE, XLSStandardInvoiceValidator::GDC_DATE,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderIDField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderGoodField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_NAME,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderTypeField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TYPE,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TYPE,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderQuantityField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_QUANTITY,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_QUANTITY,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderPriceField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_PRICE,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_PRICE,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateHeaderSummaryField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TOTAL,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_HEADER, XLStandardInvoiceFormatBuilder::ICV_GOOD_TOTAL,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateMaxItemField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID,
                         m_brokenData))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateNextMaxItemield()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 1, XLStandardInvoiceFormatBuilder::ICV_GOOD_ID,
                         m_brokenData))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateTotalCostField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 1, XLSStandardInvoiceValidator::GDC_TOTAL_COST,
                         m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 1, XLSStandardInvoiceValidator::GDC_TOTAL_COST,
                         QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateSupplierSignatureField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 3,
                          XLSStandardInvoiceValidator::GDC_SUPPLIER_SIGNATURE, m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 3,
                          XLSStandardInvoiceValidator::GDC_SUPPLIER_SIGNATURE, QVariant()))
    {
        return false;
    }

    return true;
}

bool XLSInvoiceValidatorTestsuite::validateRecieverSignatureField()
{
    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 3,
                          XLSStandardInvoiceValidator::GDC_RECIEVER_SIGNATURE, m_brokenData))
    {
        return false;
    }

    if (!checkNeededField(XLSStandardInvoiceValidator::IIR_LAST + 3,
                          XLSStandardInvoiceValidator::GDC_RECIEVER_SIGNATURE, QVariant()))
    {
        return false;
    }

    return true;
}

void XLSInvoiceValidatorTestsuite::validateSheetTest()
{
    CPPUNIT_ASSERT(validateSheet_OK());
    CPPUNIT_ASSERT(validateSheet_BAD());
}

void XLSInvoiceValidatorTestsuite::fieldsDataTest()
{
    CPPUNIT_ASSERT(validateRecieverField());
    CPPUNIT_ASSERT(validateInvoiceIDField());
    CPPUNIT_ASSERT(validateDateField());
    CPPUNIT_ASSERT(validateHeaderIDField());
    CPPUNIT_ASSERT(validateHeaderGoodField());
    CPPUNIT_ASSERT(validateHeaderTypeField());
    CPPUNIT_ASSERT(validateHeaderQuantityField());
    CPPUNIT_ASSERT(validateHeaderPriceField());
    CPPUNIT_ASSERT(validateHeaderSummaryField());
    CPPUNIT_ASSERT(validateMaxItemField());
    CPPUNIT_ASSERT(validateNextMaxItemield());
    CPPUNIT_ASSERT(validateTotalCostField());
    CPPUNIT_ASSERT(validateSupplierSignatureField());
    CPPUNIT_ASSERT(validateRecieverSignatureField());
}

CppUnit::Test *XLSInvoiceValidatorTestsuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<XLSInvoiceValidatorTestsuite>("Test Invoice Template Validation",
                                                                    &XLSInvoiceValidatorTestsuite::validateSheetTest));
    suiteOfTests->addTest(new CppUnit::TestCaller<XLSInvoiceValidatorTestsuite>("Test Particular Field Presence",
                                                                    &XLSInvoiceValidatorTestsuite::fieldsDataTest));
    return suiteOfTests;
}
