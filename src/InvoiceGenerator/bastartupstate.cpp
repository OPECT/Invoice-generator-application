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

    connect(m_window, SIGNAL(startUpWindowEvent(UI_EVENTS)), this, SLOT(handle(UI_EVENTS)));
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

void BAStartUpState::handle(UI_EVENTS event)
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
    default:
        report.reportError(tr("Error in StartUp state"));
    }
}
