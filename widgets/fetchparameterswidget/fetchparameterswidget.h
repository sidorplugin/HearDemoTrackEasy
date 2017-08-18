#ifndef FETCHPARAMETERSWIDGET_H
#define FETCHPARAMETERSWIDGET_H

#include "fetchparametersitemdelegate.h"
#include "fetchparametersmodel.h"

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>


// FetchParametersWidget - класс виджет реализующий таблицу параметров задаваемых при
// выборке, является оберткой QTableView с реализованной моделью и делегатом,
// также предоставляет доступ к полям таблицы.
class FetchParametersWidget : public QTableView
{
  Q_OBJECT
public:

  FetchParametersWidget();
  ~FetchParametersWidget();

  // Возвращает значение поля "Источник".
  QString getSource() const;
  // Возвращает значение поля "Начало".
  QDate getDateStart() const;
  // Возвращает значение поля "Конец".
  QDate getDateEnd() const;
  // Возвращает значение поля "Жанр".
  QString getGenre() const;
  // Возвращает значение поля "Период".
  QString getPeriod() const;
  // Возвращает значение поля "Фильтр".
  QString getFilter() const;

private slots:
  // Действия при изменении данных в модели.
  void on_itemChanged(QStandardItem* item);
  // Действия при выборе поля в таблице параметров.
  void on_pressed(const QModelIndex& index);

private:
  FetchParametersModel* m_model;              // Модель.
  FetchParametersItemDelegate* m_delegate;    // Делегат.

};

#endif // FETCHPARAMETERSWIDGET_H
