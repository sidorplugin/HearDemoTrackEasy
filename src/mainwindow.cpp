#include "database.h"
#include "mainwindow.h"
#include "preferences.h"
#include "fetchdialog.h"
#include "searchdialog.h"
#include "ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QClipboard>


//*************************  MainWindowPrivate  ****************************//
class MainWindowPrivate
{
public:
  Worker* worker;
  DbViewWidget* dbViewWidget;
  PlayerWidget* playerWidget;
  CoverWidget* coverWidget;
  SearchResultForm* searchResultForm;
  WaitingWidget* waiting;
  QSignalMapper* mapper;
  QMap <int, QAction*> actions;
  int state;

};



//*************************  MainWindow  ************************************//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          m_d(new MainWindowPrivate)
{
  ui->setupUi(this);
  showMaximized();

  m_d->worker = new Worker;

  connect(m_d->worker, SIGNAL(ready(int, int, QList<MediaInfo>)),
          this, SLOT(on_ready(int, int, QList<MediaInfo>)));

  connect(m_d->worker, SIGNAL(loaded()),
          this, SLOT(on_loaded()));

  connect(m_d->worker, SIGNAL(finished()),
          this, SLOT(on_finished()));

  createWidgets();
  setActions();

  m_d->state = MainWindow::ReadyState;
}


MainWindow::~MainWindow()
{
  delete ui;
  delete m_d->dbViewWidget;
  delete m_d->playerWidget;
  delete m_d->mapper;
}

Worker *MainWindow::worker()
{
  return m_d->worker;
}


void MainWindow::on_ready(int count, int total, const QList<MediaInfo>& media)
{
    qDebug() << "MainWindow::on_ready()";

    m_d->waiting->setInfo(count, total);
    QtConcurrent::run(this, addMedia, media);
//    m_d->searchResultForm->add(media);
}


void MainWindow::on_loaded()
{
    qDebug() << "MainWindow::on_loaded()";
}


void MainWindow::on_finished()
{
    qDebug() << "MainWindow::on_finished()";
    updateUI();
    m_d->waiting->stop();
}


// Создает виджеты.
void MainWindow::createWidgets()
{
  // Создает виджет для просмотра элементов БД.
  m_d->dbViewWidget = new DbViewWidget;
  // Обрабатывает сигналы контекстного меню DbViewer'а.
  connect(m_d->dbViewWidget, SIGNAL(actionTriggered(int)),
          this, SLOT(executeActionContextMenu(int)));
  ui->dockWidgetDbView->setWidget(m_d->dbViewWidget);

  // Создает виджет воспроизведения.
  m_d->playerWidget = new PlayerWidget(this);
  // Реакция на нажатие кнопок Плеера.
  connect(m_d->playerWidget, SIGNAL(clicked(int)), this, SLOT(activatePlayer(int)));

  ui->toolBar->addWidget(m_d->playerWidget);
  ui->toolBar->addSeparator();

  // Добавляет виджет обложки.
  m_d->coverWidget = new CoverWidget(this);
  ui->toolBar->addWidget(m_d->coverWidget);
  ui->toolBar->addSeparator();

  m_d->searchResultForm = new SearchResultForm;
  m_d->searchResultForm->setWindowTitle(QString("Результат выборки"));
  m_d->searchResultForm->setWindowIcon(QIcon(":/images_ui/images/fetch.png"));
  connect(m_d->searchResultForm, SIGNAL(addClicked(QList<MediaInfo>)),
          this, SLOT(on_addClickedSearchResultForm(QList<MediaInfo>)));

  m_d->waiting = new WaitingWidget(m_d->searchResultForm);
}


