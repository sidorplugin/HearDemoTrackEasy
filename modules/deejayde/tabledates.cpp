#include "tabledates.h"

TableDates::TableDates()
{

}


// Вставляет дату в таблицу.
void TableDates::insertDate(int page, const QDate &date)
{
    QList<QDate> list = m_table[page];

    if (list.isEmpty()) {
        QList<QDate> temp;
        temp.push_back(date);
        m_table.insert(page, temp);
    }
    else {
        list.push_back(date);
        m_table[page] = list;
    }    
    qDebug() << m_table;
}


// Возвращает номер страницы по дате из таблицы хранения дат.
// В случае отсутствия возращает -1.
int TableDates::getPage(const QDate &date)
{
    QHashIterator<int, QList <QDate> > i(m_table);
    while (i.hasNext()) {
        i.next();
        QList <QDate> list = i.value();
        QDate firstDate = list.first();
        QDate lastDate = list.last();
        if ( (date <= firstDate) && (date >= lastDate) ) {
            return i.key();
        }
    }
    return -1;
}


// Возвращает список дат по номеру страницы.
QList<QDate> TableDates::getDates(int page)
{
    QList<QDate> list = m_table[page];
    return list;
}


// Возвращает true если страница есть в таблице.
bool TableDates::isContains(int page)
{
    if (!m_table.value(page).isEmpty())
        return true;
    return false;
}
