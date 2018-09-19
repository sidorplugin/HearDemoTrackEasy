#ifndef TABLEDATES_H
#define TABLEDATES_H

#include <QDate>
#include <QHash>
#include <QDebug>

// Класс хранит таблицу соответствия страниц с датами вида "страница - список дат" .
// Используется модулем DeejadePageSearcher для быстрого нахождения страниц.

class TableDates
{
public:
    TableDates();

    // Вставляет дату в таблицу.
    void insertDate(int page, const QDate& date);
    // Возвращает номер страницы по дате из таблицы хранения дат.
    // В случае отсутствия возращает -1.
    int getPage(const QDate& date);
    // Возвращает список дат по номеру страницы.
    QList <QDate> getDates(int page);
    // Возвращает true если страница есть в таблице.
    bool isContains(int page);
    void clear();

private:
    // Таблица для хранения дат.
    QHash <int, QList <QDate> > m_table;
};

#endif // TABLEDATES_H
