#include "mainwindow.h"
#include "preferences.h"
#include "ui_mainwindow.h"


#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent),
                                           ui(new Ui::MainWindow),
                                           m_isSingleLoad(false)
{
  ui->setupUi(this);

  createWidgets();
  setConnections();
  setActions();

  setState(MainWindow::ReadyState);
}


MainWindow::~MainWindow()
{
  delete ui;
  delete m_fetchParametersWidget;
  delete m_dbViewWidget;
  delete m_playerWidget;
}


// Устанавливает состояние программы.
void MainWindow::setState(int state)
{
  if (m_state != state) {
    m_state = state;
    emit signal_stateChanged(m_state);
  }
}


// Возвращает статус программы.
int MainWindow::state()
{
  return m_state;
}


// Создает виджеты.
void MainWindow::createWidgets()
{
  // Создает виджет для просмотра элементов БД.
  m_dbViewWidget = new DbViewWidget;
  ui->dockWidgetDbView->setWidget(m_dbViewWidget);

  // Создает виджет воспроизведения.
  m_playerWidget = new PlayerWidget;
  ui->dockWidgetPlay->setWidget(m_playerWidget);

  // Создает виджет параметров выборки.
  m_fetchParametersWidget = new FetchParametersWidget;
  ui->dockWidgetParameters->setWidget(m_fetchParametersWidget);

  // Создает виджет показа ожидания.
  m_waitingWidget = new WaitingWidget(m_dbViewWidget);

}


// Устанавливает соединения.
void MainWindow::setConnections()
{
  qDebug() << "MainWindow::setConnections()";  

  // Обновляет интерфейс при смене состояния программы.
  connect(this, SIGNAL(signal_stateChanged(int)),
          this, SLOT(slot_updateUI(int)));

  // Оповещает виджет просмотрщик треков при смене состояния программы.
  connect(this, SIGNAL(signal_stateChanged(int)),
          m_dbViewWidget, SLOT(setState(int)));


  // Реакция на нажатие кнопок Плеера.
  connect(m_playerWidget, SIGNAL(clicked(PlayerWidget::Button)),
          this, SLOT(slot_onClickedPlayerButtons(PlayerWidget::Button)));

  // Обрабатывает сигналы контекстного меню DbViewer'а.
  connect(m_dbViewWidget, SIGNAL(executeAction(DbViewWidget::Action)),
          this, SLOT(slot_executeActionContextMenu(DbViewWidget::Action)));


}


// Устанавливает действия.
void MainWindow::setActions()
{
  qDebug() << "MainWindow::setActions()";

  // TODO Сигналы в main распределить с помощью QSignallMapper.

  connect(ui->action_Fetch, SIGNAL(triggered(bool)),
          this, SLOT(slot_fetch()));

  connect(ui->action_Download, SIGNAL(triggered(bool)),
          this, SLOT(slot_load()));

  connect(ui->action_Search, SIGNAL(triggered(bool)),
          this, SLOT(slot_search()));

  connect(ui->action_Cancel, SIGNAL(triggered(bool)),
          this, SLOT(slot_cancel()));

  connect(ui->action_Info, SIGNAL(triggered(bool)),
          this, SLOT(slot_info()));

  connect(ui->action_Delete, SIGNAL(triggered(bool)),
          this, SLOT(slot_removeTrack()));

  connect(ui->action_Clear, SIGNAL(triggered(bool)),
          this, SLOT(slot_clearDatabase()));

  connect(ui->action_Preferences, SIGNAL(triggered(bool)),
          this, SLOT(slot_openPreferencesWindow()));

  connect(ui->action_Exit, SIGNAL(triggered(bool)),
          this, SLOT(close()));

}


// Действие на нажатие кнопки "Выбрать".
void MainWindow::slot_fetch()
{
   qDebug() << "MainWindow::slot_fetch()";
  // TODO Валидатор входящих данных.
  // Если данные правильные запускает выборку.

  setState(MainWindow::FetchingState);
  DataInput dataInput = getDataFromWidgets();
  emit signal_fetch(dataInput);
}


