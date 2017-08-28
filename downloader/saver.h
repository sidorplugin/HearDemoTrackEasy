#ifndef SAVER_H
#define SAVER_H

#include "dataclasses/trackinfo.h"
#include "downloader/idtagcreator.h"

#include <QObject>
#include <QDebug>
#include <QDate>

// Класс сохраняет "сырой" поток данных в файл на диск, снабжая его тегами.

class Saver : public QObject
{
    Q_OBJECT
public:
    Saver(QObject *parent = 0);

    // Сохраняет данные bytes c данными data в папку root.
    void save(const QByteArray& bytes, TrackInfo& track, const QString& root);

signals:
    // Сигнал об успешном сохранении.
    void saved(TrackInfo&);

private:
    // Строит путь сохранения файла.
    QString buildSavePath(TrackInfo& track, const QString& root);
    // Создает тэг.
    QByteArray createTag(TrackInfo& track);
    // Возвращает валидное имя файла.
    QString getValidFileName(const QString& name);

private:
    // Генератор тегов.
    IdTagCreator m_tagCreator;


};

#endif // SAVER_H
