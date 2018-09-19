#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "dataclasses/datainput.h"
#include "baseclasses/module.h"

#include <QDialog>

namespace Ui {
  class SearchDialog;
}

class SearchDialog : public QDialog
{
  Q_OBJECT
  // TODO : для доступа из UI. Задание значений полям из контекстного меню Базы треков.
  Q_PROPERTY(QString text READ text WRITE setText)


public:
  explicit SearchDialog(const QHash <QString, Module*>& modules, QWidget *parent = 0);
  ~SearchDialog();

  void setText(const QString& text);
  QString text() const;

signals:
    // Сигнализирует о готовности к поиску.
    void okPressed(const InputPack&);

protected:
  void changeEvent(QEvent *e);

private slots:
  void populateGroupBySource(int index);
  // Проверяет правильность ввода параметров поиска.
  void on_accepted();

private:
    bool validate(const InputPack& pack);

private:
  Ui::SearchDialog *ui;
  QHash <QString, Module*> m_modules;
};

#endif // SEARCHDIALOG_H
