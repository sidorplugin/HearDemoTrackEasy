#include "database.h"

Database* Database::m_self = NULL;

Database::Database()
{
  // Создает БД и таблицы.
  initialize();

  m_model = new Model;

  m_model->setTable("tracks");
//  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//  m_model->select();
//  m_model->setHeaderData(0, Qt::Horizontal, "Ссылка");
//  m_model->setHeaderData(1, Qt::Horizontal, "Трек");
//  m_model->setHeaderData(2, Qt::Horizontal, "Стиль");
//  m_model->setHeaderData(3, Qt::Horizontal, "Артист");
//  m_model->setHeaderData(4, Qt::Horizontal, "Альбом");
//  m_model->setHeaderData(5, Qt::Horizontal, "Каталог");
//  m_model->setHeaderData(6, Qt::Horizontal, "Лэйбл");
//  m_model->setHeaderData(7, Qt::Horizontal, "Дата");
//  m_model->setHeaderData(0, Qt::Horizontal, "Ссылка");
//  m_model->setHeaderData(1, Qt::Horizontal, "Трек");
//  m_model->setHeaderData(2, Qt::Horizontal, "Стиль");
//  m_model->setHeaderData(3, Qt::Horizontal, "Артист");
//  m_model->setHeaderData(4, Qt::Horizontal, "Альбом");
//  m_model->setHeaderData(5, Qt::Horizontal, "Каталог");
//  m_model->setHeaderData(6, Qt::Horizontal, "Лэйбл");
//  m_model->setHeaderData(7, Qt::Horizontal, "Дата");
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
    error = createTracksTable();
    if (error.type() != QSqlError::NoError) {
      qWarning() << "Failure to create AlbumsTable in database " + error.text();
    }
  }
}


// Создает таблицу треков.
QSqlError Database::createTracksTable()
{
  QSqlQuery query(m_database);
  if (!query.exec(QLatin1String("CREATE TABLE tracks("
                                " id_track INTEGER NOT NULL PRIMARY KEY,"
                                " id_album INTEGER,"
                                " artist VARCHAR,"
                                " title_track VARCHAR,"
                                " title_album VARCHAR,"
                                " style VARCHAR,"
                                " catalog VARCHAR,"
                                " label VARCHAR,"
                                " date VARCHAR,"
                                " images VARCHAR,"
                                " link_track VARCHAR,"
                                " link_album VARCHAR,"
                                " source VARCHAR)")))
    return query.lastError();

  return QSqlError();
}
