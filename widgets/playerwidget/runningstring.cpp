#include "runningstring.h"

#include <QDebug>


RunningString::RunningString(QWidget *parent)
{
    m_timer.start(60, this);
}


void RunningString::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timer.timerId()) {
        update();
    } else {
        QWidget::timerEvent(event);
    }
}


void RunningString::paintEvent(QPaintEvent* event)
{
    QFontMetrics metrics(font());
    int x = (width() - metrics.width(m_text)) / 2;
    int y = (height() + metrics.ascent() - metrics.descent()) / 2;

    QPainter painter(this);
    for (int i = 0; i < m_text.size(); ++i) {
        painter.drawText(x, y, QString(m_text[i]));
        x += metrics.width(m_text[i]);
        qDebug() << x << " " << y;
    }
}
