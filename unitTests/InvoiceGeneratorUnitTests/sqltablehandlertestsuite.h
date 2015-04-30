#ifndef SQLTABLEHANDLERTESTSUITE_H
#define SQLTABLEHANDLERTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>

class SQLTableHandlerTestSuite : public CppUnit::TestFixture
{
public:
    SQLTableHandlerTestSuite();

    bool tableExist_OK();
    bool tableExist_BAD();
    bool select_OK();
    bool select_BAD();

    void tableHandlerTest();

    static CppUnit::Test *suite();

private:
    QString m_dbType;
    QString m_dbHost;
    QString m_dbName;
    QString m_dbUser;
    QString m_dbPassword;

    QString m_tableName;
    QString m_emptyTable;
    QString m_wrongTable;

    QString m_columnName;
    QString m_wrongColumnName;
    QString m_attributeVale;
    QString m_wrongAttributeVale;
};

#endif // SQLTABLEHANDLERTESTSUITE_H
