#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataclasses/datainput.h"
#include "widgets/waitingwidget/waitingwidget.h"
#include "widgets/dbviewwidget/dbviewitemdelegate.h"
#include "widgets/dbviewwidget/dbviewwidget.h"
#include "widgets/fetchparameterswidget/fetchparameterswidget.h"
#include "widgets/playerwidget/playerwidget.h"

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
  enum State { ReadyState,              // Готов.
               WaitingState,            // Ожидание.
               FetchingState,           // Идет выборка.
               FetchedState,            // Выборка окончена.
               LoadingState,            // Идет загрузка.
               LoadedState,             // Загрузка окончена.
               SearchingState,          // Идет поиск.
               SearchedState,           // Поиск окончен.
               PlayingState             // Идет проигрывание трека.
             };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  // Возвращает статус программы.
  int state();

signals:
  // Сигнал на выборку данных.
  void signal_fetch(const DataInput&);
  // Сигнал на загрузку данных.
  void signal_load(const DataInput&);
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

public slots:
  // Проигрывает трек.
  void slot_play(TrackInfo track);


private slots:
  // Действие на нажатие кнопки "Выбрать".
  void slot_fetch();
  // Действие на нажатие кнопки "Загрузить".
  void slot_load();
  // Показывает окно "Сведения".
  void slot_info();
  // Отменяет действие.
  void slot_cancel();
  // Запускает поиск.
  void slot_search();
  // Удаляет текущий трек.
  void slot_removeTrack();
  // Очищает БД.
  void slot_clearDatabase();
  // Обрабатывает задачу action для строки row поступившую от виджета DbView.
  void slot_executeActionContextMenu(DbViewWidget::Action action);
  // Открывает окно Настроек.
  void slot_openPreferencesWindow();
  // Слот реакция на нажатие кнопки Плеера.
  void slot_onClickedPlayerButtons(PlayerWidget::Button button);
  // Показывает количество выбранных страниц (текущее, всего).
  void slot_pageFetched(int count, int total);
  // Устанавливает состояние программы.
  void setState(int state);
  // Обновляет элементы интерфейса.
  void slot_updateUI(int state);


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
  FetchParametersWidget* m_fetchParametersWidget; // Виджет параметров выборки.
  DbViewWidget* m_dbViewWidget;        // Виджет "Просмотрщик БД".
  PlayerWidget* m_playerWidget;        // Виджет "Плеер".


};

#endif // MAINWINDOW_H
