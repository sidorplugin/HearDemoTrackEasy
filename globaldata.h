#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "dataclasses/moduleparameters.h"

#include <QHash>
#include <QVariant>

// GlobalData - предназначен для хранения часто применяемых или
// необходимых в разных местах программы данных и методов.
// Является классом одиночкой (Singletone).

class GlobalData
{
  static GlobalData* m_self;

protected:
  GlobalData() {}

public:
  // Возвращает единственный экземпляр объекта.
  static GlobalData* getInstance();
  // Устанавливает глобальные настройки программы.
  void setGlobalSettings(const QString& root_string,
                         int delay_value,
                         int waiting_value,
                         int loads_value);
  // Считывает глобальные настройки программы.
  void readGlobalSettings();
  // Возвращает хэш таблицу параметров модуля из XML файла.
  ModuleParameters readFromXmlFile(const QString& fileName);
  // Возвращает уникальный id строк catalog и label.
  int getUniqueId(const QString& catalog, const QString& label);

public:
  // TODO в private. Создать get и set.
  QString root;                    // Путь к папке для сохранения файлов.
  int delay;                       // Задержка между запросами.
  int waiting;                     // Время ожидания выполнения запроса.
  int loads;                       // Число одновременных загрузок.
  QList <ModuleParameters> parameters;

};

#endif // GLOBALDATA_H
