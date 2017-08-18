#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
  class Preferences;
}

class Preferences : public QDialog
{
  Q_OBJECT

public:
  explicit Preferences(QWidget *parent = 0);
  ~Preferences();

protected:
  void changeEvent(QEvent *e);

private slots:
  void save();

private:
  Ui::Preferences *ui;
  int m_delay;
  int m_loads;
  int m_waiting;
  QString m_root;
};

#endif // PREFERENCES_H
