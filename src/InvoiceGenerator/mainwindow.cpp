#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtwindowbase.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_centralWidget = new QStackedWidget();

    setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::showWindow(QTWindowBase* window)
{
    if (m_centralWidget->indexOf(window->mainWidget()) == -1)
    {
        return;
    }

    m_centralWidget->setCurrentWidget(window->mainWidget());
}

void MainWindow::addWindow(QTWindowBase* window)
{
    m_centralWidget->addWidget(window->mainWidget());
}
