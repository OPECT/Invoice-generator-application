#ifndef BASTATE_H
#define BASTATE_H

#include "batypes.h"
#include <QObject>
#include <QVariant>

class MainWindow;
class BAEngine;

class BAState : public QObject
{
public:
    BAState(BAEngine& engine);
    virtual ~BAState();

    virtual void start(MainWindow& wnd) = 0;
    virtual void notify(ALL_STATES_EVENTS event) = 0;

public slots:
    virtual void handle(UI_EVENTS event, QVariant data = QVariant()) = 0;

protected:
    BAEngine& m_engine;
};

#endif // BASTATE_H
