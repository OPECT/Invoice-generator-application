#ifndef ADDDATADIALOG_H
#define ADDDATADIALOG_H

#include <QDialog>

class QHBoxLayout;
class QPushButton;

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

protected:
    QHBoxLayout* createButtonsLayout();

protected:
    QPushButton* m_addBtn;
    QPushButton* m_cancelBtn;
};

#endif // ADDDATADIALOG_H
