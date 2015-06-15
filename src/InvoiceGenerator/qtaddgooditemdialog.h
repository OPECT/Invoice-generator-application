#ifndef QTADDGOODITEMDIALOG_H
#define QTADDGOODITEMDIALOG_H

#include "qtadddatadialog.h"
#include "qteditboxline.h"
#include <QString>
#include <QDoubleValidator>
#include <QComboBox>

class QHBoxLayout;
class TableHandler;
class DataBaseData;

class QTAddGoodItemDialog : public QTAddDataDialog
{
    Q_OBJECT
public:
    QTAddGoodItemDialog(const QString& title, const TableHandler& goodTable, const DataBaseData& dbData,
                        QWidget* parent = 0);
    virtual ~QTAddGoodItemDialog() { }

    QString goodName() { return m_goodNameLine->getEditText(); }
    QString goodCategory() { return m_goodCategoryCombo->currentText(); }
    QString goodType() { return m_goodTypeCombo->currentText(); }
    double goodPrice() { return m_goodPriceLine->getEditText().toDouble(); }


public slots:
    void itemChoosed(qint32 index);
    void itemHighlighted();
    void activateAddButton();

private:
    virtual void clearData();

    QHBoxLayout* createGoodTypeLayout();
    QHBoxLayout* createGoodCategoryLayout();

    bool isNameCorrect(const QString& name);
    bool isPriceCorrect(const QString& price);

private:
    const TableHandler& m_table;

    QString m_goodTypeMsg;
    QString m_goodNameMsg;
    QString m_goodPriceMsg;
    QString m_goodCategoryMsg;
    QString m_goodCategoryEnterMsg;

    QString m_categoryColumn;
    QString m_nameColumn;

    QTEditBoxLine* m_goodNameLine;
    QTEditBoxLine* m_goodPriceLine;
    QComboBox* m_goodTypeCombo;
    QComboBox* m_goodCategoryCombo;

    QDoubleValidator m_priceValidator;
};

#endif // QTADDGOODITEMDIALOG_H
