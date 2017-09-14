#include "filtertableheader.h"
#include "filterlineedit.h"

#include <QApplication>
#include <QTableView>
#include <QScrollBar>

FilterTableHeader::FilterTableHeader(QTableView* parent) :
    QHeaderView(Qt::Horizontal, parent)
{
    setSectionsClickable(true);
    setSortIndicatorShown(true);

    connect(this, SIGNAL(sectionResized(int,int,int)),
            this, SLOT(adjustPositions()));

    connect(parent->horizontalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(adjustPositions()));

    connect(parent->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(adjustPositions()));

}


// Создает виджеты фильтры QLineEdit в количестве number.
void FilterTableHeader::generateFilters(int number)
{
    qDeleteAll(filterWidgets);
    filterWidgets.clear();

    for (int i = 0; i < number; ++i) {
        FilterLineEdit* l = new FilterLineEdit(this, &filterWidgets, i);
        l->setVisible(true);

        connect(l, SIGNAL(delayedTextChanged(QString)),
                this, SLOT(inputChanged(QString)));

        filterWidgets.push_back(l);
    }

    adjustPositions();
}


// Возвращает размер Header'а с учетом виджета QLineEdit.
QSize FilterTableHeader::sizeHint() const
{
    QSize s = QHeaderView::sizeHint();

    if (filterWidgets.size())
        s.setHeight(s.height() + filterWidgets.at(0)->sizeHint().height() + 5);

    return s;
}


// Обновляет положение Header'а и виджета фильтра. Устанавливает margins.
void FilterTableHeader::updateGeometries()
{
    if (filterWidgets.size())
        setViewportMargins(0, 0, 0, filterWidgets.at(0)->sizeHint().height());
    else
        setViewportMargins(0, 0, 0, 0);

    QHeaderView::updateGeometries();
    adjustPositions();
}


// Устанавливает позицию виджетов фильтров.
void FilterTableHeader::adjustPositions()
{
    for (int i = 0; i < filterWidgets.size(); ++i) {
        // Перемещает и изменяет размер у виджета.
        QWidget* w = filterWidgets.at(i);
        if (QApplication::layoutDirection() == Qt::RightToLeft)
            w->move(width() - (sectionPosition(i) + sectionSize(i) - offset()),
                    w->sizeHint().height() + 2);
        else
            w->move(sectionPosition(i) - offset(), w->sizeHint().height() + 2);
        w->resize(sectionSize(i), w->sizeHint().height());
    }
}


// Слот срабатывающий когда в виджете фильтре изменен текст (с задержкой).
void FilterTableHeader::inputChanged(const QString& new_value)
{
    emit filterChanged(sender()->property("column").toInt(), new_value);
}


// Очищает текст в фильтрах.
void FilterTableHeader::clearFilters()
{
    foreach (FilterLineEdit* filterLineEdit, filterWidgets)
        filterLineEdit->clear();
}


// Устанавливает текст value в фильтре столбца column.
void FilterTableHeader::setFilter(int column, const QString& value)
{
    if(column < filterWidgets.size())
        filterWidgets.at(column)->setText(value);
}
