#include "waitingwidget.h"

#include <QDebug>

WaitingWidget::WaitingWidget(QWidget *parent) : QWidget(parent),
                                                m_parent(parent)
{
  qDebug() << "constructor waiting";
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
  m_textLabel->setAlignment( Qt::AlignCenter );
  m_textLabel->setProperty( "class", "Wait" );
  m_textLabel->setStyleSheet( STYLESHEET );
  m_textLabel->adjustSize();
  m_textLabel->raise();

  QVBoxLayout* layout = new QVBoxLayout(parent);
  layout->addWidget(m_label, 1, Qt::AlignBottom | Qt::AlignHCenter);
  layout->addWidget(m_textLabel, 1, Qt::AlignTop | Qt::AlignHCenter);

}

WaitingWidget::~WaitingWidget()
{
  qDebug() << "destructor waiting";
  stop();
  delete m_movie;
  delete m_label;
  delete m_textLabel;
}

// Устанавливает в виджет текстовую информацию о состоянии обработки.
void WaitingWidget::setInfo(int fetched, int total)
{
  m_textLabel->setText("Cтраниц " + QString::number(fetched) +
                       " из " + QString::number(total));
}

void WaitingWidget::setTitle(const QString &title)
{
    m_textLabel->setText(title);
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
