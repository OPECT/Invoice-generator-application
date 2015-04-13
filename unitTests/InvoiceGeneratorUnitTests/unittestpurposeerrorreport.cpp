#include "unittestpurposeerrorreport.h"

void UnitTestPurposeErrorReport::reportError(const QString& msg, ErrorSeverityLevel level)
{
    m_errorList.append(msg);
}
