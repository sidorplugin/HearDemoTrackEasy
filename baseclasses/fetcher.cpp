#include "baseclasses/fetcher.h"

#include <QEventLoop>

Fetcher::Fetcher(QObject *parent) : QObject(parent)
{
  m_isStop = false;
  m_delay = GlobalData::getInstance()->delay;
  m_waiting = GlobalData::getInstance()->waiting;

  // Устанавливает настройки где игнорируются загрузка картинок, java объекты и тд.
  QWebSettings* webSettings = m_page.settings();
  webSettings->setAttribute(QWebSettings::AutoLoadImages, false);
  webSettings->setAttribute(QWebSettings::PluginsEnabled, false);
  webSettings->setAttribute(QWebSettings::JavaEnabled, false);
  webSettings->setAttribute(QWebSettings::JavascriptEnabled, false);
  webSettings->setAttribute(QWebSettings::PrivateBrowsingEnabled, false);

  connect(&m_page, SIGNAL(loadFinished(bool)),
          this, SLOT(on_finished(bool)));

  connect(&m_page, SIGNAL(loadProgress(int)),
          this, SLOT(progress(int)));

  connect(&m_page, SIGNAL(loadStarted()),
          this, SLOT(on_started()));

  connect(&m_timer, SIGNAL(timeout()),
          this, SLOT(on_timeOut()));
}

Fetcher::~Fetcher()
{

}


void Fetcher::start(const QString &url)
{
  qDebug() << "Fetcher::start(" << url << ")";
  m_url = url;
  m_page.mainFrame()->load(QUrl(url));
}


void Fetcher::stop()
{
  qDebug() << "Fetcher::stop" << m_timer.timerId();
  m_page.triggerAction(QWebPage::Stop);
  m_isStop = true;
  m_timer.stop();
}


QString Fetcher::url() const
{
  return m_url;
}

// Устанавливает жанр.
void Fetcher::setGenre(const QString &genre)
{
  m_genre = genre;
}


void Fetcher::progress(int progress)
{
   qDebug() << "progress = " << progress;
}


void Fetcher::on_started()
{
  qDebug() << "Fetcher::on_started" << m_timer.timerId();
  qDebug() << "waiting = " << m_waiting;
  m_timer.start(m_waiting);
  qDebug() << "Fetcher::on_started" << m_timer.timerId();
}


void Fetcher::on_finished(bool ok)
{
  qDebug() << "Fetcher::on_finished()" << ok;
  if (ok) {
    qDebug() << "stop timeout";
    m_timer.stop();
    result(ok);
  }
}


void Fetcher::on_timeOut()
{
  qDebug() << "Fetcher::on_timeOut";
  // Перегрузка страницы.
  m_page.triggerAction(QWebPage::ReloadAndBypassCache);
}


void Fetcher::pause(int max)
{
  if (max == 0)
    return;

  int num = 3 + qrand() % (max - 3);
  qDebug() << "pause value = " << num;

  QEventLoop wait;
  QTimer::singleShot(num * 1000, &wait, SLOT(quit()));
  wait.exec();
}
