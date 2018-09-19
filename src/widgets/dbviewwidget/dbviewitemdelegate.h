#ifndef DBVIEWITEMDELEGATE_H
#define DBVIEWITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QDebug>
#include <QPainter>
#include <QProgressBar>
#include <QApplication>

class DbViewItemDelegate : public QStyledItemDelegate
{
  Q_OBJECT
public:
  DbViewItemDelegate(QObject * parent = 0);

  void paint(QPainter *painter,
             const QStyleOptionViewItem &option,
             const QModelIndex &index) const;


};

#endif // DBVIEWITEMDELEGATE_H
