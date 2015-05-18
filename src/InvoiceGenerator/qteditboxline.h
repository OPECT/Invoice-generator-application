#ifndef QTEDITBOXLINE_H
#define QTEDITBOXLINE_H

#include <QObject>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

class QValidator;

class QTEditBoxLine : public QObject
{
    Q_OBJECT
public:
    explicit QTEditBoxLine(QString label, quint32 editLimit, const QValidator* validator = 0, QObject* parent = 0);

    void setEditText(QString text) { m_edit.setText(text); }
    void clearText() { m_edit.clear(); }
    QString getEditText() const { return m_edit.text(); }

    QHBoxLayout *getLayout() { return &m_layout; }
    bool isDataReady() const { return !m_edit.text().isEmpty(); }

    void setEditLimit(quint32 limit);

signals:
    void editBoxChanged(const QString &text);

private:
    QHBoxLayout m_layout;
    QLabel m_info;
    QLineEdit m_edit;
};

#endif // QTEDITBOXLINE_H
