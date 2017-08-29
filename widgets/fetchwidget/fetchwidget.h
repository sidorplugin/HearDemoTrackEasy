#ifndef FETCHWIDGET_H
#define FETCHWIDGET_H

#include "fetchitemdelegate.h"
#include "fetchmodel.h"

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>


// FetchWidget - класс виджет реализующий таблицу параметров задаваемых при
// выборке, является оберткой QTableView с реализованной моделью и делегатом,
// также предоставляет доступ к полям таблицы.
class FetchWidget : public QTableView
{
  Q_OBJECT
public:
  enum Key {
    Source,
    DateStart,
    DateEnd,
    Style,
    Period,
    Filter
  };


  FetchWidget();
  ~FetchWidget();

  // Возвращает значение по ключу key.
  QVariant data(int key);

private slots:
  // Действия при изменении данных в модели.
  void on_itemChanged(QStandardItem* item);
  // Действия при выборе поля в таблице параметров.
  void on_pressed(const QModelIndex& index);

private:
  FetchModel* m_model;              // Модель.
  FetchItemDelegate* m_delegate;    // Делегат.

};

#endif // FETCHWIDGET_H
