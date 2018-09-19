#ifndef SEARCHRESULTFORM_H
#define SEARCHRESULTFORM_H

#include "dataclasses/mediainfo.h"
#include "searchresultmodel.h"

#include <QWidget>

namespace Ui {
  class SearchResultForm;
}

class SearchResultForm : public QWidget
{
  Q_OBJECT

public:
  explicit SearchResultForm(QWidget *parent = 0);
  ~SearchResultForm();

  bool hasReport() const;

signals:
  // Сигнал с результирующим списком выделенных треков.
  void addClicked(const QList<MediaInfo>&);

public slots:
  // Добавляет список треков в таблицу.
  void add(const QList<MediaInfo>& tracks);

private slots:
  // Проверяет треки модели, формирует список выделенных и отправляет их.
  void exportTracks();
  // Отмечает или снимает все флажки у треков.
  void checkUncheckAllTracks(bool ok);

protected:
  void changeEvent(QEvent *e);

private:
  Ui::SearchResultForm *ui;
  SearchResultModel* m_model;
};

#endif // SEARCHRESULTFORM_H
