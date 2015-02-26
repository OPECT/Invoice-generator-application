#ifndef INVOICELISTSUITE_H
#define INVOICELISTSUITE_H

#include "invoiceitem.h"

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>

class InvoiceDataSuite : public CppUnit::TestFixture
{
public:
    InvoiceDataSuite();

    void createInvoiceData_OK1();
    void createInvoiceData_OK2();

    void getInvoiceData_OK();

    static CppUnit::Test *suite();

private:
    InvoiceItem m_item1;
    InvoiceItem m_item2;
};

#endif // INVOICELISTSUITE_H
