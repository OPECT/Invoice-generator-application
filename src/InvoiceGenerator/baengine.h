#ifndef BAENGINE_H
#define BAENGINE_H

#include "batypes.h"
#include "mainwindow.h"
#include "initialsettings.h"
#include "generalinvoicedata.h"
#include <QMap>

class BAState;

class BAEngine
{
public:
    BAEngine();
    ~BAEngine();

    void run();
    void swithcState(BUSSINESS_APPLICATION_STATE state);

    void storeInvoiceDataNow() { m_settings.saveGeneralInfo(m_invoiceData); }

    GeneralInvoiceData& invoiceData() { return m_invoiceData; }

private:
    MainWindow m_window;
    ApplicationStates m_states;
    BAState* m_currentState;

    InitialSettings m_settings;
    GeneralInvoiceData m_invoiceData;
};

#endif // BAENGINE_H
