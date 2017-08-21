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
  delete m_mapper;
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
  // TODO разобраться с парентами у виджетов.

  // Создает виджет для просмотра элементов БД.
  m_dbViewWidget = new DbViewWidget;
  ui->dockWidgetDbView->setWidget(m_dbViewWidget);

  // Создает виджет воспроизведения.
  m_playerWidget = new PlayerWidget(this);
  ui->dockWidgetPlay->setWidget(m_playerWidget);

  // Создает виджет параметров выборки.
  m_fetchParametersWidget = new FetchParametersWidget;
  ui->dockWidgetParameters->setWidget(m_fetchParametersWidget);

  // Создает виджет показа ожидания.
  m_waitingWidget = new WaitingWidget(m_dbViewWidget);

  // Добавляет виджет поиска.
  m_searchWidget = new SearchWidget(this);
  ui->dockWidgetSearch->setWidget(m_searchWidget);

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
  connect(m_playerWidget, SIGNAL(clicked(int)),
          this, SLOT(slot_onClickedPlayerButtons(int)));

  // Обрабатывает сигналы контекстного меню DbViewer'а.
  connect(m_dbViewWidget, SIGNAL(executeAction(DbViewWidget::Action)),
          this, SLOT(slot_executeActionContextMenu(DbViewWidget::Action)));

}


// Устанавливает действия.
void MainWindow::setActions()
{
  qDebug() << "MainWindow::setActions()";

  m_actions.insert(MainWindow::FetchAction, ui->action_Fetch);
  m_actions.insert(MainWindow::LoadAction, ui->action_Load);
  m_actions.insert(MainWindow::CancelAction, ui->action_Cancel);
  m_actions.insert(MainWindow::InfoAction, ui->action_Info);
  m_actions.insert(MainWindow::DeleteAction, ui->action_Delete);
  m_actions.insert(MainWindow::ClearAction, ui->action_Clear);
  m_actions.insert(MainWindow::PreferencesAction, ui->action_Preferences);
  m_actions.insert(MainWindow::ExitAction, ui->action_Exit);

  m_mapper = new QSignalMapper(this);
  connect(m_mapper, SIGNAL(mapped(int)),
          this, SLOT(executeAction(int)));

  QMapIterator <int, QAction*> i(m_actions);
  while (i.hasNext()) {
      i.next();
      QAction* action = i.value();
      connect(action, SIGNAL(triggered(bool)), m_mapper, SLOT(map()));
      m_mapper->setMapping(action, i.key());
  }

}


// Слот реакция на нажатие кнопки Плеера.
// В зависимости от нажатой кнопки плеера отправляет сигнал с номером
// строки трека в базе.
void MainWindow::slot_onClickedPlayerButtons(int button)
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
void MainWindow::slot_play(TrackInfo& track)
{
  m_playerWidget->play(track);
}


void MainWindow::executeAction(int action)
{
  switch (action) {
    case MainWindow::FetchAction:
    {
      qDebug() << "MainWindow::FetchAction";
      // TODO Валидатор входящих данных.
      // Если данные правильные запускает выборку.

      DataInput dataInput = getDataFromWidgets();

      QString msgString = "Параметры : \n\n" +
              dataInput.toStringList().join("\n") +
              "\n\nВы уверены что хотите произвести выборку с этими параметрами?";
      // Выдает запрос на подтверждение выборки.
      int result = QMessageBox::question(this, "Выборка", msgString);

      if (result == QMessageBox::Yes) {
          setState(MainWindow::FetchingState);
          emit signal_fetch(dataInput);
      }
    }
    break;

    case MainWindow::LoadAction:
    {
        qDebug() << "MainWindow::DownloadAction";

        setState(MainWindow::LoadingState);
        DataInput dataInput = getDataFromWidgets();
        emit signal_load(dataInput);
    }
    break;

    case MainWindow::SearchAction:
    {
        qDebug() << "MainWindow::SearchAction";
        setState(MainWindow::SearchingState);
        DataInput dataInput = getDataFromWidgets();
        emit signal_search(dataInput);
    }
    break;

    case MainWindow::CancelAction:
    {
      qDebug() << "MainWindow::CancelAction";

      setState(MainWindow::WaitingState);
      emit signal_cancel();
    }
    break;

    case MainWindow::InfoAction:
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
    break;

    case MainWindow::DeleteAction:
    {
      qDebug() << "MainWindow::DeleteAction";

      // Выдает запрос на подтверждение удаления выделенной записи из БД.
      int result = QMessageBox::question(this, "Удаление выделенной записи БД.",
                            "Вы уверены что хотите удалить выделенную запись из БД?");

      if (result == QMessageBox::Yes) {
          int row = m_dbViewWidget->currentIndex().row();
          emit signal_removeTrack(row);
      }
    }
    break;

    case MainWindow::ClearAction:
    {
        // Выдает запрос на подтверждение удаления всех записей из БД.
        int result = QMessageBox::question(this, "Удаление всех записей БД.",
                              "Вы уверены что хотите удалить все записи из БД?");

        if (result == QMessageBox::Yes) {
            emit signal_clearDatabase();
        }
    }
    break;

    case MainWindow::PreferencesAction:
    {
        Preferences preferencesWindow;
        preferencesWindow.exec();
    }
    break;

    case MainWindow::ExitAction:
      close();
    break;
  }
}


// Показывает количество выбранных страниц (текущее, всего).
void MainWindow::slot_pageFetched(int count, int total)
{
  m_dbViewWidget->resizeColumnsToContents();
  m_waitingWidget->setFetchingPage(count, total);

  ui->statusBar->showMessage(QString("Выбрано " + QString::number(count) +
                             " из " + QString::number(total) + " страниц"));
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
            executeAction(MainWindow::LoadAction);
        break;

        case DbViewWidget::SearchLabel :
        case DbViewWidget::SearchArtist :
            executeAction(MainWindow::SearchAction);
        break;

        case DbViewWidget::CopyLink :
            emit signal_copyLink(row);
        break;

        case DbViewWidget::CopyTitle :
          emit signal_copyTitle(row);
        break;

        case DbViewWidget::Remove :
            executeAction(MainWindow::DeleteAction);
        break;

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
  ui->action_Load->setEnabled(ok);
  ui->action_Preferences->setEnabled(ok);
}



// Возвращает данные с виджетов.
DataInput MainWindow::getDataFromWidgets()
{
  DataInput dataInput;

  dataInput.setData(DataInput::Source, m_fetchParametersWidget->getSource());
  dataInput.setData(DataInput::DateStart, m_fetchParametersWidget->getDateStart());
  dataInput.setData(DataInput::DateEnd, m_fetchParametersWidget->getDateEnd());
  dataInput.setData(DataInput::Genre, m_fetchParametersWidget->getGenre());
  dataInput.setData(DataInput::Period, m_fetchParametersWidget->getPeriod());
  dataInput.setData(DataInput::Filter, m_fetchParametersWidget->getFilter());
  dataInput.setData(DataInput::SingleLoad, m_isSingleLoad);
  dataInput.setData(DataInput::Row, m_dbViewWidget->currentIndex().row());
  dataInput.setData(DataInput::Search, m_searchWidget->getData());

  return dataInput;
}
