#include "qtaddcategorydialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

QTAddCategoryDialog::QTAddCategoryDialog(const QString &title, const QString &description, quint32 dataLimit,
                                                             QWidget *parent) :
    QTAddDataDialog(parent), m_category(description, dataLimit, 0, this), m_addBtn(tr("Add")), m_cancelBtn(tr("Cancel"))
{
    m_addBtn.setEnabled(false);
    connect(&m_cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(&m_addBtn, SIGNAL(clicked()), this, SLOT(addConfirmed()));
    connect(&m_category, SIGNAL(editBoxChanged(const QString&)), this, SLOT(textChanged(const QString&)));

    QHBoxLayout *pBtnLayout = new QHBoxLayout();
    pBtnLayout->addStretch();
    pBtnLayout->addWidget(&m_addBtn);
    pBtnLayout->addWidget(&m_cancelBtn);

    QVBoxLayout *pMainLayout = new QVBoxLayout();
    pMainLayout->addLayout(m_category.getLayout());
    pMainLayout->addLayout(pBtnLayout);

    setLayout(pMainLayout);
    setWindowTitle(title);
    setFixedHeight(sizeHint().height());
}

void QTAddCategoryDialog::textChanged(const QString &text)
{
    m_addBtn.setEnabled(m_category.isDataReady());
}
