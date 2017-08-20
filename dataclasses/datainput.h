#ifndef DATAINPUT_H
#define DATAINPUT_H

#include "dataclasses/trackinfo.h"

#include <QString>
#include <QHash>
#include <QDate>

// Структура DataInput хранит данные "Источника".
struct DataInput
{
public:
  QString source;                  // Источник.
  QString genre;                   // Текущий жанр. Будет отображаться в БД.
  QString period;                  // Текущий период.
  QString filter;                  // Текущий фильтр.
  QString search;                  // Строка поиска.
  int row;                         // Текущая строка в виджете просмотра треков.

  QDate dateStart;                 // Глубина выборки с.
  QDate dateEnd;                   // Глубина выборки по.

  bool isSingleLoad;               // Одиночная загрузка?

};

Q_DECLARE_METATYPE(DataInput)



#endif // DATAINPUT_H
