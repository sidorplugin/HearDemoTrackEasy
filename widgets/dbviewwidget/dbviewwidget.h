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
                SearchLabel,
                SearchArtist,
                CopyLink,
                CopyTitle,
                Remove };

  DbViewWidget(QWidget* parent = 0);
  ~DbViewWidget();

public slots:
  // Устанавливает статус программы.
  void setState(int state);

signals:
  // Сигнал на выполнение действия action.
  void executeAction(DbViewWidget::Action action);

private slots:
  // Вызов контекстного меню.
  void on_customContextMenuRequested(QPoint position);
  // Отправляет сигнал на выполнение действия.
  void sendAction(int id);

private:
  // Создает действие для контекстного меню.
  QAction* createAction(int id, const QStringList& info, int state);

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
