#ifndef QTCUSTOMERDATABASEWINDOW_H
#define QTCUSTOMERDATABASEWINDOW_H

#include "qtdatabasewindow.h"

class DataBaseData;

class QTCustomerDataBaseWindow : public QTDataBaseWindow
{
    Q_OBJECT
public:
    QTCustomerDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model, const QString& name,
                             const DataBaseData& dbData, QObject* parent = 0);

protected slots:
    void addItemButtonEvent();

private:
    const DataBaseData& m_dataBaseData;
    QString m_addCustomerMsg;
};

#endif // QTCUSTOMERDATABASEWINDOW_H
