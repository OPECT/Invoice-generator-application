#include "qtadddatadialog.h"

QTAddDataDialog::QTAddDataDialog(QWidget *parent) :
    QDialog(parent)
{
}

void QTAddDataDialog::show()
{
    clearData();
    QDialog::show();
}

void QTAddDataDialog::addConfirmed()
{
    emit addConfirmedNofify();
}
