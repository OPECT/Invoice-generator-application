#ifndef INVOICETEMPLATEVALIDATOR_H
#define INVOICETEMPLATEVALIDATOR_H

#include <QString>

class InvoiceTemplateValidator
{
public:
    InvoiceTemplateValidator(const QString &target) : m_targetFile(target) { }
    ~InvoiceTemplateValidator() { }

    virtual bool validateSheet(const QString &sheetNamee) = 0;

protected:
    QString m_targetFile;
};

#endif // INVOICETEMPLATEVALIDATOR_H
