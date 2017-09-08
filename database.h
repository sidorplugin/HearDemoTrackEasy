#ifndef DATABASE_H
#define DATABASE_H

#include "dataclasses/mediainfo.h"
#include "model.h"

#include <QObject>
#include <QtSql>
#include <QSqlTableModel>

// Database - класс базы данных типа QSQLITE.
// Является классом одиночкой (Singletone).

class Database
{
  static Database* m_self;

protected:
  Database();

public:
  // Возвращает единственный экземпляр БД (создает если необходимо).
  static Database* getInstance();
  Model* model() { return m_model; }

private:
  void initialize();              // Инициализация базы данных.
  QSqlError createTracksTable();  // Создает таблицу треков.

private:
  QSqlDatabase m_database;
  Model* m_model;
};

#endif // DATABASE_H
