#ifndef BAMODIFYDBSTATE_H
#define BAMODIFYDBSTATE_H

#include "bautils.h"
#include "bamodifydbbasestate.h"
#include "baengine.h"
#include "messageboxerrorreport.h"

template<typename WINDOW, typename MODEL, TABLE_NAMES TABLE_NAME>
class BAModifyDBState : public BAModifyDBBaseState
{
public:
    BAModifyDBState(BAEngine& engine, MainWindow& wnd);
    ~BAModifyDBState();
    virtual void notify(ALL_STATES_EVENTS event);

private:
    void recreateWindow();

private:
    MODEL* m_model;
};

template<typename WINDOW, typename MODEL, TABLE_NAMES TABLE_NAME>
BAModifyDBState<WINDOW, MODEL, TABLE_NAME>::BAModifyDBState(BAEngine& engine, MainWindow& wnd)
    : BAModifyDBBaseState(engine, wnd, Utils::tableNames()[TABLE_NAME])
{
    m_model = new MODEL(0, m_engine.dataBaseManager().database());
    m_model->setTable(Utils::tableNames()[TABLE_NAME]);
    m_window = new WINDOW(m_dbHandler, m_model, m_windowName, m_engine.dataBaseData());
    m_mainWindow.addWindow(m_window);

    connect(m_window, SIGNAL(dataBaseWindowEvent(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
}

template<typename WINDOW, typename MODEL, TABLE_NAMES TABLE_NAME>
BAModifyDBState<WINDOW, MODEL, TABLE_NAME>::~BAModifyDBState()
{
    if (!m_model->parent())
    {
        delete m_model;
    }
    disconnect(m_window, SIGNAL(dataBaseWindowEvent(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
    delete m_window;
}

template<typename WINDOW, typename MODEL, TABLE_NAMES TABLE_NAME>
void BAModifyDBState<WINDOW, MODEL, TABLE_NAME>::notify(ALL_STATES_EVENTS event)
{
    MessageBoxErrorReport report;

    switch(event)
    {
    case ASE_DATA_BASE_REOPENED:
        recreateWindow();
        break;
    default:
        report.reportError("Error during data base state notification");
        break;
    }
}

template<typename WINDOW, typename MODEL, TABLE_NAMES TABLE_NAME>
void BAModifyDBState<WINDOW, MODEL, TABLE_NAME>::recreateWindow()
{
    delete m_model;
    m_model = new MODEL(0, m_engine.dataBaseManager().database());
    m_model->setTable(Utils::tableNames()[TABLE_NAME]);

    m_mainWindow.removeWindow(m_window);
    disconnect(m_window, SIGNAL(dataBaseWindowEvent(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
    delete m_window;
    m_window = new WINDOW(m_dbHandler, m_model, m_windowName, m_engine.dataBaseData());
    m_mainWindow.addWindow(m_window);

    connect(m_window, SIGNAL(dataBaseWindowEvent(UI_EVENTS, QVariant)), this, SLOT(handle(UI_EVENTS, QVariant)));
}

#endif // BAMODIFYDBSTATE_H
