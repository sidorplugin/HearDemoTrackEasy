#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "ui_playerwidgetform.h"
#include "dataclasses/mediainfo.h"

#include <QObject>
#include <QDebug>
#include <QMediaPlayer>
#include <QMouseEvent>


// Виджет PlayerWidget - плеер, проигрывает mp3 файлы (в том числе и из сети),
// показывает информацию о файле, курсор длительности
// воспроизведения трека. Из органов управления: воспроизведение, пауза, стоп,
// следующий, предыдущий трек, громкость, слайдер перемотки.

class PlayerWidget : public QWidget
{
  Q_OBJECT

public:
  enum Button {
      PlayButton,
      PreviousButton,
      NextButton
  };

  PlayerWidget(QWidget *parent = 0);
  ~PlayerWidget();


public slots:
  // Воспроизводит трек.
  void play(MediaInfo& track);

signals:
  // Сигнал о нажатии кнопки управления плеером.
  void clicked(int);

private slots:
  // Перемотка трека на позицию.
  void rewind(int position);
  // Устанавливает продолжительность трека в мсек.
  void setDuration(qint64 duration);
  // Устанавливает позицию слайдера перемотки.
  void setPositionSliderRewind(qint64 position);

private:
  // Фильтрует событие нажатие мышью по слайдеру перемотки и слайдеру громкости.
  bool eventFilter(QObject* watched, QEvent* event);
  // TODO:
  //  void wheelEvent(QWheelEvent *event);

private:
  QMediaPlayer* m_player;
  Ui::PlayerWidgetForm* ui;
  qint64 m_duration;

};

#endif // PLAYERWIDGET_H
