#include <cppunit/TextTestRunner.h>
#include "invoicedatasuite.h"
#include "documentwrappertestsuite.h"
#include "xlsinvoicevalidatortestsuite.h"

int main()
{
    CppUnit::TextTestRunner runner;

    runner.addTest(InvoiceDataSuite::suite());
    runner.addTest(DocumentWrapperTestSuite::suite());
    runner.addTest(XLSInvoiceValidatorTestsuite::suite());

    runner.run();
    return 0;
}
