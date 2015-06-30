#include "bastartupstate.h"
#include "qtstartupwindow.h"
#include "mainwindow.h"
#include "messageboxerrorreport.h"
#include "baengine.h"

#include <QApplication>

BAStartUpState::BAStartUpState(BAEngine& engine, MainWindow& wnd) : BAState(engine), m_windowTitle("StartUp Window")
{
    m_window = new QTStartUpWindow(m_engine.invoiceData(), m_windowTitle);
    wnd.addWindow(m_window);

    connect(m_window, SIGNAL(startUpWindowEvent(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
}

BAStartUpState::~BAStartUpState()
{
    delete m_window;
}

void BAStartUpState::start(MainWindow &wnd)
{
    m_window->show();
    wnd.showWindow(m_window);
}

void BAStartUpState::notify(ALL_STATES_EVENTS event)
{
    MessageBoxErrorReport report;

    switch(event)
    {
    case ASE_DATA_BASE_REOPENED:
        break;
    default:
        report.reportError("Error during start up state notification");
        break;
    }
}

void BAStartUpState::handle(UI_EVENTS event, QVariant data)
{
    MessageBoxErrorReport report;

    switch(event)
    {
    case UIE_EXIT:
        QApplication::exit();
        break;
    case UIE_STARTUP_PROCEED:
        m_engine.storeInvoiceDataNow();
        break;
    case UIE_OPEN_GOODS_DB:
        m_engine.switchState(BAS_GOODS_DB);
        break;
    case UIE_OPEN_CUSTOMERS_DB:
        m_engine.switchState(BAS_CUSTOMERS_DB);
        break;
    default:
        report.reportError("Error in StartUp state");
    }
}
