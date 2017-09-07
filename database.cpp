#include "database.h"

Database* Database::m_self = NULL;

Database::Database()
{
  // Создает БД и таблицы.
  initialize();

  m_model = new Model;
}


// Возвращает единственный экземпляр БД (создает если необходимо).
Database* Database::getInstance()
{
  if (!m_self)
    m_self = new Database;
  return m_self;
}


// Инициализация базы данных.
void Database::initialize()
{
  qDebug() << "Database::initialize()";

  QSqlError error;
  m_database = QSqlDatabase::addDatabase("QSQLITE");
  m_database.setDatabaseName("database.db");

  if (!m_database.open()) {
    error = m_database.lastError();
    qWarning() << error.text();
    return;
  }

  if (m_database.tables().isEmpty()) {
    error = createAlmumsTable();
    if (error.type() != QSqlError::NoError) {
      qWarning() << "Failure to create AlbumsTable in database " + error.text();
    }
    error = createTracksTable();
    if (error.type() != QSqlError::NoError) {
      qWarning() << "Failure to create TracksTable in database " + error.text();
    }
  }
}


// Создает таблицу альбомов.
QSqlError Database::createAlmumsTable()
{
  QSqlQuery query(m_database);
  if (!query.exec(QLatin1String("CREATE TABLE albums(id INTEGER NOT NULL PRIMARY KEY,"
                                " artist VARCHAR,"
                                " title VARCHAR,"
                                " style VARCHAR,"
                                " catalog VARCHAR,"
                                " label VARCHAR,"
                                " date VARCHAR,"
                                " images VARCHAR,"
                                " source VARCHAR)")))
    return query.lastError();

  return QSqlError();
}


// Создает таблицу треков.
QSqlError Database::createTracksTable()
{
  QSqlQuery query(m_database);
  if (!query.exec(QLatin1String("CREATE TABLE tracks(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                " title VARCHAR,"
                                " link VARCHAR,"
                                " album_id INTEGER NOT NULL,"
                                " FOREIGN KEY (album_id) REFERENCES album(id))")))
    return query.lastError();

  return QSqlError();
}
