#include "searchresultwidget.h"

SearchResultWidget::SearchResultWidget(QWidget *parent) : QWidget(parent)
{
  // Задает поля в таблице.
  // Подключает делегат c CheckBox'ом.

  // Прописывает соединения на реакции кнопок.
  // По нажатию на Добавить вызывает слот обработки добавляемых треков.
  // По нажатию на Отмена вызывает слот где удаляются результаты и закрывается окно.
}


// Добавляет список треков в таблицу.
void SearchResultWidget::addTracks(const QList<TrackInfo> &tracks)
{
  // Для каждого элемента списка создает item с данными.
  foreach (TrackInfo track, tracks) {

  // Добавляет в таблицу.
  }
}


// Обрабатывает выделенные треки в таблице.
void SearchResultWidget::handleCheckedTracks()
{
//  emit ready(list);
}

