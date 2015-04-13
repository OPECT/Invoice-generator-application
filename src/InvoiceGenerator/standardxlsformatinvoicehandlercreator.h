#ifndef STANDARDXLSFORMATINVOICEHANDLERCREATOR_H
#define STANDARDXLSFORMATINVOICEHANDLERCREATOR_H

#include "invoicehandlercreator.h"
#include "xlstandardinvoiceformatbuilder.h"
#include "xlsdocumentwrapper.h"
#include "messageboxerrorreport.h"

class StandardXLSFormatInvoiceHandlerCreator : public InvoiceHandlerCreator
{
public:
    StandardXLSFormatInvoiceHandlerCreator();

    virtual DocInvoiceBuilder& createHandler() { return m_handler; }
    virtual InvoiceDocumentWrapper& createDocumentWrapper() { return m_docWrapper; }
    virtual ErrorReport& createErrorReporter() { return m_report; }

private:
    MessageBoxErrorReport m_report;
    XLSDocumentWrapper m_docWrapper;
    XLStandardInvoiceFormatBuilder m_handler;
};

#endif // STANDARDXLSFORMATINVOICEHANDLERCREATOR_H
