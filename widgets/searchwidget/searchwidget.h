#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include "ui_searchform.h"
#include "dataclasses/moduleparameters.h"

#include <QObject>
#include <QWidget>

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    enum Key {
      Source,
      Group,
      Text
    };

    explicit SearchWidget(QWidget *parent = 0);

    void setData(int key, const QVariant& value);
    QVariant data(int key) const;



private slots:
    void setSearchGroupItem(int index);

private:
    Ui::SearchWidgetForm* ui;
    QMap<int, QVariant> m_data;

};

#endif // SEARCHWIDGET_H
