#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
  m_player = new QMediaPlayer(this);

  ui = new Ui::PlayerWidgetForm;
  ui->setupUi(this);

  // Устанавливает фильтр событий на слайдеры для реализации перемещения.
  ui->slider_Rewind->installEventFilter(this);
  ui->slider_Volume->installEventFilter(this);

  // Устанавливает диапазон громкости.
  ui->slider_Volume->setRange(0, 100);

  // Реализует систему обработки нескольких сигналов одним слотом.
  m_mapper = new QSignalMapper;
  connect(m_mapper, SIGNAL(mapped(int)),
          this, SIGNAL(clicked(int)));

  // Хранит кнопки в списке для дальнейшего перебора в цикле.
  m_buttons.insert(PlayerWidget::PlayButton, ui->toolButton_Play);
  m_buttons.insert(PlayerWidget::PreviousButton, ui->toolButton_Previous);
  m_buttons.insert(PlayerWidget::NextButton, ui->toolButton_Next);

  QMapIterator <int, QToolButton*> i(m_buttons);
  while (i.hasNext()) {
      i.next();
      QToolButton* button = i.value();
      connect(button, SIGNAL(clicked(bool)), m_mapper, SLOT(map()));
      m_mapper->setMapping(button, i.key());
  }

  connect(ui->toolButton_Pause, SIGNAL(clicked(bool)),
          m_player, SLOT(pause()));

  connect(ui->toolButton_Stop, SIGNAL(clicked(bool)),
          m_player, SLOT(stop()));

  connect(m_player, SIGNAL(durationChanged(qint64)),
          this, SLOT(setDurationTrack(qint64)));

  connect(m_player, SIGNAL(positionChanged(qint64)),
          this, SLOT(setPositionSliderRewind(qint64)));

  connect(ui->slider_Rewind, SIGNAL(sliderMoved(int)),
          this, SLOT(rewindTrack(int)));

}

PlayerWidget::~PlayerWidget()
{
  delete m_player;
  delete ui;
  delete m_mapper;
}


// Воспроизводит трек.
void PlayerWidget::play(AlbumInfo& track)
{
  m_player->setMedia(QUrl(track.data(AlbumInfo::Tracks).toHash().values().at(0).toString()));
  m_player->setVolume(ui->slider_Volume->value());
  m_player->play();

  // Отображает информацию о треке в виджете.
  ui->label_TrackInfo->setText(
                       track.data(AlbumInfo::Artist).toString() + " - " +
                       track.data(AlbumInfo::Title).toString());
}


// Устанавливает продолжительность трека в мсек.
void PlayerWidget::setDurationTrack(qint64 duration)
{
  m_duration = duration;
  ui->slider_Rewind->setMaximum(duration);
}


// Устанавливает позицию слайдера перемотки.
void PlayerWidget::setPositionSliderRewind(qint64 position)
{
  ui->slider_Rewind->setValue(position);

  // Если конец трека проигрывает следующий.
  if ((position == m_duration) && (m_duration != 0))
    emit clicked(PlayerWidget::NextButton);
}


// Перемотка трека на позицию.
void PlayerWidget::rewindTrack(int position)
{
  m_player->setPosition(position);
}


// Фильтрует событие нажатие мышью по слайдеру перемотки и слайдеру громкости.
bool PlayerWidget::eventFilter(QObject* watched, QEvent* event)
{
  if (watched == ui->slider_Rewind &&
      event->type() == QEvent::MouseButtonRelease ) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      rewindTrack(QStyle::sliderValueFromPosition(
                    ui->slider_Rewind->minimum(),
                    ui->slider_Rewind->maximum(),
                    mouseEvent->x(),
                    ui->slider_Rewind->width())
                  );
     return true;
  }

  if (watched == ui->slider_Volume &&
      event->type() == QEvent::MouseButtonRelease ) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      m_player->setVolume(QStyle::sliderValueFromPosition(
                              ui->slider_Volume->minimum(),
                              ui->slider_Volume->maximum(),
                              mouseEvent->y(),
                              ui->slider_Volume->height(),
                              true)
                          );
      return true;
  }
  return false;
}
