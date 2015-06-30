#ifndef QTDATABASEWINDOW_H
#define QTDATABASEWINDOW_H

#include "qtwindowbase.h"
#include "batypes.h"
#include <QList>
#include <QString>
#include <QVariant>

class QPushButton;
class QHBoxLayout;
class QWidget;
class QTabWidget;
class QSqlTableModel;
class QTableView;
class TableHandler;

class QTDataBaseWindow : public QTWindowBase
{
    Q_OBJECT
public:
    virtual ~QTDataBaseWindow() { }
    virtual void show();

signals:
    void dataBaseWindowEvent(UI_EVENTS event, QVariant data = QVariant());

protected slots:
    void tabChanged(qint32 index);
    void tableSelectionChanged(const QModelIndex &index);

    void deleteItemButtonEvent();
    void openDBButtonEvent();
    void saveDBButtonEvent();

protected:
    QTDataBaseWindow(const TableHandler& sqlHandler, QSqlTableModel* model, const QString& name, const QString& filter,
                     QObject* parent = 0);

    QHBoxLayout* createTableGridLayout();
    QHBoxLayout* createButtonsLayout();
    QWidget *createTableWidget();
    void addTabs();

protected:
    QList<QTableView*> m_tableViews;

    QPushButton* m_openDBButton;
    QPushButton* m_saveDBButton;
    QPushButton* m_deleteItemButton;
    QPushButton* m_addItemButton;
    QPushButton* m_backButton;

    QTabWidget *m_tabWidget;

    QSqlTableModel* m_dataModel;
    const TableHandler& m_sqlHandler;

    const QString& m_filterColumn;

private:
    QString m_openDBButtonMsg;
    QString m_saveDBButtonMsg;
    QString m_deleteItemButtonMsg;
    QString m_addItemButtonMsg;
    QString m_backButtonMsg;

    QString m_openDBMsg;
    QString m_saveDBMsg;
    QString m_filterDBMsg;
    QString m_dbFilterList;
};

#endif // QTDATABASEWINDOW_H
