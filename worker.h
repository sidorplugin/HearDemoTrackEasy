#ifndef WORKER_H
#define WORKER_H

#include "mainwindow.h"
#include "dataclasses/datainput.h"
#include "baseclasses/modulefactory.h"
#include "baseclasses/module.h"
#include "downloader/downloader.h"
#include "model.h"

#include <QObject>

// Главный рабочий модуль приложения. Обрабатывает все команды,
// поступающие из интерфейса. Перераспределяет работу между своими компонентами
// (Модулями источников, загрузчиком, поисковиком).


class Worker : public QObject
{
  Q_OBJECT
public:

  // TODO Хранение в xml
  // Источник.
  enum Source { DeejayDe_Source,
                Hardwax_Source,
                Juno_Source };

  explicit Worker(QObject *parent = 0);
  ~Worker();

  // Создает модуль.
  void createModule(ModuleFactory* factory);

public slots:
  // Стартует выборку.
  void slot_fetch(DataInput& input);
  // Загружает треки.
  void slot_load(DataInput& input);
  // Стартует поиск.
  void slot_search(DataInput& input);
  // Отменяет действие.
  void slot_cancel();
  // Устанавливает состояние программы.
  void slot_setState(int state);
  // По получению сигналов от модулей о завершении работы отправляет сигнал Ui
  // об изменении статуса.
  void slot_onModulesFinished();
  // Добавляет треки в модель.
  void addTracksToModel(const QList<MediaInfo>& tracks);


signals:
  // Изменено состояние программы.
  void signal_stateChanged(int);
  // Страница выбрана (текущая, всего).
  void signal_pageFetched(int, int);
  // Готовы треки для передачи.
  void signal_ready(const QList<MediaInfo>&);

private slots:
  // Добавляет треки.
  void handleTracksFromModule(const QList<MediaInfo>& tracks);

private:
  // Создает загрузчик.
  void createDownloader();


private:
  DataInput m_input;
  QHash <QString, Module*> m_modules;  // Хранит модули приложения.
  Downloader* m_downloader;            // Загрузчик.
  Model* m_model;                // Модель.
  int m_state;                         // Состояние программы.


};

#endif // WORKER_H
