#include "htmlelement.h"

#include <QRegExp>
#include <QDebug>


HtmlElement::HtmlElement()
{
}

HtmlElement::HtmlElement(const QString& source, const QString& parent)
{
  m_source = source;
  m_parent = parent;
}

void HtmlElement::setSource(const QString &source, const QString& parent)
{
  m_source = source;
  m_parent = parent;
}


QString HtmlElement::attribute(const QString &attr) const
{
  QRegExp rx1, rx2;
  rx1.setPattern(QString("%1=\"").arg(attr));
  rx2.setPattern(QString("\""));
  int pos = rx1.indexIn(m_source);
  pos += rx1.matchedLength();
  int pos2 = rx2.indexIn(m_source, pos);
  return m_source.mid(pos, pos2 - pos);
}


// TODO c вложенными тегами. Общая функция нахождения блока. FindNext(selector, element);
QList<HtmlElement> HtmlElement::findAll(const QString &selectorString) const
{
  QList <HtmlElement> result;

  if (selectorString.isEmpty()) return result;

  Selector selector = getSelector(selectorString);

  int offset = 0;
  int posBegin = 0;
  QString element;
  while (true) {
      element = getElement(selector, offset, posBegin);
      if (!element.isEmpty())
          result.append(HtmlElement(element, m_source));
      else
          break;
  }
  return result;
}


HtmlElement HtmlElement::findFirst(const QString &selectorString) const
{
  HtmlElement result;

  if (selectorString.isEmpty()) return result;

  Selector selector = getSelector(selectorString);

  int offset = 0;
  int posBegin = 0;
  QString element = getElement(selector, offset, posBegin);
  if (!element.isEmpty())
    result.setSource(element, m_source);

  return result;
}


HtmlElement HtmlElement::nextSibling() const
{
  HtmlElement result;

  if (m_parent.isEmpty()) return result;

  int pos = m_parent.indexOf(m_source);

  if (pos == -1) return result;

  QRegExp rx1("<(\\w+)");
  QRegExp rx2;
  pos += m_source.size();
  if (rx1.indexIn(m_parent, pos) != -1) {
      QString tag = rx1.cap();
      tag.remove("<");
      rx2.setPattern(QString("</%1>").arg(tag));
      int pos2 = rx2.indexIn(m_parent, pos);
      pos2 += rx2.matchedLength();
      QString element = m_parent.mid(pos, pos2 - pos);
      result.setSource(element, m_parent);
    }
  return result;
}


HtmlElement HtmlElement::previousSibling() const
{
  HtmlElement result;

  if (!m_parent.isEmpty()) return result;

  int posEnd = m_parent.indexOf(m_source);

  if (posEnd == -1) return result;

//  int pos = QRegExp("/>").lastIndexIn(m_parent, posEnd);
//  int pos = QRegExp("</(\\w+)>").lastIndexIn(m_parent, posEnd);


  QPair<QString, int> pair = getPreviousSiblingEndTag(m_parent, posEnd);
  int posBegin = getPreviousSiblingBeginTag(m_parent, pair);
  result.setSource(m_parent.mid(posBegin, posEnd - posBegin));
  return result;
}


HtmlElement HtmlElement::firstChild() const
{
  HtmlElement result;

  QRegExp rx1("<(\\w+)");
  int pos = 0;
  if ((pos = rx1.indexIn(m_source, pos + 2)) != -1) {
      QString tag = rx1.cap().remove("<");
      result = findFirst(QString("%1").arg(tag));
  }
  return result;
}



QStringList HtmlElement::classes() const
{
  QStringList result;
  QRegExp rx1("class=\"");
  QRegExp rx2("\"");
  int pos = 0;
  while ((pos = rx1.indexIn(m_source, pos)) != -1) {
      pos += rx1.matchedLength();
      int pos2 = rx2.indexIn(m_source, pos);
      result.append(m_source.mid(pos, pos2 - pos));
  }
  return result;
}


bool HtmlElement::hasClass(const QString& className) const
{
  HtmlElement thisElement(m_source);
  return !thisElement.findFirst(QString(".%1").arg(className)).isEmpty();
}


QString HtmlElement::toPlainText() const
{
  QStringList result;
  QRegExp rx1(">");
  QRegExp rx2("<");
  QRegExp rxClear("^((\\n)|(\\s+))|(&nbsp;)|(\\s{2,})|((\\n)|(\\s+))$");

  int pos = 0;
  while ((pos = rx1.indexIn(m_source, pos)) != -1 ) {
      pos += rx1.matchedLength();
      int pos2 = rx2.indexIn(m_source, pos);
      QString value = m_source.mid(pos, pos2 - pos);
      value.remove(rxClear).replace("&mdash;", " - ").replace("&ndash;", " - ");
      if (!value.isEmpty()) result.push_back(value);
  }

  return result.join(" ");
}


bool HtmlElement::isEmpty() const
{
  return m_source.isEmpty();
}


QString HtmlElement::toString() const
{
  return m_source;
}


Selector HtmlElement::getSelector(const QString &selectorString) const
{
  Selector result;
  result.noEndTag = false;
  QStringList list;

  // getClass.
  list = selectorString.split(".");
  if (list.size() == 2) result.className = list.at(1);
  if (selectorString.contains(".") && list.size() == 1)
    result.className = selectorString;

  // getTag.
  QRegExp rx("[.#]");
  list = selectorString.split(rx);
  if (list.size() == 2)
    result.tagName = list.at(0);
  if (list.size() == 1)
    result.tagName = selectorString;

  // getId.
  list = selectorString.split("#");
  if (list.size() == 2)
    result.idName = list.at(1);
  if (selectorString.contains("#") && list.size() == 1)
    result.idName = selectorString;

  // endTag.
  if (result.tagName == "img" || result.tagName == "link")
    result.noEndTag = true;

  return result;
}


