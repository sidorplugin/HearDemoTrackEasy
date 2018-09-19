#include "dbviewwidget.h"
#include "database.h"
#include "model.h"

#include <QAction>
#include <QMenu>

DbViewWidget::DbViewWidget(QWidget* parent)
{
    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, SIGNAL(mapped(int)),
            this, SIGNAL(actionTriggered(int)));

    // Создает и настраивает прогрессбар делегат для первой ячейки таблицы.
    m_delegate = new DbViewItemDelegate(this);
    setModel(Database::getInstance()->model());
    setItemDelegateForColumn(2, m_delegate);

    // Настраивает Header таблицы.
    m_tableHeader = new FilterTableHeader(this);
    setHorizontalHeader(m_tableHeader);
    // Создает Header'ы для всех колонок модели.
    m_tableHeader->generateFilters(Database::getInstance()->model()->columnCount());
    // При изменении значения в фильтре обновляет модель.
    connect(m_tableHeader, SIGNAL(filterChanged(int, QString)),
            this, SLOT(updateFilter(int, QString)));

    // Производит выборку данных из модели.
    Database::getInstance()->model()->select();

    // Настраивает параметры таблицы.
    verticalHeader()->setDefaultSectionSize(21);
    if (!Database::getInstance()->model()->isEmpty())
      resizeColumnsToContents();

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    setCornerButtonEnabled(false);

    setColumnHidden(0, true);
    setColumnHidden(1, true);

    // Создаем объект контекстного меню.
    createMenu();

}


DbViewWidget::~DbViewWidget()
{
  delete m_signalMapper;
  delete m_delegate;
}


// Устанавливает статус программы.
void DbViewWidget::setState(int state)
{
  m_state = state;
}


// Фильтрует модель по колонке column и значению value.
void DbViewWidget::updateFilter(int column, const QString &value)
{
  Database::getInstance()->model()->updateFilter(column, value);
}


// Показывает контекстное меню.
void DbViewWidget::popupContextMenu(QPoint position)
{  
  // Обновляем состояние действий в контекстном меню.
  updateActionsEnabled(m_state);
  // Вызываем контекстное меню.
  m_menu->popup(viewport()->mapToGlobal(position));
}


// Создает контекстное меню.
void DbViewWidget::createMenu()
{
  m_menu = new QMenu(this);

  // Создаем подменю Копирования и Поиска.
  m_copyMenu = new QMenu("Копировать", this);
  m_copyMenu->setIcon(QIcon(":/images_ui/images/copy.png"));
  m_searchMenu = new QMenu("Поиск", this);
  m_searchMenu->setIcon(QIcon(":/images_ui/images/search.png"));

  // Создает действия.
  createActions();

  // Добавляет подменю Копирования и Поиска в основное меню.
  m_menu->addMenu(m_copyMenu);
  m_menu->addMenu(m_searchMenu);

  // Устанавливает контекстное меню.
  setContextMenuPolicy(Qt::CustomContextMenu);

  // Подключает СЛОТ вызова контекстного меню.
  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(popupContextMenu(QPoint)));
}


// Создает действия.
void DbViewWidget::createActions()
{
  QStringList namesList;
  namesList << "Воспроизвести" << "Загрузить" << "Артист" << "Название"
            << "Лэйбл" << "Артист" << "Название" << "Лэйбл" << "Альбом"
            << "Ссылка" << "Удалить";

  QStringList iconsList;
  iconsList << ":/images_ui/images/player_play.png"
            << ":/images_ui/images/download.png"
            << "" << "" << "" << "" << "" << "" << "" << ""
            << ":/images_ui/images/delete.png";

  // Заполняет таблицу данными.
  for (int i = DbViewWidget::Play_Action; i <= DbViewWidget::Remove_Action; i++) {
    QAction* action = new QAction(namesList.at(i), this);
    action->setIcon(QIcon(iconsList.at(i)));
    m_actionsTable.insert(i, action);

    // Подключаем СЛОТы обработчики для действий контекстного меню.
    connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
    m_signalMapper->setMapping(action, i);

    // Распределяет действия по меню.
    if (i == DbViewWidget::SearchArtist_Action ||
        i == DbViewWidget::SearchTitle_Action ||
        i == DbViewWidget::SearchLabel_Action)
      m_searchMenu->addAction(action);
    else if (i == DbViewWidget::Play_Action ||
             i == DbViewWidget::Load_Action ||
             i == DbViewWidget::Remove_Action)
      m_menu->addAction(action);
    else
      m_copyMenu->addAction(action);

  }

}


// Обновляет свойство enabled у действий меню.
void DbViewWidget::updateActionsEnabled(int state)
{
  QMapIterator <int, QAction*> i(m_actionsTable);
  while (i.hasNext()) {
      i.next();
      int id = i.key();
      QAction* action = i.value();
      QString name =  action->text();

      // TODO Отключает нужные действия в контекстном меню.
      switch (state) {
        case 3 :
          if (name != "Воспроизвести")
            action->setDisabled(true);
        break;
        case 2 :
        case 4 :
          action->setDisabled(true);
        break;
      }
  }
}
