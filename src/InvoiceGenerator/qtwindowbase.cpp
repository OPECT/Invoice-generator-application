#include "qtwindowbase.h"
#include <QWidget>

QTWindowBase::QTWindowBase(const QString& name, QObject* parent) :  QObject(parent), m_windowName(name)
{
    m_mainWidget = new QWidget();
}

QTWindowBase::~QTWindowBase()
{
    if (!m_mainWidget->parent())
    {
        delete m_mainWidget;
    }
}

void QTWindowBase::show()
{
    m_mainWidget->show();
}

void QTWindowBase::hide()
{
    if (!m_mainWidget->isHidden())
    {
        m_mainWidget->hide();
    }
}
