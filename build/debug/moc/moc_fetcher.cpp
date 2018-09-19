/****************************************************************************
** Meta object code from reading C++ file 'fetcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/baseclasses/fetcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fetcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Fetcher_t {
    QByteArrayData data[9];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fetcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fetcher_t qt_meta_stringdata_Fetcher = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Fetcher"
QT_MOC_LITERAL(1, 8, 10), // "signalLoad"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 3), // "url"
QT_MOC_LITERAL(4, 24, 8), // "finished"
QT_MOC_LITERAL(5, 33, 7), // "stopped"
QT_MOC_LITERAL(6, 41, 5), // "fetch"
QT_MOC_LITERAL(7, 47, 14), // "QNetworkReply*"
QT_MOC_LITERAL(8, 62, 5) // "reply"

    },
    "Fetcher\0signalLoad\0\0url\0finished\0"
    "stopped\0fetch\0QNetworkReply*\0reply"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fetcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void Fetcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fetcher *_t = static_cast<Fetcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLoad((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->finished(); break;
        case 2: _t->stopped(); break;
        case 3: _t->fetch((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Fetcher::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fetcher::signalLoad)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Fetcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fetcher::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Fetcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fetcher::stopped)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject Fetcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Fetcher.data,
      qt_meta_data_Fetcher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fetcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fetcher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fetcher.stringdata0))
        return static_cast<void*>(const_cast< Fetcher*>(this));
    return QObject::qt_metacast(_clname);
}

int Fetcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Fetcher::signalLoad(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Fetcher::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Fetcher::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
