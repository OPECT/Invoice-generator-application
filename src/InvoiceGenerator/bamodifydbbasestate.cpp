#include "bautils.h"
#include "bamodifydbbasestate.h"
#include "baengine.h"
#include "mainwindow.h"
#include "messageboxerrorreport.h"
#include "qtdatabasewindow.h"

#include <QFile>

BAModifyDBBaseState::BAModifyDBBaseState(BAEngine& engine, MainWindow& wnd, const QString& tableName)
    : BAState(engine), m_mainWindow(wnd), m_dbHandler(tableName, m_engine.dataBaseManager().database()),
      m_windowName("Goods DataBase")
{
}

BAModifyDBBaseState::~BAModifyDBBaseState()
{
}

void BAModifyDBBaseState::start(MainWindow &wnd)
{
    m_window->show();
    wnd.showWindow(m_window);
}

void BAModifyDBBaseState::handle(UI_EVENTS event, QVariant data)
{
    MessageBoxErrorReport report;
    QString newFileName;

    switch(event)
    {
    case UIE_BACK:
        m_engine.storeDataBaseDataNow();
        m_engine.switchState(BAS_START_UP);
        break;
    case UIE_DATA_BASE_SAVED:
        newFileName = data.toString();
        if (!newFileName.endsWith(Utils::dataBaseExtensions().at(0)))
        {
            newFileName += Utils::dataBaseExtensions().at(0);
        }
        QFile::copy(m_engine.dataBaseData().dataBaseFile(), newFileName);
        break;
    case UIE_NEW_DATABASE_LOADED:
        m_engine.dataBaseData().dataBaseFile(data.toString());
        m_engine.reopenDataBase();

        m_mainWindow.showWindow(m_window);
        break;
    default:
        report.reportError("Error in StartUp state");
    }
}
