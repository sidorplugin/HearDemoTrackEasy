#include "dbviewitemdelegate.h"

DbViewItemDelegate::DbViewItemDelegate(QObject* parent)
{
}

void DbViewItemDelegate::paint(QPainter* painter,
                               const QStyleOptionViewItem& option,
                               const QModelIndex& index) const
{
  if (!index.isValid())
    return;

  painter->save();
  int value = index.data(Qt::AccessibleTextRole).toInt();

  QStyleOptionProgressBar opt;
  opt.state = option.state;
  opt.direction = option.direction;
  opt.rect = option.rect;
  opt.fontMetrics = option.fontMetrics;  
  opt.palette = option.palette;
  opt.minimum = 0;
  opt.maximum = 100;
  opt.rect = option.rect;
  opt.progress = value;
  opt.textAlignment = Qt::AlignLeft;
  opt.textVisible = true;
  opt.text = index.data(Qt::DisplayRole).toString();

  QProgressBar bar;
  QApplication::style()->drawControl(QStyle::CE_ProgressBar, &opt, painter, &bar);

  painter->restore();

}
