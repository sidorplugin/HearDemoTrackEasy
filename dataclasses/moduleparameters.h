#ifndef MODULEPARAMETERS_H
#define MODULEPARAMETERS_H

#include <QHash>
#include <QVariant>


class ModuleParametersPrivate;

class ModuleParameters
{
public:
  enum Key {
    Id,
    Name,
    Address,
    Icon,
    SearchGroups,
    Styles,
    Periods,
    Filters
  };

  ModuleParameters();
  ModuleParameters(const ModuleParameters& other);
  ModuleParameters& operator=(const ModuleParameters& other);
  ~ModuleParameters();

  // Устанавливает значение value по ключу key.
  void setData(int key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(int key);
  // Возвращает список параметров.
  QStringList toStringList() const;

private:
  QString nameKey(int key) const;

private:
  ModuleParametersPrivate* m_d;  
};

#endif // MODULEPARAMETERS_H
