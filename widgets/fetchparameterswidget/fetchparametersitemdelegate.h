#ifndef FETCHPARAMETERSITEMDELEGATE_H
#define FETCHPARAMETERSITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

// Класс FetchParametersItemDelegate представляет универсальный элемент делегата.
// Для редактирования ячейки предоставляются виджеты QComboBox и QDateEdit.

class FetchParametersItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  FetchParametersItemDelegate(QObject *parent);

  // Создает виджет для редактирования ячейки.
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  // Устанавливает данные в виджет из модели по индексу.
  void setEditorData(QWidget *editor, const QModelIndex &index) const;

  // Устанавливает данные из editor в модель по данному индексу.
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

  // Обновляет позицию делегата.
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;

private slots:
  // Обновляет модель и закрывает виджет-делегат.
  void closeAndCommitEditor();

};

#endif // FETCHPARAMETERSITEMDELEGATE_H
