#include "documentwrappertestsuite.h"
#include "xlsdocumentwrapper.h"

#include <cppunit/TestCaller.h>
#include <QFile>

DocumentWrapperTestSuite::DocumentWrapperTestSuite() : m_correctTemplateFile("../standardInvoice.xlsx"),
    m_templateSheet("Invoice"), m_newSheet("NewSheet"), m_wrongTemplateFile("111.111"),
    m_wrongTemplateSheet("WrongInvoice"), m_wrongNewSheet("WrongNewSheet"), m_testRow(7), m_testCol(13),
    m_doubleData(0.334567), m_stringData("Test Data To Write"), m_resultFile("result.xslx")
{
}

bool DocumentWrapperTestSuite::createDocument_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create())
    {
        return false;
    }
    return doc.isDocumentCreated();
}

bool DocumentWrapperTestSuite::createDocument_BAD()
{
    XLSDocumentWrapper doc(m_wrongTemplateFile);
    if (!doc.create())
    {
        return false;
    }

    if (doc.create())
    {
        return false;
    }

    if (!doc.create(true))
    {
        return false;
    }
    return doc.isDocumentCreated();
}

bool DocumentWrapperTestSuite::saveDocument_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }

    if (!doc.save(m_resultFile, true))
    {
        return false;
    }

    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return !doc.isDocumentCreated();
}

bool DocumentWrapperTestSuite::saveDocument_BAD()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (doc.save(m_resultFile, true))
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }

    if (doc.save("", true))
    {
        return false;
    }

    if (!doc.save(m_resultFile, true))
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }

    if (doc.save(m_resultFile))
    {
        return false;
    }

    if (!doc.save(m_resultFile, true))
    {
        return false;
    }

    if (!QFile::exists(m_resultFile))
    {
        return false;
    }

    QFile::remove(m_resultFile);
    return !doc.isDocumentCreated();
}

bool DocumentWrapperTestSuite::copySheet_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }

    QStringList names = doc.documentSheetNames();
    if (names.count() != 2)
    {
        return false;
    }
    if (names.at(0) != m_templateSheet)
    {
        return false;
    }
    if (names.at(1) != m_newSheet)
    {
        return false;
    }

    return true;
}

bool DocumentWrapperTestSuite::copySheet_BAD()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);

    if (doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }

    QStringList names = doc.documentSheetNames();
    if (!names.empty())
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }

    if (doc.copySheetFromSource(m_wrongTemplateSheet, m_newSheet))
    {
        return false;
    }

    names = doc.documentSheetNames();
    if (names.count() != 1)
    {
        return false;
    }
    if (names.at(0) != m_templateSheet)
    {
        return false;
    }
    return true;
}

bool DocumentWrapperTestSuite::changeSheet_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }

    return true;
}

bool DocumentWrapperTestSuite::changeSheet_BAD()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (doc.changeCurrentSheet(m_wrongNewSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }

    return true;
}

bool DocumentWrapperTestSuite::deleteSheet()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (doc.deleteSheet(m_newSheet))
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }
    if (doc.deleteSheet(m_wrongNewSheet))
    {
        return false;
    }
    if (!doc.deleteSheet(m_newSheet))
    {
        return false;
    }

    QStringList names = doc.documentSheetNames();
    if (names.count() != 1)
    {
        return false;
    }
    if (names.at(0) != m_templateSheet)
    {
        return false;
    }

    if (doc.deleteSheet(m_templateSheet))
    {
        return false;
    }
    if (doc.deleteSheet(m_newSheet))
    {
        return false;
    }

    return true;
}

bool DocumentWrapperTestSuite::writeData_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }
    if (!doc.writeDouble(m_testRow, m_testCol, m_doubleData) || !doc.writeString(m_testCol, m_testRow, m_stringData))
    {
        return false;
    }
    return true;
}

bool DocumentWrapperTestSuite::writeData_BAD()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (doc.writeDouble(m_testRow, m_testCol, m_doubleData) || doc.writeString(m_testCol, m_testRow, m_stringData))
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }
    if (!doc.writeDouble(m_testRow, m_testCol, m_doubleData) || !doc.writeString(m_testCol, m_testRow, m_stringData))
    {
        return false;
    }

    if (!doc.deleteSheet(m_newSheet))
    {
        return false;
    }

    if (!doc.writeDouble(m_testRow, m_testCol, m_doubleData) || !doc.writeString(m_testCol, m_testRow, m_stringData))
    {
        return false;
    }
    return true;
}

bool DocumentWrapperTestSuite::readData_OK()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);
    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }
    if (!doc.writeDouble(m_testRow, m_testCol, m_doubleData) || !doc.writeString(m_testCol, m_testRow, m_stringData))
    {
        return false;
    }

    QVariant doubleData = doc.readData(m_testRow, m_testCol);
    QVariant stringData = doc.readData(m_testCol, m_testRow);

    if (!doubleData.isValid() || !stringData.isValid())
    {
        return false;
    }

    if (doubleData.toDouble() != m_doubleData || stringData.toString() != m_stringData)
    {
        return false;
    }

    return true;
}

bool DocumentWrapperTestSuite::readData_BAD()
{
    XLSDocumentWrapper doc(m_correctTemplateFile);

    if (doc.readData(m_testRow, m_testCol).isValid())
    {
        return false;
    }

    if (!doc.create() || !doc.isDocumentCreated())
    {
        return false;
    }
    if (!doc.copySheetFromSource(m_templateSheet, m_newSheet))
    {
        return false;
    }
    if (!doc.changeCurrentSheet(m_newSheet))
    {
        return false;
    }

    if (doc.readData(m_testRow, m_testCol).isValid())
    {
        return false;
    }

    return true;
}

void DocumentWrapperTestSuite::documentOperations()
{
    CPPUNIT_ASSERT(createDocument_OK());
    CPPUNIT_ASSERT(createDocument_BAD());
    CPPUNIT_ASSERT(saveDocument_OK());
    CPPUNIT_ASSERT(saveDocument_BAD());
}

void DocumentWrapperTestSuite::sheetOperations()
{
    CPPUNIT_ASSERT(copySheet_OK());
    CPPUNIT_ASSERT(copySheet_BAD());
    CPPUNIT_ASSERT(changeSheet_OK());
    CPPUNIT_ASSERT(changeSheet_BAD());
    CPPUNIT_ASSERT(deleteSheet());
}

void DocumentWrapperTestSuite::readWriteOperations()
{
    CPPUNIT_ASSERT(writeData_OK());
    CPPUNIT_ASSERT(writeData_BAD());
    CPPUNIT_ASSERT(readData_OK());
    CPPUNIT_ASSERT(readData_BAD());
}

CppUnit::Test *DocumentWrapperTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<DocumentWrapperTestSuite>("Test Document Creation and Saving",
                                                                    &DocumentWrapperTestSuite::documentOperations));
    suiteOfTests->addTest(new CppUnit::TestCaller<DocumentWrapperTestSuite>("Test Sheet Operations",
                                                                    &DocumentWrapperTestSuite::sheetOperations));
    suiteOfTests->addTest(new CppUnit::TestCaller<DocumentWrapperTestSuite>("Test Read and Write Operations",
                                                                    &DocumentWrapperTestSuite::readWriteOperations));
    return suiteOfTests;
}
