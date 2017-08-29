#ifndef DBVIEWWIDGET_H
#define DBVIEWWIDGET_H

#include "dbviewitemdelegate.h"

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
  // Делегат колонки "Ссылка".
  DbViewItemDelegate* m_delegate;
  QSignalMapper* m_signalMapper;
  QList <DbViewWidget::Action> m_actionIdList;
  QStringList m_actionNameList;
  QStringList m_actionIconList;
  // Таблица действий контекстного меню.
  // (id = DbViewWidget::Action, List = name, icon).
  QMap <int, QVariant> m_actionsTable;


  int m_state;

};

#endif // DBVIEWWIDGET_H
