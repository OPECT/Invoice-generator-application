#include "sqltablehandlertestsuite.h"
#include "databasemanager.h"
#include "tablehandler.h"

#include <cppunit/TestCaller.h>

SQLTableHandlerTestSuite::SQLTableHandlerTestSuite() : m_dbType("QSQLITE"), m_dbHost("localhost"),
    m_dbName("TableHandlerTest"), m_dbUser("UnitTest"), m_dbPassword("Test123"), m_tableName("myTable"),
    m_emptyTable("emptyTable"), m_wrongTable("nonExsitingTable"), m_columnName("Field1"), m_wrongColumnName("Wrong"),
    m_attributeVale("Test"), m_wrongAttributeVale("wrongValue")
{
}

bool SQLTableHandlerTestSuite::tableExist_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler handler(m_tableName, dbManager.database());
    if (!handler.isTableExist())
    {
        return false;
    }

    return true;
}

bool SQLTableHandlerTestSuite::tableExist_BAD()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler handler1(m_emptyTable, dbManager.database());
    if (!handler1.isTableExist())
    {
        return false;
    }

    TableHandler handler2(m_wrongTable, dbManager.database());
    if (handler2.isTableExist())
    {
        return false;
    }

    return true;
}

bool SQLTableHandlerTestSuite::select_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler handler(m_tableName, dbManager.database());
    QList<QVariant> result;
    if (!handler.select("*", "", false, result))
    {
        return false;
    }
    if (result.count() != 3)
    {
        return false;
    }
    result.clear();

    if (!handler.select(m_columnName, "", true, result))
    {
        return false;
    }
    if (result.count() != 2)
    {
        return false;
    }
    result.clear();

    if (!handler.select("*", m_columnName + " = \"" + m_attributeVale + "\"", true, result))
    {
        return false;
    }
    if (result.count() != 2)
    {
        return false;
    }

    return true;
}

bool SQLTableHandlerTestSuite::select_BAD()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    TableHandler handler(m_tableName, dbManager.database());
    TableHandler handler1(m_wrongTable, dbManager.database());
    QList<QVariant> result;
    if (handler.select(m_wrongColumnName, "", false, result))
    {
        return false;
    }
    if (!result.empty())
    {
        return false;
    }

    if (handler1.select(m_columnName, "", false, result))
    {
        return false;
    }
    if (!result.empty())
    {
        return false;
    }

    if (handler.select(m_columnName, m_wrongColumnName + " = \"" + m_attributeVale + "\"", false, result))
    {
        return false;
    }
    if (!result.empty())
    {
        return false;
    }

    if (handler.select(m_columnName, m_wrongColumnName + " = " + m_attributeVale, false, result))
    {
        return false;
    }
    if (!result.empty())
    {
        return false;
    }

    if (!handler.select(m_columnName, m_columnName + " = \"" + m_wrongAttributeVale + "\"", false, result))
    {
        return false;
    }
    if (!result.empty())
    {
        return false;
    }

    return true;
}

void SQLTableHandlerTestSuite::tableHandlerTest()
{
    CPPUNIT_ASSERT(tableExist_OK());
    CPPUNIT_ASSERT(tableExist_BAD());
    CPPUNIT_ASSERT(select_OK());
    CPPUNIT_ASSERT(select_BAD());
}

CppUnit::Test *SQLTableHandlerTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<SQLTableHandlerTestSuite>("Test TableHandler API",
                                                                    &SQLTableHandlerTestSuite::tableHandlerTest));
    return suiteOfTests;
}
