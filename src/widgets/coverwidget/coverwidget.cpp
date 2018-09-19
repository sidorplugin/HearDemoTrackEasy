#include "coverwidget.h"
#include "ui_coverwidget.h"

#include <QNetworkReply>
#include <QEventLoop>
#include <QImage>

CoverWidget::CoverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverWidget)
{
    ui->setupUi(this);

    m_nam = new QNetworkAccessManager(this);

    ui->cover1->setScaledContents(true);
    ui->cover2->setScaledContents(true);
}

CoverWidget::~CoverWidget()
{
    delete ui;
    delete m_nam;
}


void CoverWidget::setImage(MediaInfo& media)
{
    // Отображает обложку альбома.
    QStringList covers = media.data(MediaInfo::Images).toString().split(";");

    if (covers.isEmpty()) return;

    QString firstSavedCover;
    if (!m_covers.isEmpty()) {
        firstSavedCover = m_covers.at(0);
    }

    if (firstSavedCover != covers.at(0)) {
        m_covers = covers;
        for (int i = 0; i < covers.count(); i++) {
            // Скачивает изображение.
            QImage image = loadImage(covers.at(i));
            // Устанавливает image на позицию pos.
            if (i == 0) {
                ui->cover1->clear();
                ui->cover1->setPixmap(QPixmap::fromImage(image));
            }
            else {
                ui->cover2->clear();
                ui->cover2->setPixmap(QPixmap::fromImage(image));
            }
        }
    }
}


QImage CoverWidget::loadImage(const QString &link)
{
    qDebug() << "loadImage(" << link << ")";

    QImage image;
    QNetworkReply* reply = m_nam->get(QNetworkRequest(QUrl(link)));

    QEventLoop eventloop;
    connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
    eventloop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if ((statusCode == 301) || (statusCode == 302) ||(statusCode == 307)) {
            QUrl redirectUrl =
                reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            reply->deleteLater();
            image = loadImage(redirectUrl.toString());
        }
        else {
            QByteArray ba = reply->readAll();
            if (!image.loadFromData(ba))
                qDebug() << "error load from data ";
        }
    }
    else {
        qDebug() << "error: " << reply->error();
    }

    reply->deleteLater();
    return image;

}
