#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include "ui_searchresultform.h"
#include "dataclasses/trackinfo.h"

#include <QObject>
#include <QWidget>

class SearchResultWidget : public QWidget
{
  Q_OBJECT
public:
  explicit SearchResultWidget(QWidget *parent = 0);

signals:
  // Сигнал с результирующим списком выделенных треков.
  void ready(const QList<TrackInfo>&);

public slots:
  // Добавляет список треков в таблицу.
  void addTracks(const QList<TrackInfo>& tracks);

private slots:
  // Обрабатывает выделенные треки в таблице.
  void handleCheckedTracks();

private:
    Ui::SearchResultForm* ui;
    QList<TrackInfo> m_tracks;

};

#endif // SEARCHRESULTWIDGET_H
