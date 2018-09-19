#include "logger.h"
#include <QFile>
#include <QHash>
#include <QMutex>
#include <QMutexLocker>

// Класс LogStreamPrivate нужен только для вызова конструктора
// LogStream(const QString& logFileName, bool append),
// поскольку в этом случае нужно хранить указатель на файл куда производится
// запись. В других случаях это не нужно.
class LogStreamPrivate
{
public:
    LogStreamPrivate():file(0)
    {}

    ~LogStreamPrivate()
    {
        if(file){
            file->close();
            delete file;
        }
    }

public:
    QFile* file;
};

//-----------------------------------------------------------------------------
// TODO: есть ли необходимость в этом констуркторе?
// Он конечно удобен, но все тоже можно реализовать и с помощью
// LogStream( QIODevice * device )
LogStream::LogStream(const QString& logFileName, bool append)
          :m_d(new LogStreamPrivate)
{
    QFile* file = new QFile(logFileName);
    if ( file->open(QIODevice::WriteOnly |
                   (append ? QIODevice::Append : QIODevice::Truncate)) ) {
        setDevice(file);
        m_d->file = file;
    }
    else {
        delete file;
        setDevice(0);
    }
}


LogStream::~LogStream()
{
    if(m_d){
        delete m_d;
    }
}

// ----------------------------------------------------------------------------
// LogEntry используется вместо обычного указателя на LogStream, поскольку
// первоначально была идея, что будут храниться еще какие-то дополнительные
// параметры.

struct LogEntry
{
    LogStream* log;
};


class LoggerPrivate
{
public:
    LoggerPrivate() : mutex()
    {}

public:
    QMutex mutex;
    QHash<QString,LogEntry> logs;
    // logsNames нужен для удобства.
    // Используется для более эффективной работы getStream(unsigned int index)
    QList<QString> logsNames;
};


//-----------------------------------------------------------------------------

Logger::Logger()
       :m_d(new LoggerPrivate)
{}

Logger::~Logger()
{
    if(m_d){
        delete m_d;
    }
}


void Logger::removeLog(const QString& name)
{
    if(m_d){
        QMutexLocker locker(&m_d->mutex);
        QHash<QString,LogEntry>::iterator i = m_d->logs.find(name);
        if(i != m_d->logs.end()){
            const LogEntry& entry  = i.value();
            if(entry.log){
                delete entry.log;
            }
            m_d->logs.erase(i);
            m_d->logsNames.removeAll(name);
        }
    }
}

// Макрос для вставки новых элементов.  Поскольку создание объектов LogStream
// производиться нами, то перед тем как  вставлять новый нужно правильно убрать
// старый для того, чтобы избежать утечек памяти.

#define INSERT_LOG(name,entry) Logger::removeLog(name);         \
                               QMutexLocker locker(&m_d->mutex);\
                               m_d->logsNames.push_back(name);  \
                               m_d->logs[name] = entry;

void Logger::makeLog(const QString& name, QIODevice * device )
{
    if (m_d) {
        LogEntry entry;
        entry.log = new LogStream(device);

        INSERT_LOG(name,entry);
    }
}


void Logger::makeLog(const QString& name, FILE * fileHandle,
                     QIODevice::OpenMode openMode)
{
    if (m_d) {
        LogEntry entry;
        entry.log = new LogStream(fileHandle,openMode);

        INSERT_LOG(name,entry);
    }
}


void Logger::makeLog(const QString& name, QString * string , QIODevice::OpenMode openMode)
{
    if (m_d) {
        LogEntry entry;
        entry.log = new LogStream(string,openMode);

        INSERT_LOG(name,entry);
    }
}

void Logger::makeLog(const QString& name, QByteArray * array, QIODevice::OpenMode openMode)
{
    if (m_d) {
        LogEntry entry;
        entry.log = new LogStream(array,openMode);

        INSERT_LOG(name,entry);
    }
}


void Logger::makeLog(const QString& name, const QString& logFileName, bool append)
{
    if (m_d) {
        LogEntry entry;
        entry.log = new LogStream(logFileName,append);

        INSERT_LOG(name,entry);
    }
}

#undef INSERT_LOG

unsigned int Logger::logCount()
{
    return m_d ? m_d->logs.count() : 0;
}


QList<QString> Logger::logsNames()
{
    QList<QString> lst;
    if (m_d) {
        lst = m_d->logsNames;
    }
    return lst;
}

LogStream* Logger::getStream(unsigned int index)
{
    LogStream* stream = 0;
    if (m_d && (index < m_d->logsNames.size())) {
        QMutexLocker locker(&m_d->mutex);
        QHash<QString,LogEntry>::const_iterator ci =
                          m_d->logs.find(m_d->logsNames.at(index));
        if (ci != m_d->logs.end()) {
            stream = ci.value().log;
        }
    }
    return stream;
}


LogStream* Logger::getStream(const QString& name)
{
    LogStream* stream = 0;
    if (m_d) {
        QMutexLocker locker(&m_d->mutex);
        stream = m_d->logs.value(name).log;
    }
    return stream;
}

void Logger::makeNote(const QString& note)
{
    for (unsigned int i = 0; i < Logger::logCount(); i++) {
        LogStream* stream = Logger::getStream(i);

        QMutexLocker locker(&m_d->mutex);
        stream->operator << (note);
        stream->flush();
    }
}


Logger& operator<<(Logger& logger, const QString& note)
{
    logger.makeNote(note);
    return logger;
}

//-----------------------------------------------------------------------------

Logger g_log;

Logger& gLogger()
{
    return g_log;
}

#undef INSERT_LOG

//-----------------------------------------------------------------------------
#include <qdatetime>

void logMessageHandler(QtMsgType type, const char *msg)
{
    QString note = QString("[%1]%2\n").
      arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")).arg(msg);
    switch (type) {
        case QtDebugMsg:
            gLogger()<<note;
        break;
        case QtWarningMsg:
            gLogger()<<note;
        break;
        case QtCriticalMsg:
            gLogger()<<note;
        break;
        case QtFatalMsg:
            gLogger()<<note;
        break;
     }
}

