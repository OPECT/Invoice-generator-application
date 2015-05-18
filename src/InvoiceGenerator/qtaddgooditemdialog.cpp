#include "qtaddgooditemdialog.h"
#include "bautils.h"
#include "badefines.h"
#include "qteditboxline.h"
#include "tablehandler.h"
#include "databasedata.h"

#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHashIterator>
#include <QList>
#include <QVariant>

QTAddGoodItemDialog::QTAddGoodItemDialog(const QString& title, const TableHandler& goodTable,
    const DataBaseData& dbData, QWidget* parent) :
    QTAddDataDialog(parent), m_table(goodTable), m_goodTypeMsg(tr("Good Type")), m_goodNameMsg(tr("Good name")),
    m_goodPriceMsg(tr("Good price")), m_goodCategoryMsg(tr("Good category")),
    m_goodCategoryEnterMsg(tr("Enter new category")), m_categoryColumn(dbData.goodCategoryColumn()),
    m_nameColumn(dbData.goodNameColumn()), m_priceValidator()
{
    m_priceValidator.setNotation(QDoubleValidator::StandardNotation);
    m_goodNameLine = new QTEditBoxLine(m_goodNameMsg, MAX_GOOD_NAME_LENGTH);
    m_goodPriceLine = new QTEditBoxLine(m_goodPriceMsg, MAX_FLOAT_NUMBER_LENGTH, &m_priceValidator);

    connect(m_goodNameLine, SIGNAL(editBoxChanged(const QString&)), this, SLOT(activateAddButton()));
    connect(m_goodPriceLine, SIGNAL(editBoxChanged(const QString&)), this, SLOT(activateAddButton()));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(m_goodNameLine->getLayout());
    mainLayout->addLayout(m_goodPriceLine->getLayout());
    mainLayout->addLayout(createGoodTypeLayout());
    mainLayout->addLayout(createGoodCategoryLayout());
    mainLayout->addLayout(createButtonsLayout());

    setLayout(mainLayout);
    setWindowTitle(title);
    setFixedHeight(sizeHint().height());
}

QHBoxLayout* QTAddGoodItemDialog::createGoodTypeLayout()
{
    using Utils::goodTypes;

    m_goodTypeCombo = new QComboBox();
    QLabel* goodTypeLabel = new QLabel(m_goodTypeMsg);

    QHashIterator<Utils::GOOT_TYPE, QString> iter(goodTypes());

    while (iter.hasNext())
    {
        m_goodTypeCombo->addItem(tr(iter.next().value().toUtf8()), "");
    }
    m_goodTypeCombo->setEditable(false);

    QHBoxLayout* comboLayout = new QHBoxLayout();
    comboLayout->addWidget(goodTypeLabel);
    comboLayout->addStretch();
    comboLayout->addWidget(m_goodTypeCombo);
    comboLayout->addStretch();

    return comboLayout;
}

QHBoxLayout* QTAddGoodItemDialog::createGoodCategoryLayout()
{
    m_goodCategoryCombo = new QComboBox();
    QLabel* goodCategoryLabel = new QLabel(m_goodCategoryMsg);

    m_goodCategoryCombo->addItem(m_goodCategoryEnterMsg, "");

    QList<QVariant> categories;
    if (m_table.select(m_categoryColumn, "", true, categories))
    {
        QListIterator<QVariant> iter(categories);
        while (iter.hasNext())
        {
            m_goodCategoryCombo->addItem(iter.next().toString(), "");
        }
    }
    m_goodCategoryCombo->setEditable(false);
    connect(m_goodCategoryCombo, SIGNAL(activated(int)), this, SLOT(itemChoosed(qint32)));
    connect(m_goodCategoryCombo, SIGNAL(highlighted(int)), this, SLOT(itemHighlighted()));
    connect(m_goodCategoryCombo, SIGNAL(editTextChanged(const QString&)), this,
            SLOT(activateAddButton()));

    QHBoxLayout *comboLayout = new QHBoxLayout();
    comboLayout->addWidget(goodCategoryLabel);
    comboLayout->addWidget(m_goodCategoryCombo);
    comboLayout->addStretch();

    return comboLayout;
}

bool QTAddGoodItemDialog::isNameCorrect(const QString& name)
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

bool QTAddGoodItemDialog::isPriceCorrect(const QString& price)
{
    bool result;
    price.toDouble(&result);

    return result;
}

void QTAddGoodItemDialog::itemChoosed(qint32 index)
{
    if (index == 0)
    {
        m_goodCategoryCombo->setItemText(index, "");
        m_goodCategoryCombo->setEditable(true);
    }
    else
    {
        m_goodCategoryCombo->setEditable(false);
    }
    activateAddButton();
}

void QTAddGoodItemDialog::activateAddButton()
{
    if (m_goodCategoryCombo->currentText().isEmpty() || m_goodCategoryCombo->currentText() == m_goodCategoryEnterMsg ||
        !isNameCorrect(m_goodNameLine->getEditText()) || !isPriceCorrect(m_goodPriceLine->getEditText()))
    {
        m_addBtn->setEnabled(false);
    }
    else
    {
        m_addBtn->setEnabled(true);
    }
}

void QTAddGoodItemDialog::itemHighlighted()
{
    m_goodCategoryCombo->setItemText(0, m_goodCategoryEnterMsg);
}

void QTAddGoodItemDialog::clearData()
{

}
