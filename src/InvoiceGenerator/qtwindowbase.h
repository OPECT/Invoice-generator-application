#ifndef QTWINDOWBASE_H
#define QTWINDOWBASE_H

#include <QObject>
#include <QString>

class QWidget;

class QTWindowBase : public QObject
{
    Q_OBJECT
public:
    explicit QTWindowBase(const QString& name, QObject* parent = 0);
    virtual ~QTWindowBase();

    virtual void show();
    virtual void hide();

    const QWidget* mainWidget() { return m_mainWidget; }
    const QString& windowName() { return m_windowName; }

protected:
    QString m_windowName;
    QWidget* m_mainWidget;
};

#endif // QTWINDOWBASE_H
