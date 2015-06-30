#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "batypes.h"

class QStackedWidget;
class QTWindowBase;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void showWindow(QTWindowBase* window);
    void addWindow(QTWindowBase* window);
    void removeWindow(QTWindowBase* window);

private:
    QStackedWidget* m_centralWidget;

    Ui::MainWindow* m_ui;
};

#endif // MAINWINDOW_H
