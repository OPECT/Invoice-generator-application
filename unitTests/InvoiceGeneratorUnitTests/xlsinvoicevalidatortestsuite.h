#ifndef XLSINVOICEVALIDATORTESTSUITE_H
#define XLSINVOICEVALIDATORTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>
#include <QVariant>

class XLSInvoiceValidatorTestsuite : public CppUnit::TestFixture
{
public:
    XLSInvoiceValidatorTestsuite();

    void validateSheetTest();
    void fieldsDataTest();

    bool validateSheet_OK();
    bool validateSheet_BAD();

    bool validateRecieverField();
    bool validateInvoiceIDField();
    bool validateDateField();
    bool validateHeaderIDField();
    bool validateHeaderGoodField();
    bool validateHeaderTypeField();
    bool validateHeaderQuantityField();
    bool validateHeaderPriceField();
    bool validateHeaderSummaryField();
    bool validateMaxItemField();
    bool validateNextMaxItemield();
    bool validateTotalCostField();
    bool validateSupplierSignatureField();
    bool validateRecieverSignatureField();

    static CppUnit::Test *suite();

private:
    bool checkNeededField(quint32 row, quint32 col, QVariant data);

private:
    const QString m_targetFile;
    const QString m_targetSheet;

    const QString m_updatedFile;
    const QVariant m_brokenData;

    const QString m_wrongTargetFile;
    const QString m_wrongTargetSheet;
};

#endif // XLSINVOICEVALIDATORTESTSUITE_H
