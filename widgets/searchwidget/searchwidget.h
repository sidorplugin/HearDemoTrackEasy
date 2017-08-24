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
    explicit SearchWidget(QWidget *parent = 0);

    void setData(const QVariant& data);
    QVariant data() const;

private slots:
    void setSearchGroupItem(int index);

private:
    Ui::SearchWidgetForm* ui;

};

#endif // SEARCHWIDGET_H
