#include <cppunit/TextTestRunner.h>
#include "invoicedatasuite.h"

int main()
{
    CppUnit::TextTestRunner runner;

    runner.addTest(InvoiceDataSuite::suite());

    runner.run();
    return 0;
}
