#ifndef FETCHDIALOG_H
#define FETCHDIALOG_H

#include "dataclasses/moduleparameters.h"
#include "dataclasses/datainput.h"
#include "baseclasses/module.h"

#include <QDialog>

namespace Ui {
class FetchDialog;
}

class FetchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FetchDialog(const QHash <QString, Module*>& modules, QWidget *parent = 0);
    ~FetchDialog();

signals:
    // Сигнализирует о готовности к выборке.
    void okPressed(const InputPack&);

private slots:
    // Обновляет данные в полях диалога по id источника.
    void updateUI(int sourceId);
    // Проверяет правильность ввода параметров выборки.
    void on_accepted();

private:
    bool validate(const InputPack& pack);

private:
    Ui::FetchDialog *ui;
    QHash <QString, Module*> m_modules;
};


#endif // FETCHDIALOG_H
