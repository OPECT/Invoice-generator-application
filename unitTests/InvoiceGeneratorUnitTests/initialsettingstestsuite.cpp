#include "initialsettingstestsuite.h"
#include "unittestpurposeinitialsettings.h"
#include "databasedata.h"

#include <cppunit/TestCaller.h>

InitialSettingsTestSuite::InitialSettingsTestSuite() : m_invoiceType(IT_SimpleInvoice),
    m_invoiceID(1234), m_company("Some Company"), m_traderFirstName("Trader Name"),
    m_traderSecondName("Trader Surname"), m_tableName("DB Table"), m_userName("User"), m_passwrod("Password"),
    m_fileName("DBFile.ext"), m_invoiceTypeEmpty(IT_NONE), m_empty()
{
}

bool InitialSettingsTestSuite::checkKeyField(const QSettings& settings, const QString &key, const QVariant &data)
{
    if (!settings.contains(key))
    {
        return false;
    }

    QVariant verifyData = settings.value(key);
    if (!verifyData.isValid() || verifyData != data)
    {
        return false;
    }
    return true;
}

bool InitialSettingsTestSuite::saveGeneralData_OK()
{
    GeneralInvoiceData data(QDate(), m_invoiceType, m_invoiceID, m_company, m_traderFirstName, m_traderSecondName);
    UnitTestPurposeInitialSettings settings;

    settings.saveGeneralInfo(data);

    QSettings verifySet(settings.organizationName(), settings.applicationName());
    verifySet.beginGroup(settings.generalGroupKey());

    if (!checkKeyField(verifySet, settings.companyNameKey(), QVariant(m_company)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.invoiceTypeKey(), QVariant(m_invoiceType)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderNameKey(), QVariant(m_traderFirstName)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderSurnameKey(), QVariant(m_traderSecondName)))
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::saveGeneralData_BAD()
{
    GeneralInvoiceData data(QDate(), m_invoiceTypeEmpty, m_invoiceID, m_empty, m_empty, m_empty);
    UnitTestPurposeInitialSettings settings;

    // Check that data from previous test are stored
    QSettings verifySet(settings.organizationName(), settings.applicationName());
    verifySet.beginGroup(settings.generalGroupKey());

    if (!checkKeyField(verifySet, settings.companyNameKey(), QVariant(m_company)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.invoiceTypeKey(), QVariant(m_invoiceType)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderNameKey(), QVariant(m_traderFirstName)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderSurnameKey(), QVariant(m_traderSecondName)))
    {
        return false;
    }

    // overwrite previous data
    settings.saveGeneralInfo(data);

    if (!checkKeyField(verifySet, settings.companyNameKey(), QVariant(m_empty)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.invoiceTypeKey(), QVariant(m_invoiceTypeEmpty)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderNameKey(), QVariant(m_empty)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.traderSurnameKey(), QVariant(m_empty)))
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::saveDBData_OK()
{
    DataBaseData data;
    UnitTestPurposeInitialSettings settings;
    data.userName(m_userName);
    data.password(m_passwrod);
    data.dataBaseFile(m_fileName);

    settings.saveDBInfo(data);

    QSettings verifySet(settings.organizationName(), settings.applicationName());
    verifySet.beginGroup(settings.databaseGroupKey());

    if (!checkKeyField(verifySet, settings.userNameKey(), QVariant(m_userName)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.passwordKey(), QVariant(m_passwrod)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.dbFileNameKey(), QVariant(m_fileName)))
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::saveDBData_BAD()
{
    DataBaseData data;
    UnitTestPurposeInitialSettings settings;

    // Check that data from previous test are stored
    QSettings verifySet(settings.organizationName(), settings.applicationName());
    verifySet.beginGroup(settings.databaseGroupKey());

    if (!checkKeyField(verifySet, settings.userNameKey(), QVariant(m_userName)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.passwordKey(), QVariant(m_passwrod)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.dbFileNameKey(), QVariant(m_fileName)))
    {
        return false;
    }

    // overwrite previous data
    settings.saveDBInfo(data);

    if (!checkKeyField(verifySet, settings.userNameKey(), QVariant(m_empty)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.passwordKey(), QVariant(m_empty)))
    {
        return false;
    }

    if (!checkKeyField(verifySet, settings.dbFileNameKey(), QVariant(m_empty)))
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::propagateGeneralData_OK()
{
    GeneralInvoiceData initData(QDate(), m_invoiceType, m_invoiceID, m_company, m_traderFirstName, m_traderSecondName);
    GeneralInvoiceData resultData(QDate(), m_invoiceTypeEmpty, m_invoiceID, m_empty, m_empty, m_empty);
    UnitTestPurposeInitialSettings settings;

    settings.saveGeneralInfo(initData);
    settings.propagateGeneralInfo(resultData);

    if (resultData.companyName() != m_company)
    {
        return false;
    }
    if (resultData.invoiceType() != m_invoiceType)
    {
        return false;
    }
    if (resultData.traderName() != m_traderFirstName)
    {
        return false;
    }
    if (resultData.traderSecondName() != m_traderSecondName)
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::propagateGeneralData_BAD()
{
    UnitTestPurposeInitialSettings sets;
    QSettings settings(sets.organizationName(), sets.applicationName());
    GeneralInvoiceData data(QDate(), m_invoiceType, m_invoiceID, m_company, m_traderFirstName, m_traderSecondName);

    settings.clear();
    sets.propagateGeneralInfo(data);
    if (data.companyName() != m_empty)
    {
        return false;
    }
    if (data.invoiceType() != m_invoiceTypeEmpty)
    {
        return false;
    }
    if (data.traderName() != m_empty)
    {
        return false;
    }
    if (data.traderSecondName() != m_empty)
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::propagateDBData_OK()
{
    DataBaseData initData;
    DataBaseData resultData;
    UnitTestPurposeInitialSettings settings;

    initData.userName(m_userName);
    initData.password(m_passwrod);
    initData.dataBaseFile(m_fileName);

    settings.saveDBInfo(initData);
    settings.propagateDBInfo(resultData);

    if (resultData.userName() != m_userName)
    {
        return false;
    }
    if (resultData.password() != m_passwrod)
    {
        return false;
    }
    if (resultData.dataBaseFile() != m_fileName)
    {
        return false;
    }

    return true;
}

bool InitialSettingsTestSuite::propagateDBData_BAD()
{
    UnitTestPurposeInitialSettings sets;
    QSettings settings(sets.organizationName(), sets.applicationName());
    DataBaseData data;

    settings.clear();
    sets.propagateDBInfo(data);
    if (data.userName() != sets.defaultUserName())
    {
        return false;
    }
    if (data.password() != sets.defaultPasswordKey())
    {
        return false;
    }
    if (data.dataBaseFile() != sets.defaultDBFileNameKey())
    {
        return false;
    }

    return true;
}

void InitialSettingsTestSuite::saveDataTest()
{
    CPPUNIT_ASSERT(saveGeneralData_OK());
    CPPUNIT_ASSERT(saveGeneralData_BAD());
    CPPUNIT_ASSERT(saveDBData_OK());
    CPPUNIT_ASSERT(saveDBData_BAD());
}

void InitialSettingsTestSuite::propagateDataTest()
{
    CPPUNIT_ASSERT(propagateGeneralData_OK());
    CPPUNIT_ASSERT(propagateGeneralData_BAD());
    CPPUNIT_ASSERT(propagateDBData_OK());
    CPPUNIT_ASSERT(propagateDBData_BAD());
}

void InitialSettingsTestSuite::tearDown()
{
    UnitTestPurposeInitialSettings sets;
    QSettings(sets.organizationName(), sets.applicationName()).clear();
}

CppUnit::Test *InitialSettingsTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<InitialSettingsTestSuite>("Test Saving Configuration Data",
                                                                    &InitialSettingsTestSuite::saveDataTest));
    suiteOfTests->addTest(new CppUnit::TestCaller<InitialSettingsTestSuite>("Test Loading Configuration Data",
                                                                    &InitialSettingsTestSuite::propagateDataTest));
    return suiteOfTests;
}