void MainWindow::setActions()
{
  qDebug() << "MainWindow::setActions()";

  m_d->actions.insert(MainWindow::FetchAction,       ui->action_Fetch);
  m_d->actions.insert(MainWindow::LoadAction,        ui->action_Load);
  m_d->actions.insert(MainWindow::SearchAction,      ui->action_Search);
  m_d->actions.insert(MainWindow::CancelAction,      ui->action_Cancel);
  m_d->actions.insert(MainWindow::InfoAction,        ui->action_Info);
  m_d->actions.insert(MainWindow::RemoveAction,      ui->action_Remove);
  m_d->actions.insert(MainWindow::ClearAction,       ui->action_Clear);
  m_d->actions.insert(MainWindow::PreferencesAction, ui->action_Preferences);
  m_d->actions.insert(MainWindow::OpenDbAction,      ui->action_OpenDb);
  m_d->actions.insert(MainWindow::SaveDbAction,      ui->action_SaveDb);
  m_d->actions.insert(MainWindow::ExitAction,        ui->action_Exit);

  m_d->mapper = new QSignalMapper(this);
  connect(m_d->mapper, SIGNAL(mapped(int)),
          this, SLOT(executeAction(int)));

  QMapIterator <int, QAction*> i(m_d->actions);
  while (i.hasNext()) {
      i.next();
      QAction* action = i.value();
      connect(action, SIGNAL(triggered(bool)), m_d->mapper, SLOT(map()));
      m_d->mapper->setMapping(action, i.key());
  }
}


// Обрабатывает действие главного окна.
void MainWindow::executeAction(int action)
{
  switch (action) {
    case MainWindow::FetchAction:
    {
      qDebug() << "MainWindow::FetchAction";

      m_d->state = MainWindow::FetchState;
      updateUI();

      FetchDialog* dlg = new FetchDialog(worker()->modules());
      dlg->show();
      connect(dlg, &FetchDialog::okPressed, [=] (const InputPack& input) {
          m_d->searchResultForm->show();
          // Показывает виджет ожидания.
          m_d->waiting->setTitle("Идет выборка");
          m_d->waiting->start();
          m_d->worker->execute(Module::FetchMode, input);
      });
    }
    break;

    case MainWindow::LoadAction:
    {
        qDebug() << "MainWindow::LoadAction";

        m_d->state = MainWindow::LoadState;
        updateUI();
        m_d->worker->load(0, false);
    }
    break;

    case MainWindow::SearchAction:
    {
        qDebug() << "MainWindow::SearchAction";

//        SearchDialog* dlg = new SearchDialog;
////        if (!searchBuffer.isEmpty) {
////          dlg->setProperty("text", searchBuffer);
////        }
//        dlg->show();
//        connect(dlg, &SearchDialog::okPressed, [=] (const InputPack& input) {
//            SearchResultForm* searchResultForm = new SearchResultForm;
//            searchResultForm->setWindowTitle(QString("Результат поиска"));
//            searchResultForm->setWindowIcon(QIcon(":/images_ui/images/search.png"));
//            searchResultForm->show();

//            connect(m_d->worker, SIGNAL(ready(QList<MediaInfo>)),
//                    searchResultForm, SLOT(add(QList<MediaInfo>)));

//            // Когда в окне результата выборки нажата add добавляет треки в модель.
//            connect(searchResultForm, &SearchResultForm::addClicked, [=] (const QList<MediaInfo> list) {
//                m_d->worker->add(list);
//              });

//            m_d->worker->execute(Module::SearchMode, input);
//            m_d->state = MainWindow::SearchState;
//            updateUI();
//        });

    }
    break;

    case MainWindow::CancelAction:
    {
      qDebug() << "MainWindow::CancelAction";
      m_d->worker->cancel(m_d->state);
    }
    break;

    case MainWindow::InfoAction:
    {
      QMessageBox msgBox;
      msgBox.setWindowIcon(QIcon(":/images_ui/images/deejayDeFavicon.ico"));
      msgBox.setWindowTitle("Сведения о Hear Demo Track Easy");
      msgBox.setIconPixmap(QPixmap("://images/information.png"));
      msgBox.setText("Программа 'Hear Demo Track Easy' помогает искателям "
                     "музыкальных записей и диджеям следить за новинками таких"
                     "интернет ресурсов как www.deejay.de, www.juno.co.uk, "
                     "www.hardwax.com. \n");
      msgBox.exec();
    }
    break;

    case MainWindow::RemoveAction:
    {
      qDebug() << "MainWindow::RemoveAction";

      // Выдает запрос на подтверждение удаления выделенной записи из БД.
      int result = QMessageBox::question(this, "Удаление выделенной записи БД.",
                            "Вы уверены что хотите удалить выделенную запись из БД?");

      if (result == QMessageBox::Yes) {
          int row = m_d->dbViewWidget->currentIndex().row();
          m_d->worker->removeFromModel(row);
      }
    }
    break;

    case MainWindow::ClearAction:
    {
        // Выдает запрос на подтверждение удаления всех записей из БД.
        int result = QMessageBox::question(this, "Удаление всех записей БД.",
                              "Вы уверены что хотите удалить все записи из БД?");

        if (result == QMessageBox::Yes) {
            m_d->worker->clearModel();
        }
    }
    break;

    case MainWindow::PreferencesAction:
    {
        Preferences* preferencesWindow = new Preferences;
        preferencesWindow->exec();
    }
    break;

    case MainWindow::OpenDbAction:
    break;

    case MainWindow::SaveDbAction:
    break;

    case MainWindow::ExitAction:
      close();
    break;
  }
}