// Действие на нажатие кнопки "Загрузить".
void MainWindow::slot_load()
{
  qDebug() << "MainWindow::slot_load()";

  setState(MainWindow::LoadingState);
  DataInput dataInput = getDataFromWidgets();
  emit signal_load(dataInput);
}


// Отменяет действие.
// Cancel action.
void MainWindow::slot_cancel()
{
  qDebug() << "MainWindow::slot_cancel";

  setState(MainWindow::WaitingState);
  emit signal_cancel();
}


// Слот реакция на нажатие кнопки Плеера.
// В зависимости от нажатой кнопки плеера отправляет сигнал с номером
// строки трека в базе.
void MainWindow::slot_onClickedPlayerButtons(PlayerWidget::Button button)
{
  qDebug() << "MainWindow::slot_onClickedPlayerButtons";

  // Получает текущую строку виджета "Просмотрщик треков".
  int row = m_dbViewWidget->currentIndex().row();

  // Увеличивает значение index при нажатой кнопке "Next".
  if (button == PlayerWidget::NextButton)
    row++;
  // Уменьшает значение index при нажатой кнопке "Previous".
  if (button == PlayerWidget::PreviousButton) {
    if (row != 0)
      row--;
  }

  // Устанавливает index текущей строкой в виджете "Просмотрщик треков".
  m_dbViewWidget->selectRow(row);

  emit signal_play(row);
}


// Проигрывает трек.
void MainWindow::slot_play(TrackInfo track)
{
  m_playerWidget->play(track);
}


// Показывает количество выбранных страниц (текущее, всего).
void MainWindow::slot_pageFetched(int count, int total)
{
  m_dbViewWidget->resizeColumnsToContents();
  m_waitingWidget->setFetchingPage(count, total);

  ui->statusBar->showMessage(QString("Выбрано " + QString::number(count) +
                             " из " + QString::number(total) + " страниц"));
}


// Запускает поиск.
void MainWindow::slot_search()
{

}


// Обрабатывает задачу action для строки row поступившую от виджета DbView.
void MainWindow::slot_executeActionContextMenu(DbViewWidget::Action action)
{
   // Получает текущую строку виджета "Просмотрщик треков".
   int row = m_dbViewWidget->currentIndex().row();
   // В зависимости от action обрабатывает задачу.
    switch (action) {
        case DbViewWidget::Play :
            slot_onClickedPlayerButtons(PlayerWidget::PlayButton);
        break;

        case DbViewWidget::Load :
            m_isSingleLoad = true;
            slot_load();
        break;

        case DbViewWidget::SearchLabel :
          slot_search();
        break;

        case DbViewWidget::SearchArtist :
        break;

        case DbViewWidget::CopyLink :
            emit signal_copyLink(row);
        break;

        case DbViewWidget::CopyTitle :
          emit signal_copyTitle(row);
        break;

        case DbViewWidget::Remove :
            slot_removeTrack();
        break;

    }
}


// Удаляет текущий трек.
void MainWindow::slot_removeTrack()
{
  qDebug() << "MainWindow::deleteRowInTable";

  // Выдает запрос на подтверждение удаления выделенной записи из БД.
  int result = QMessageBox::question(this, "Удаление выделенной записи БД.",
                        "Вы уверены что хотите удалить выделенную запись из БД?");

  if (result == QMessageBox::Yes) {
      int row = m_dbViewWidget->currentIndex().row();
      emit signal_removeTrack(row);
  }

}


