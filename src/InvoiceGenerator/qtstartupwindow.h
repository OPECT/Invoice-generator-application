#ifndef QTSTARTUPWINDOW_H
#define QTSTARTUPWINDOW_H

#include "qtwindowbase.h"
#include "batypes.h"

#include <QIntValidator>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QCalendarWidget;
class QTEditBoxLine;
class QComboBox;

class QTStartUpWindow : public QTWindowBase
{
    Q_OBJECT
public:
    QTStartUpWindow(const QString& name, QObject* parent = 0);
    virtual ~QTStartUpWindow() { }

private slots:
    void personalDataChanged(const QString& text);
    void activateButton();

private:
    QHBoxLayout* createButtonsLayout();
    QHBoxLayout* createDataLayout();
    QVBoxLayout* createInvoiceDataLayout();
    QVBoxLayout* createTraderDataLayout();
    QHBoxLayout* createInvoiceComboLayout();

    INVOICE_TYPE currentComboItemToInvoiceType();

private:
    QCalendarWidget* m_calendar;
    QComboBox* m_invoiceCombo;

    QTEditBoxLine* m_invoiceNumber;
    QTEditBoxLine* m_companyName;
    QTEditBoxLine* m_traderName;
    QTEditBoxLine* m_traderSurname;

    QPushButton* m_customersButton;
    QPushButton* m_goodsButton;
    QPushButton* m_proceedButton;
    QPushButton* m_exitButton;

    QString m_invoiceNumberMsg;
    QString m_companyNameMsg;
    QString m_traderNameMsg;
    QString m_traderSurnameMsg;
    QString m_invoiceComboeMsg;

    QIntValidator m_invoiceIdValidator;
};

#endif // QTSTARTUPWINDOW_H
