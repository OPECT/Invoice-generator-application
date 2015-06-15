#include "qsqlcustomermodel.h"
#include "badefines.h"

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
        if (value.toString().isEmpty() || value.toString().count() > MAX_CUSTOMER_NAME_LENGTH)
        {
            return false;
        }
        break;

    case CDC_MULTIPLIER:
        bool isUint;
        value.toUInt(&isUint);
        if (!isUint || value.toUInt(&isUint) > MAX_DISCOUNT_VALUE )
            return false;
        break;

    case CDC_REGION:
        //XXX Add combobox or just set appropriate flag to not editable (page 253)
        return false;

    default:
        return false;
    }

    return QSqlTableModel::setData(index, value);
}
