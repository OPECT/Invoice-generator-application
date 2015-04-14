#include "qsqlgoodsmodel.h"

QSQLGoodsModel::QSQLGoodsModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{
}

bool QSQLGoodsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
    {
        return false;
    }

    switch(index.column())
    {
    case GDC_NAME:
        if (value.toString().isEmpty())
        {
            return false;
        }
        break;

    case GDC_TYPE:
        //XXX Add combobox
        return false;

    case GDC_PRICE:
        bool isDouble;
        value.toDouble(&isDouble);
        if (!isDouble)
            return false;

    case GDC_CATEGORY:
        //XXX Add combobox
        return false;

    default:
        return false;
    }

    return QSqlTableModel::setData(index, value);
}

