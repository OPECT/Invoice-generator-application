#include "qtaddcustomerdialog.h"
#include "badefines.h"
#include "qteditboxline.h"
#include "tablehandler.h"
#include "databasedata.h"

#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListIterator>
#include <QList>
#include <QVariant>

QTAddCustomerDialog::QTAddCustomerDialog(const QString& title, const TableHandler& customerTable,
    const DataBaseData& dbData, QWidget* parent) : QTAddDataDialog(parent), m_table(customerTable),
    m_customerNameMsg(tr("Customer name")), m_customerDiscountMsg(tr("Customer discount")),
    m_customerRegionMsg(tr("Customer region")), m_customerRegionEnterMsg(tr("Enter new region")),
    m_regionColumn(dbData.customerRegionColumn()), m_nameColumn(dbData.customerNameColumn()),
    m_discountValidator(0, MAX_DISCOUNT_VALUE, this)
{
    m_customerNameLine = new QTEditBoxLine(m_customerNameMsg, MAX_CUSTOMER_NAME_LENGTH);
    m_customerDiscountLine = new QTEditBoxLine(m_customerDiscountMsg, MAX_DISCOUNT_NUMBER_LENGTH,
                                               &m_discountValidator);

    connect(m_customerNameLine, SIGNAL(editBoxChanged(const QString&)), this, SLOT(activateAddButton()));
    connect(m_customerDiscountLine, SIGNAL(editBoxChanged(const QString&)), this, SLOT(activateAddButton()));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(m_customerNameLine->getLayout());
    mainLayout->addLayout(m_customerDiscountLine->getLayout());
    mainLayout->addLayout(createCustomerRegionLayout());
    mainLayout->addLayout(createButtonsLayout());

    setLayout(mainLayout);
    setWindowTitle(title);
    setFixedHeight(sizeHint().height());
}

QHBoxLayout* QTAddCustomerDialog::createCustomerRegionLayout()
{
    m_customerRegionCombo = new QComboBox();

    m_customerRegionCombo->addItem(m_customerRegionEnterMsg, "");
    QList<QVariant> regions;
    if (m_table.select(m_regionColumn, "", true, regions))
    {
        QListIterator<QVariant> iter(regions);
        while (iter.hasNext())
        {
            m_customerRegionCombo->addItem(iter.next().toString(), "");
        }
    }
    m_customerRegionCombo->setEditable(false);
    connect(m_customerRegionCombo, SIGNAL(activated(int)), this, SLOT(itemChoosed(qint32)));
    connect(m_customerRegionCombo, SIGNAL(highlighted(int)), this, SLOT(itemHighlighted()));
    connect(m_customerRegionCombo, SIGNAL(editTextChanged(const QString&)), this,
            SLOT(activateAddButton()));

    QHBoxLayout *comboLayout = new QHBoxLayout();
    comboLayout->addWidget(new QLabel(m_customerRegionMsg));
    comboLayout->addWidget(m_customerRegionCombo);
    comboLayout->addStretch();

    return comboLayout;
}

bool QTAddCustomerDialog::isNameCorrect(const QString& name)
{
    if (name.isEmpty())
    {
        return false;
    }

    QString filter = m_nameColumn + " = \"" + name + "\"";
    QList<QVariant> names;
    if (!m_table.select(m_nameColumn, filter, true, names) || !names.empty())
    {
        return false;
    }

    return true;
}

bool QTAddCustomerDialog::isDiscountCorrect(const QString& discountText)
{
    return !discountText.isEmpty();
}

void QTAddCustomerDialog::itemChoosed(qint32 index)
{
    if (index == 0)
    {
        m_customerRegionCombo->setItemText(index, "");
        m_customerRegionCombo->setEditable(true);
        m_customerRegionCombo->lineEdit()->setMaxLength(MAX_CUSTOMER_REGION_NAME_LENGTH);
    }
    else
    {
        m_customerRegionCombo->setEditable(false);
    }
    activateAddButton();
}

void QTAddCustomerDialog::activateAddButton()
{
    if (m_customerRegionCombo->currentText().isEmpty() || m_customerRegionCombo->currentText() ==
        m_customerRegionEnterMsg || !isNameCorrect(m_customerNameLine->getEditText()) ||
        !isDiscountCorrect(m_customerDiscountLine->getEditText()))
    {
        m_addBtn->setEnabled(false);
    }
    else
    {
        m_addBtn->setEnabled(true);
    }
}

void QTAddCustomerDialog::itemHighlighted()
{
    m_customerRegionCombo->setItemText(0, m_customerRegionEnterMsg);
}

void QTAddCustomerDialog::clearData()
{

}
