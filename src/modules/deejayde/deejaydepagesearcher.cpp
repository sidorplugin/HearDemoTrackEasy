#include "deejaydepagesearcher.h"

// Возвращает информацию о страницах.
QList<int> DeejayDePageSearcher::getPagesInfo(const QVariantList &params)
{
  QList<int> result;

  m_table.clear();
  m_isStop = false;

  if (params.size() != 3) return result;

  QString link = params.at(0).toString();
  QDate dateStart = params.at(1).toDate();
  QDate dateEnd = params.at(2).toDate();

  // Находит стартовую страницу.
  int startPage = page(link, dateEnd);
  qDebug() << "startPage = " << startPage;
  if (startPage == -1)
    return QList<int>();

  // Находит конечную страницу.
  int endPage = page(link, dateStart);
  qDebug() << "endPage = " << endPage;
  if (endPage == -1)
    return QList<int>();

  // Вычисляет общее колличество страниц.
  int totalPages = endPage - startPage + 1;

  // Возвращает список.
  result << startPage << endPage << totalPages;

  return result;
}



// Возвращает номер страницы для date.
int DeejayDePageSearcher::page(const QString& address, const QDate& date)
{
  qDebug() << "page(" << date << ")";

  // Если искомая дата сегодня, возвращает 1-ую страницу.
  if (date == QDate::currentDate())
      return 1;

  // Проверяет дату на наличие в таблице.  Если найдена, выходит из функции с
  // значением из таблицы.
  if (int p = m_table.getPage(date) != -1) {
      qDebug() << "find date in table, page = ", p;
      return p;
  }

  // Иначе продолжается поиск.
  // Подготавливает переменные к работе.
  m_isFinded = false;
  m_start = 1;
  m_isLimitFinded = false;

  m_searchDate = date;
  m_end = ANCHOR;
  m_current = m_end;

  // Пока не найдется искомая страница запрашивает страницы с вновь определенным
  // m_current.

  // TODO Выход по отмене из этого цикла.
  while (!m_isFinded && m_current != 1) {
    qDebug() << "searching...";

    if (m_isStop) {
      qDebug() << "stopped...return -1 DeejayDePageSearcher::page()";
      break;
      return -1;
    }

    // Проверяет страницу на наличие в таблице дат для случая если страница
    // уже была запрошена ранее.
    // Получает список дат для запрошеной страницы.
    QList <QDate> list = m_table.getDates(m_current);
    // Если дата есть в списке сверяет искомую дату с значениями в таблице.
    if (!list.isEmpty()) {
        qDebug() << "page has in table";
        // Берет последнюю дату в списке.
        QDate lastDate = list.last();
        // Если искомая дата раньше чем последняя в списке, задает начало
        // диапазону поиска равным m_current.
        if ( date < lastDate) {
            m_start = m_current;
        }
        // Если искомая дата позже чем последняя в списке, задает конец
        // диапазону поиска равным m_current.
        if ( date > lastDate) {
            m_end = m_current;
        }
        // Вычисляет m_current для следующего запроса.
        m_current = (m_start + m_end) / 2;
        qDebug() << "m_current = " << m_current;
    }
    // Иначе если даты нет в списке производит запрос в сеть.
    else {
        if (m_isStop) {
          qDebug() << "stopped...return -1 DeejayDePageSearcher::page()";
          break;
          return -1;
        }

        load(address.arg(QString::number(m_current)));

        // Остается в цикле пока не произведется выборка.
        QEventLoop wait;
        connect(this, SIGNAL(finished()), &wait, SLOT(quit()));
        wait.exec();
    }
  }
  return m_current;
}


