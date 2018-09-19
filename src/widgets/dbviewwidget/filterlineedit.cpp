#include "filterlineedit.h"

#include <QTimer>
#include <QKeyEvent>

FilterLineEdit::FilterLineEdit(QWidget* parent,
                               QList<FilterLineEdit*>* filters,
                               int column)
               : QLineEdit(parent), m_filterList(filters), m_column(column)
{
    setPlaceholderText(tr("Фильтр"));
    setClearButtonEnabled(true);
    setProperty("column", column);

    m_delaySignalTimer = new QTimer(this);
    m_delaySignalTimer->setInterval(1000);

    connect(this, SIGNAL(textChanged(QString)),
            m_delaySignalTimer, SLOT(start()));

    connect(m_delaySignalTimer, SIGNAL(timeout()),
            this, SLOT(delayedSignalTimerTriggered()));

    connect(this, SIGNAL(editingFinished()),
            this, SLOT(delayedSignalTimerTriggered()));
}

// Отправляет задержаный сигнал со строкой поиска.
void FilterLineEdit::delayedSignalTimerTriggered()
{
    m_delaySignalTimer->stop();
    emit delayedTextChanged(text());
}


// Перемещает фокус по фильтрам в столбцах по нажатию клавиш Tab.
void FilterLineEdit::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Tab)
    {
        if(m_column < m_filterList->size() - 1)
        {
            m_filterList->at(m_column + 1)->setFocus();
            event->accept();
        }
    } else if(event->key() == Qt::Key_Backtab) {
        if(m_column > 0)
        {
            m_filterList->at(m_column - 1)->setFocus();
            event->accept();
        }
    }
}

// Очищает строку текста с задержкой.
void FilterLineEdit::clear()
{
    QLineEdit::clear();
    delayedSignalTimerTriggered();
}


// Устанавливает строку текста с задержкой.
void FilterLineEdit::setText(const QString& text)
{
    QLineEdit::setText(text);
    delayedSignalTimerTriggered();
}
