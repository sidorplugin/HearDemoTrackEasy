#ifndef DOWNLOADHANDLER_H
#define DOWNLOADHANDLER_H

#include <QObject>
#include <QHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSignalMapper>


// Класс загрузчик файлов по https ссылке. Работает в многопоточном режиме.
// (см. QNetworkAccessManager). Результатом работы загрузчика являются
// готовый ответ (readyReply), ошибка при загрузке error и прогресс в загрузке
// (downloadProgress)).

class DownloadHandler : public QObject
{
  Q_OBJECT
public:
  DownloadHandler();

  // Загружает файл с данным href.
  void load(const QString& href);

  // Останавливает загрузку файлов.
  void stop();

signals:
  // Сигнал о готовности результата.
  void readyReply(QString, QNetworkReply*);
  void downloadProgress(const QString&, qint64, qint64);
  void error(const QString&);

private slots:
  // Слот. По завершению загрузки отправляет результат.
  void on_finished(const QString& href);
  // Слот. Оповещает о прогрессе в закачке.
  void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);


private:
  QNetworkAccessManager* m_networkManager;
  QSignalMapper* m_mapper;
  QHash <QString, QNetworkReply*> m_repliesTable;
  QHash <QString, QString> m_redirectHrefTable;
  bool m_isStoped;

};

#endif // DOWNLOADHANDLER_H
