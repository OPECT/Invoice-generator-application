#include "qsqlcustomermodel.h"

QSQLCustomerModel::QSQLCustomerModel(QObject * parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{
}

bool QSQLCustomerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
    {
        return false;
    }

    switch(index.column())
    {
    case CDC_NAME:
        if (value.toString().isEmpty())
        {
            return false;
        }
        break;

    case CDC_MULTIPLIER:
        bool isDouble;
        value.toDouble(&isDouble);
        if (!isDouble)
            return false;

    case CDC_REGION:
        //XXX Add combobox
        return false;

    default:
        return false;
    }

    return QSqlTableModel::setData(index, value);
}
