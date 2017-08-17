#include "waitingwidget.h"

WaitingWidget::WaitingWidget(QWidget *parent) : QWidget(parent),
                                                m_parent(parent)
{
  m_movie = new QMovie(":/images_ui/images/loading.gif");

  m_label = new QLabel(parent);
  m_label->setMovie(m_movie);
  m_label->setAlignment( Qt::AlignCenter );
  m_label->setProperty( "class", "Wait" );
  m_label->setStyleSheet( STYLESHEET );
  m_label->adjustSize();
  m_label->raise();
  m_label->hide();
  resize( 100, 100 );

  m_textLabel = new QLabel(parent);
  m_textLabel->setText("Идет выборка");
  m_textLabel->setAlignment( Qt::AlignCenter );
  m_textLabel->setProperty( "class", "Wait" );
  m_textLabel->setStyleSheet( STYLESHEET );
  m_textLabel->adjustSize();
  m_textLabel->raise();
  m_textLabel->hide();

  QVBoxLayout* layout = new QVBoxLayout(parent);
  layout->addWidget(m_label, 1, Qt::AlignBottom | Qt::AlignHCenter);
  layout->addWidget(m_textLabel, 1, Qt::AlignTop | Qt::AlignHCenter);

}

WaitingWidget::~WaitingWidget()
{
  stop();
}

// Устанавливает в виджет текстовую информацию о состоянии обработки.
void WaitingWidget::setFetchingPage(int count, int total)
{
  m_textLabel->setText("Выбрано страниц " + QString::number(count) +
                       " из " + QString::number(total));
}


void WaitingWidget::resizeEvent(QResizeEvent *)
{
  int x = ( m_parent->width() - m_label->width() ) / 2;
  int y = CENTER_POSITION_FROM_PARENT_TOP * m_parent->height() - m_label->height() / 2;
  m_label->move( x, y );
}


void WaitingWidget::start()
{
  m_movie->start();
  m_label->show();
  m_textLabel->show();
}

void WaitingWidget::stop()
{
  m_movie->stop();
  m_label->hide();
  m_textLabel->hide();
}

