#ifndef QTADDGOODITEMDIALOG_H
#define QTADDGOODITEMDIALOG_H

#include "qtadddatadialog.h"
#include <QString>
#include <QDoubleValidator>

class QComboBox;
class QHBoxLayout;
class QTEditBoxLine;
class TableHandler;
class DataBaseData;

class QTAddGoodItemDialog : public QTAddDataDialog
{
    Q_OBJECT
public:
    QTAddGoodItemDialog(const QString& title, const TableHandler& goodTable, const DataBaseData& dbData,
                        QWidget* parent = 0);
    virtual ~QTAddGoodItemDialog() { }

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
