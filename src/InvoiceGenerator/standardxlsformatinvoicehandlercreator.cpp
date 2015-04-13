#include "standardxlsformatinvoicehandlercreator.h"

StandardXLSFormatInvoiceHandlerCreator::StandardXLSFormatInvoiceHandlerCreator() :
    m_report(), m_docWrapper("standardInvoice.xlsx"), m_handler(m_docWrapper, m_report)
{
}
