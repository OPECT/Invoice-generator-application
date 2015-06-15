#ifndef QSQLCUSTOMERMODEL_H
#define QSQLCUSTOMERMODEL_H

#include <QSqlTableModel>

class QSQLCustomerModel : public QSqlTableModel
{
    Q_OBJECT

public:
    enum CustomerDataColumn {
        CDC_NAME = 1,
        CDC_REGION,
        CDC_MULTIPLIER
    };

public:
    QSQLCustomerModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif // QSQLCUSTOMERMODEL_H
