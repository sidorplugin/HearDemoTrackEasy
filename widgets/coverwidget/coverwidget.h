#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class CoverWidget;
}

class CoverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverWidget(QWidget *parent = 0);
    ~CoverWidget();

    // Устанавливает изображение по link на позицию pos.
    void setImage(int pos, const QString& link);

private:
    QImage loadImage(const QString &link);

private:
    Ui::CoverWidget *ui;
    QNetworkAccessManager* m_nam;
};

#endif // COVERWIDGET_H
