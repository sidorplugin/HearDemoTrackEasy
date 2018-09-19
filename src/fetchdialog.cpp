#include "fetchdialog.h"
#include "ui_fetchdialog.h"

#include <QDebug>
#include <QMessageBox>

FetchDialog::FetchDialog(const QHash <QString, Module*>& modules, QWidget *parent) :
    QDialog(parent),
    m_modules(modules),
    ui(new Ui::FetchDialog)
{
    ui->setupUi(this);

    setProperty("modal", true);

    foreach (Module* module, m_modules) {
        ui->source->addItem(QIcon(module->parameters().data(ModuleParameters::Icon).toString()),
                                  module->parameters().data(ModuleParameters::Name).toString());
    }

    ui->dateStart->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    ui->dateEnd->setDate(QDate::currentDate());

    connect(ui->source, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateUI(int)));

    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(on_accepted()));

    connect(ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(close()));

    updateUI(0);
}


FetchDialog::~FetchDialog()
{
  delete ui;
}


// Обновляет данные в полях диалога по id источника.
void FetchDialog::updateUI(int sourceId)
{
    ui->style->clear();
    ui->period->clear();
    ui->filter->clear();
    if (sourceId <= m_modules.size()) {
        ModuleParameters mp = m_modules.value(ui->source->currentText())->parameters();
        bool isContainsDatePeriod = mp.data(ModuleParameters::isContainsDatePeriod).toBool();
        ui->dateStart->setEnabled(isContainsDatePeriod);
        ui->dateEnd->setEnabled(isContainsDatePeriod);
        ui->dateStart->setEnabled(false);
        ui->dateEnd->setEnabled(false);
        ui->style->addItems(mp.data(ModuleParameters::Styles).toMap().keys());
        ui->period->addItems(mp.data(ModuleParameters::Periods).toMap().keys());
        ui->filter->addItems(mp.data(ModuleParameters::Filters).toMap().keys());
    }
}

// Проверяет правильность ввода параметров выборки.
void FetchDialog::on_accepted()
{
    InputPack input;
    input.fetchPack.source = ui->source->currentText();
    input.fetchPack.dateStart = ui->dateStart->date();
    input.fetchPack.dateEnd = ui->dateEnd->date();
    input.fetchPack.style = ui->style->currentText();
    input.fetchPack.period = ui->period->currentText();
    input.fetchPack.filter = ui->filter->currentText();

    if (validate(input)) {
            emit okPressed(input);
            deleteLater();
    }
    else
      QMessageBox::warning(this, "Предупреждение",
                                 "Не правильно заданы параметры для выборки.\n"
                                 "Возможно вы забыли указать значение Жанра, "
                                 "Периода, Фильтра или указали параметры в избытке");
}


bool FetchDialog::validate(const InputPack& pack)
{
    // TODO.
    return true;
}
