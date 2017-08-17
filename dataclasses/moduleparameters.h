#ifndef MODULEPARAMETERS_H
#define MODULEPARAMETERS_H

#include <QHash>
#include <QVariant>


const QString ID = "Id";
const QString NAME = "Name";
const QString ADDRESS = "Address";
const QString ICON = "Icon";
const QString GENRES = "Genres";
const QString PERIODS = "Periods";
const QString FILTERS = "Filters";
const int VALUE = 0;
const int LINK = 1;

class ModuleParametersPrivate;

class ModuleParameters
{
public:
  ModuleParameters();
  ModuleParameters(const ModuleParameters& other);
  ModuleParameters& operator=(const ModuleParameters& other);
  ~ModuleParameters();

  // Устанавливает/Возвращает параметры модуля.
  void setId(int id);
  int id() const;

  void setName(const QString& name);
  QString name() const;

  void setAddress(const QString& address);
  QString address() const;

  void setIcon(const QString& icon);
  QString icon() const;

  void setGenre(const QString& genre, const QString& value, const QString& link);
  QStringList genreInfo(const QString& genre) const;
  QStringList genres() const;

  void setPeriod(const QString& period, const QString& value, const QString& link);
  QStringList periodInfo(const QString& period) const;
  QStringList periods() const;

  void setFilter(const QString& filter, const QString& value, const QString& link);
  QStringList filterInfo(const QString& filter) const;
  QStringList filters() const;

  // Возвращает список параметров.
  QStringList toStringList() const;

private:
  ModuleParametersPrivate* m_d;
};

#endif // MODULEPARAMETERS_H
