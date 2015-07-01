#ifndef BAGOODSMODIFYSTATE_H
#define BAGOODSMODIFYSTATE_H

#include "bastate.h"
#include "tablehandler.h"

#include <QString>

class QTDataBaseWindow;

class BAModifyDBBaseState : public BAState
{
    Q_OBJECT
public:
    BAModifyDBBaseState(BAEngine& engine, MainWindow& wnd, const QString& tableName);
    ~BAModifyDBBaseState();

    virtual void start(MainWindow& wnd);

public slots:
    virtual void handle(UI_EVENTS event, QVariant data);

protected:
    MainWindow& m_mainWindow;
    TableHandler m_dbHandler;

    QTDataBaseWindow* m_window;

    QString m_windowName;
};

#endif // BAGOODSMODIFYSTATE_H
