#include "moduleparameters.h"

#include <QDebug>

class ModuleParametersPrivate
{
public:
  QMap <int, QVariant> data;
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


// Устанавливает значение value по ключу key.
void ModuleParameters::setData(int key, const QVariant &value)
{
  m_d->data.insert(key, value);
}


// Возвращает значение по ключу key.
QVariant ModuleParameters::data(int key)
{
  return m_d->data.value(key);
}


ModuleParameters& ModuleParameters::operator=(const ModuleParameters& other)
{
  *m_d = *other.m_d;
   return *this;
}


// Возвращает список параметров.
QStringList ModuleParameters::toStringList() const
{
  QStringList result;

  QMapIterator<int, QVariant> i(m_d->data);
  while (i.hasNext()) {
      i.next();
      QVariant variant = i.value();
      if (variant.canConvert<QVariantHash>()) {
          QMapIterator<QString, QVariant> j(variant.toMap());
          while (j.hasNext()) {
              j.next();
              QStringList list = j.value().toStringList();
              result.push_back(j.key() + " : " + list.at(0) + " : " + list.at(1));
          }
      }
      else
        result.push_back(nameKey(i.key()) + " : " + variant.toString());
  }

  return result;
}


QString ModuleParameters::nameKey(int key) const
{
  QString name;
  switch (key) {
      case ModuleParameters::Id :             name = "Id";               break;
      case ModuleParameters::Name :           name = "Name";             break;
      case ModuleParameters::Address :        name = "Address";          break;
      case ModuleParameters::Icon :           name = "Icon";             break;
      case ModuleParameters::SearchGroups :   name = "SearchGroups";     break;
      case ModuleParameters::Styles :         name = "Styles";           break;
      case ModuleParameters::Periods :        name = "Periods";          break;
      case ModuleParameters::Filters :        name = "Filters";          break;
  }
  return name;
}
