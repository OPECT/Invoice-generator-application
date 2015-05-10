#ifndef PRICECALCULATIONTESTSUITE_H
#define PRICECALCULATIONTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>

class PriceCalculationTestSuite : public CppUnit::TestFixture
{
public:
    PriceCalculationTestSuite();

    bool calculate_OK();
    bool calculateGoodPrice_BAD();
    bool calculateDiscountPrice_BAD();

    void calculateTest();

    static CppUnit::Test *suite();

private:
    QString m_dbType;
    QString m_dbHost;
    QString m_dbName;
    QString m_dbUser;
    QString m_dbPassword;

    QString m_customerTableName;
    QString m_goodTableName;

    quint32 m_goodId;
    quint32 m_customerId;

    quint32 m_wrongGoodId;
    quint32 m_duplicatedGoodId;
    quint32 m_goodIdWithWrongPrice;

    quint32 m_wrongCustomerId;
    quint32 m_duplicatedCustomerId;
    quint32 m_customerIdWithWrongDisc;
    quint32 m_customerIdWithNegativeDisc;
    quint32 m_customerIdWithTooBigDisc;

    double m_compareEpsilon;
    double m_calculatedPrice;
};

#endif // PRICECALCULATIONTESTSUITE_H
