#ifndef DBVIEWWIDGET_H
#define DBVIEWWIDGET_H

#include "dbviewitemdelegate.h"
#include "filtertableheader.h"

#include <QObject>
#include <QTableView>
#include <QHeaderView>
#include <QMouseEvent>
#include <QSignalMapper>

class DbViewWidget : public QTableView
{
  Q_OBJECT
  // TODO : PROPERTY для управления из UI. (как то: disable меню)
public:
  // Вид действия.
  enum Action { Play_Action,
                Load_Action,
                SearchArtist_Action,
                SearchTitle_Action,
                SearchLabel_Action,
                CopyArtist_Action,
                CopyTitle_Action,
                CopyLabel_Action,
                CopyAlbum_Action,
                CopyLink_Action,
                Remove_Action
              };

  DbViewWidget(QWidget* parent = 0);
  ~DbViewWidget();

public slots:
  // Устанавливает статус программы.
  void setState(int state);
  // Фильтрует модель по колонке column и значению value.
  void updateFilter(int column, const QString& value);

signals:
  // Активировано действие.
  void actionTriggered(int action);

private slots:
  // Показывает контекстное меню.
  void popupContextMenu(QPoint position);

private:
  // Создает контекстное меню.
  void createMenu();
  // Создает действия.
  void createActions();
  // Обновляет свойство enabled у действий меню.
  void updateActionsEnabled(int state);

private:
  DbViewItemDelegate* m_delegate;
  QSignalMapper* m_signalMapper;
  FilterTableHeader* m_tableHeader;
  QMap <int, QAction*> m_actionsTable;
  QMenu* m_menu;
  QMenu* m_copyMenu;
  QMenu* m_searchMenu;
  // TODO :
  // ContextMenu m_menu;

  int m_state;

};

#endif // DBVIEWWIDGET_H
