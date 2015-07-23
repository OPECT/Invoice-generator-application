#ifndef BAINVOICELISTSTATE_H
#define BAINVOICELISTSTATE_H

#include "bastate.h"
#include "batypes.h"

class QTInvoiceListWindow;

class BAInvoiceListState : public BAState
{
    Q_OBJECT
public:
    BAInvoiceListState(BAEngine& engine, MainWindow& wnd);
    ~BAInvoiceListState();

    virtual void start(MainWindow& wnd);
    virtual void notify(ALL_STATES_EVENTS event);

public slots:
    virtual void handle(UI_EVENTS event, QVariant data);

private:
    void generateDocument(const QString& file);

private:
    QTInvoiceListWindow* m_window;
    InvoiceList m_invoiceList;

    QString m_windowTitle;
};

#endif // BAINVOICELISTSTATE_H
