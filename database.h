#ifndef DATABASE_H
#define DATABASE_H

#include "dataclasses/trackinfo.h"
#include "widgets/dbviewwidget/dbviewmodel.h"

#include <QObject>
#include <QtSql>
#include <QSqlTableModel>

// Database - класс базы данных типа QSQLITE.
// Является классом одиночкой (Singletone).

const QString TABLE_NAME = "tracks";

const QString RU_HEADER_HREF =    "Ссылка";
const QString RU_HEADER_TRACK =   "Трек";
const QString RU_HEADER_GENRE =   "Стиль";
const QString RU_HEADER_ARTIST =  "Артист";
const QString RU_HEADER_ALBUM =   "Альбом";
const QString RU_HEADER_CATALOG = "Каталог";
const QString RU_HEADER_LABEL =   "Лэйбл";
const QString RU_HEADER_DATE =    "Дата";

class Database
{
  static Database* m_self;

protected:
  Database();

public:
  // Возвращает единственный экземпляр БД (создает если необходимо).
  static Database* getInstance();
  DbViewModel* model() { return m_model; }

private:
  void initialize();       // Инициализация базы данных.
  QSqlError createTable(); // Создает таблицу.

private:
  QSqlDatabase m_database;
  DbViewModel* m_model;
};

#endif // DATABASE_H
