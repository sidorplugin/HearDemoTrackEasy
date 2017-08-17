#ifndef DEEJAYDEPAGESEARCHER_H
#define DEEJAYDEPAGESEARCHER_H

#include "baseclasses/pagesearcher.h"
#include "tabledates.h"

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QWebElement>

// Класс DeejayDePageSearcher находит по дате страницу на ресурсе deejay.de.
// Поиск основан на методе бинарного поиска. Для ускорения работы метода
// запрошенные страницы кэшируются (Таблица хранения дат, класс TableDates).
// Таблица существует на время работы программы (так как музыка постоянно
// пополняется и соответствие дат и страниц будет тоже меняться).

class DeejayDePageSearcher : public PageSearcher
{
public:

  // Указывает на положение искомой даты в предыдущем поиске.
  enum Directive { None,
                   DateIsLater,
                   DateIsEarlier };

  DeejayDePageSearcher();
  ~DeejayDePageSearcher();

  // Возвращает информацию о страницах.
  QList<int> getPagesInfo(const QVariantList &params);

protected slots:
  // Действие после загрузки страницы.
  // Считывает с загруженной страницы даты и сверяет с ними искомую.
  void result(bool ok);

private:
  // Возвращает номер страницы для date.
  int page(const QString& address, const QDate& date);
  // Возвращает true если searchDate находится в диапазоне firstDate и lastDate.
  // Переменная flag при возврате функцией false укажет ранней или поздней
  // приходится искомая дата для диапазона.
  bool isContains(const QDate& searchDate, const QString& firstDate,
                  const QString& lastDate, DeejayDePageSearcher::Directive& flag);
  // Устанавливает диапазон поиска в переменные start и end в зависимости от флагов
  // directiveFlag(указывает на положение искомой даты в предыдущем поиске) и
  // searchFlag(найдена ли верхняя граница поиска или нет).
  void setLimits(DeejayDePageSearcher::Directive directiveFlag,
                 bool isLimitFinded, int& start, int& end);

private:
  TableDates m_table;                 // Таблица хранения дат.
  DeejayDePageSearcher::Directive m_directiveFlag;
  bool m_isFinded;                    // Страница найдена.
  QDate m_searchDate;                 // Дата поиска.
  int m_start;                        // Начало отрезка поиска.
  int m_end;                          // Конец отрезка поиска.
  int m_current;                      // Текущий номер страницы.
  bool m_isLimitFinded;               // Найден верхний предел поиска?


};

#endif // DEEJAYDEPAGESEARCHER_H
