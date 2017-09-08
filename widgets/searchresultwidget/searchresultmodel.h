#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "dataclasses/mediainfo.h"

#include <QStandardItemModel>
#include <QObject>

class SearchResultModel : public QStandardItemModel
{
public:
  SearchResultModel();

  // Добавляет трек в модель.
  void add(MediaInfo& track);
  // Возвращает информацию о треке по номеру строки.
  MediaInfo getAlbumInfo(int row);
  // Возвращает true если элемент в строке row выделен.
  bool isCheckedState(int row);
  // Возвращает строковое значение перечисления Items.
  QString name(int key);

};

#endif // SEARCHRESULTMODEL_H
