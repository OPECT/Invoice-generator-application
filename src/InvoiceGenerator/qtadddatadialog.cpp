#include "qtadddatadialog.h"

#include <QPushButton>
#include <QHBoxLayout>

QTAddDataDialog::QTAddDataDialog(QWidget *parent) : QDialog(parent)
{
}

void QTAddDataDialog::show()
{
    clearData();
    QDialog::show();
}

void QTAddDataDialog::addConfirmed()
{
    emit addConfirmedNofify();
}

QHBoxLayout* QTAddDataDialog::createButtonsLayout()
{
    m_addBtn = new QPushButton(tr("Add"));
    m_cancelBtn = new QPushButton(tr("Cancel"));

    m_addBtn->setEnabled(false);
    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_addBtn, SIGNAL(clicked()), this, SLOT(addConfirmed()));

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(m_addBtn);
    btnLayout->addWidget(m_cancelBtn);

    return btnLayout;
}
