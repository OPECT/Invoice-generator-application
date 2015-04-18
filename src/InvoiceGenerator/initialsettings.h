#ifndef INITIALSETTINGS_H
#define INITIALSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>

class GeneralInvoiceData;
class DataBaseData;

class InitialSettings : public QObject
{
    Q_OBJECT
public:
    explicit InitialSettings(const QString& org = "FamilyInc.", const QString &app = "Bussiness Application",
                             QObject *parent = 0);
    void saveGeneralInfo(const GeneralInvoiceData &data);
    void saveDBInfo(const DataBaseData &data);

    void propagateGeneralInfo(GeneralInvoiceData &data);
    void propagateDBInfo(DataBaseData &data);

    //protected attribute is only for unit tests purposes
protected:
    QString m_orgName;
    QString m_appName;
    QSettings m_settings;

    QString m_dataBaseGroupKey;
    QString m_generalGroupKey;

    QString m_generalCompanyNameKey;
    QString m_generalInvoiceTypeKey;
    QString m_generalTraderNameKey;
    QString m_generalTraderSurnameKey;

    QString m_DBUserNameKey;
    QString m_DBUserPwdKey;
    QString m_DBFileNameKey;
};

#endif // INITIALSETTINGS_H