// Обрабатывает действие action контекстного меню.
void MainWindow::executeActionContextMenu(int action)
{
   // Получает текущую строку виджета "Просмотрщик треков".
   int row = m_d->dbViewWidget->currentIndex().row();

   // Считывает информацию о треке.
   MediaInfo media = m_d->worker->getMediaInfo(row);
   QString artist = media.data(MediaInfo::Artist).toString();
   QString label = media.data(MediaInfo::Label).toString();
   QString source = media.data(MediaInfo::Source).toString();
   QString titleTrack = media.data(MediaInfo::Title_Track).toString();
   QString linkTrack = media.data(MediaInfo::Link_Track).toString();
   QString titleAlbum = media.data(MediaInfo::Title_Album).toString();


   // В зависимости от action обрабатывает задачу.
    switch (action) {
        case DbViewWidget::Play_Action :
            activatePlayer(PlayerWidget::PlayButton);
        break;

        case DbViewWidget::Load_Action :
            m_d->worker->load(row, true);
        break;

        case DbViewWidget::SearchArtist_Action :
        {
            // Устанавливает данные в диалоге поиска.
          // TODO :
//            m_d->searchWidget->setData(SearchWidget::Source, source);
//            m_d->searchWidget->setData(SearchWidget::Group, "Artists");
//            m_d->searchWidget->setData(SearchWidget::Text, artist);
            executeAction(MainWindow::SearchAction);
        }
        break;

        case DbViewWidget::SearchTitle_Action :
        {
            // Устанавливает данные в виджете поиска.
//            m_d->searchWidget->setData(SearchWidget::Source, source);
//            m_d->searchWidget->setData(SearchWidget::Group, "Titles");
//            m_d->searchWidget->setData(SearchWidget::Text, titleTrack);
            executeAction(MainWindow::SearchAction);
        }
        break;

        case DbViewWidget::SearchLabel_Action :
        {
            // Устанавливает данные в виджете поиска.
//            m_d->searchWidget->setData(SearchWidget::Source, source);
//            m_d->searchWidget->setData(SearchWidget::Group, "Labels");
//            m_d->searchWidget->setData(SearchWidget::Text, label);
            executeAction(MainWindow::SearchAction);
        }
        break;

        case DbViewWidget::CopyArtist_Action :
            QApplication::clipboard()->setText(artist);
        break;

        case DbViewWidget::CopyTitle_Action :
            QApplication::clipboard()->setText(artist + " - " + titleTrack);
        break;

        case DbViewWidget::CopyLabel_Action :
            QApplication::clipboard()->setText(label);
        break;

        case DbViewWidget::CopyAlbum_Action :
            QApplication::clipboard()->setText(titleAlbum);
        break;

        case DbViewWidget::CopyLink_Action :
            QApplication::clipboard()->setText(linkTrack);
        break;

        case DbViewWidget::Remove_Action :
            executeAction(MainWindow::RemoveAction);
        break;

      }
}

