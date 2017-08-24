#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataclasses/datainput.h"
#include "widgets/waitingwidget/waitingwidget.h"
#include "widgets/dbviewwidget/dbviewitemdelegate.h"
#include "widgets/dbviewwidget/dbviewwidget.h"
#include "widgets/fetchwidget/fetchwidget.h"
#include "widgets/playerwidget/playerwidget.h"
#include "widgets/searchwidget/searchwidget.h"
#include "widgets/searchresultwidget/searchresultwidget.h"

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

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  // Состояние программы.
  enum State {
    ReadyState,              // Готов.
    WaitingState,            // Ожидание.
    FetchingState,           // Идет выборка.
    FetchedState,            // Выборка окончена.
    LoadingState,            // Идет загрузка.
    LoadedState,             // Загрузка окончена.
    SearchingState,          // Идет поиск.
    SearchedState,           // Поиск окончен.
    PlayingState             // Идет проигрывание трека.
  };

  // Действия Ui.
  enum Actions {
    FetchAction,
    LoadAction,
    SearchAction,
    CancelAction,
    InfoAction,
    DeleteAction,
    ClearAction,
    PreferencesAction,
    ExitAction
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  // Возвращает статус программы.
  int state();

signals:
  // Сигнал на выборку данных.
  void signal_fetch(DataInput&);
  // Сигнал на загрузку данных.
  void signal_load(DataInput&);
  // Сигнал на поиск данных.
  void signal_search(DataInput&);
  // Сигнал на отмену действия.
  void signal_cancel();
  // Сигнал на удаление текущего трека.
  void signal_removeTrack(int);
  // Сигнал на очищение БД.
  void signal_clearDatabase();
  // Сигнал запрос на получение инфо о треке по номеру строки.
  void signal_play(int row);
  // Сигнал на копирование ссылки трека.
  void signal_copyLink(int row);
  // Сигнал на копирование названия трека.
  void signal_copyTitle(int row);
  // Сигнал на изменение состояния программы.
  void signal_stateChanged(int);
  // Сигнал с результирующим списком выделенных треков.
  void signal_ready(const QList<TrackInfo>&);

public slots:
  // Проигрывает трек.
  void slot_play(TrackInfo& track);


private slots:
  //
  void executeAction(int action);
  // Обрабатывает задачу action для строки row поступившую от виджета DbView.
  void slot_executeActionContextMenu(DbViewWidget::Action action);
  // Слот реакция на нажатие кнопки Плеера.
  void slot_onClickedPlayerButtons(int button);
  // Показывает количество выбранных страниц (текущее, всего).
  void slot_pageFetched(int count, int total);
  // Устанавливает состояние программы.
  void setState(int state);
  // Обновляет элементы интерфейса.
  void slot_updateUI(int state);
  // Добавляет треки в виджет результатов поиска.
  void slot_addTracks(const QList<TrackInfo>& tracks);


private:
  // Создает виджеты.
  void createWidgets();
  // Устанавливает соединения.
  void setConnections();
  // Устанавливает действия.
  void setActions();
  // Возвращает данные с виджетов.
  DataInput getDataFromWidgets();
  // Включает/отключает кнопки ToolBar.
  void enableToolBarButtons(bool ok);

private:
  Ui::MainWindow *ui;                  // Графический интерфейс.
  int m_state;                         // Состояние программы.
  bool m_isSingleLoad;                 // Одиночная загрузка или нет.

  WaitingWidget* m_waitingWidget;      // Виджет ожидания.
  FetchWidget* m_fetchParametersWidget; // Виджет параметров выборки.
  DbViewWidget* m_dbViewWidget;        // Виджет "Просмотрщик БД".
  PlayerWidget* m_playerWidget;        // Виджет "Плеер".
  SearchWidget* m_searchWidget;
  SearchResultWidget* m_searchResultWidget;

  QSignalMapper* m_mapper;
  QMap <int, QAction*> m_actions;


};

#endif // MAINWINDOW_H
