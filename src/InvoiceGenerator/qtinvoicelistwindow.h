#ifndef QTINVOICELISTWINDOW_H
#define QTINVOICELISTWINDOW_H

#include "qtwindowbase.h"
#include "batypes.h"
#include <QVariant>
#include <QModelIndex>

class QPushButton;
class QHBoxLayout;
class QTableView;
class QStandardItemModel;

class QTInvoiceListWindow : public QTWindowBase
{
    Q_OBJECT
public:
    QTInvoiceListWindow(const QString& name, InvoiceList& list, QObject* parent = 0);

signals:
    void dataBaseWindowEvent(UI_EVENTS event, QVariant data = QVariant());

protected slots:
    void generateInvoiceEvent();
    void addInvoiceEvent();
    void deleteInvoiceEvent();
    void backButtonEvent();

    void invoiceClicked(const QModelIndex &index);

private:
    QHBoxLayout* createButtonsLayout();
    QHBoxLayout* createGridLayout();

private:
    InvoiceList& m_invoiceList;

    QPushButton* m_generateFileButton;
    QPushButton* m_deleteInvoiceButton;
    QPushButton* m_addInvoiceButton;
    QPushButton* m_backButton;

    QStandardItemModel* m_model;
    QTableView* m_tableGrid;
    QModelIndex m_currentIndex;

    QString m_invoiceIdColumnName;
    QString m_invoiceCustomerColumnName;
    QString m_invoiceItemCountColumnName;

    QString m_generateFileButtonMsg;
    QString m_deleteInvoiceButtonMsg;
    QString m_addInvoiceButtonMsg;
    QString m_backButtonMsg;

    static const quint16 InvoiceIdColumn = 0;
    static const quint16 CustomerNameColumn = 1;
    static const quint16 InvoiceSizeColumn = 2;
};

#endif // QTINVOICELISTWINDOW_H