// Обновляет элементы интерфейса.
void MainWindow::slot_updateUI(int state)
{
  qDebug() << "MainWindow::slot_updateUI";
  switch (state) {
    case MainWindow::ReadyState :
      m_waitingWidget->stop();
      ui->statusBar->showMessage("Готов");
      m_dbViewWidget->setEnabled(true);
      m_playerWidget->setEnabled(true);
      m_fetchParametersWidget->setEnabled(true);
      enableToolBarButtons(true);
    break;

    case MainWindow::FetchingState :
      m_waitingWidget->start();
      ui->statusBar->showMessage("Идет выборка");
      m_playerWidget->setEnabled(false);
      enableToolBarButtons(false);
    break;

    case MainWindow::FetchedState :
      m_waitingWidget->stop();
      ui->statusBar->showMessage("Выборка окончена");
      m_playerWidget->setEnabled(true);
      enableToolBarButtons(true);
    break;

    case MainWindow::LoadingState :
      ui->statusBar->showMessage("Идет загрузка");
      m_playerWidget->setEnabled(false);
      enableToolBarButtons(false);
    break;

    case MainWindow::LoadedState :
      ui->statusBar->showMessage("Загрузка окончена");
      if (m_isSingleLoad)
        m_isSingleLoad = false;
      m_playerWidget->setEnabled(true);
      enableToolBarButtons(true);
    break;

    case MainWindow::PlayingState :
      ui->statusBar->showMessage("Идет проигрывание трека");
      enableToolBarButtons(false);
    break;

    case MainWindow::SearchingState :
      ui->statusBar->showMessage("Идет поиск");
      m_playerWidget->setEnabled(false);
      enableToolBarButtons(false);
    break;

    case MainWindow::SearchedState :
      ui->statusBar->showMessage("Поиск завершен");
      m_playerWidget->setEnabled(true);
      enableToolBarButtons(true);
    break;
  }

}


// Enable or disable interface elements.
void MainWindow::enableToolBarButtons(bool ok)
{
  qDebug() << "MainWindow::enableToolBarButtons";

  // Enable or disable buttons.
  ui->action_Fetch->setEnabled(ok);
  ui->action_Download->setEnabled(ok);
  ui->action_Search->setEnabled(ok);
  ui->action_Preferences->setEnabled(ok);
}


// Показывает окно "Сведения".
// Show window "About".
void MainWindow::slot_info()
{
  QMessageBox msgBox;
  msgBox.setWindowIcon(QIcon(":/images_ui/images/deejayDeFavicon.ico"));
  msgBox.setWindowTitle("Сведения о Hear Demo Track Easy");
  msgBox.setIconPixmap(QPixmap("://images/information.png"));
  msgBox.setText("Программа 'Hear Demo Track Easy' помогает любителям музыки и \n"
                 "диджеям следить за новинками www.deejay.de, www.juno.co.uk и \n"
                 "www.hardwax.com. \n");
  msgBox.exec();
}


// Очищает БД.
// Clear all elements from database.
void MainWindow::slot_clearDatabase()
{
  // Выдает запрос на подтверждение удаления всех записей из БД.
  int result = QMessageBox::question(this, "Удаление всех записей БД.",
                        "Вы уверены что хотите удалить все записи из БД?");

  if (result == QMessageBox::Yes) {
      emit signal_clearDatabase();
  }
}


// Открывает окно Настроек.
// Open window "Preferences".
void MainWindow::slot_openPreferencesWindow()
{
  Preferences preferencesWindow;
  preferencesWindow.exec();
}


// Возвращает данные с виджетов.
DataInput MainWindow::getDataFromWidgets()
{
  DataInput dataInput;

  dataInput.source = m_fetchParametersWidget->getSource();
  dataInput.dateStart = m_fetchParametersWidget->getDateStart();
  dataInput.dateEnd = m_fetchParametersWidget->getDateEnd();
  dataInput.genre = m_fetchParametersWidget->getGenre();
  dataInput.period = m_fetchParametersWidget->getPeriod();
  dataInput.filter = m_fetchParametersWidget->getFilter();
  dataInput.isSingleLoad = m_isSingleLoad;
  dataInput.row = m_dbViewWidget->currentIndex().row();

  return dataInput;
}
