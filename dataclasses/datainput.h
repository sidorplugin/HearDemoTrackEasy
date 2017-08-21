#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QString>
#include <QHash>
#include <QDate>
#include <QVariant>

// Структура DataInput хранит данные для передачи из виджетов на выполнение
// рабочему модулю.
class DataInput
{
public:
  enum Key {
    Source,          // Источник.
    Genre,           // Текущий жанр. Будет отображаться в БД.
    Period,          // Текущий период.
    Filter,          // Текущий фильтр.
    Search,          // Информация по поиску.
    Row,             // Текущая строка в виджете просмотра треков.
    DateStart,       // Глубина выборки с.
    DateEnd,         // Глубина выборки по.
    SingleLoad       // Одиночная загрузка?
  };

  // Устанавливает значение value по ключу key.
  void setData(DataInput::Key key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(DataInput::Key key);
  // Возвращает строковое значение информации в виде списка.
  QStringList toStringList() const;

private:
  // Возвращает строковое значение ключа.
  QString keyToString(DataInput::Key key) const;
  // Возвращает строковое значение ключа на русском.
  QString keyToRusString(DataInput::Key key) const;


private:
  QMap <DataInput::Key, QVariant> m_data;

};

Q_DECLARE_METATYPE(DataInput)



#endif // DATAINPUT_H
