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
    foreach (ModuleParameters p, parameters) {
        int id = p.data(ModuleParameters::Id).toInt();
        QString name = p.data(ModuleParameters::Name).toString();
        QString icon = p.data(ModuleParameters::Icon).toString();
        QStringList searchGroups =
            p.data(ModuleParameters::SearchGroups).toStringList();
        ui->comboBox_Source->addItem(QIcon(icon), name, searchGroups);
    }

    connect(ui->comboBox_Source, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setSearchGroupItem(int)));

}

void SearchWidget::setData(int key, const QVariant &value)
{
  m_data.insert(key, value);
}

QVariant SearchWidget::data(int key) const
{
  return m_data.value(key);
}

void SearchWidget::setSearchGroupItem(int index)
{
    ui->comboBox_Group->clear();
    QStringList groups = ui->comboBox_Source->itemData(index).toStringList();
    foreach (QString group, groups) {
        ui->comboBox_Group->addItem(group);
    }
}

