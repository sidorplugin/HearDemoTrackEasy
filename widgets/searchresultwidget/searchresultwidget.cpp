#include "searchresultwidget.h"

#include <QDebug>

SearchResultWidget::SearchResultWidget(QWidget *parent) : QMainWindow(parent)
{
  ui = new Ui::SearchResultForm;
  ui->setupUi(this);

  m_model = new SearchResultModel;

  // Загружает модель в таблицу.
  ui->tableView->setModel(m_model);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setColumnHidden(5, true);
  ui->tableView->verticalHeader()->setDefaultSectionSize(21);
  ui->tableView->setCornerButtonEnabled(false);


  // Прописывает соединения на реакции кнопок.
  // По нажатию на Добавить вызывает слот обработки добавляемых треков.
  connect(ui->pushButton_AddTracks, SIGNAL(clicked(bool)),
          this, SLOT(checkTracks()));

  // По нажатию на Отмена вызывает слот где удаляются результаты и закрывается окно.
  connect(ui->pushButton_Cancel, SIGNAL(clicked(bool)),
          this, SLOT(close()));

  // Действие по выделению бокса "Выделить все".
  connect(ui->checkBox, SIGNAL(toggled(bool)),
          this, SLOT(checkUncheckAllTracks(bool)));

}

SearchResultWidget::~SearchResultWidget()
{
  delete ui;
  delete m_model;
}


// Добавляет список треков в таблицу.
void SearchResultWidget::addTracks(const QList<TrackInfo> &tracks)
{
  qDebug() << "SearchResultWidget::addTracks";

  // Добавляет в модель треки.
  foreach (TrackInfo track, tracks) {
    m_model->add(track);
  }
  ui->tableView->resizeColumnsToContents();
}


// Проверяет треки модели, формирует список выделенных и отправляет их.
void SearchResultWidget::checkTracks()
{
  QList <TrackInfo> result;

  // Проверяет все элементы модели на CheckState в первом столбце.
  for (int i = 0; i < m_model->rowCount(); i++) {
    // Если элемент выделен.
    if (m_model->isCheckedState(i)) {
      // Считывает дынные трека из модели.
      TrackInfo track = m_model->getTrackInfo(i);
      // Добавляет в результирующий список.
      result.push_back(track);
    }
  }

  emit ready(result);
  close();
}


// Отмечает или снимает все флажки у треков.
void SearchResultWidget::checkUncheckAllTracks(bool ok)
{
  Qt::CheckState state;
  ok? state = Qt::Checked : state = Qt::Unchecked;

  // У всех элементов модели устанавливает CheckState равным ok.
  for (int i = 0; i < m_model->rowCount(); i++) {
    m_model->item(i, 0)->setCheckState(state);
  }
}
