#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "ui_playerwidgetform.h"
#include "dataclasses/trackinfo.h"
//#include "runningstring.h"

#include <QObject>
#include <QDebug>
#include <QMediaPlayer>
#include <QSignalMapper>
#include <QMouseEvent>


// Виджет PlayerWidget - плеер, проигрывает mp3 файлы (в том числе и из сети),
// показывает информацию о файле, курсор длительности
// воспроизведения трека. Из органов управления: воспроизведение, пауза, стоп,
// следующий, предыдущий трек, громкость, слайдер перемотки.

class PlayerWidget : public QWidget
{
  Q_OBJECT
public:
  enum Button { PlayButton,
                PreviousButton,
                NextButton };

  PlayerWidget();
  ~PlayerWidget();


public slots:
  // Воспроизводит трек.
  void play(TrackInfo& track);

signals:
  // Сигнал о нажатии кнопки управления плеером.
  void clicked(PlayerWidget::Button buttton);

private slots:
  // Перемотка трека на позицию.
  void rewindTrack(int position);
  // Устанавливает продолжительность трека в мсек.
  void setDurationTrack(qint64 duration);
  // Устанавливает позицию слайдера перемотки.
  void setPositionSliderRewind(qint64 position);

  // Действие на нажатие клавиш управления.
  // Отправляет команду запрос на воспроизведение трека.
  void on_clickedControlButtons(const QString& key);

private:
  // Фильтрует событие нажатие мышью по слайдеру перемотки и слайдеру громкости.
  bool eventFilter(QObject* watched, QEvent* event);

private:
  QMediaPlayer* m_player;
  QSignalMapper* m_mapper;
//  RunningString* m_runningString;
  Ui::PlayerWidgetForm* m_playerUi;
  qint64 m_duration;
  QList <QToolButton*> m_buttons;
};

#endif // PLAYERWIDGET_H
