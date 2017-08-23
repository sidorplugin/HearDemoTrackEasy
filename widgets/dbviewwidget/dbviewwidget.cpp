#include "dbviewwidget.h"
#include "database.h"

#include <QAction>
#include <QMenu>

DbViewWidget::DbViewWidget(QWidget* parent)
{
    // Заполняет данные для контекстного меню.
    m_actionIdList << DbViewWidget::Play << DbViewWidget::Load
                   << DbViewWidget::SearchLabel << DbViewWidget::SearchArtist
                   << DbViewWidget::CopyLink << DbViewWidget::CopyTitle
                   << DbViewWidget::Remove;

    m_actionNameList << "Воспроизвести" << "Загрузить"
                     << "Искать лэйбл" << "Искать артиста"
                     << "Копировать ссылку" << "Копировать название"
                     << "Удалить";

    m_actionIconList << ":/images_ui/images/player_play.png"
                     << ":/images_ui/images/download.png"
                     << ":/images_ui/images/search_label.png"
                     << ":/images_ui/images/search_title.png"
                     << ":/images_ui/images/link.png"
                     << ":/images_ui/images/copy_title.png"
                     << ":/images_ui/images/delete.png";

    // Заполняет таблицу данными.
    for (int i = 0; i < m_actionIdList.size(); i++) {
      QStringList listInfo;
      listInfo << m_actionNameList.at(i) << m_actionIconList.at(i);
      m_actionsTable.insert(m_actionIdList.at(i), listInfo);
    }

    // Настраивает QSignalMapper для нахождения активированного действия меню.
    m_signalMapper = new QSignalMapper(this);
    // По получению сигнала от QSignalMapper с id действия, запускает слот
    // отправления сигнала на выполнение действия.
    connect(m_signalMapper, SIGNAL(mapped(int)),
            this, SLOT(sendAction(int)));

    // Создает и настраивает прогрессбар делегат для первой ячейки таблицы.
    m_delegate = new DbViewItemDelegate;
    setModel(Database::getInstance()->model());
    setItemDelegateForColumn(0, m_delegate);
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

    // Подключает СЛОТ вызова контекстного меню.
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(on_customContextMenuRequested(QPoint)));

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


// Вызов контекстного меню.
void DbViewWidget::on_customContextMenuRequested(QPoint position)
{
  // Создаем объект контекстного меню.
  QMenu* menu = new QMenu(this);

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

      menu->addAction(action);
  }

  // Вызываем контекстное меню.
  menu->popup(viewport()->mapToGlobal(position));
}


// Отправляет сигнал на выполнение действия.
void DbViewWidget::sendAction(int id)
{
  emit executeAction(m_actionIdList.at(id));
}


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
