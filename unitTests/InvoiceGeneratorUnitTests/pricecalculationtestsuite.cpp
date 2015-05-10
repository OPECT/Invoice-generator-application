#include "pricecalculationtestsuite.h"
#include "tablehandler.h"
#include "databasemanager.h"
#include "pricecalculationwithdiscount.h"

#include <cppunit/TestCaller.h>
#include <math.h>

PriceCalculationTestSuite::PriceCalculationTestSuite() : m_dbType("QSQLITE"), m_dbHost("localhost"),
    m_dbName("PriceCalculationDB"), m_dbUser("UnitTest"), m_dbPassword("Test123"), m_customerTableName("customers"),
    m_goodTableName("goods"), m_goodId(1), m_customerId(1), m_wrongGoodId(120), m_duplicatedGoodId(2),
    m_goodIdWithWrongPrice(3), m_wrongCustomerId(100), m_duplicatedCustomerId(2), m_customerIdWithWrongDisc(3),
    m_customerIdWithNegativeDisc(4), m_customerIdWithTooBigDisc(5), m_compareEpsilon(0.00000001),
    m_calculatedPrice(0.4332)
{
}

bool PriceCalculationTestSuite::calculate_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler goodsTable(m_goodTableName, dbManager.database());
    TableHandler customersTable(m_customerTableName, dbManager.database());
    PriceCalculationWithDiscount calculator(goodsTable, customersTable);

    double finalPrice = 0;
    if (!calculator.calculate(m_goodId, m_customerId, finalPrice))
    {
        return false;
    }

    if (abs(finalPrice - m_calculatedPrice) > m_compareEpsilon)
    {
        return false;
    }

    return true;
}

bool PriceCalculationTestSuite::calculateGoodPrice_BAD()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler goodsTable(m_goodTableName, dbManager.database());
    TableHandler customersTable(m_customerTableName, dbManager.database());
    PriceCalculationWithDiscount calculator(goodsTable, customersTable);

    double finalPrice = 0;
    if (calculator.calculate(m_wrongGoodId, m_customerId, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_duplicatedGoodId, m_customerId, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_goodIdWithWrongPrice, m_customerId, finalPrice))
    {
        return false;
    }
    if (finalPrice != 0)
    {
        return false;
    }

    return true;
}

bool PriceCalculationTestSuite::calculateDiscountPrice_BAD()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler goodsTable(m_goodTableName, dbManager.database());
    TableHandler customersTable(m_customerTableName, dbManager.database());
    PriceCalculationWithDiscount calculator(goodsTable, customersTable);

    double finalPrice = 0;
    if (calculator.calculate(m_goodId, m_wrongCustomerId, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_goodId, m_duplicatedCustomerId, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_goodId, m_customerIdWithWrongDisc, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_goodId, m_customerIdWithNegativeDisc, finalPrice))
    {
        return false;
    }
    if (calculator.calculate(m_goodId, m_customerIdWithTooBigDisc, finalPrice))
    {
        return false;
    }

    if (finalPrice != 0)
    {
        return false;
    }
    return true;
}


void PriceCalculationTestSuite::calculateTest()
{
    CPPUNIT_ASSERT(calculate_OK());
    CPPUNIT_ASSERT(calculateGoodPrice_BAD());
    CPPUNIT_ASSERT(calculateDiscountPrice_BAD());
}

CppUnit::Test *PriceCalculationTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<PriceCalculationTestSuite>("Test price calculation",
                                                                    &PriceCalculationTestSuite::calculateTest));
    return suiteOfTests;
}
