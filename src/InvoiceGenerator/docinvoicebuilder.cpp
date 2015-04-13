#include "docinvoicebuilder.h"
#include "errorreport.h"

DocInvoiceBuilder::DocInvoiceBuilder(ErrorReport &errorReporter, QObject *parent)
    : QObject(parent), m_reporter(errorReporter)
{

}

void DocInvoiceBuilder::reportError(const QString &msg)
{
    m_reporter.reportError(msg, ErrorReport::ESL_CRITICAL);
}
