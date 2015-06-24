#include "qtstartupwindow.h"
#include "badefines.h"
#include "qteditboxline.h"
#include "bautils.h"
#include "generalinvoicedata.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QCalendarWidget>
#include <QComboBox>
#include <QMapIterator>
#include <QFile>

QTStartUpWindow::QTStartUpWindow(GeneralInvoiceData& data, const QString &name, QObject *parent)
    : QTWindowBase(name, parent), m_generalData(data), m_invoiceNumberMsg(tr("Enter invoice number")),
    m_companyNameMsg(tr("Enter company name")), m_traderNameMsg(tr("Enter trader name")),
    m_traderSurnameMsg(tr("Enter trader surname")), m_invoiceComboeMsg(tr("Choose invoice type")),
    m_invoiceIdValidator(0, MAX_INVOICE_ID_VALUE, this)
{
    QVBoxLayout* wndLayout = new QVBoxLayout();
    wndLayout->addLayout(createDataLayout());
    wndLayout->addStretch();
    wndLayout->addLayout(createButtonsLayout());

    m_mainWidget->setLayout(wndLayout);
}

QTStartUpWindow::~QTStartUpWindow()
{
    delete m_invoiceNumber;
    delete m_companyName;
    delete m_traderName;
    delete m_traderSurname;
}

void QTStartUpWindow::show()
{
    if (m_companyName->getEditText().isEmpty())
    {
        m_companyName->setEditText(m_generalData.companyName());
    }
    if (m_traderName->getEditText().isEmpty())
    {
        m_traderName->setEditText(m_generalData.traderName());
    }
    if (m_traderSurname->getEditText().isEmpty())
    {
        m_traderSurname->setEditText(m_generalData.traderSecondName());
    }
    QTWindowBase::show();
}

QHBoxLayout* QTStartUpWindow::createButtonsLayout()
{
    m_proceedButton = new QPushButton(tr("Invoices"));
    m_goodsButton = new QPushButton(tr("Goods"));
    m_customersButton = new QPushButton(tr("Customers"));
    m_exitButton = new QPushButton(tr("Exit"));

    m_proceedButton->setEnabled(false);
    connect(m_proceedButton, SIGNAL(clicked()), this, SLOT(proceedPressed()));
    connect(m_goodsButton, SIGNAL(clicked()), this, SLOT(openGoodsPressed()));
    connect(m_customersButton, SIGNAL(clicked()), this, SLOT(openCustomersPressed()));
    connect(m_exitButton, SIGNAL(clicked()), this, SLOT(exitPressed()));

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_goodsButton);
    btnLayout->addWidget(m_customersButton);
    btnLayout->addStretch();
    btnLayout->addWidget(m_proceedButton);
    btnLayout->addWidget(m_exitButton);

    return btnLayout;
}

QHBoxLayout* QTStartUpWindow::createDataLayout()
{
    m_calendar = new QCalendarWidget();
    m_calendar->setMaximumSize(m_calendar->minimumSizeHint());

    QHBoxLayout* dataLayout = new QHBoxLayout();
    dataLayout->addWidget(m_calendar);
    dataLayout->addLayout(createInvoiceDataLayout());

    return dataLayout;
}

QVBoxLayout* QTStartUpWindow::createInvoiceDataLayout()
{
    m_invoiceNumber = new QTEditBoxLine(m_invoiceNumberMsg, MAX_INVOICE_ID_LENGTH, &m_invoiceIdValidator);
    m_companyName = new QTEditBoxLine(m_companyNameMsg, MAX_COMPANY_NAME_LENGTH);
    m_traderName = new QTEditBoxLine(m_traderNameMsg, MAX_TRADER_NAME_LENGTH);
    m_traderSurname = new QTEditBoxLine(m_traderSurnameMsg, MAX_TRADER_SECOND_NAME_LENGTH);

    connect(m_invoiceNumber, SIGNAL(editBoxChanged(const QString&)), this, SLOT(personalDataChanged(const QString&)));
    connect(m_companyName, SIGNAL(editBoxChanged(const QString&)), this, SLOT(personalDataChanged(const QString&)));
    connect(m_traderName, SIGNAL(editBoxChanged(const QString&)), this, SLOT(personalDataChanged(const QString&)));
    connect(m_traderSurname, SIGNAL(editBoxChanged(const QString&)), this, SLOT(personalDataChanged(const QString&)));

    QVBoxLayout* dataLayout = new QVBoxLayout();
    dataLayout->addLayout(createInvoiceComboLayout());
    dataLayout->addLayout(m_invoiceNumber->getLayout());
    dataLayout->addLayout(m_companyName->getLayout());
    dataLayout->addLayout(m_traderName->getLayout());
    dataLayout->addLayout(m_traderSurname->getLayout());
    dataLayout->addStretch();

    return dataLayout;
}

QHBoxLayout* QTStartUpWindow::createInvoiceComboLayout()
{
    m_invoiceCombo = new QComboBox();

    QMap<INVOICE_TYPE, QString> types(Utils::invoiceTypes());
    QMapIterator<INVOICE_TYPE, QString> invoiceTypeIter(types);

    while (invoiceTypeIter.hasNext())
    {
        m_invoiceCombo->addItem(tr(invoiceTypeIter.next().value().toStdString().c_str()), "");
    }
    connect(m_invoiceCombo, SIGNAL(activated(int)), this, SLOT(activateButton()));

    QHBoxLayout* comboLayout = new QHBoxLayout();
    comboLayout->addWidget(new QLabel(m_invoiceComboeMsg));
    comboLayout->addWidget(m_invoiceCombo);
    comboLayout->addStretch();

    return comboLayout;
}

INVOICE_TYPE QTStartUpWindow::currentComboItemToInvoiceType()
{
    return Utils::invoiceTypes().key(m_invoiceCombo->currentText());
}

void QTStartUpWindow::personalDataChanged(const QString& text)
{
    if (text.isEmpty())
    {
        m_proceedButton->setEnabled(false);
    }
    else
    {
        activateButton();
    }
}

void QTStartUpWindow::activateButton()
{
    if (m_invoiceNumber->getEditText().isEmpty() || m_companyName->getEditText().isEmpty() ||
        m_traderName->getEditText().isEmpty() || m_traderSurname->getEditText().isEmpty() ||
        !QFile::exists(Utils::invoiceTypeFiles().value(currentComboItemToInvoiceType())))
    {
        m_proceedButton->setEnabled(false);
    }
    else
    {
        m_proceedButton->setEnabled(true);
    }
}

void QTStartUpWindow::exitPressed()
{
    emit startUpWindowEvent(UIE_EXIT);
}

void QTStartUpWindow::proceedPressed()
{
    m_generalData.companyName(m_companyName->getEditText());
    m_generalData.invoiceId(m_invoiceNumber->getEditText().toUInt());
    m_generalData.invoiceType(Utils::invoiceTypes().key(m_invoiceCombo->currentText()));
    m_generalData.traderName(m_traderName->getEditText());
    m_generalData.traderSecondName(m_traderSurname->getEditText());
    m_generalData.date(m_calendar->selectedDate());
    emit startUpWindowEvent(UIE_STARTUP_PROCEED);
}

void QTStartUpWindow::openCustomersPressed()
{
    emit startUpWindowEvent(UIE_OPEN_CUSTOMERS_DB);
}

void QTStartUpWindow::openGoodsPressed()
{
    emit startUpWindowEvent(UIE_OPEN_GOODS_DB);
}
