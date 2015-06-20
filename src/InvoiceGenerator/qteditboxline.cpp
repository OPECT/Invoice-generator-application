#include "qteditboxline.h"

QTEditBoxLine::QTEditBoxLine(const QString& label, quint32 editLimit, const QValidator* validator, QObject *parent) :
    QObject(parent)
{
    m_info = new QLabel(label);
    m_info->setMinimumWidth(label.count() * m_info->font().pointSize());

    m_edit = new QLineEdit();
    m_edit->setMinimumWidth(editLimit * m_edit->font().pointSize());
    m_edit->setMaxLength(editLimit);
    m_edit->setValidator(validator);

    m_layout = new QHBoxLayout();
    m_layout->addWidget(m_info);
    m_layout->addWidget(m_edit);
    m_layout->addStretch();

    connect(m_edit, SIGNAL(textChanged(const QString&)), this, SIGNAL(editBoxChanged(const QString&)));
}

QTEditBoxLine::~QTEditBoxLine()
{
    if (!m_layout->parent())
    {
        delete m_layout;
    }
}

void QTEditBoxLine::setEditLimit(quint32 limit)
{
    m_edit->setMaximumWidth(limit * m_edit->font().pointSize());
    m_edit->setMaxLength(limit);
}
