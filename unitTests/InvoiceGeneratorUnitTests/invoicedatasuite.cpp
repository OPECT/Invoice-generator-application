#include "invoicedatasuite.h"
#include "invoicedata.h"

#include <cppunit/TestCaller.h>

static const QString CustomerName = "Customer";
static const QString GoodName1 = "Good1";
static const QString GoodName2 = "Good2";

static const quint32 InvoiceId = 111;
static const quint32 GoodCount1 = 12;
static const quint32 GoodCount2 = 10;

static const InvoiceItem::GOOD_QUANTITY_TYPE GoodType1 = InvoiceItem::GQT_NUM;
static const InvoiceItem::GOOD_QUANTITY_TYPE GoodType2 = InvoiceItem::GQT_KG;

static const double GoodPrice1 = 12.34;
static const double GoodPrice2 = 2.5;

InvoiceDataSuite::InvoiceDataSuite() :
    m_item1(GoodName1, GoodCount1, GoodType1, GoodPrice1), m_item2(GoodName2, GoodCount2, GoodType2, GoodPrice2)
{
}

void InvoiceDataSuite::createInvoiceData_OK1()
{
    InvoiceData data;

    data.customerName(CustomerName);
    data.invoiceID(InvoiceId);
    data.setLast(true);

    CPPUNIT_ASSERT(data.getGoodsList().empty());

    data.addItem(m_item1);
    data.addItem(m_item2);

    CPPUNIT_ASSERT(data.customerName() == CustomerName);
    CPPUNIT_ASSERT(data.invoiceID() == InvoiceId);
    CPPUNIT_ASSERT(data.isLast() == true);
    CPPUNIT_ASSERT(data.getGoodsList().count() == 2);

    CPPUNIT_ASSERT(data.getGoodsList().at(0).name() == GoodName1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).quantity() == GoodCount1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).quantityType() == GoodType1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).goodPrice() == GoodPrice1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).totalPrice() == GoodPrice1 * GoodCount1);

    CPPUNIT_ASSERT(data.getGoodsList().at(1).name() == GoodName2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).quantity() == GoodCount2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).quantityType() == GoodType2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).goodPrice() == GoodPrice2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).totalPrice() == GoodPrice2 * GoodCount2);
}

void InvoiceDataSuite::createInvoiceData_OK2()
{
    InvoiceData data(CustomerName, InvoiceId, true);

    CPPUNIT_ASSERT(data.getGoodsList().empty());

    data.addItem(m_item1);
    data.addItem(m_item2);

    CPPUNIT_ASSERT(data.customerName() == CustomerName);
    CPPUNIT_ASSERT(data.invoiceID() == InvoiceId);
    CPPUNIT_ASSERT(data.isLast() == true);
    CPPUNIT_ASSERT(data.getGoodsList().count() == 2);

    CPPUNIT_ASSERT(data.getGoodsList().at(0).name() == GoodName1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).quantity() == GoodCount1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).quantityType() == GoodType1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).goodPrice() == GoodPrice1);
    CPPUNIT_ASSERT(data.getGoodsList().at(0).totalPrice() == GoodPrice1 * GoodCount1);

    CPPUNIT_ASSERT(data.getGoodsList().at(1).name() == GoodName2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).quantity() == GoodCount2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).quantityType() == GoodType2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).goodPrice() == GoodPrice2);
    CPPUNIT_ASSERT(data.getGoodsList().at(1).totalPrice() == GoodPrice2 * GoodCount2);
}

void InvoiceDataSuite::getInvoiceData_OK()
{
    InvoiceData data(CustomerName, InvoiceId, true);
    double totalSummary = GoodCount1 * GoodPrice1 + GoodCount2 * GoodPrice2;

    CPPUNIT_ASSERT(data.getGoodsList().empty());
    CPPUNIT_ASSERT(data.getTotalSummary() == 0);

    data.addItem(m_item1);
    data.addItem(m_item2);

    CPPUNIT_ASSERT(data.getGoodsList().count() == 2);
    CPPUNIT_ASSERT(data.getTotalSummary() == totalSummary);
}

CppUnit::Test *InvoiceDataSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<InvoiceDataSuite>("Test Invoice Data Creation",
                                                                    &InvoiceDataSuite::createInvoiceData_OK1));
    suiteOfTests->addTest(new CppUnit::TestCaller<InvoiceDataSuite>("Test Invoice Data Creation",
                                                                    &InvoiceDataSuite::createInvoiceData_OK2));
    suiteOfTests->addTest(new CppUnit::TestCaller<InvoiceDataSuite>("Test Invoice Data Retreival",
                                                                    &InvoiceDataSuite::getInvoiceData_OK));
    return suiteOfTests;
}
