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
  m_model->setHeaderData(0, Qt::Horizontal, RU_HEADER_ARTIST);
  m_model->setHeaderData(1, Qt::Horizontal, RU_HEADER_TITLE);
  m_model->setHeaderData(2, Qt::Horizontal, RU_HEADER_ALBUM);
  m_model->setHeaderData(3, Qt::Horizontal, RU_HEADER_STYLE);
  m_model->setHeaderData(4, Qt::Horizontal, RU_HEADER_CATALOG);
  m_model->setHeaderData(5, Qt::Horizontal, RU_HEADER_LABEL);
  m_model->setHeaderData(6, Qt::Horizontal, RU_HEADER_DATE);
  m_model->setHeaderData(7, Qt::Horizontal, RU_HEADER_LINK_TRACK);
  m_model->setHeaderData(8, Qt::Horizontal, RU_HEADER_LINK_IMAGE);
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
  if (!query.exec(QLatin1String("CREATE TABLE tracks(artist VARCHAR,"
                                  " title VARCHAR,"
                                  " album VARCHAR,"
                                  " style VARCHAR,"
                                  " catalog VARCHAR,"
                                  " label VARCHAR,"
                                  " date VARCHAR,"
                                  " link_track VARCHAR,"
                                  " link_image VARCHAR)")))
    return query.lastError();

  return QSqlError();
}
