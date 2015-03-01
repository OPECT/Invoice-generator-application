#ifndef ADDDATADIALOG_H
#define ADDDATADIALOG_H

#include <QDialog>

class QTAddDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QTAddDataDialog(QWidget *parent = 0);
    virtual ~QTAddDataDialog() { }

    virtual void show();

private:
    virtual void clearData() = 0;

signals:
    void addConfirmedNofify();

public slots:
    void addConfirmed();
};

#endif // ADDDATADIALOG_H
