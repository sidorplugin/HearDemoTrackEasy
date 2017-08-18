#include "globaldata.h"
#include "preferences.h"
#include "ui_preferencesForm.h"

#include <QDebug>
#include <QDirModel>
#include <QCompleter>
#include <QValidator>
#include <QMessageBox>
#include <QPushButton>

Preferences::Preferences(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Preferences)
{
  ui->setupUi(this);

  // Настройка QCompleter (подсказка и подстановка путей) для строки root.
  QCompleter *completer = new QCompleter(this);
  completer->setModel(new QDirModel(completer));
  ui->lineEdit_Root->setCompleter(completer);

  // Загружает глобальные настройки и отображает их в виджете.
  GlobalData::getInstance()->readGlobalSettings();
  ui->spinBox_Delay->setValue(GlobalData::getInstance()->delay);
  ui->spinBox_Waiting->setValue(GlobalData::getInstance()->waiting);
  ui->spinBox_Loads->setValue(GlobalData::getInstance()->loads);
  ui->lineEdit_Root->setText(GlobalData::getInstance()->root);

  // По нажатию "Сохранить" вызывает слот сохранения настроек.
  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

Preferences::~Preferences()
{
  delete ui;
}

void Preferences::changeEvent(QEvent *e)
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


void Preferences::save()
{
  GlobalData::getInstance()->setGlobalSettings(
                             ui->lineEdit_Root->text(),
                             ui->spinBox_Delay->text().toInt(),
                             ui->spinBox_Waiting->text().toInt(),
                             ui->spinBox_Loads->text().toInt());
}
