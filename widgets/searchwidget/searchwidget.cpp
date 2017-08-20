#include "searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    m_searchUi = new Ui::SearchWidgetForm;
    m_searchUi->setupUi(this);
}

