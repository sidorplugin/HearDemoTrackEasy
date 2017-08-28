#include "dataclasses/datainput.h"


// Устанавливает значение value по ключу key.
void DataInput::setData(DataInput::Key key, const QVariant &value)
{
  m_data.insert(key, value);
}


// Возвращает значение по ключу key.
QVariant DataInput::data(DataInput::Key key)
{
  return m_data.value(key);
}


// Возвращает строковое значение информации в виде списка.
QStringList DataInput::toStringList() const
{
  QStringList result;
  QMapIterator <DataInput::Key, QVariant> i(m_data);
  while (i.hasNext()) {
      i.next();
      if (i.key() == DataInput::Row || i.key() == DataInput::SingleLoad)
        continue;
      QString nameKey = keyToRusString(i.key());
      if (!i.value().toString().isEmpty())
        result.append(nameKey + " : " + i.value().toString());
  }
  return result;
}


// Возвращает строковое значение ключа.
QString DataInput::keyToString(DataInput::Key key) const
{
  QString name;
  switch (key) {
      case DataInput::Source :        name = "Source";         break;
      case DataInput::Genre :         name = "Genre";          break;
      case DataInput::Period :        name = "Period";         break;
      case DataInput::Filter :        name = "Filter";         break;
      case DataInput::SearchSource :  name = "SearchSource";   break;
      case DataInput::SearchGroup :   name = "SearchGroup";    break;
      case DataInput::SearchText :    name = "SearchText";     break;
      case DataInput::Row :           name = "Row";            break;
      case DataInput::DateStart :     name = "DateStart";      break;
      case DataInput::DateEnd :       name = "DateEnd";        break;
      case DataInput::SingleLoad :    name = "SingleLoad";     break;
  }
  return name;
}


// Возвращает строковое значение ключа.
QString DataInput::keyToRusString(DataInput::Key key) const
{
  QString name;
  switch (key) {
      case DataInput::Source :        name = "Источник";               break;
      case DataInput::Genre :         name = "Жанр";                   break;
      case DataInput::Period :        name = "Период";                 break;
      case DataInput::Filter :        name = "Фильтр";                 break;
      case DataInput::SearchSource :  name = "Поиск-Источник";         break;
      case DataInput::SearchGroup :   name = "Поиск-Группа";           break;
      case DataInput::SearchText :    name = "Поиск-Текст";            break;
      case DataInput::Row :           name = "Строка";                 break;
      case DataInput::DateStart :     name = "Выбрать с";              break;
      case DataInput::DateEnd :       name = "Выбрать до";             break;
      case DataInput::SingleLoad :    name = "Одиночная загрузка";     break;
  }
  return name;
}
