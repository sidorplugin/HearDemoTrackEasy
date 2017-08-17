#ifndef RUNNINGSTRING_H
#define RUNNINGSTRING_H

#include <QObject>
#include <QLineEdit>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QPainter>

class RunningString : public QLineEdit
{
    Q_OBJECT
public:
    RunningString(QWidget* parent = 0);

    void setText(const QString& text) { m_text = text; }

protected:
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);

private:
    QBasicTimer m_timer;
    QString m_text;
};


#endif // RUNNINGSTRING_H
