#include "fetchitemdelegate.h"
#include "fetchmodel.h"
#include "mainwindow.h"

#include <QComboBox>
#include <QDateEdit>

FetchItemDelegate::FetchItemDelegate(QObject *parent)
                      : QStyledItemDelegate(parent)
{
}


// Создает виджет для редактирования ячейки.
QWidget *FetchItemDelegate::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
  // Определяет номер строки выделенного поля.
  int row = index.row();

  // В данном классе делегате используются 2 вида виджетов. QComboBox и QDateEdit.
  // В зависимости от выделенного поля создает определенный делегат-виджет.
  switch (row) {
    case FetchModel::SourceItem:
    case FetchModel::StyleItem:
    case FetchModel::PeriodItem:
    case FetchModel::FilterItem:
    {
      // Создает виджет QComboBox.
      QComboBox *comboBox = new QComboBox(parent);
      comboBox->setFrame(false);
      return comboBox;
    }
    break;

    case FetchModel::StartDateItem:
    case FetchModel::EndDateItem:
    {
      // Создает виджет QDateEdit. Устанавливает меню при редактировании
      // в виде календаря.
      QDateEdit *dateEdit = new QDateEdit(parent);
      dateEdit->setCalendarPopup(true);
      dateEdit->setFrame(false);
      return dateEdit;
    }
    break;
  }
}



// Устанавливает данные в виджет из модели по индексу.
void FetchItemDelegate::setEditorData(QWidget *editor,
                                          const QModelIndex &index) const
{
  // Определяет индекс значения поля "Источник" и номер строки выделенного поля.
  QString source = index.sibling(FetchModel::SourceItem, 0).
                   data(Qt::DisplayRole).toString();
  int row = index.row();

  // В зависимости от выделенного поля устанавливает данные из модели которые
  // соответствуют определенным критериям.
  switch (row) {
    case FetchModel::SourceItem: // Поле "Источник".
      {
        // Получает виджет QComboBox из editor.
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        // Считывает таблицу "Имя - Иконка" из модели.
        QMap <QString, QVariant> data = index.data(ROLE_SOURCE_DATA).toMap();

        // Устанавливает данные из таблицы в виджет.
        QMapIterator <QString, QVariant> i(data);
        while (i.hasNext()) {
            i.next();
            int id = i.key().toInt();
            QStringList info = i.value().toStringList();
            QString name = info.at(0);
            QString icon = info.at(1);
            comboBox->addItem(QIcon(icon), name, id);
        }
        // Устанавливает текущее значение.
        comboBox->setCurrentIndex(index.data(ROLE_CURRENT_INDEX).toInt());

        // Если данные в виджете изменились, вносит изменения в модель
        // и закрывает виджет.
        connect(comboBox, SIGNAL(currentIndexChanged(int)),
                    this, SLOT(closeAndCommitEditor()));

      }
    break;
    case FetchModel::StyleItem:  // Поле "Жанр".
    case FetchModel::PeriodItem: // Поле "Период".
    case FetchModel::FilterItem: // Поле "Фильтр".
    {
        // Получает виджет QComboBox из editor.
        QComboBox *comboBox = static_cast<QComboBox*>(editor);

        // В зависимости от значения в поле "Источник" устанавливает
        // определенный список.
        QStringList list;
        list = index.data(ROLE_LIST).toMap().value(source).toStringList();
        // Добавляет список в ComboBox и устанавливает текущее значение.
        comboBox->addItems(list);
        comboBox->setCurrentIndex(0);

        // Если данные в виджете изменились, вносит изменения в модель
        // и закрывает виджет.
        connect(comboBox, SIGNAL(currentIndexChanged(int)),
                    this, SLOT(closeAndCommitEditor()));
    }
    break;

    case FetchModel::EndDateItem:    // Поле "Конец".
    case FetchModel::StartDateItem:  // Поле "Начало".
    {
        // Получает виджет QDateEdit из editor.
        QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);

        // Считывает дату из модели и устанавливает в виджет QDateEdit.
        QString date = index.model()->data(index, Qt::DisplayRole).toString();
        dateEdit->setDate(QDate::fromString(date, "dd.MM.yyyy"));

        // Если данные в QDateEdit изменились, вносит изменения в модель
        // и закрывает QDateEdit.
        connect(dateEdit, SIGNAL(dateChanged(QDate)),
                this, SLOT(closeAndCommitEditor()));
    }
    break;
  }
}



// Устанавливает данные из editor в модель по данному индексу.
void FetchItemDelegate::setModelData(QWidget *editor,
                                         QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
  QString value;
  int row = index.row();

  switch (row) {
    case FetchModel::SourceItem:  // Поле "Источник".
    {
        // Получает виджет QComboBox из editor. Сохраняет его текущее значение.
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        value = comboBox->currentText();

        QString id = comboBox->currentData().toString();
        // Сохраняет текущую иконку в модель с ролью DecorationRole.
        QString icon = index.data(ROLE_SOURCE_DATA).toMap().value(id).
                       toStringList().at(1);
        model->setData(index, QIcon(icon), Qt::DecorationRole);
        model->setData(index, id, ROLE_CURRENT_INDEX);
    }
    break;

    case FetchModel::StyleItem:     // Поле "Жанр".
    case FetchModel::PeriodItem:    // Поле "Период".
    case FetchModel::FilterItem:    // Поле "Фильтр".
    {
      // Получает виджет QComboBox из editor. Сохраняет его текущее значение.
      QComboBox *comboBox = static_cast<QComboBox*>(editor);
      value = comboBox->currentText();
    }
    break;

    case FetchModel::StartDateItem:  // Поле "Начало".
    case FetchModel::EndDateItem:    // Поле "Конец".
    {
      // Получает виджет QDateEdit из editor. Сохраняет отображаемую дату в value.
      QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
      value = dateEdit->date().toString("dd.MM.yyyy");

      // Подсвечивает поле если текущая дата позднее поля "Конец", иначе
      // восстанавливает нормальный цвет поля.
      QString dateString = index.sibling(2, 0).data(Qt::DisplayRole).toString();
      if (dateEdit->date() > QDate::fromString(dateString, "dd.MM.yyyy"))
        model->setData(index, QBrush(QColor("#ff8981")), Qt::BackgroundRole);
      else
        model->setData(index, QGuiApplication::palette().background(), Qt::BackgroundRole);
    }
    break;
  }

  // Сохраняет отображаемое значение в виджете в модель с ролью DisplayRole.
  model->setData(index, value, Qt::DisplayRole);
}



// Обновляет позицию делегата.
void FetchItemDelegate::updateEditorGeometry(QWidget *editor,
                                                 const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
  editor->setGeometry(option.rect);
}



// Обновляет модель и закрывает виджет-делегат.
void FetchItemDelegate::closeAndCommitEditor()
{
  // Сохраняет виджет отправитель.
  QWidget* widget = qobject_cast<QWidget*>(sender());

  // Обновляет модель и закрывает виджет.
  emit commitData(widget);
  emit closeEditor(widget);
}
