#include "qtcustomerdatabasewindow.h"
#include "qtaddcustomerdialog.h"
#include "qsqlcustomermodel.h"
#include "databasedata.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

QTCustomerDataBaseWindow::QTCustomerDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model,
    const QString& name, const DataBaseData& dbData, QObject* parent) :
    QTDataBaseWindow(sqlHandler, model, name, dbData.customerRegionColumn(), parent), m_dataBaseData(dbData),
    m_addCustomerMsg(tr("Add New Customer"))
{
    QVBoxLayout* wndLayout = new QVBoxLayout();
    wndLayout->addLayout(createTableGridLayout());
    wndLayout->addStretch();
    wndLayout->addLayout(createButtonsLayout());

    connect(m_addItemButton, SIGNAL(clicked()), this, SLOT(addItemButtonEvent()));
    connect(m_deleteItemButton, SIGNAL(clicked()), this, SLOT(deleteItemButtonEvent()));
    connect(m_backButton, SIGNAL(clicked()), this, SLOT(backButtonEvent()));
    m_mainWidget->setLayout(wndLayout);
}

void QTCustomerDataBaseWindow::addItemButtonEvent()
{
    QTAddCustomerDialog dlg(m_addCustomerMsg, m_sqlHandler, m_dataBaseData);
    if (!dlg.exec())
    {
        return;
    }

    quint16 newRowIndex = m_dataModel->rowCount();
    m_dataModel->insertRows(newRowIndex, 1);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLCustomerModel::CDC_NAME), dlg.customerName(),
                         Qt::UserRole);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLCustomerModel::CDC_REGION), dlg.customerRegion(),
                         Qt::UserRole);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLCustomerModel::CDC_MULTIPLIER), dlg.customerDiscount(),
                         Qt::UserRole);
    m_dataModel->submitAll();

    // XXX think about switching tabs in case new region was entered
}

void QTCustomerDataBaseWindow::backButtonEvent()
{
    emit dataBaseWindowEvent(UIE_BACK, QVariant());
}
