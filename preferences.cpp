#include "globaldata.h"
#include "preferences.h"
#include "ui_preferencesForm.h"

Preferences::Preferences(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Preferences)
{
  ui->setupUi(this);

  // Загружает глобальные настройки и отображает их в виджете.
  GlobalData::getInstance()->readGlobalSettings();
  ui->lineEdit_Delay->setText(QString::number(GlobalData::getInstance()->delay));
  ui->lineEdit_Waiting->setText(QString::number(GlobalData::getInstance()->waiting));
  ui->lineEdit_Loads->setText(QString::number(GlobalData::getInstance()->loads));
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
  m_delay = ui->lineEdit_Delay->text().toInt();
  m_loads = ui->lineEdit_Loads->text().toInt();
  m_waiting = ui->lineEdit_Waiting->text().toInt();
  m_root = ui->lineEdit_Root->text();

  GlobalData::getInstance()->setGlobalSettings(m_root, m_delay, m_waiting, m_loads);
}
