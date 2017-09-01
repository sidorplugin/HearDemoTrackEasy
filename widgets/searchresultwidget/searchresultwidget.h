#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include "ui_searchresultform.h"
#include "dataclasses/albuminfo.h"
#include "searchresultmodel.h"

#include <QCloseEvent>
#include <QObject>
#include <QMainWindow>

class SearchResultWidget : public QMainWindow
{
  Q_OBJECT
public:
  explicit SearchResultWidget(QWidget *parent = 0);
  ~SearchResultWidget();

signals:
  // Сигнал с результирующим списком выделенных треков.
  void ready(const QList<AlbumInfo>&);

public slots:
  // Добавляет список треков в таблицу.
  void addTracks(const QList<AlbumInfo>& tracks);

private slots:
  // Проверяет треки модели, формирует список выделенных и отправляет их.
  void checkTracks();
  // Отмечает или снимает все флажки у треков.
  void checkUncheckAllTracks(bool ok);

private:
    Ui::SearchResultForm* ui;
    SearchResultModel* m_model;

};

#endif // SEARCHRESULTWIDGET_H
