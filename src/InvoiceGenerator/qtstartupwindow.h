#ifndef QTSTARTUPWINDOW_H
#define QTSTARTUPWINDOW_H

#include "qtwindowbase.h"
#include "batypes.h"

#include <QIntValidator>
#include <QVariant>

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QCalendarWidget;
class QTEditBoxLine;
class QComboBox;
class GeneralInvoiceData;

class QTStartUpWindow : public QTWindowBase
{
    Q_OBJECT
public:
    QTStartUpWindow(GeneralInvoiceData& data, const QString& name, QObject* parent = 0);
    virtual ~QTStartUpWindow();

    virtual void show();

signals:
    void startUpWindowEvent(UI_EVENTS event, QVariant = QVariant());

private slots:
    void personalDataChanged(const QString& text);
    void activateButton();
    void exitPressed();
    void proceedPressed();
    void openCustomersPressed();
    void openGoodsPressed();

private:
    QHBoxLayout* createButtonsLayout();
    QHBoxLayout* createDataLayout();
    QVBoxLayout* createInvoiceDataLayout();
    QHBoxLayout* createInvoiceComboLayout();

    INVOICE_TYPE selectedInvoiceType();

private:
    GeneralInvoiceData& m_generalData;

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
