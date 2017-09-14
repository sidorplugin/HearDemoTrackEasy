#ifndef FILTERTABLEHEADER_H
#define FILTERTABLEHEADER_H

#include <QHeaderView>
#include <QList>

class QLineEdit;
class QTableView;
class FilterLineEdit;

class FilterTableHeader : public QHeaderView
{
    Q_OBJECT

public:
    explicit FilterTableHeader(QTableView* parent = 0);
    // Возвращает размер Header'а с учетом виджета QLineEdit.
    QSize sizeHint() const;
    
public slots:
    // Создает виджеты фильтры QLineEdit в количестве number.
    void generateFilters(int number);
    // Устанавливает позицию виджетов фильтров.
    void adjustPositions();
    // Очищает текст в фильтрах.
    void clearFilters();
    // Устанавливает текст value в фильтре столбца column.
    void setFilter(int column, const QString& value);

signals:
    // Текст фильтра колонки column изменен на значение value.
    void filterChanged(int column, QString value);

protected:
    // Обновляет положение Header'а и виджета фильтра. Устанавливает margins.
    void updateGeometries();

private slots:
    // Слот срабатывающий когда в виджете фильтре изменен текст (с задержкой).
    void inputChanged(const QString& new_value);

private:
    QList<FilterLineEdit*> filterWidgets;
};

#endif
