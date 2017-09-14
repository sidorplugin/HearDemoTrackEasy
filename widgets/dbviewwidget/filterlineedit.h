#ifndef FILTERLINEEDIT_H
#define FILTERLINEEDIT_H

#include <QLineEdit>
#include <QList>

class QTimer;
class QKeyEvent;

class FilterLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit FilterLineEdit(QWidget* parent, QList<FilterLineEdit*>* filters, int column);

    // Очищает строку текста с задержкой.
    void clear();
    // Устанавливает строку текста с задержкой.
    void setText(const QString& text);

private slots:
    // Отправляет задержаный сигнал со строкой поиска.
    void delayedSignalTimerTriggered();

signals:
    // Задержаный QLineEdit::textChanged().
    void delayedTextChanged(QString text);

protected:
    // Перемещает фокус по фильтрам в столбцах по нажатию клавиш Tab.
    void keyReleaseEvent(QKeyEvent* event);

private:
    QList<FilterLineEdit*>* m_filterList;
    int m_column;
    QTimer* m_delaySignalTimer;
};

#endif
