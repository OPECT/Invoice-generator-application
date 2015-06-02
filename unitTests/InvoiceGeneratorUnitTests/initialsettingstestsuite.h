#ifndef INITIALSETTINGSTESTSUITE_H
#define INITIALSETTINGSTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include "generalinvoicedata.h"

class QSettings;

class InitialSettingsTestSuite : public CppUnit::TestFixture
{
public:
    InitialSettingsTestSuite();

    bool saveGeneralData_OK();
    bool saveGeneralData_BAD();
    bool saveDBData_OK();
    bool saveDBData_BAD();
    bool propagateGeneralData_OK();
    bool propagateGeneralData_BAD();
    bool propagateDBData_OK();
    bool propagateDBData_BAD();

    void saveDataTest();
    void propagateDataTest();

    virtual void tearDown();

    static CppUnit::Test *suite();

private:
    bool checkKeyField(const QSettings& settings, const QString &key, const QVariant &data);

private:
    INVOICE_TYPE m_invoiceType;
    quint32 m_invoiceID;
    QString m_company;
    QString m_traderFirstName;
    QString m_traderSecondName;

    QString m_tableName;
    QString m_userName;
    QString m_passwrod;
    QString m_fileName;

    INVOICE_TYPE m_invoiceTypeEmpty;
    QString m_empty;
};

#endif // INITIALSETTINGSTESTSUITE_H
