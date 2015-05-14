#include <cppunit/TextTestRunner.h>
#include "invoicedatasuite.h"
#include "documentwrappertestsuite.h"
#include "xlsinvoicevalidatortestsuite.h"
#include "xlsdocumentbuildertestsuite.h"
#include "initialsettingstestsuite.h"
#include "databasemanagertestsuite.h"
#include "sqltablehandlertestsuite.h"
#include "pricecalculationtestsuite.h"

int main()
{
    CppUnit::TextTestRunner runner;

    runner.addTest(InvoiceDataSuite::suite());
    runner.addTest(DocumentWrapperTestSuite::suite());
    runner.addTest(XLSInvoiceValidatorTestsuite::suite());
    runner.addTest(XLSDocumentBuilderTestSuite::suite());
    runner.addTest(InitialSettingsTestSuite::suite());
    runner.addTest(DataBaseManagerTestSuite::suite());
    runner.addTest(SQLTableHandlerTestSuite::suite());
    runner.addTest(PriceCalculationTestSuite::suite());

    runner.run();
    return 0;
}
