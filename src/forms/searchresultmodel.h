#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "dataclasses/mediainfo.h"

#include <QStandardItemModel>
#include <QObject>

class SearchResultModel : public QStandardItemModel
{
public:
  SearchResultModel();

  // Добавляет медиа информацию в модель.
  void add(MediaInfo& media);
  // Возвращает информацию о треке по номеру строки.
  MediaInfo mediaInfo(int row);
  // Возвращает true если элемент в строке row выделен.
  bool isCheckedState(int row);

};

#endif // SEARCHRESULTMODEL_H
