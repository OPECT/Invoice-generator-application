#include "qtdatabasewindow.h"
#include "tablehandler.h"
#include "bautils.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTabWidget>
#include <QTableView>
#include <QListIterator>
#include <QFileDialog>
#include <QStringListIterator>

QTDataBaseWindow::QTDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model, const QString& name,
                                   const QString& filter, QObject* parent)
    : QTWindowBase(name, parent), m_dataModel(model), m_sqlHandler(sqlHandler), m_filterColumn(filter),
      m_openDBButtonMsg(tr("Open Data Base")), m_saveDBButtonMsg(tr("Save Data Base")),
      m_deleteItemButtonMsg(tr("Delete Item")), m_addItemButtonMsg(tr("Add New Item")), m_backButtonMsg(tr("Back")),
      m_openDBMsg(tr("Open Data Base")), m_saveDBMsg(tr("Save Data Base")), m_filterDBMsg(tr("DataBase files"))
{
    QStringListIterator iter(Utils::dataBaseExtensions());
    if (iter.hasNext())
    {
        m_dbFilterList += "(*" + iter.next() + ")";
    }

    while(iter.hasNext())
    {
        m_dbFilterList += " (*" + iter.next() + ")";
    }

}

void QTDataBaseWindow::show()
{
    tabChanged(0);
    QTWindowBase::show();
}

QHBoxLayout* QTDataBaseWindow::createTableGridLayout()
{
    m_dataModel->select();

    m_tabWidget = new QTabWidget();
    addTabs();

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(qint32)));

    QHBoxLayout* gridLayout = new QHBoxLayout();
    gridLayout->addWidget(m_tabWidget);

    return gridLayout;
}

QHBoxLayout* QTDataBaseWindow::createButtonsLayout()
{
    m_openDBButton = new QPushButton(m_openDBButtonMsg);
    m_saveDBButton = new QPushButton(m_saveDBButtonMsg);
    m_deleteItemButton = new QPushButton(m_deleteItemButtonMsg);
    m_addItemButton = new QPushButton(m_addItemButtonMsg);
    m_backButton = new QPushButton(m_backButtonMsg);

    m_deleteItemButton->setEnabled(false);

    connect(m_openDBButton, SIGNAL(clicked()), this, SLOT(openDBButtonEvent()));
    connect(m_saveDBButton, SIGNAL(clicked()), this, SLOT(saveDBButtonEvent()));

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_openDBButton);
    btnLayout->addWidget(m_saveDBButton);
    btnLayout->addStretch();
    btnLayout->addWidget(m_deleteItemButton);
    btnLayout->addWidget(m_addItemButton);
    btnLayout->addWidget(m_backButton);

    return btnLayout;
}

QWidget* QTDataBaseWindow::createTableWidget()
{
    QTableView* table = new QTableView();

    table->setModel(m_dataModel);
    table->setAlternatingRowColors(true);
    table->setColumnHidden(0, true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableViews.append(table);
    connect(table, SIGNAL(clicked(const QModelIndex &)), this, SLOT(tableSelectionChanged(const QModelIndex &)));

    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(table);
    tab->setLayout(layout);
    return tab;
}

void QTDataBaseWindow::addTabs()
{
    QList<QVariant> tabs;
    m_sqlHandler.select(m_filterColumn, "", true, tabs);

    m_tabWidget->addTab(createTableWidget(), "All");

    QListIterator<QVariant> iter(tabs);
    while (iter.hasNext())
    {
        m_tabWidget->addTab(createTableWidget(), iter.next().toString());
    }
}

void QTDataBaseWindow::tabChanged(qint32 index)
{
    m_dataModel->setTable(m_dataModel->tableName());
    if (index != 0)
    {
        m_dataModel->setFilter(m_filterColumn + " = \"" + m_tabWidget->tabText(index) + "\"");
    }
    m_dataModel->select();
    m_deleteItemButton->setEnabled(false);
}

void QTDataBaseWindow::tableSelectionChanged(const QModelIndex &index)
{
    m_deleteItemButton->setEnabled(index.isValid());
}

void QTDataBaseWindow::deleteItemButtonEvent()
{
    quint32 itemIndex = m_tableViews.at(m_tabWidget->currentIndex())->currentIndex().row();

    m_dataModel->removeRows(itemIndex, 1);
    m_dataModel->submitAll();
    tabChanged(m_tabWidget->currentIndex());
}

void QTDataBaseWindow::openDBButtonEvent()
{
    QString fileName = QFileDialog::getOpenFileName(m_mainWidget, m_openDBMsg, ".",
                                                    m_filterDBMsg + " " + m_dbFilterList);
    if (!fileName.isEmpty())
    {
        emit dataBaseWindowEvent(UIE_NEW_DATABASE_LOADED, fileName);
    }
}

void QTDataBaseWindow::saveDBButtonEvent()
{
    QString fileName = QFileDialog::getSaveFileName(m_mainWidget, m_saveDBMsg, ".", m_filterDBMsg + m_dbFilterList);
    if (!fileName.isEmpty())
    {
        emit dataBaseWindowEvent(UIE_DATA_BASE_SAVED, fileName);
    }
}