QPair<QString, int> HtmlElement::getPreviousSiblingEndTag(const QString& str, int pos) const
{
  QPair<QString, int> result;
  QString resultString;
  bool isReading;
  QChar symbol;
  int position = pos;
  while (true) {
      position--;
      symbol = str.at(position);
      if (symbol == '>') {
          isReading = true;
          continue;
      }
      if (symbol == '<') {
          result.first = resultString.remove("/");
          result.second = position;
          break;
      }
      if (isReading) resultString.prepend(symbol);
  }
  return result;
}


int HtmlElement::getPreviousSiblingBeginTag(const QString& str, const QPair<QString, int>& pair) const
{
  int result;
  QString bufferString;
  QString tag = pair.first;
  int tagSize = tag.size();
  QChar lastSymbol = tag.at(tagSize - 1);
  int pos = pair.second;
  bool findSymbol = false;
  while (true) {
      pos--;
      QChar symbol = str.at(pos);
      // Если найден символ равный последнему символу тега.
      if (symbol == lastSymbol) findSymbol = true;
      if (findSymbol) {
          // Проверяет равна ли длинна буфера и длинна тега.
          if (bufferString.size() == (tagSize + 1)) {
              // Если Да - результат найден.
              if (bufferString == QString("<%1").arg(tag)) {
                  result = pos;
                  break;
              }
              // Иначе очищает буфер и устанавливает флаг нахождения символа в false.
              bufferString.clear();
              findSymbol = false;
              continue;
          }
          // Если длинна буфера и длинна тега не равна - добавляет в конец буфера текущий символ.
          bufferString.prepend(symbol);
      }
  }
  return result;
}


int HtmlElement::getCountEntry(const QRegExp& rx, const QString& str) const
{
    int result = 0;
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        pos += rx.matchedLength();
        result++;
    }
    return result;
}


QString HtmlElement::getElement(const Selector& selector, int& offset, int& posBegin) const
{
  QString result;

  QRegExp rx1, rx2;
  bool needSearchTag = false;
  // "tag"
  if (selector.className.isEmpty() && selector.idName.isEmpty() && !selector.tagName.isEmpty()) {
      rx1.setPattern(QString("<%1[ >]").arg(selector.tagName));
      if (selector.noEndTag)
        rx2.setPattern("/>");
      else
        rx2.setPattern(QString("</%1>").arg(selector.tagName));
  }
  // ".class" or "tag.class"
  if (!selector.className.isEmpty() && selector.idName.isEmpty()) {
    needSearchTag = true;
    rx1.setPattern(QString("class=\"%1\"").arg(selector.className));
    if (!selector.tagName.isEmpty())
      rx2.setPattern(QString("</%1>").arg(selector.tagName));
    else
      rx2.setPattern(QString("</(\\w+)>"));
  }
  // "#id" or "tag#id"
  if (selector.className.isEmpty() && !selector.idName.isEmpty()) {
    needSearchTag = true;
    rx1.setPattern(QString("id=\"%1\"").arg(selector.idName));
    if (!selector.tagName.isEmpty())
      rx2.setPattern(QString("</%1>").arg(selector.tagName));
    else
      rx2.setPattern(QString("</(\\w+)>"));
  }

  rx1.setMinimal(true);
  rx2.setMinimal(true);

  if (rx1.isEmpty() || rx2.isEmpty()) return result;

  int countEntry;
  if ((offset = rx1.indexIn(m_source, offset)) != -1) {
      if (needSearchTag) {
          if (!selector.tagName.isEmpty())
            posBegin = m_source.lastIndexOf("<" + selector.tagName, offset);
          else {
            rx1.setPattern(QString("<(\\w+)[ >]"));
            posBegin = rx1.lastIndexIn(m_source, offset);
            // Находит значение tag.
            QString tag = rx1.cap().remove("<").trimmed();
            rx1.setPattern(QString("<%1").arg(tag));
            rx2.setPattern(QString("</%1>").arg(tag));
          }
      }
      else
        posBegin = offset;

      offset += rx1.matchedLength();

      int posEnd = rx2.indexIn(m_source, offset);
      posEnd += rx2.matchedLength();
      QString firstBlock = m_source.mid(posBegin, posEnd - posBegin);

      // Если в первом блоке не содержится еще одного такого же тега, результат найден.
      countEntry = getCountEntry(rx1, firstBlock);
      if (countEntry == 1) {
        result = firstBlock;
        return result;
      }
      // Если в первом блоке есть такой же тег, начинает поиск истинного конца тега.
      else {
          QString element = m_source.mid(offset, posEnd - offset);
          offset = 0;
          while (true) {
            countEntry = getCountEntry(rx1, element);
            if (countEntry == 0) {
                element = m_source.mid(posBegin, posEnd - posBegin);
                result = element;
                break;
            }
            else {
                offset = posEnd;
                posEnd = getPosition(rx2, m_source, offset, countEntry);
                if (posEnd != -1)
                  element = m_source.mid(offset, posEnd - offset);
            }
          }
      }
  }
  return result;
}


int HtmlElement::getPosition(const QRegExp& rx, const QString& str, int position, int count) const
{
    int result = -1;
    int entry = count;
    int pos = position;
    while (((pos = rx.indexIn(str, pos)) != -1) && (entry != 0)) {
        pos += rx.matchedLength();
        result = pos;
        entry--;
    }
    return result;
}
