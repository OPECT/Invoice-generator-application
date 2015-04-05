#ifndef MESSAGEBOXERRORREPORT_H
#define MESSAGEBOXERRORREPORT_H

#include "errorreport.h"
#include <QMessageBox>

class MessageBoxErrorReport : public ErrorReport, public QMessageBox
{
public:
    MessageBoxErrorReport(QWidget * parent = 0);
    virtual ~MessageBoxErrorReport();

    virtual void reportError(const QString& msg, ErrorSeverityLevel level = ErrorReport::ESL_CRITICAL);

private:
    static QString m_trErrorTitle;
    static QString m_trWarningTitle;
};

#endif // MESSAGEBOXERRORREPORT_H
