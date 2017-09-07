#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>

class AlbumModel : public QSqlRelationalTableModel
{
public:
  AlbumModel();
};

#endif // ALBUMMODEL_H
