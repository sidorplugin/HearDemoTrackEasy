#include "fetchwidget.h"

#include <QDate>
#include <QDebug>

FetchWidget::FetchWidget()
{
  m_model = new FetchModel(this);
  m_delegate = new FetchItemDelegate(this);

  // Настраивает таблицу.
  setModel(m_model);
  setItemDelegateForColumn(0, m_delegate);
  verticalHeader()->setDefaultSectionSize(21);
  horizontalHeader()->setStretchLastSection(true);
  setEditTriggers(QAbstractItemView::AllEditTriggers);
  setAlternatingRowColors(true);
  setRowHidden(4, true);
  setRowHidden(5, true);

  setCornerButtonEnabled(false);

  // Действия при изменении данных в поле таблицы параметров.
  connect(m_model, SIGNAL(itemChanged(QStandardItem*)),
          this, SLOT(on_itemChanged(QStandardItem*)));

  // Действия при выборе поля в таблице параметров.
  connect(this, SIGNAL(pressed(QModelIndex)),
          this, SLOT(on_pressed(QModelIndex)));

}

FetchWidget::~FetchWidget()
{
  delete m_model;
  delete m_delegate;
}


// Возвращает значение по ключу key.
QVariant FetchWidget::data(int key)
{
  QVariant result;
  switch (key) {
    case FetchWidget::Source :
      result = model()->index(FetchModel::SourceItem, 0).
               data(Qt::DisplayRole).toString();
    break;
    case FetchWidget::DateStart :
      result = QDate::fromString(model()->index(FetchModel::StartDateItem, 0).
                                data(Qt::DisplayRole).toString(), "dd.MM.yyyy");
    break;
    case FetchWidget::DateEnd :
      result = QDate::fromString(model()->index(FetchModel::EndDateItem, 0).
                               data(Qt::DisplayRole).toString(), "dd.MM.yyyy");
    break;
    case FetchWidget::Style :
      result = model()->index(FetchModel::StyleItem, 0).data().toString();
    break;
    case FetchWidget::Period :
      result = model()->index(FetchModel::PeriodItem, 0).data().toString();
    break;
    case FetchWidget::Filter :
      result = model()->index(FetchModel::FilterItem, 0).data().toString();
    break;
  }

  return result;
}


// Действия при изменении данных в модели.
void FetchWidget::on_itemChanged(QStandardItem *item)
{
    int row = item->row();
    int id = item->data(FetchModel::CurrentIndexRole).toInt();

    // В зависимости от номера строки производит скрытие или редактирование
    // других ячеек.
    switch (row) {
      case FetchModel::SourceItem:  // Поле "Источник".
      {
        // Сбрасывает значения полей Жанр, Период, Фильтр.
          model()->setData(model()->index(FetchModel::StyleItem, 0), "");
          model()->setData(model()->index(FetchModel::PeriodItem, 0), "");
          model()->setData(model()->index(FetchModel::FilterItem, 0), "");

        // В зависимости от выбранного "Источника" скрывает поля.
        switch (id) {
          case 0:
            setRowHidden(FetchModel::StartDateItem, false);
            setRowHidden(FetchModel::EndDateItem, false);
            setRowHidden(FetchModel::PeriodItem, true);
            setRowHidden(FetchModel::FilterItem, true);
            model()->setData(model()->index(FetchModel::StartDateItem, 0),
                             QDate::currentDate().toString("dd.MM.yyyy"));
            model()->setData(model()->index(FetchModel::EndDateItem, 0),
                             QDate::currentDate().toString("dd.MM.yyyy"));
          break;
          case 1:
            setRowHidden(FetchModel::StartDateItem, true);
            setRowHidden(FetchModel::EndDateItem, true);
            setRowHidden(FetchModel::PeriodItem, false);
            setRowHidden(FetchModel::FilterItem, false);
            model()->setData(model()->index(FetchModel::StartDateItem, 0), "");
            model()->setData(model()->index(FetchModel::EndDateItem, 0), "");
          break;
          case 2:
            setRowHidden(FetchModel::StartDateItem, true);
            setRowHidden(FetchModel::EndDateItem, true);
            setRowHidden(FetchModel::PeriodItem, false);
            setRowHidden(FetchModel::FilterItem, true);
            model()->setData(model()->index(FetchModel::StartDateItem, 0), "");
            model()->setData(model()->index(FetchModel::EndDateItem, 0), "");
          break;
        }
      }
      break;
    }
    model()->submit();
}


// Действия при выборе поля в таблице параметров.
void FetchWidget::on_pressed(const QModelIndex &index)
{
  int row = index.row();
  // Запоминает значение индекса в поле "Источник".
  int indexSource = index.sibling(FetchModel::SourceItem, 0).
                    data(FetchModel::CurrentIndexRole).toInt();

  // В зависимости от номера строки производит скрытие или редактирование
  // других ячеек.
  switch (row) {
    case FetchModel::StyleItem:   // Поле "Жанр".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Период" и "Фильтр".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchModel::PeriodItem, 0), "");
          model()->setData(model()->index(FetchModel::FilterItem, 0), "");
      }
      // Если "Источник" JUNO, тогда очищает поле "Период".
      if (indexSource == 2) {
          model()->setData(model()->index(FetchModel::PeriodItem, 0), "");
      }

    }
    break;

    case FetchModel::PeriodItem:   // Поле "Период".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Жанр" и "Фильтр".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchModel::StyleItem, 0), "");
          model()->setData(model()->index(FetchModel::FilterItem, 0), "");
      }
    }
    break;

    case FetchModel::FilterItem:   // Поле "Фильтр".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Жанр" и "Период".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchModel::StyleItem, 0), "");
          model()->setData(model()->index(FetchModel::PeriodItem, 0), "");
      }
    }
    break;
  }
  model()->submit();
}
