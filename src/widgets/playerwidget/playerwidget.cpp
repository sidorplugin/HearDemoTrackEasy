#include "playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
  m_player = new QMediaPlayer(this);

  ui = new Ui::PlayerWidgetForm;
  ui->setupUi(this);

  // Устанавливает фильтр событий на слайдеры для реализации перемещения.
  ui->rewind->installEventFilter(this);
  ui->volume->installEventFilter(this);

  // Устанавливает диапазон громкости.
  ui->volume->setRange(0, 100);

  connect(ui->play, &QToolButton::clicked, [=] () {
      emit clicked(PlayerWidget::PlayButton);
  });

  connect(ui->previous, &QToolButton::clicked, [=] () {
      emit clicked(PlayerWidget::PreviousButton);
  });

  connect(ui->next, &QToolButton::clicked, [=] () {
      emit clicked(PlayerWidget::NextButton);
  });

  connect(ui->pause, SIGNAL(clicked(bool)),
          m_player, SLOT(pause()));

  connect(ui->stop, SIGNAL(clicked(bool)),
          m_player, SLOT(stop()));

  connect(m_player, SIGNAL(durationChanged(qint64)),
          this, SLOT(setDuration(qint64)));

  connect(m_player, SIGNAL(positionChanged(qint64)),
          this, SLOT(setPositionSliderRewind(qint64)));

  connect(ui->rewind, SIGNAL(sliderMoved(int)),
          this, SLOT(rewind(int)));

}

PlayerWidget::~PlayerWidget()
{
  delete m_player;
  delete ui;
}


// Воспроизводит трек.
void PlayerWidget::play(MediaInfo& track)
{
  qDebug() << track.data(MediaInfo::Title_Track).toString();

  m_player->setMedia(QUrl(track.data(MediaInfo::Link_Track).toString()));
  m_player->setVolume(ui->volume->value());
  m_player->play();

  // Отображает информацию о треке в виджете.
  ui->info->setText(track.data(MediaInfo::Artist).toString() + " - " +
                    track.data(MediaInfo::Title_Track).toString());
}


// Устанавливает продолжительность трека в мсек.
void PlayerWidget::setDuration(qint64 duration)
{
  m_duration = duration;
  ui->rewind->setMaximum(duration);
}


// Устанавливает позицию слайдера перемотки.
void PlayerWidget::setPositionSliderRewind(qint64 position)
{
  ui->rewind->setValue(position);

  // Если конец трека проигрывает следующий.
  if ((position == m_duration) && (m_duration != 0))
    emit clicked(PlayerWidget::NextButton);
}


// Перемотка трека на позицию.
void PlayerWidget::rewind(int position)
{
  m_player->setPosition(position);
}


// Фильтрует событие нажатие мышью по слайдеру перемотки и слайдеру громкости.
bool PlayerWidget::eventFilter(QObject* watched, QEvent* event)
{
  if (watched == ui->rewind &&
      event->type() == QEvent::MouseButtonRelease ) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      rewind(QStyle::sliderValueFromPosition(
                    ui->rewind->minimum(),
                    ui->rewind->maximum(),
                    mouseEvent->x(),
                    ui->rewind->width())
                  );
     return true;
  }

  if (watched == ui->volume &&
      event->type() == QEvent::MouseButtonRelease) {
      QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
      m_player->setVolume(QStyle::sliderValueFromPosition(
                              ui->volume->minimum(),
                              ui->volume->maximum(),
                              mouseEvent->y(),
                              ui->volume->height(),
                              true)
                          );
      return true;
  }
  return false;
}


//void PlayerWidget::wheelEvent(QWheelEvent *event)
//{
//}
