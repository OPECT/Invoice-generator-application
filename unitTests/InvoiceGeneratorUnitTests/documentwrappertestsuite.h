#ifndef DOCUMENTWRAPPERTESTSUITE_H
#define DOCUMENTWRAPPERTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>

class DocumentWrapperTestSuite : public CppUnit::TestFixture
{
public:
    DocumentWrapperTestSuite();

    void documentOperations();
    void sheetOperations();
    void readWriteOperations();

    bool createDocument_OK();
    bool createDocument_BAD();

    bool saveDocument_OK();
    bool saveDocument_BAD();

    bool copySheet_OK();
    bool copySheet_BAD();

    bool changeSheet_OK();
    bool changeSheet_BAD();

    bool deleteSheet();

    bool writeData_OK();
    bool writeData_BAD();

    bool readData_OK();
    bool readData_BAD();

    static CppUnit::Test *suite();

private:
    const QString m_correctTemplateFile;
    const QString m_templateSheet;
    const QString m_newSheet;

    const QString m_wrongTemplateFile;
    const QString m_wrongTemplateSheet;
    const QString m_wrongNewSheet;

    const quint32 m_testRow;
    const quint32 m_testCol;
    const double m_doubleData;
    const QString m_stringData;

    const QString m_resultFile;
};

#endif // DOCUMENTWRAPPERTESTSUITE_H