// Устанавливает диапазон поиска в переменные start и end в зависимости от флагов
// directiveFlag(указывает на положение искомой даты в предыдущем поиске) и
// searchFlag(найдена ли верхняя граница поиска или нет).
void DeejayDePageSearcher::setLimits(DeejayDePageSearcher::Directive directiveFlag,
                  bool isLimitFinded, int& start, int& end)
{
  qDebug() << "setLimits()";

  // Если верхний предел поиска найден определяет границы.
  if (isLimitFinded) {
      qDebug() << "LimitFinded";
      if (directiveFlag == DeejayDePageSearcher::DateIsLater) {
        qDebug() << "DateIsLater";
        end = m_current;
      }
      if (directiveFlag == DeejayDePageSearcher::DateIsEarlier) {
        qDebug() << "DateIsEarlier";
        start = m_current;
      }
    }
    // Иначе если верхний предел поиска не найден определяет границы.
    else {
      qDebug() << "Limit not Finded";
      if (directiveFlag == DeejayDePageSearcher::DateIsLater) {
        qDebug() << "DateIsLater";
        m_isLimitFinded = true;
        end = m_current;
      }
      if (directiveFlag == DeejayDePageSearcher::DateIsEarlier) {
        qDebug() << "DateIsEarlier";
        start = m_current;
        end = m_current * 2;
      }
    }
}


// Возвращает true если searchDate находится в диапазоне firstDate и lastDate.
// Переменная flag при возврате функцией false укажет ранней или поздней
// приходится искомая дата для диапазона.
bool DeejayDePageSearcher::isContains(const QDate& searchDate,
                                     const QString &firstDate,
                                     const QString &lastDate,
                                     DeejayDePageSearcher::Directive& flag)
{
    // Если дата находится в диапазоне.
    if ( (searchDate <= QDate::fromString(firstDate, "dd.MM.yyyy")) &&
         (searchDate >= QDate::fromString(lastDate, "dd.MM.yyyy")) ) {
        return true;
    }
    // Если искомая дата более поздняя чем на странице.
    else if (searchDate > QDate::fromString(firstDate, "dd.MM.yyyy") ) {
      flag = DeejayDePageSearcher::DateIsLater;
      return false;
    }
    // Если искомая дата более ранняя чем на странице.
    else if (searchDate < QDate::fromString(lastDate, "dd.MM.yyyy") ) {
      flag = DeejayDePageSearcher::DateIsEarlier;
      return false;
    }
}


void DeejayDePageSearcher::fetch(QNetworkReply* reply)
{
  qDebug() << "DeejayDePageSearcher::fetch()" << m_searchDate;

  QString html = reply->readAll();
  HtmlElement root(html);

  if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "error reply" << reply->errorString();
      return;
  }

  if (!root.hasClass("news")) {
      m_current = m_current / 2;
      return;
  }

  QList<HtmlElement> dateCollection = root.findAll("h2.news");
  // Берет первую и последнюю даты коллекции.
  QRegExp rxDate("(\\d{2}).(\\d{2}).(\\d{4})");
  rxDate.indexIn(dateCollection.first().toPlainText());
  QString firstDate = rxDate.cap();
  rxDate.indexIn(dateCollection.last().toPlainText());
  QString lastDate = rxDate.cap();

  // Записывает даты в таблицу хранения дат.
  m_table.insertDate(m_current, QDate().fromString(firstDate, "dd.MM.yyyy"));
  m_table.insertDate(m_current, QDate().fromString(lastDate, "dd.MM.yyyy"));

  // Проверяет положение m_searchDate относительно дат на загруженной странице.
  bool contains = isContains(m_searchDate, firstDate, lastDate, m_directiveFlag);
  qDebug() << "m_directiveFlag = " << m_directiveFlag;
  // В случае если искомая дата находится на этой странице, выставляет флаг
  // окончания и испускает сигнал о завершении.
  if (contains) {
    qDebug() << "finded";
    m_isFinded = true;
    emit finished();
    return;
  }

  // Если искомая дата не на этой странице, устанавливает новый диапазон для
  // поиска.
  setLimits(m_directiveFlag, m_isLimitFinded, m_start, m_end);
  // Рассчитывает номер страницы для дальнейшего поиска.
  m_current = (m_start + m_end) / 2;

  qDebug() << m_start << m_current << m_end;

  reply->deleteLater();
  // Сигнал о завершении. Выход из метода и дальнейший поиск с новым m_current.
  emit finished();
}


