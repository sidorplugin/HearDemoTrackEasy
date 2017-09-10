#include "dbviewwidget.h"
#include "database.h"

#include <QAction>
#include <QMenu>

DbViewWidget::DbViewWidget(QWidget* parent)
{
    // Заполняет данные для контекстного меню.
    m_actionIdList << DbViewWidget::Play
                   << DbViewWidget::Load
                   << DbViewWidget::Search_Artist
                   << DbViewWidget::Search_Title
                   << DbViewWidget::Search_Label
                   << DbViewWidget::Copy_Artist
                   << DbViewWidget::Copy_Title
                   << DbViewWidget::Copy_Label
                   << DbViewWidget::Copy_Album
                   << DbViewWidget::Copy_Link
                   << DbViewWidget::Remove;

    m_actionNameList << "Воспроизвести"
                     << "Загрузить"
                     << "Артист"
                     << "Название"
                     << "Лэйбл"
                     << "Артист"
                     << "Название"
                     << "Лэйбл"
                     << "Альбом"
                     << "Ссылка"
                     << "Удалить";

    m_actionIconList << ":/images_ui/images/player_play.png"
                     << ":/images_ui/images/download.png"
                     << ""
                     << ""
                     << ""
                     << ""
                     << ""
                     << ""
                     << ""
                     << ""
                     << ":/images_ui/images/delete.png";

    // Заполняет таблицу данными.
    for (int i = 0; i < m_actionIdList.size(); i++) {
      QStringList listInfo;
      listInfo << m_actionNameList.at(i) << m_actionIconList.at(i);
      m_actionsTable.insert(m_actionIdList.at(i), listInfo);
    }

    m_signalMapper = new QSignalMapper(this);
    connect(m_signalMapper, SIGNAL(mapped(int)),
            this, SIGNAL(actionTriggered(int)));

    // Создает и настраивает прогрессбар делегат для первой ячейки таблицы.
    m_delegate = new DbViewItemDelegate;
    setModel(Database::getInstance()->model());
    setItemDelegateForColumn(2, m_delegate);

    Database::getInstance()->model()->select();

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    // Настраивает параметры таблицы.
    verticalHeader()->setDefaultSectionSize(21);
    if (!Database::getInstance()->model()->isEmpty())
      resizeColumnsToContents();

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setCornerButtonEnabled(false);

    // Устанавливаем Контекстное Меню.
    setContextMenuPolicy(Qt::CustomContextMenu);

//    setColumnHidden(0, true);
//    setColumnHidden(1, true);

    // Подключает СЛОТ вызова контекстного меню.
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(createContextMenu(QPoint)));

//    connect(this->horizontalHeader(), SIGNAL(activated(QModelIndex)),
//            this, SLOT(slot1(QModelIndex)));
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


// Создает контекстное меню.
void DbViewWidget::createContextMenu(QPoint position)
{
  // Создаем объект контекстного меню.
  QMenu* menu = new QMenu(this);
  // Создаем подменю Копирования и Поиска.
  QMenu* copyMenu = new QMenu("Копировать", this);
  copyMenu->setIcon(QIcon(":/images_ui/images/copy.png"));
  QMenu* searchMenu = new QMenu("Поиск", this);
  searchMenu->setIcon(QIcon(":/images_ui/images/search.png"));

  // Создаём действия для контекстного меню.
  QMapIterator <int, QVariant> i(m_actionsTable);
  while (i.hasNext()) {
      i.next();
      int id = i.key();
      QStringList info = i.value().toStringList();
      QAction* action = createAction(id, info, m_state);

      // Подключаем СЛОТы обработчики для действий контекстного меню.
      connect(action, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
      m_signalMapper->setMapping(action, id);

      if (nameAction(id).contains("Search"))
        searchMenu->addAction(action);
      else if (nameAction(id).contains("Copy"))
        copyMenu->addAction(action);
      else
        menu->addAction(action);

  }

  menu->addMenu(copyMenu);
  menu->addMenu(searchMenu);

  // Вызываем контекстное меню.
  menu->popup(viewport()->mapToGlobal(position));
}

//void DbViewWidget::slot1(const QModelIndex &index)
//{
//    Database::getInstance()->model()->setSort(index.column(), Qt::AscendingOrder);
//    Database::getInstance()->model()->select();
//}


// Создает действие для контекстного меню.
QAction* DbViewWidget::createAction(int id, const QStringList& info, int state)
{
  QString name = info.at(0);
  QString icon = info.at(1);

  QAction* action = new QAction(name, this);
  action->setIcon(QIcon(icon));

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

  return action;
}



QString DbViewWidget::nameAction(int code)
{
  QString name;
  switch (code) {
    case DbViewWidget::Play :          name = "Play";             break;
    case DbViewWidget::Load :          name = "Load";             break;
    case DbViewWidget::Search_Artist : name = "Search_Artist";    break;
    case DbViewWidget::Search_Title :  name = "Search_Title";     break;
    case DbViewWidget::Search_Label :  name = "Search_Label";     break;
    case DbViewWidget::Copy_Artist :   name = "Copy_Artist";      break;
    case DbViewWidget::Copy_Title :    name = "Copy_Title";       break;
    case DbViewWidget::Copy_Label :    name = "Copy_Label";       break;
    case DbViewWidget::Copy_Album :    name = "Copy_Album";       break;
    case DbViewWidget::Copy_Link :     name = "Copy_Link";        break;
    case DbViewWidget::Remove :        name = "Remove";           break;

  }
  return name;
}
