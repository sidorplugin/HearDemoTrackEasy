#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "dataclasses/trackinfo.h"

#include <QStandardItemModel>
#include <QObject>

class SearchResultModel : public QStandardItemModel
{
public:
  enum Items {
    CheckItem,
    ArtistItem,
    TitleItem,
    AlbumItem,
    GenreItem,
    LinkItem,
    CatalogItem,
    PublisherItem,
    DateItem
  };

  SearchResultModel();

  // Добавляет трек в модель.
  void add(TrackInfo& track);
  // Возвращает информацию о треке по номеру строки.
  TrackInfo getTrackInfo(int row);
  // Возвращает true если элемент в строке row выделен.
  bool isCheckedState(int row);
  // Возвращает строковое значение перечисления Items.
  QString name(int key);

};

#endif // SEARCHRESULTMODEL_H
