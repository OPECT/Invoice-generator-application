#ifndef INVOICEHANDLERCREATOR_H
#define INVOICEHANDLERCREATOR_H

class DocInvoiceBuilder;
class InvoiceDocumentWrapper;
class ErrorReport;

class InvoiceHandlerCreator
{
public:
    InvoiceHandlerCreator() {}
    virtual ~InvoiceHandlerCreator() {}

    virtual DocInvoiceBuilder& createHandler() = 0;
    virtual InvoiceDocumentWrapper& createDocumentWrapper() = 0;
    virtual ErrorReport& createErrorReporter() = 0;
};

#endif // INVOICEHANDLERCREATOR_H
