#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QString>
#include <QDate>

// Хранит входные данные выборки.
struct FetchInputPack
{
  QString source;        // Источник.
  QDate dateStart;       // Глубина выборки с.
  QDate dateEnd;         // Глубина выборки по.
  QString style;         // Текущий жанр. Будет отображаться в БД.
  QString period;        // Текущий период.
  QString filter;        // Текущий фильтр.
};

// Хранит входные данные поиска.
struct SearchInputPack
{
  QString source;        // Информация по поиску.
  QString group;
  QString text;
};

// Хранит входные данные.
struct InputPack
{
  FetchInputPack fetchPack;
  SearchInputPack searchPack;
};

#endif // DATAINPUT_H
