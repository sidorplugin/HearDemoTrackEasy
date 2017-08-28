#ifndef IDTAGCREATOR_H
#define IDTAGCREATOR_H

#include <QObject>
#include <QDebug>

// TODO Hash хранение.

class IdTagCreator
{
public:
  enum Version {
    DeejayDe,
    Hardwax
  };

  enum Key {
    Header,
    Title,
    Artist,
    Album,
    Year,
    Comment,
    Style,
    Ver
  };

  IdTagCreator(){}

  // Устанавливает значение value по ключу key.
  void setData(IdTagCreator::Key key, const QVariant& value);
  // Возвращает значение по ключу key.
  QVariant data(IdTagCreator::Key key);

  // Возвращает код стиля.
  int codeStyle(const QString& style);

public:
  // Возвращает блок тэга.
  QByteArray tag() const;

private:
  QHash <IdTagCreator::Key, QVariant> m_data;

};

#endif // IDTAGCREATOR_H
