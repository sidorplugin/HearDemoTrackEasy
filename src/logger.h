#ifndef LOGGER_H
#define LOGGER_H

#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QList>

// LogStream - класс-обертка, представляющий поток для вывода отладочной информации.
class LogStreamPrivate;

class LogStream : public QTextStream
{
  Q_DISABLE_COPY(LogStream);
public:
  LogStream() : QTextStream(){}
  LogStream( QIODevice * device ): QTextStream(device), m_d(0){}
  LogStream( FILE * fileHandle,
             QIODevice::OpenMode openMode = QIODevice::WriteOnly) :
    QTextStream(fileHandle,openMode), m_d(0) {}
  LogStream( QString * string,
             QIODevice::OpenMode openMode  = QIODevice::WriteOnly) :
    QTextStream(string,openMode), m_d(0) {}
  LogStream( QByteArray * array,
             QIODevice::OpenMode openMode = QIODevice::WriteOnly) :
    QTextStream(array,openMode), m_d(0) {}
  /*!
          Создает поток вывода отладочной информации в файл logFileName,
          если append true то записи добавляются в конец файла,
          иначе перед созданем потока содержисое файла уничтожается
          Если файл не удалось открыть device() вернет 0.
        */

  LogStream(const QString& logFileName, bool append = false);

  virtual ~LogStream();

private:
  LogStreamPrivate* m_d;
};

//----------------------------------------------------------------------------
/*
      Logger - класс одиночка представляющий мэнеджер потоков вывода отладочной
               информации.
      makeLog - регистрирует поток вывода отладочной информации.
      logCount - возваращает количество зарегистрированных котоков вывода.
      logsNames - возвращает все имена зарегистрированных потоков.
      getStream(int) - возвращает поток вывода по индексу.
      getStream(QString) - возвращает поток вывода по имени.
    */

class LoggerPrivate;

class  Logger
{
  Q_DISABLE_COPY(Logger)

public:
  Logger();
  ~Logger();

  void makeLog(const QString& name, QIODevice * device );
  void makeLog(const QString& name, FILE * fileHandle,
               QIODevice::OpenMode openMode = QIODevice::WriteOnly );
  void makeLog(const QString& name, QString * string ,
               QIODevice::OpenMode openMode = QIODevice::WriteOnly );
  void makeLog(const QString& name, QByteArray * array,
               QIODevice::OpenMode openMode = QIODevice::WriteOnly );
  void makeLog(const QString& name, const QString& logFileName,
               bool append = false);

  unsigned int logCount();
  QList<QString> logsNames();
  LogStream* getStream(unsigned int index);
  LogStream* getStream(const QString& name);

  void makeNote(const QString& note);

private:
  void removeLog(const QString& name);

private:
  LoggerPrivate* m_d;
};

Logger&  operator<<(Logger& logger, const QString& note);

Logger&  gLogger();

//-----------------------------------------------------------------------------
// функция коротая пеернаправляет вывод сообщений qDebug() qWarning() и
// qCritical() в логгер Logger и его потоки вывода.
// При записи сообщений в потоки qDebug() qWarning() и qCritical() будет
// записывать сообщение вида [dd.MM.yyyy hh:mm:ss]message\n,
// где dd.MM.yyyy hh:mm:ss время записи сообщения.
// Запись сообщений происходит во все потоки логера.
// Для инсталяции нужно вызвать qInstallMsgHandler(logMessageHandler).

void  logMessageHandler(QtMsgType type, const char *msg);

#endif // LOGGER_H
