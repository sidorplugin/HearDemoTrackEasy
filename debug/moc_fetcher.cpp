/****************************************************************************
** Meta object code from reading C++ file 'fetcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../baseclasses/fetcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fetcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fetcher_t {
    QByteArrayData data[12];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fetcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fetcher_t qt_meta_stringdata_Fetcher = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Fetcher"
QT_MOC_LITERAL(1, 8, 7), // "fetched"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 14), // "Fetcher::State"
QT_MOC_LITERAL(4, 32, 5), // "ready"
QT_MOC_LITERAL(5, 38, 16), // "QList<TrackInfo>"
QT_MOC_LITERAL(6, 55, 6), // "result"
QT_MOC_LITERAL(7, 62, 2), // "ok"
QT_MOC_LITERAL(8, 65, 8), // "progress"
QT_MOC_LITERAL(9, 74, 10), // "on_started"
QT_MOC_LITERAL(10, 85, 11), // "on_finished"
QT_MOC_LITERAL(11, 97, 10) // "on_timeOut"

    },
    "Fetcher\0fetched\0\0Fetcher::State\0ready\0"
    "QList<TrackInfo>\0result\0ok\0progress\0"
    "on_started\0on_finished\0on_timeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fetcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   55,    2, 0x09 /* Protected */,
       8,    1,   58,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    1,   62,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,

       0        // eod
};

void Fetcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fetcher *_t = static_cast<Fetcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fetched((*reinterpret_cast< Fetcher::State(*)>(_a[1]))); break;
        case 1: _t->ready((*reinterpret_cast< const QList<TrackInfo>(*)>(_a[1]))); break;
        case 2: _t->result((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_started(); break;
        case 5: _t->on_finished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_timeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<TrackInfo> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Fetcher::*_t)(Fetcher::State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fetcher::fetched)) {
                *result = 0;
            }
        }
        {
            typedef void (Fetcher::*_t)(const QList<TrackInfo> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Fetcher::ready)) {
                *result = 1;
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Fetcher::fetched(Fetcher::State _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Fetcher::ready(const QList<TrackInfo> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
