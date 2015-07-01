#ifndef BAENGINE_H
#define BAENGINE_H

#include "batypes.h"
#include "mainwindow.h"
#include "initialsettings.h"
#include "generalinvoicedata.h"
#include "databasedata.h"
#include "databasemanager.h"

#include <QMap>
#include <QString>

class BAState;

class BAEngine
{
public:
    BAEngine();
    ~BAEngine();

    void run();
    void switchState(BUSSINESS_APPLICATION_STATE state);
    void reopenDataBase();

    void storeInvoiceDataNow() { m_settings.saveGeneralInfo(m_invoiceData); }
    void storeDataBaseDataNow() { m_settings.saveDBInfo(m_dataBaseData); }

    GeneralInvoiceData& invoiceData() { return m_invoiceData; }
    DataBaseData& dataBaseData() { return m_dataBaseData; }
    DataBaseManager& dataBaseManager() { return m_dbManager; }

private:
    void prepareDataBase();
    void prepareDataBaseTables();

    void notifyAll(ALL_STATES_EVENTS event);

private:
    MainWindow m_window;
    ApplicationStates m_states;
    DataBaseManager m_dbManager;

    InitialSettings m_settings;
    GeneralInvoiceData m_invoiceData;
    DataBaseData m_dataBaseData;

    QString m_dbType;
    QString m_dbHost;
};

#endif // BAENGINE_H
