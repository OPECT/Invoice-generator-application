#ifndef QTGOODSDATABASEWINDOW_H
#define QTGOODSDATABASEWINDOW_H

#include "qtdatabasewindow.h"

class DataBaseData;

class QTGoodsDataBaseWindow : public QTDataBaseWindow
{
    Q_OBJECT
public:
    QTGoodsDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model, const QString& name,
                          const DataBaseData& dbData, QObject* parent = 0);

protected slots:
    void addItemButtonEvent();
    void backButtonEvent();

private:
    const DataBaseData& m_dataBaseData;
    QString m_addGoodsMsg;
};

#endif // QTGOODSDATABASEWINDOW_H
