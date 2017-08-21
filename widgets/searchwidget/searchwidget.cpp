#include "searchwidget.h"
#include "globaldata.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::SearchWidgetForm;
    ui->setupUi(this);

    // Берет информацию о модулях из глобальных данных.
    QList<ModuleParameters> parameters = GlobalData::getInstance()->parameters;

    ui->comboBox_Source->addItem(QIcon(":/images_ui/images/all.png"), "All",
                                 QStringList("All"));
    ui->comboBox_Group->addItem("All");
    foreach (ModuleParameters parameter, parameters) {
        int id = parameter.id();
        QString name = parameter.name();
        QString icon = parameter.icon();
        QStringList searchGroups = parameter.searchGroups();
        ui->comboBox_Source->addItem(QIcon(icon), name, searchGroups);
    }


    connect(ui->comboBox_Source, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setSearchGroupItem(int)));
}


QVariant SearchWidget::getData() const
{
  QStringList data;
  data << ui->comboBox_Source->currentText() <<
          ui->comboBox_Group->currentText() <<
          ui->lineEdit->text();

  return data;
}


void SearchWidget::setSearchGroupItem(int index)
{
    ui->comboBox_Group->clear();
    QStringList groups = ui->comboBox_Source->itemData(index).toStringList();
    foreach (QString group, groups) {
        ui->comboBox_Group->addItem(group);
    }
}

