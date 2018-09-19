#include "searchresultform.h"
#include "ui_searchresultform.h"

SearchResultForm::SearchResultForm(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SearchResultForm)
{
  ui->setupUi(this);
  hide();

  m_model = new SearchResultModel;

  // Загружает модель в таблицу.
  ui->table->setModel(m_model);
  ui->table->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
  ui->table->verticalHeader()->setDefaultSectionSize(21);
  ui->table->setCornerButtonEnabled(false);
  ui->table->setColumnHidden(0, true);
  ui->table->setColumnHidden(1, true);

  ui->add->setDisabled(true);
  ui->checkAll->setDisabled(true);
  ui->report->setDisabled(true);


  // Прописывает соединения на реакции кнопок.
  // По нажатию на Добавить вызывает слот обработки добавляемых треков.
  connect(ui->add, SIGNAL(clicked(bool)),
          this, SLOT(exportTracks()));

  // По нажатию на Отмена вызывает слот где удаляются результаты и закрывается окно.
  connect(ui->cancel, SIGNAL(clicked(bool)),
          this, SLOT(close()));

  // Действие по выделению бокса "Выделить все".
  connect(ui->checkAll, SIGNAL(toggled(bool)),
          this, SLOT(checkUncheckAllTracks(bool)));
}

SearchResultForm::~SearchResultForm()
{
  delete ui;
  delete m_model;
}


bool SearchResultForm::hasReport() const
{
  return ui->report->isChecked();
}


void SearchResultForm::changeEvent(QEvent *e)
{
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
    }
}


// Добавляет список треков в таблицу.
void SearchResultForm::add(const QList<MediaInfo> &tracks)
{
  qDebug() << "SearchResultForm::add";

  //?
  // Добавляет в модель треки.
  foreach (MediaInfo track, tracks) {
    m_model->add(track);
  }
  ui->table->resizeColumnsToContents();

  ui->add->setEnabled(true);
  ui->checkAll->setEnabled(true);
  ui->report->setEnabled(true);
}


// Проверяет треки модели, формирует список выделенных и отправляет их.
void SearchResultForm::exportTracks()
{
  QList <MediaInfo> result;

  // Проверяет все элементы модели на CheckState в первом столбце.
  for (int i = 0; i < m_model->rowCount(); i++) {
    // Если элемент выделен.
    if (m_model->isCheckedState(i)) {
      // Считывает дынные трека из модели.
      MediaInfo media = m_model->mediaInfo(i);
      // Добавляет в результирующий список.
      result.push_back(media);
    }
  }
  emit addClicked(result);
}


// Отмечает или снимает все флажки у треков.
void SearchResultForm::checkUncheckAllTracks(bool ok)
{
  Qt::CheckState state;
  ok? state = Qt::Checked : state = Qt::Unchecked;

  // У всех элементов модели устанавливает CheckState равным ok.
  for (int i = 0; i < m_model->rowCount(); i++) {
    m_model->item(i, MediaInfo::Artist)->setCheckState(state);
  }
}
