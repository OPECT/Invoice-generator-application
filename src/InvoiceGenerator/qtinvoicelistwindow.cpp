#include "qtinvoicelistwindow.h"
#include "invoicedata.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QFileDialog>

QTInvoiceListWindow::QTInvoiceListWindow(const QString& name, InvoiceList& list, QObject* parent)
    : QTWindowBase(name, parent), m_invoiceList(list), m_invoiceIdColumnName(tr("Invoice Id")),
      m_invoiceCustomerColumnName(tr("Customer")), m_invoiceItemCountColumnName(tr("Number of Items")),
      m_generateFileButtonMsg(tr("Generate")), m_deleteInvoiceButtonMsg(tr("Delete")),
      m_addInvoiceButtonMsg(tr("Add Invoice")), m_backButtonMsg(tr("Back")),
      m_generateDocumentMsg(tr("Generate new document")), m_invoiceFileFormat(".xlsx")
{
    QVBoxLayout* wndLayout = new QVBoxLayout();

    wndLayout->addLayout(createGridLayout());
    wndLayout->addLayout(createButtonsLayout());
    m_mainWidget->setLayout(wndLayout);
}

QHBoxLayout* QTInvoiceListWindow::createGridLayout()
{
    m_model = new QStandardItemModel();

    m_tableGrid = new QTableView();
    m_tableGrid->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableGrid->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_tableGrid, SIGNAL(clicked(QModelIndex)), this, SLOT(invoiceClicked(QModelIndex)));

    QHBoxLayout* gridLayout = new QHBoxLayout();
    gridLayout->addWidget(m_tableGrid);

    return gridLayout;
}

QHBoxLayout* QTInvoiceListWindow::createButtonsLayout()
{
    m_generateFileButton = new QPushButton(m_generateFileButtonMsg);
    m_deleteInvoiceButton = new QPushButton(m_deleteInvoiceButtonMsg);
    m_addInvoiceButton = new QPushButton(m_addInvoiceButtonMsg);
    m_backButton = new QPushButton(m_backButtonMsg);

    connect(m_generateFileButton, SIGNAL(clicked()), this, SLOT(generateInvoiceEvent()));
    connect(m_addInvoiceButton, SIGNAL(clicked()), this, SLOT(addInvoiceEvent()));
    connect(m_deleteInvoiceButton, SIGNAL(clicked()), this, SLOT(deleteInvoiceEvent()));
    connect(m_backButton, SIGNAL(clicked()), this, SLOT(backButtonEvent()));

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_generateFileButton);
    btnLayout->addStretch();
    btnLayout->addWidget(m_deleteInvoiceButton);
    btnLayout->addWidget(m_addInvoiceButton);
    btnLayout->addWidget(m_backButton);

    return btnLayout;
}

void QTInvoiceListWindow::updateWindow()
{
    m_model->clear();

    QStringList headers;
    headers << m_invoiceIdColumnName << m_invoiceCustomerColumnName << m_invoiceItemCountColumnName;
    m_model->setHorizontalHeaderLabels(headers);

    QListIterator<InvoiceData> iter(m_invoiceList);
    quint16 row = 0;
    while (iter.hasNext())
    {
        const InvoiceData& invoice = iter.next();
        QStandardItem *invoiceId = new QStandardItem(QString::number(invoice.invoiceID()));
        QStandardItem *customerName = new QStandardItem(invoice.customerName());
        QStandardItem *invoiceSize = new QStandardItem(QString::number(invoice.getGoodsList().size()));
        m_model->setItem(row, InvoiceIdColumn, invoiceId);
        m_model->setItem(row, CustomerNameColumn, customerName);
        m_model->setItem(row, InvoiceSizeColumn, invoiceSize);
        row++;
    }
    m_tableGrid->setModel(m_model);
    m_tableGrid->resizeColumnsToContents();
    m_tableGrid->setColumnWidth(CustomerNameColumn, m_tableGrid->columnWidth(CustomerNameColumn) * 2);

    m_deleteInvoiceButton->setEnabled(false);
}

void QTInvoiceListWindow::show()
{
    updateWindow();
    QTWindowBase::show();
}

void QTInvoiceListWindow::generateInvoiceEvent()
{
    QString fileName = QFileDialog::getSaveFileName(m_mainWidget, m_generateDocumentMsg, ".");
    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith(m_invoiceFileFormat))
        {
            fileName += m_invoiceFileFormat;
        }
        emit invoiceListEvents(UIE_GENERATE_INVOICE, fileName);
    }
}

void QTInvoiceListWindow::addInvoiceEvent()
{
    emit invoiceListEvents(UIE_ADD_NEW_INVOICE);
}

void QTInvoiceListWindow::deleteInvoiceEvent()
{
    m_invoiceList.removeAt(m_currentIndex.row());
    m_model->removeRow(m_currentIndex.row());
    m_model->submit();
    m_deleteInvoiceButton->setEnabled(false);
}

void QTInvoiceListWindow::backButtonEvent()
{
    emit invoiceListEvents(UIE_BACK);
}

void QTInvoiceListWindow::invoiceClicked(const QModelIndex &index)
{
    if (!index.isValid())
    {
        m_deleteInvoiceButton->setEnabled(false);
        m_currentIndex = index;
        return;
    }

    m_deleteInvoiceButton->setEnabled(true);
    if (m_currentIndex.isValid() && m_currentIndex.row() == index.row())
    {
        emit invoiceListEvents(UIE_EDIT_INVOICE, index.row());
    }
    m_currentIndex = index;
}