void MainWindow::activatePlayer(int button)
{
  // Получает номер текущей строки виджета.
  int row = m_d->dbViewWidget->currentIndex().row();

  // Увеличивает значение row при нажатой кнопке "Next".
  if (button == PlayerWidget::NextButton)
    row++;
  // Уменьшает значение row при нажатой кнопке "Previous".
  if (button == PlayerWidget::PreviousButton) {
      if (row != 0)
        row--;
  }

  // Устанавливает row текущей строкой в виджете.
  m_d->dbViewWidget->selectRow(row);

  MediaInfo media = m_d->worker->getMediaInfo(row);
  m_d->playerWidget->play(media);
  m_d->coverWidget->setImage(media);
}


void MainWindow::on_addClickedSearchResultForm(const QList<MediaInfo> &media)
{
  // Показывает виджет ожидания.
  m_d->waiting->setTitle("Идет добавление в модель");
  m_d->waiting->start();

  bool report = m_d->searchResultForm->hasReport();

  m_d->worker->enableFixReport();
  m_d->worker->addToModel(media);
  m_d->waiting->stop();
  m_d->searchResultForm->close();
  m_d->searchResultForm->deleteLater();
  m_d->dbViewWidget->resizeColumnsToContents();

  if (report) {
      QMessageBox msg;
      msg.setText(QString("                   Добавлено треков %1 из %2                     ")
                  .arg(m_d->worker->countAddedTracks())
                  .arg(media.size()));
      msg.setIcon(QMessageBox::Information);
      msg.setProperty("detailedText", true);
      msg.setDetailedText(m_d->worker->report());
      msg.exec();
    }
}


// Обновляет элементы интерфейса.
void MainWindow::updateUI()
{
  qDebug() << "MainWindow::updateUI";
//  switch (m_d->state) {
//    case MainWindow::ReadyState :
//      m_d->dbViewWidget->setEnabled(true);
//      m_d->playerWidget->setEnabled(true);
//      enableToolBarButtons(true);
//    break;

//    case MainWindow::FetchState :
////      m_d->waitingWidget->start();
////      ui->statusBar->showMessage("Идет выборка");
////      m_d->playerWidget->setEnabled(false);
////      enableToolBarButtons(false);
//    break;

//    case MainWindow::LoadState :
//      m_d->playerWidget->setEnabled(false);
//      enableToolBarButtons(false);
//    break;

//    case MainWindow::PlayState :
////      ui->statusBar->showMessage("Идет проигрывание трека");
////      enableToolBarButtons(false);
//    break;

//    case MainWindow::SearchState :
////      m_d->waitingWidget->start();
////      ui->statusBar->showMessage("Идет поиск");
////      m_d->dbViewWidget->setEnabled(false);
////      m_d->playerWidget->setEnabled(false);
////      enableToolBarButtons(false);
//    break;
//  }
}

void MainWindow::addMedia(const QList<MediaInfo> &media) {
  m_d->searchResultForm->add(media);
}


// Enable or disable interface elements.
void MainWindow::enableToolBarButtons(bool ok)
{
  qDebug() << "MainWindow::enableToolBarButtons";

  // Enable or disable buttons.
  ui->action_Fetch->setEnabled(ok);
  ui->action_Load->setEnabled(ok);
  ui->action_Search->setEnabled(ok);
  ui->action_Preferences->setEnabled(ok);
}


void MainWindow::setTextStatus(const QString &text)
{
  ui->statusBar->showMessage(text);
}
