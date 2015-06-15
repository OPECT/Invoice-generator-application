#ifndef QTADDCUSTOMERDIALOG_H
#define QTADDCUSTOMERDIALOG_H

#include "qtadddatadialog.h"
#include "qteditboxline.h"
#include <QString>
#include <QIntValidator>
#include <QComboBox>

class QHBoxLayout;
class TableHandler;
class DataBaseData;
class QValidator;

class QTAddCustomerDialog : public QTAddDataDialog
{
    Q_OBJECT

public:
    QTAddCustomerDialog(const QString& title, const TableHandler& customerTable, const DataBaseData& dbData,
                        QWidget* parent = 0);
    virtual ~QTAddCustomerDialog() { }

    QString customerName() { return m_customerNameLine->getEditText(); }
    QString customerRegion() { return m_customerRegionCombo->currentText(); }
    quint32 customerDiscount() { return m_customerNameLine->getEditText().toUInt(); }

public slots:
    void itemChoosed(qint32 index);
    void itemHighlighted();
    void activateAddButton();

private:
    virtual void clearData();

    QHBoxLayout* createCustomerRegionLayout();

    bool isNameCorrect(const QString& name);
    bool isDiscountCorrect(const QString& discountText);

private:
    const TableHandler& m_table;

    QString m_customerNameMsg;
    QString m_customerDiscountMsg;
    QString m_customerRegionMsg;
    QString m_customerRegionEnterMsg;

    QString m_regionColumn;
    QString m_nameColumn;

    QTEditBoxLine* m_customerNameLine;
    QTEditBoxLine* m_customerDiscountLine;
    QComboBox* m_customerRegionCombo;

    QIntValidator m_discountValidator;
};

#endif // QTADDCUSTOMERDIALOG_H
