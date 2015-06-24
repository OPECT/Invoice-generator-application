#ifndef BASTARTUPSTATE_H
#define BASTARTUPSTATE_H

#include "bastate.h"
#include <QString>

class QTStartUpWindow;
class BAEngine;

class BAStartUpState : public BAState
{
    Q_OBJECT

public:
    BAStartUpState(BAEngine& engine, MainWindow& wnd);
    ~BAStartUpState();

    virtual void start(MainWindow& wnd);

public slots:
    virtual void handle(UI_EVENTS event);

private:
    QTStartUpWindow* m_window;

    QString m_windowTitle;
};

#endif // BASTARTUPSTATE_H
