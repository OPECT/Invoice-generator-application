#ifndef QTADDCATEGORYDIALOG_H
#define QTADDCATEGORYDIALOG_H

#include "qtadddatadialog.h"
#include "qteditboxline.h"
#include <QPushButton>

//XXX add error message box on reaching maximum number of data symbols
class QTAddCategoryDialog : public QTAddDataDialog
{
    Q_OBJECT
public:
    explicit QTAddCategoryDialog(const QString &title, const QString &description, quint32 dataLimit,
                                 QWidget *parent = 0);
    virtual ~QTAddCategoryDialog() {}

    QString getInputData() { return m_category.getEditText(); }

private:
    virtual void clearData() { m_category.clearText(); }

signals:

public slots:
    void textChanged(const QString &text);

private:
    QTEditBoxLine m_category;

    QPushButton m_addBtn;
    QPushButton m_cancelBtn;
};

#endif // QTADDCATEGORYDIALOG_H
