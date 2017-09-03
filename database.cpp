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
  m_model->setHeaderData(0, Qt::Horizontal, RU_HEADER_ID);
  m_model->setHeaderData(1, Qt::Horizontal, RU_HEADER_ARTIST);
  m_model->setHeaderData(2, Qt::Horizontal, RU_HEADER_TITLE_TRACK);
  m_model->setHeaderData(3, Qt::Horizontal, RU_HEADER_TITLE_ALBUM);
  m_model->setHeaderData(4, Qt::Horizontal, RU_HEADER_STYLE);
  m_model->setHeaderData(5, Qt::Horizontal, RU_HEADER_CATALOG);
  m_model->setHeaderData(6, Qt::Horizontal, RU_HEADER_LABEL);
  m_model->setHeaderData(7, Qt::Horizontal, RU_HEADER_DATE);
  m_model->setHeaderData(8, Qt::Horizontal, RU_HEADER_LINK_TRACK);
  m_model->setHeaderData(9, Qt::Horizontal, RU_HEADER_LINK_IMAGES);
  m_model->setHeaderData(10,Qt::Horizontal, RU_HEADER_SOURCE);
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
  if (!query.exec(QLatin1String("CREATE TABLE album(id INTEGER NOT NULL PRIMARY KEY,"
                                " artist VARCHAR,"
                                " title VARCHAR,"
                                " style VARCHAR,"
                                " catalog VARCHAR,"
                                " label VARCHAR,"
                                " date VARCHAR,"
                                " images VARCHAR,"
                                " source VARCHAR)")))
    return query.lastError();
  if (!query.exec(QLatin1String("CREATE TABLE tracks(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                " title VARCHAR,"
                                " link VARCHAR,"
                                " album_id INTEGER NOT NULL,"
                                " FOREIGN KEY (album_id) REFERENCES album(id))")))
    return query.lastError();

  return QSqlError();
}
