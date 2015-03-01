#ifndef ERRORREPORT_H
#define ERRORREPORT_H

#include <QString>

class ErrorReport
{
public:
    enum ErrorSeverityLevel { ESL_CRITICAL, ESL_WARNING, ESL_INFO };
public:
    ErrorReport() {}
    virtual ~ErrorReport() {}

    virtual void reportError(const QString& msg, ErrorSeverityLevel level) = 0;

};

#endif // ERRORREPORT_H
