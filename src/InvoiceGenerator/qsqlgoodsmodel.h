#ifndef QSQLGOODSMODEL_H
#define QSQLGOODSMODEL_H

#include <QSqlTableModel>

class QSQLGoodsModel : public QSqlTableModel
{
    Q_OBJECT
public:
    enum GoodDataColumn {
        GDC_NAME = 1,
        GDC_TYPE,
        GDC_CATEGORY,
        GDC_PRICE
    };

public:
    QSQLGoodsModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif // QSQLGOODSMODEL_H
