#include "moduleparameters.h"

#include <QDebug>

class ModuleParametersPrivate
{
public:
  QHash <QString, QVariant> parameters;
  QHash <QString, QVariant> genres;
  QHash <QString, QVariant> periods;
  QHash <QString, QVariant> filters;
};


ModuleParameters::ModuleParameters()
                   :m_d(new ModuleParametersPrivate)
{
}


ModuleParameters::ModuleParameters(const ModuleParameters& other)
                 :m_d(new ModuleParametersPrivate)
{
  *this = other;
}


ModuleParameters::~ModuleParameters()
{
  delete m_d;
}


ModuleParameters& ModuleParameters::operator=(const ModuleParameters& other)
{
  *m_d = *other.m_d;
   return *this;
}


void ModuleParameters::setId(int id)
{
  m_d->parameters.insert(ID, id);
}


int ModuleParameters::id() const
{
  return m_d->parameters.value(ID).toInt();
}


void ModuleParameters::setName(const QString &name)
{
  m_d->parameters.insert(NAME, name);
}


QString ModuleParameters::name() const
{
  return m_d->parameters.value(NAME).toString();
}


void ModuleParameters::setAddress(const QString &address)
{
  m_d->parameters.insert(ADDRESS, address);
}


QString ModuleParameters::address() const
{
  return m_d->parameters.value(ADDRESS).toString();
}


void ModuleParameters::setIcon(const QString &icon)
{
  m_d->parameters.insert(ICON, icon);
}


QString ModuleParameters::icon() const
{
  return m_d->parameters.value(ICON).toString();
}


void ModuleParameters::setGenre(const QString& genre, const QString& value,
                                const QString &link)
{
  QStringList info;
  info << value << link;
  m_d->genres.insert(genre, info);
}


QStringList ModuleParameters::genreInfo(const QString &genre) const
{
  return m_d->genres.value(genre).toStringList();
}


QStringList ModuleParameters::genres() const
{
  return m_d->genres.keys();
}


void ModuleParameters::setPeriod(const QString &period, const QString& value,
                                 const QString &link)
{
  QStringList info;
  info << value << link;
  m_d->periods.insert(period, info);
}


QStringList ModuleParameters::periodInfo(const QString &period) const
{
  return m_d->periods.value(period).toStringList();
}


QStringList ModuleParameters::periods() const
{
   return m_d->periods.keys();
}


void ModuleParameters::setFilter(const QString &filter, const QString& value,
                                 const QString &link)
{
  QStringList info;
  info << value << link;
  m_d->filters.insert(filter, info);
}


QStringList ModuleParameters::filterInfo(const QString &filter) const
{
  return m_d->filters.value(filter).toStringList();
}


QStringList ModuleParameters::filters() const
{
  return m_d->filters.keys();
}


// Возвращает список параметров.
QStringList ModuleParameters::toStringList() const
{
  QStringList result;
  result.push_back(QString::number(id()));
  result.push_back(name());
  result.push_back(address());
  result.push_back(icon());

  QHashIterator <QString, QVariant> g(m_d->genres);
  while (g.hasNext()) {
    g.next();
    result.append(g.key());
    result.append(g.value().toStringList());
  }

  QHashIterator <QString, QVariant> p(m_d->periods);
  while (p.hasNext()) {
    p.next();
    result.append(p.key());
    result.append(p.value().toStringList());
  }

  QHashIterator <QString, QVariant> f(m_d->filters);
  while (f.hasNext()) {
    f.next();
    result.append(f.key());
    result.append(f.value().toStringList());
  }

  return result;
}
