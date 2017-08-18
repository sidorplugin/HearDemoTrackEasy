#include "playerwidget.h"

PlayerWidget::PlayerWidget()
{
  m_player = new QMediaPlayer(this);

  m_playerUi = new Ui::PlayerWidgetForm;
  m_playerUi->setupUi(this);

//  m_runningString = new RunningString(this);
//  m_playerUi->verticalLayout->addWidget(m_runningString);

  // Устанавливает фильтр событий на слайдеры для реализации перемещения.
  m_playerUi->slider_Rewind->installEventFilter(this);
  m_playerUi->slider_Volume->installEventFilter(this);

  // Устанавливает диапазон громкости.
  m_playerUi->slider_Volume->setRange(0, 100);

  // Реализует систему обработки нескольких сигналов одним слотом.
  m_mapper = new QSignalMapper;
  connect(m_mapper, SIGNAL(mapped(QString)),
          this, SLOT(on_clickedControlButtons(QString)));

  // Хранит кнопки в списке для дальнейшего перебора в цикле.
  m_buttons << m_playerUi->toolButton_Play
            << m_playerUi->toolButton_Previous
            << m_playerUi->toolButton_Next;

  // Для каждой кнопки устанавливает идентификатор в виде его имени.
  foreach (QToolButton* button, m_buttons) {
    connect(button, SIGNAL(clicked(bool)), m_mapper, SLOT(map()));
    m_mapper->setMapping(button, button->objectName());
  }

  connect(m_playerUi->toolButton_Pause, SIGNAL(clicked(bool)),
          m_player, SLOT(pause()));

  connect(m_playerUi->toolButton_Stop, SIGNAL(clicked(bool)),
          m_player, SLOT(stop()));

  connect(m_player, SIGNAL(durationChanged(qint64)),
          this, SLOT(setDurationTrack(qint64)));

  connect(m_player, SIGNAL(positionChanged(qint64)),
          this, SLOT(setPositionSliderRewind(qint64)));

  connect(m_playerUi->slider_Rewind, SIGNAL(sliderMoved(int)),
          this, SLOT(rewindTrack(int)));

}

PlayerWidget::~PlayerWidget()
{
  delete m_player;
  delete m_playerUi;
  delete m_mapper;
}


// Воспроизводит трек.
void PlayerWidget::play(TrackInfo& track)
{
  m_player->setMedia(QUrl(track.data(TrackInfo::Link).toString()));
  m_player->setVolume(m_playerUi->slider_Volume->value());
  m_player->play();

//  m_runningString->setText(
//          track.data(TrackInfo::AlbumArtist).toString() + " - " +
//          track.data(TrackInfo::Title).toString());

  // Отображает информацию о треке в виджете.
  m_playerUi->label_TrackInfo->setText(
                       track.data(TrackInfo::AlbumArtist).toString() + " - " +
                       track.data(TrackInfo::Title).toString());
}


// Устанавливает продолжительность трека в мсек.
void PlayerWidget::setDurationTrack(qint64 duration)
{
  m_duration = duration;
  m_playerUi->slider_Rewind->setMaximum(duration);
}


// Устанавливает позицию слайдера перемотки.
void PlayerWidget::setPositionSliderRewind(qint64 position)
{
  m_playerUi->slider_Rewind->setValue(position);

  // Если конец трека проигрывает следующий.
  if ((position == m_duration) && (m_duration != 0))
      on_clickedControlButtons("toolButton_Next");
}

// Действие на нажатие клавиш управления.
// Отправляет команду запрос на воспроизведение трека.
void PlayerWidget::on_clickedControlButtons(const QString& key)
{
  if (key == "toolButton_Play") {
    emit clicked(PlayerWidget::PlayButton);
  }
  else if (key == "toolButton_Next") {
    emit clicked(PlayerWidget::NextButton);
  }
  else
    emit clicked(PlayerWidget::PreviousButton);
}


// Перемотка трека на позицию.
void PlayerWidget::rewindTrack(int position)
{
  m_player->setPosition(position);
}


// Фильтрует событие нажатие мышью по слайдеру перемотки и слайдеру громкости.
bool PlayerWidget::eventFilter(QObject* watched, QEvent* event)
{
  if (watched == m_playerUi->slider_Rewind &&
      event->type() == QEvent::MouseButtonRelease ) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      rewindTrack(QStyle::sliderValueFromPosition(
                    m_playerUi->slider_Rewind->minimum(),
                    m_playerUi->slider_Rewind->maximum(),
                    mouseEvent->x(),
                    m_playerUi->slider_Rewind->width())
                  );
     return true;
  }

  if (watched == m_playerUi->slider_Volume &&
      event->type() == QEvent::MouseButtonRelease ) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      m_player->setVolume(QStyle::sliderValueFromPosition(
                              m_playerUi->slider_Volume->minimum(),
                              m_playerUi->slider_Volume->maximum(),
                              mouseEvent->y(),
                              m_playerUi->slider_Volume->height(),
                              true)
                          );
      return true;
  }
  return false;
}
