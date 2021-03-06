#include "qtgoodsdatabasewindow.h"
#include "qtaddgooditemdialog.h"
#include "qsqlgoodsmodel.h"
#include "databasedata.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

QTGoodsDataBaseWindow::QTGoodsDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model,
    const QString& name, const DataBaseData& dbData, QObject* parent) :
    QTDataBaseWindow(sqlHandler, model, name, dbData.goodCategoryColumn(), parent), m_dataBaseData(dbData),
    m_addGoodsMsg(tr("Add New Good"))
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

void QTGoodsDataBaseWindow::addItemButtonEvent()
{
    QTAddGoodItemDialog dlg(m_addGoodsMsg, m_sqlHandler, m_dataBaseData);
    if (!dlg.exec())
    {
        return;
    }

    quint16 newRowIndex = m_dataModel->rowCount();
    m_dataModel->insertRows(newRowIndex, 1);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLGoodsModel::GDC_NAME), dlg.goodName(), Qt::UserRole);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLGoodsModel::GDC_TYPE), dlg.goodType(), Qt::UserRole);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLGoodsModel::GDC_PRICE), dlg.goodPrice(), Qt::UserRole);
    m_dataModel->setData(m_dataModel->index(newRowIndex, QSQLGoodsModel::GDC_CATEGORY), dlg.goodCategory(),
                         Qt::UserRole);
    m_dataModel->submitAll();

// XXX think about switching tabs in case new region was entered
}

void QTGoodsDataBaseWindow::backButtonEvent()
{
    emit dataBaseWindowEvent(UIE_BACK, QVariant());
}
