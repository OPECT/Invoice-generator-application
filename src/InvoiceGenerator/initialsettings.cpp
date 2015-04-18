#include "initialsettings.h"
#include "generalinvoicedata.h"
#include "databasedata.h"

InitialSettings::InitialSettings(const QString& org, const QString &app, QObject *parent) :
    QObject(parent), m_orgName(org), m_appName(app), m_settings(m_orgName, m_appName), m_dataBaseGroupKey("DataBase"),
    m_generalGroupKey("General"), m_generalCompanyNameKey("Company Name"), m_generalInvoiceTypeKey("Invoice Type"),
    m_generalTraderNameKey("Trader Name"), m_generalTraderSurnameKey("Trader Surname"), m_DBUserNameKey("User Name"),
    m_DBUserPwdKey("Password"), m_DBFileNameKey("DataBase File")
{
}

void InitialSettings::saveGeneralInfo(const GeneralInvoiceData &data)
{
    m_settings.beginGroup(m_generalGroupKey);
    m_settings.setValue(m_generalCompanyNameKey, data.companyName());
    m_settings.setValue(m_generalInvoiceTypeKey, data.invoiceType());
    m_settings.setValue(m_generalTraderNameKey, data.traderName());
    m_settings.setValue(m_generalTraderSurnameKey, data.traderSecondName());
    m_settings.endGroup();
}

void InitialSettings::saveDBInfo(const DataBaseData &data)
{
    m_settings.beginGroup(m_dataBaseGroupKey);
    m_settings.setValue(m_DBUserNameKey, data.userName());
    m_settings.setValue(m_DBUserPwdKey, data.password());
    m_settings.setValue(m_DBFileNameKey, data.dataBaseFile());
    m_settings.endGroup();
}

void InitialSettings::propagateGeneralInfo(GeneralInvoiceData &data)
{
    m_settings.beginGroup(m_generalGroupKey);
    data.companyName(m_settings.value(m_generalCompanyNameKey, "").toString());
    data.invoiceType(static_cast<GeneralInvoiceData::InvoiceType>(m_settings.value(m_generalInvoiceTypeKey,
                                                                                   0).toInt()));
    data.traderName(m_settings.value(m_generalTraderNameKey, "").toString());
    data.traderSecondName(m_settings.value(m_generalTraderSurnameKey, "").toString());
    m_settings.endGroup();
}

void InitialSettings::propagateDBInfo(DataBaseData &data)
{
    m_settings.beginGroup(m_dataBaseGroupKey);
    data.userName(m_settings.value(m_DBUserNameKey, "").toString());
    data.password(m_settings.value(m_DBUserPwdKey, "").toString());
    data.dataBaseFile(m_settings.value(m_DBFileNameKey, "").toString());
    m_settings.endGroup();
}
