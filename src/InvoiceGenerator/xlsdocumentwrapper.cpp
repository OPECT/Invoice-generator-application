#include "xlsdocumentwrapper.h"

using namespace QXlsx;

XLSDocumentWrapper::XLSDocumentWrapper(const QString &templateFile)
    : InvoiceDocumentWrapper(templateFile), m_pInvoiceBook(0), m_pCurrentSheet(0)
{
}

XLSDocumentWrapper::~XLSDocumentWrapper()
{
    releaseDocument();
}

bool XLSDocumentWrapper::create(bool overwrite)
{
    if (!overwrite && m_pInvoiceBook)
    {
        return false;
    }

    releaseDocument();
    m_pInvoiceBook = new Document(m_template);

    if (!(m_pCurrentSheet = m_pInvoiceBook->currentWorksheet()))
    {
        releaseDocument();
        return false;
    }

    return true;
}

bool XLSDocumentWrapper::copySheetFromSource(const QString &srcName, const QString &dstName)
{
    if (!m_pInvoiceBook || !m_pInvoiceBook->copySheet(srcName, dstName))
    {
        return false;
    }

    return true;
}

bool XLSDocumentWrapper::changeCurrentSheet(const QString &sheetName)
{
    //XXX handle selection rollback in case of fail in last assignment
    if (!m_pInvoiceBook || !m_pInvoiceBook->selectSheet(sheetName) ||
        !(m_pCurrentSheet = m_pInvoiceBook->currentWorksheet()))
    {
        return false;
    }

    return true;
}

bool XLSDocumentWrapper::deleteSheet(const QString &name)
{
    if (!m_pInvoiceBook || !m_pCurrentSheet)
    {
        return false;
    }

    bool deleteCurrentSheet = m_pCurrentSheet->sheetName() == name ? true : false;

    if (!m_pInvoiceBook->deleteSheet(name))
    {
        return false;
    }

    if (deleteCurrentSheet)
    {
        QStringList names = m_pInvoiceBook->sheetNames();
        if (names.empty() || !changeCurrentSheet(names[0]))
        {
            m_pCurrentSheet = 0;
        }
    }
    return true;
}

bool XLSDocumentWrapper::save(const QString& name, bool overwrite)
{
    if (!m_pInvoiceBook || name.isEmpty())
    {
        return false;
    }
    if (QFile::exists(name) && !overwrite)
    {
        return false;
    }

    if (!m_pInvoiceBook->saveAs(name))
    {
        return false;
    }

    releaseDocument();
    return true;
}

bool XLSDocumentWrapper::writeString(quint32 row, quint32 col, const QString &data)
{
    if (!m_pCurrentSheet)
    {
        return false;
    }
    return m_pCurrentSheet->writeString(row, col, data);
}

bool XLSDocumentWrapper::writeDouble(quint32 row, quint32 col, double data)
{
    if (!m_pCurrentSheet)
    {
        return false;
    }
    return m_pCurrentSheet->writeNumeric(row, col, data);
}

QVariant XLSDocumentWrapper::readData(quint32 row, quint32 col)
{
    if (!m_pCurrentSheet)
    {
        return QVariant();
    }
    return m_pCurrentSheet->read(row, col);
}

void XLSDocumentWrapper::releaseDocument()
{
    if (m_pInvoiceBook)
    {
        delete m_pInvoiceBook;
        m_pInvoiceBook = 0;
        m_pCurrentSheet = 0;
    }
}
