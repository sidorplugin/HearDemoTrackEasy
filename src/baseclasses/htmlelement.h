#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <QVariantList>
#include <QString>
#include <QRegExp>
#include <QList>
#include <QPair>

struct Selector
{
  QString tagName;
  QString idName;
  QString className;
  bool noEndTag;
};


class HtmlElement
{
public:
  HtmlElement();
  HtmlElement(const QString& source, const QString& parent = QString());
  ~HtmlElement(){}

  void setSource(const QString& source, const QString& parent = QString());
  QString attribute(const QString& attr) const;
  QList<HtmlElement> findAll(const QString& selectorString) const;
  HtmlElement findFirst(const QString& selectorString) const;
  HtmlElement nextSibling() const;
  HtmlElement previousSibling() const;
  HtmlElement firstChild() const;
  QStringList classes() const;
  bool hasClass(const QString& className) const;
  QString toPlainText() const;
  bool isEmpty() const;
  QString toString() const;

private:
  Selector getSelector(const QString& selectorString) const;
  QPair<QString, int> getPreviousSiblingEndTag(const QString& str, int pos) const;
  int getPreviousSiblingBeginTag(const QString& str, const QPair<QString, int>& pair) const;
  int getCountEntry(const QRegExp& rx, const QString& str) const;
  QString getElement(const Selector& selector, int& offset, int& posBegin) const;
  int getPosition(const QRegExp& rx, const QString& str, int position, int count) const;

private:
  QString m_source;
  QString m_parent;
};

#endif // HTMLELEMENT_H
