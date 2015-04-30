#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class QStringList;
class QString;

/* It is not possible to provide suitable interface to limit SQLDataBase connections.
 * 1) QSqlDatabase class doesn't provide suitable interface.
 *    Usage of its static members to limit connection creation cause failures on desctruction
 * 2) CPPUnit configuration doesn't allow to create global QSqlDatabase object.
 *    So it is not possible to make DataBaseManager singleton.
 *    As destruction of such object at the end causes crash.
 * So it was decided to provide simple interface with simple class logic.
 * No limitations are done on logic level.
 * Usage of this class should be limitted on user level with some conventions.
 * It is not allowed to create more than one DataBaseManager class
 * XXX: This behavior should be redesigned
 * */

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();

    QSqlDatabase& database() { return m_db; }
    bool isDataBaseReady() const { return m_isDBReady; }

    bool openDB(const QString& type, const QString& host, const QString& name,const QString& user,
                  const QString& password);

    bool createTable(const QString& table, const QStringList& tableAttr);
    bool isTableExist(const QString& table) const;

private:
    QSqlDatabase m_db;
    bool m_isDBReady;
};

#endif // DATABASEMANAGER_H
