#include "messageboxerrorreport.h"

QString MessageBoxErrorReport::m_trErrorTitle = tr("Invoice Generator Error");
QString MessageBoxErrorReport::m_trWarningTitle = tr("Invoice Generator Warning");

MessageBoxErrorReport::MessageBoxErrorReport(QWidget * parent)
    : ErrorReport(), QMessageBox(parent)
{
}

MessageBoxErrorReport::~MessageBoxErrorReport()
{
}

void MessageBoxErrorReport::reportError(const QString& msg, ErrorSeverityLevel level)
{
    if (level == ErrorReport::ESL_CRITICAL)
    {
        QMessageBox::critical(0, m_trErrorTitle, msg);
    }
    else
    {
        QMessageBox::warning(0, m_trWarningTitle, msg);
    }
}
