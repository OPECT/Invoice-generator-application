#include "databasemanagertestsuite.h"
#include "databasemanager.h"
#include "tablehandler.h"

#include <cppunit/TestCaller.h>
#include <QFile>
#include <QStringList>

DataBaseManagerTestSuite::DataBaseManagerTestSuite() : m_dbType("QSQLITE"), m_dbHost("localhost"),
    m_dbName("UnitTestDB"), m_newDBName("NewDB"), m_dbUser("UnitTest"), m_dbPassword("Test123"),
    m_tableName("myTable"), m_tableAttr1("Attribute1"), m_tableAttr2("Attribute2"), m_tableAttr3("Attribute3")
{
}

bool DataBaseManagerTestSuite::openDB_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    return true;
}

bool DataBaseManagerTestSuite::openDB_BAD()
{
    DataBaseManager dbManager;
    DataBaseManager dbManager1;

    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }
    if (dbManager.openDB(m_dbType, m_dbHost, m_newDBName, m_dbUser, m_dbPassword))
    {
        return false;
    }
    if (!dbManager1.openDB(m_dbType, m_dbHost, m_newDBName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }
    if(!QFile::exists(m_newDBName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    QFile::remove(m_newDBName);
    return true;
}

bool DataBaseManagerTestSuite::createTable_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    QStringList attributes;
    attributes << m_tableAttr1 << m_tableAttr2 << m_tableAttr3;
    if (!dbManager.createTable(m_tableName, attributes))
    {
        return false;
    }

    TableHandler query(m_tableName, dbManager.database());
    QList<QVariant> data;
    if (!query.select("*", "", false, data))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    return true;
}

bool DataBaseManagerTestSuite::createTable_BAD()
{
    DataBaseManager dbManager;
    QStringList attributes;
    attributes << m_tableAttr1 << m_tableAttr2 << m_tableAttr3;
    if (dbManager.createTable(m_tableName, attributes))
    {
        return false;
    }

    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    if (!dbManager.createTable(m_tableName, attributes))
    {
        return false;
    }

    if (dbManager.createTable(m_tableName, attributes))
    {
        return false;
    }

    TableHandler query(m_tableName, dbManager.database());
    QList<QVariant> data;
    if (!query.select("*", "", false, data))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    return true;
}

bool DataBaseManagerTestSuite::checkTable_OK()
{
    DataBaseManager dbManager;
    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    QStringList attributes;
    attributes << m_tableAttr1 << m_tableAttr2 << m_tableAttr3;
    if (!dbManager.createTable(m_tableName, attributes))
    {
        return false;
    }

    if (!dbManager.isTableExist(m_tableName))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    return true;
}

bool DataBaseManagerTestSuite::checkTable_BAD()
{
    DataBaseManager dbManager;
    if (dbManager.isTableExist(m_tableName))
    {
        return false;
    }

    if (!dbManager.openDB(m_dbType, m_dbHost, m_dbName, m_dbUser, m_dbPassword))
    {
        return false;
    }

    if (dbManager.isTableExist(m_tableName))
    {
        return false;
    }

    if(!QFile::exists(m_dbName))
    {
        return false;
    }

    QFile::remove(m_dbName);
    return true;
}

void DataBaseManagerTestSuite::openDataBaseTest()
{
    CPPUNIT_ASSERT(openDB_OK());
    CPPUNIT_ASSERT(openDB_BAD());
}

void DataBaseManagerTestSuite::dataBaseActionsTest()
{
    CPPUNIT_ASSERT(createTable_OK());
    CPPUNIT_ASSERT(createTable_BAD());
    CPPUNIT_ASSERT(checkTable_OK());
    CPPUNIT_ASSERT(checkTable_BAD());
}

void DataBaseManagerTestSuite::setUp()
{
    if(QFile::exists(m_dbName))
    {
        QFile::remove(m_dbName);
    }
}

CppUnit::Test *DataBaseManagerTestSuite::suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite;

    suiteOfTests->addTest(new CppUnit::TestCaller<DataBaseManagerTestSuite>("Test open DataBase",
                                                                    &DataBaseManagerTestSuite::openDataBaseTest));
    suiteOfTests->addTest(new CppUnit::TestCaller<DataBaseManagerTestSuite>("Test DataBase actions",
                                                                    &DataBaseManagerTestSuite::dataBaseActionsTest));
    return suiteOfTests;
}
