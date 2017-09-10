#include "coverwidget.h"
#include "ui_coverwidget.h"

#include <QNetworkReply>

CoverWidget::CoverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverWidget)
{
    ui->setupUi(this);

    m_nam = new QNetworkAccessManager(this);

    ui->label_Image1->setScaledContents(true);
    ui->label_Image2->setScaledContents(true);
}

CoverWidget::~CoverWidget()
{
    delete ui;
    delete m_nam;
}


// Устанавливает изображение по link на позицию pos.
void CoverWidget::setImage(int pos, const QString &link)
{
    ui->label_Image1->clear();
    ui->label_Image2->clear();

    // Скачивает изображение по link.
    QImage image = loadImage(link);


    // Устанавливает image на позицию pos.
    pos == 0 ? ui->label_Image1->setPixmap(QPixmap::fromImage(image)) :
               ui->label_Image2->setPixmap(QPixmap::fromImage(image));

}

QImage CoverWidget::loadImage(const QString &link)
{
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
