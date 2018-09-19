#include "database.h"

Database* Database::m_self = NULL;

Database::Database()
{
  // Создает БД и таблицы.
  initialize();

  m_model = new Model;

  m_model->setTable("tracks");
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  m_model->select();

  // Создает заголовки модели.
  for (int i = MediaInfo::Id_Track; i <= MediaInfo::Source; i++) {
      m_model->setHeaderData(i, Qt::Horizontal, MediaInfo::name(i));
  }
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
