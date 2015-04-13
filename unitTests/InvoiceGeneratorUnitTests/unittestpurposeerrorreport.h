#ifndef UNITTESTPURPOSEERRORREPORT_H
#define UNITTESTPURPOSEERRORREPORT_H

#include "errorreport.h"
#include <QStringList>

class UnitTestPurposeErrorReport : public ErrorReport
{
public:
    UnitTestPurposeErrorReport() { }

    virtual void reportError(const QString& msg, ErrorSeverityLevel level = ErrorReport::ESL_CRITICAL);

    const QStringList& getErrorList() { return m_errorList; }
    void clearErrorList() { m_errorList.clear(); }

private:
    QStringList m_errorList;
};

#endif // UNITTESTPURPOSEERRORREPORT_H
