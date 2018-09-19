/****************************************************************************
** Meta object code from reading C++ file 'downloadhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/downloader/downloadhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DownloadHandler_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownloadHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownloadHandler_t qt_meta_stringdata_DownloadHandler = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DownloadHandler"
QT_MOC_LITERAL(1, 16, 10), // "readyReply"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 43, 16), // "downloadProgress"
QT_MOC_LITERAL(5, 60, 5), // "error"
QT_MOC_LITERAL(6, 66, 11), // "on_finished"
QT_MOC_LITERAL(7, 78, 4), // "href"
QT_MOC_LITERAL(8, 83, 19), // "on_downloadProgress"
QT_MOC_LITERAL(9, 103, 13), // "bytesReceived"
QT_MOC_LITERAL(10, 117, 10) // "bytesTotal"

    },
    "DownloadHandler\0readyReply\0\0QNetworkReply*\0"
    "downloadProgress\0error\0on_finished\0"
    "href\0on_downloadProgress\0bytesReceived\0"
    "bytesTotal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownloadHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       4,    3,   44,    2, 0x06 /* Public */,
       5,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   54,    2, 0x08 /* Private */,
       8,    2,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::LongLong,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    9,   10,

       0        // eod
};

void DownloadHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownloadHandler *_t = static_cast<DownloadHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyReply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QNetworkReply*(*)>(_a[2]))); break;
        case 1: _t->downloadProgress((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 2: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_finished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DownloadHandler::*_t)(QString , QNetworkReply * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownloadHandler::readyReply)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DownloadHandler::*_t)(const QString & , qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownloadHandler::downloadProgress)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DownloadHandler::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownloadHandler::error)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DownloadHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DownloadHandler.data,
      qt_meta_data_DownloadHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DownloadHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownloadHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadHandler.stringdata0))
        return static_cast<void*>(const_cast< DownloadHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int DownloadHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DownloadHandler::readyReply(QString _t1, QNetworkReply * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DownloadHandler::downloadProgress(const QString & _t1, qint64 _t2, qint64 _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DownloadHandler::error(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
