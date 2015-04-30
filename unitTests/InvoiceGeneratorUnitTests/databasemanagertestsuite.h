#ifndef DATABASEMANAGERTESTSUITE_H
#define DATABASEMANAGERTESTSUITE_H

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <QString>

class DataBaseManagerTestSuite : public CppUnit::TestFixture
{
public:
    DataBaseManagerTestSuite();

    bool openDB_OK();
    bool openDB_BAD();

    bool createTable_OK();
    bool createTable_BAD();
    bool checkTable_OK();
    bool checkTable_BAD();

    void openDataBaseTest();
    void dataBaseActionsTest();

    virtual void setUp();
    static CppUnit::Test *suite();

private:
    QString m_dbType;
    QString m_dbHost;
    QString m_dbName;
    QString m_newDBName;
    QString m_dbUser;
    QString m_dbPassword;

    QString m_tableName;
    QString m_tableAttr1;
    QString m_tableAttr2;
    QString m_tableAttr3;
};

#endif // DATABASEMANAGERTESTSUITE_H
