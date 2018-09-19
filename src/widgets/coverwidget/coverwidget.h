#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include "dataclasses/mediainfo.h"

#include <QNetworkAccessManager>
#include <QWidget>

namespace Ui {
class CoverWidget;
}

class CoverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverWidget(QWidget *parent = 0);
    ~CoverWidget();

    void setImage(MediaInfo& media);

private:
    QImage loadImage(const QString &link);

private:
    Ui::CoverWidget *ui;
    QNetworkAccessManager* m_nam;
    QStringList m_covers;
};

#endif // COVERWIDGET_H
