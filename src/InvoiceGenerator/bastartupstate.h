#ifndef BASTARTUPSTATE_H
#define BASTARTUPSTATE_H

#include "bastate.h"
#include <QString>

class QTStartUpWindow;

class BAStartUpState : public BAState
{
    Q_OBJECT

public:
    BAStartUpState(BAEngine& engine, MainWindow& wnd);
    ~BAStartUpState();

    virtual void start(MainWindow& wnd);
    virtual void notify(ALL_STATES_EVENTS event);

public slots:
    virtual void handle(UI_EVENTS event, QVariant data);

private:
    QTStartUpWindow* m_window;

    QString m_windowTitle;
};

#endif // BASTARTUPSTATE_H
