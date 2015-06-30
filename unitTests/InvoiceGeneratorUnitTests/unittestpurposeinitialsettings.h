#ifndef UNITTESTPURPOSEINITIALSETTINGS_H
#define UNITTESTPURPOSEINITIALSETTINGS_H

#include"initialsettings.h"

class UnitTestPurposeInitialSettings : public InitialSettings
{
public:
    UnitTestPurposeInitialSettings() { }

    const QString& organizationName() { return m_orgName; }
    const QString& applicationName() { return m_appName; }
    const QString& generalGroupKey() { return m_generalGroupKey; }
    const QString& databaseGroupKey() { return m_dataBaseGroupKey; }
    const QString& companyNameKey() { return m_generalCompanyNameKey; }
    const QString& invoiceTypeKey() { return m_generalInvoiceTypeKey; }
    const QString& traderNameKey() { return m_generalTraderNameKey; }
    const QString& traderSurnameKey() { return m_generalTraderSurnameKey; }
    const QString& userNameKey() { return m_DBUserNameKey; }
    const QString& passwordKey() { return m_DBUserPwdKey; }
    const QString& dbFileNameKey() { return m_DBFileNameKey; }
    const QString& defaultUserName() { return m_defaultDBUserName; }
    const QString& defaultPasswordKey() { return m_defaultDBPassword; }
    const QString& defaultDBFileNameKey() { return m_defaultDBFileName; }
};

#endif // UNITTESTPURPOSEINITIALSETTINGS_H
