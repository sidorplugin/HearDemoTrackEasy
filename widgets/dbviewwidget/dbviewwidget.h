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
public:
  // Вид действия.
  enum Action { Play,
                Load,
                Search_Artist,
                Search_Title,
                Search_Label,
                Copy_Artist,
                Copy_Title,
                Copy_Label,
                Copy_Album,
                Copy_Link,
                Remove };

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
  // Создает контекстное меню.
  void createContextMenu(QPoint position);

private:
  // Создает действие для контекстного меню.
  QAction* createAction(int id, const QStringList& info, int state);

  QString nameAction(int code);

private:
  DbViewItemDelegate* m_delegate;
  QSignalMapper* m_signalMapper;
  FilterTableHeader* m_tableHeader;
  QList <DbViewWidget::Action> m_actionIdList;
  QStringList m_actionNameList;
  QStringList m_actionIconList;
  // Таблица действий контекстного меню.
  // (id = DbViewWidget::Action, List = name, icon).
  QMap <int, QVariant> m_actionsTable;
  QMenu* m_menu;
  QMenu* m_copyMenu;
  QMenu* m_searchMenu;

  int m_state;

};

#endif // DBVIEWWIDGET_H
