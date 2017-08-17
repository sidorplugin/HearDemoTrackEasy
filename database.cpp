#include "database.h"

Database* Database::m_self = NULL;

Database::Database()
{
  // Создает БД и таблицы.
  initialize();

  // Создает и настраивает модель.
  m_model = new DbViewModel();
  m_model->setTable(TABLE_NAME);
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_model->select();
  m_model->setHeaderData(0, Qt::Horizontal, RU_HEADER_HREF);
  m_model->setHeaderData(1, Qt::Horizontal, RU_HEADER_TRACK);
  m_model->setHeaderData(2, Qt::Horizontal, RU_HEADER_GENRE);
  m_model->setHeaderData(3, Qt::Horizontal, RU_HEADER_ARTIST);
  m_model->setHeaderData(4, Qt::Horizontal, RU_HEADER_ALBUM);
  m_model->setHeaderData(5, Qt::Horizontal, RU_HEADER_CATALOG);
  m_model->setHeaderData(6, Qt::Horizontal, RU_HEADER_LABEL);
  m_model->setHeaderData(7, Qt::Horizontal, RU_HEADER_DATE);
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
    qWarning() << "error open Db " + error.text();
  }

  if (m_database.tables().isEmpty()) {
    error = createTable();
    if (error.type() != QSqlError::NoError) {
      qWarning() << "Failure to create table in database " + error.text();
    }
  }
}

// TODO Переименовать на createTables
// Создает таблицы.
QSqlError Database::createTable()
{
  qDebug() << "Database::createTable";

  QSqlQuery query(m_database);
  if (!query.exec(QLatin1String("CREATE TABLE tracks(href VARCHAR PRIMARY KEY,"
                                  " track VARCHAR,"
                                  " style VARCHAR,"
                                  " artist VARCHAR,"
                                  " album VARCHAR,"
                                  " catalog VARCHAR,"
                                  " label VARCHAR,"
                                  " date VARCHAR)")))
    return query.lastError();

  if (!query.exec(QLatin1String(
                   "CREATE TABLE emptyReleases(href VARCHAR PRIMARY KEY)")))
    return query.lastError();

  return QSqlError();
}
