#ifndef LOGGER_H
#define LOGGER_H

#include <QIODevice>
#include <QString>
#include <QTextStream>
#include <QList>

// LogStream - �����-�������, �������������� ����� ��� ������ ���������� ����������.
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
          ������� ����� ������ ���������� ���������� � ���� logFileName,
          ���� append true �� ������ ����������� � ����� �����,
          ����� ����� �������� ������ ���������� ����� ������������
          ���� ���� �� ������� ������� device() ������ 0.
        */

  LogStream(const QString& logFileName, bool append = false);

  virtual ~LogStream();

private:
  LogStreamPrivate* m_d;
};

//----------------------------------------------------------------------------
/*
      Logger - ����� �������� �������������� �������� ������� ������ ����������
               ����������.
      makeLog - ������������ ����� ������ ���������� ����������.
      logCount - ����������� ���������� ������������������ ������� ������.
      logsNames - ���������� ��� ����� ������������������ �������.
      getStream(int) - ���������� ����� ������ �� �������.
      getStream(QString) - ���������� ����� ������ �� �����.
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
// ������� ������� �������������� ����� ��������� qDebug() qWarning() �
// qCritical() � ������ Logger � ��� ������ ������.
// ��� ������ ��������� � ������ qDebug() qWarning() � qCritical() �����
// ���������� ��������� ���� [dd.MM.yyyy hh:mm:ss]message\n,
// ��� dd.MM.yyyy hh:mm:ss ����� ������ ���������.
// ������ ��������� ���������� �� ��� ������ ������.
// ��� ���������� ����� ������� qInstallMsgHandler(logMessageHandler).

void  logMessageHandler(QtMsgType type, const char *msg);

#endif // LOGGER_H
