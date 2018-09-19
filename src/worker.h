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

class WorkerPrivate;

class Worker : public QObject
{
  Q_OBJECT
public:
  explicit Worker();
  ~Worker();

  // Стартует выборку.
  void execute(int mode, const InputPack& input);
  //
  void initialize();
  // Загружает все треки или один трек в строке row.
  void load(int row = 0, bool single = false);
  // Отменяет действие.
  void cancel(int state);
  // Возвращает информацию о треке по строке.
  MediaInfo getMediaInfo(int row);
  //
  void enableFixReport();
  // Добавляет медиа-информацию в модель.
  void addToModel(const QList<MediaInfo> &media);
  //
  void removeFromModel(int row);
  //
  void clearModel();
  //
  int countAddedTracks() const;
  //
  QString report() const;
  //
  QHash <QString, Module*> modules() const;

signals:
  // Найдены треки.
  void ready(int, int, const QList<MediaInfo>&);
  // Окончена загрузка.
  void loaded();
  // Окончена работа worker.
  void finished();

private:
  // Создает загрузчик.
  void createDownloader();
  // Создает модуль.
  void createModule(ModuleFactory* factory);

private:
  WorkerPrivate* m_d;
};

#endif // WORKER_H
