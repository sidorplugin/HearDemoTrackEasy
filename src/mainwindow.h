#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataclasses/datainput.h"
#include "widgets/waitingwidget/waitingwidget.h"
#include "widgets/dbviewwidget/dbviewitemdelegate.h"
#include "widgets/dbviewwidget/dbviewwidget.h"
#include "widgets/playerwidget/playerwidget.h"
#include "widgets/coverwidget/coverwidget.h"
#include "forms/searchresultform.h"
#include "worker.h"

#include <QMainWindow>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMediaContent>
#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>

namespace Ui {
  class MainWindow;
}

class Worker;
class MainWindowPrivate;

class MainWindow : public QMainWindow
{
  Q_OBJECT
  Q_PROPERTY(QString textStatus WRITE setTextStatus)

public:
  // Состояние интерфейса.
  enum State {
    ReadyState,              // Готов.
    FetchState,              // Выборка.
    LoadState,               // Загрузка.
    SearchState,             // Поиск.
    PlayState                // Плеер.
  };

  // Действия Ui.
  enum Actions {
    FetchAction,
    LoadAction,
    SearchAction,
    CancelAction,
    InfoAction,
    RemoveAction,
    ClearAction,
    PreferencesAction,
    OpenDbAction,
    SaveDbAction,
    ExitAction
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  Worker* worker();

public slots:
  void on_ready(int count, int total, const QList<MediaInfo>& media);
  void on_loaded();
  void on_finished();

private slots:
  // Обрабатывает действие главного окна.
  void executeAction(int action);
  // Обрабатывает действие контекстного меню.
  void executeActionContextMenu(int action);
  //
  void activatePlayer(int button);
  //
  void on_addClickedSearchResultForm(const QList<MediaInfo>& media);

private:
  // Создает виджеты.
  void createWidgets();
  // Устанавливает действия.
  void setActions();
  // Включает/отключает кнопки ToolBar.
  void enableToolBarButtons(bool ok);
  //
  void setTextStatus(const QString& text);
  // Обновляет элементы интерфейса.
  void updateUI();
  //
  void addMedia(const QList<MediaInfo>& media);

private:  
  MainWindowPrivate* m_d;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
