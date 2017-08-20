#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include "ui_searchform.h"

#include <QObject>
#include <QWidget>

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);

signals:

public slots:

private:
    Ui::SearchWidgetForm* m_searchUi;

};

#endif // SEARCHWIDGET_H
