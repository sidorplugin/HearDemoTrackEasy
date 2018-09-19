#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "dataclasses/moduleparameters.h"

#include <QMessageBox>

SearchDialog::SearchDialog(const QHash <QString, Module*>& modules, QWidget *parent) :
  QDialog(parent),
  m_modules(modules),
  ui(new Ui::SearchDialog)
{
  ui->setupUi(this);

  setProperty("modal", true);

  ui->source->addItem(QIcon(":/images_ui/images/all.png"), "All", QStringList("All"));
  ui->group->addItem("All");
  foreach (Module* module, m_modules) {
      int id = module->parameters().data(ModuleParameters::Id).toInt();
      QString name = module->parameters().data(ModuleParameters::Name).toString();
      QString icon = module->parameters().data(ModuleParameters::Icon).toString();
      QStringList searchGroups =
          module->parameters().data(ModuleParameters::SearchGroups).toStringList();
      ui->source->addItem(QIcon(icon), name, searchGroups);
  }

  connect(ui->source, SIGNAL(currentIndexChanged(int)),
          this, SLOT(populateGroupBySource(int)));

  connect(ui->buttonBox, SIGNAL(accepted()),
          this, SLOT(on_accepted()));

  connect(ui->buttonBox, SIGNAL(rejected()),
          this, SLOT(close()));
}


SearchDialog::~SearchDialog()
{
  delete ui;
}


void SearchDialog::setText(const QString &text)
{
  ui->text->setText(text);
}


QString SearchDialog::text() const
{
  return ui->text->text();
}


void SearchDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      ui->retranslateUi(this);
      break;
    default:
      break;
    }
}


void SearchDialog::populateGroupBySource(int index)
{
  ui->group->clear();
  QStringList groups = ui->source->itemData(index).toStringList();
  foreach (QString group, groups) {
      ui->group->addItem(group);
    }
}

// Проверяет правильность ввода параметров поиска.
void SearchDialog::on_accepted()
{
  InputPack input;
  input.searchPack.source = ui->source->currentText();
  input.searchPack.group = ui->group->currentText();
  input.searchPack.text = ui->text->text();

  if (validate(input)) {
    emit okPressed(input);
  }
  else
    QMessageBox::warning(this, "Предупреждение",
                               "Не правильно заданы параметры для поиска.\n"
                               "Возможно вы забыли указать некоторые значения");
}

bool SearchDialog::validate(const InputPack &pack)
{
  // TODO:
  return true;
}
