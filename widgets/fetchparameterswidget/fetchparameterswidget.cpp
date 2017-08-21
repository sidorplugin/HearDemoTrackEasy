#include "fetchparameterswidget.h"

#include <QDate>
#include <QDebug>

FetchParametersWidget::FetchParametersWidget()
{
  m_model = new FetchParametersModel(this);
  m_delegate = new FetchParametersItemDelegate(this);

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

FetchParametersWidget::~FetchParametersWidget()
{
  delete m_model;
  delete m_delegate;
}


// Возвращает значение поля "Источник".
QString FetchParametersWidget::getSource() const
{
  return model()->index(FetchParametersModel::SourceItem, 0).
         data(Qt::DisplayRole).toString();
}


// Возвращает значение поля "Начало".
QDate FetchParametersWidget::getDateStart() const
{
  return QDate::fromString(model()->index(FetchParametersModel::StartDateItem, 0).
         data(Qt::DisplayRole).toString(), "dd.MM.yyyy");
}


// Возвращает значение поля "Конец".
QDate FetchParametersWidget::getDateEnd() const
{
  return QDate::fromString(model()->index(FetchParametersModel::EndDateItem, 0).
         data(Qt::DisplayRole).toString(), "dd.MM.yyyy");
}

// Возвращает значение поля "Жанр".
QString FetchParametersWidget::getGenre() const
{
  return model()->index(FetchParametersModel::GenreItem, 0).data().toString();
}


// Возвращает значение поля "Период".
QString FetchParametersWidget::getPeriod() const
{
  return model()->index(FetchParametersModel::PeriodItem, 0).data().toString();
}


// Возвращает значение поля "Фильтр".
QString FetchParametersWidget::getFilter() const
{
  return model()->index(FetchParametersModel::FilterItem, 0).data().toString();
}


// Действия при изменении данных в модели.
void FetchParametersWidget::on_itemChanged(QStandardItem *item)
{
    int row = item->row();
    int id = item->data(ROLE_CURRENT_INDEX).toInt();

    // В зависимости от номера строки производит скрытие или редактирование
    // других ячеек.
    switch (row) {
      case FetchParametersModel::SourceItem:  // Поле "Источник".
      {
        // Сбрасывает значения полей Жанр, Период, Фильтр.
          model()->setData(model()->index(FetchParametersModel::GenreItem, 0), "");
          model()->setData(model()->index(FetchParametersModel::PeriodItem, 0), "");
          model()->setData(model()->index(FetchParametersModel::FilterItem, 0), "");

        // В зависимости от выбранного "Источника" скрывает поля.
        switch (id) {
          case 0:
            setRowHidden(FetchParametersModel::StartDateItem, false);
            setRowHidden(FetchParametersModel::EndDateItem, false);
            setRowHidden(FetchParametersModel::PeriodItem, true);
            setRowHidden(FetchParametersModel::FilterItem, true);
            model()->setData(model()->index(FetchParametersModel::StartDateItem, 0),
                             QDate::currentDate().toString("dd.MM.yyyy"));
            model()->setData(model()->index(FetchParametersModel::EndDateItem, 0),
                             QDate::currentDate().toString("dd.MM.yyyy"));
          break;
          case 1:
            setRowHidden(FetchParametersModel::StartDateItem, true);
            setRowHidden(FetchParametersModel::EndDateItem, true);
            setRowHidden(FetchParametersModel::PeriodItem, false);
            setRowHidden(FetchParametersModel::FilterItem, false);
            model()->setData(model()->index(FetchParametersModel::StartDateItem, 0), "");
            model()->setData(model()->index(FetchParametersModel::EndDateItem, 0), "");
          break;
          case 2:
            setRowHidden(FetchParametersModel::StartDateItem, true);
            setRowHidden(FetchParametersModel::EndDateItem, true);
            setRowHidden(FetchParametersModel::PeriodItem, false);
            setRowHidden(FetchParametersModel::FilterItem, true);
            model()->setData(model()->index(FetchParametersModel::StartDateItem, 0), "");
            model()->setData(model()->index(FetchParametersModel::EndDateItem, 0), "");
          break;
        }
      }
      break;
    }
    model()->submit();
}


// Действия при выборе поля в таблице параметров.
void FetchParametersWidget::on_pressed(const QModelIndex &index)
{
  int row = index.row();
  // Запоминает значение индекса в поле "Источник".
  int indexSource = index.sibling(FetchParametersModel::SourceItem, 0).
                    data(ROLE_CURRENT_INDEX).toInt();

  // В зависимости от номера строки производит скрытие или редактирование
  // других ячеек.
  switch (row) {
    case FetchParametersModel::GenreItem:   // Поле "Жанр".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Период" и "Фильтр".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchParametersModel::PeriodItem, 0), "");
          model()->setData(model()->index(FetchParametersModel::FilterItem, 0), "");
      }
      // Если "Источник" JUNO, тогда очищает поле "Период".
      if (indexSource == 2) {
          model()->setData(model()->index(FetchParametersModel::PeriodItem, 0), "");
      }

    }
    break;

    case FetchParametersModel::PeriodItem:   // Поле "Период".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Жанр" и "Фильтр".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchParametersModel::GenreItem, 0), "");
          model()->setData(model()->index(FetchParametersModel::FilterItem, 0), "");
      }
    }
    break;

    case FetchParametersModel::FilterItem:   // Поле "Фильтр".
    {
      // Если "Источник" HARDWAX, тогда очищает поля "Жанр" и "Период".
      if (indexSource == 1) {
          model()->setData(model()->index(FetchParametersModel::GenreItem, 0), "");
          model()->setData(model()->index(FetchParametersModel::PeriodItem, 0), "");
      }
    }
    break;
  }
  model()->submit();
}
