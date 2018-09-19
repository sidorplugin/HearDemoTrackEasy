#include "preferences.h"
#include "ui_preferencesForm.h"

#include <QDebug>
#include <QDirModel>
#include <QCompleter>
#include <QValidator>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

Preferences::Preferences(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Preferences)
{
  ui->setupUi(this);

  // Настройка QCompleter (подсказка и подстановка путей) для строки root.
  QCompleter *completer = new QCompleter(this);
  completer->setModel(new QDirModel(completer));
  ui->lineEdit_Root->setCompleter(completer);

  QSettings settings("settings.ini", QSettings::IniFormat);
  ui->spinBox_Delay->setValue(settings.value("Delay").toInt());
  ui->spinBox_Waiting->setValue(settings.value("Waiting").toInt());
  ui->spinBox_Loads->setValue(settings.value("Loads").toInt());
  ui->lineEdit_Root->setText(settings.value("Root").toString());

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
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.setValue("Delay", ui->spinBox_Delay->text().toInt());
  settings.setValue("Root", ui->lineEdit_Root->text());
  settings.setValue("Waiting", ui->spinBox_Waiting->text().toInt());
  settings.setValue("Loads", ui->spinBox_Loads->text().toInt());

  deleteLater();
}
