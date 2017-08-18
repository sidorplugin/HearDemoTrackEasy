/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[24];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 19), // "signal_stateChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "signal_pageFetched"
QT_MOC_LITERAL(4, 47, 11), // "signal_play"
QT_MOC_LITERAL(5, 59, 9), // "TrackInfo"
QT_MOC_LITERAL(6, 69, 10), // "slot_fetch"
QT_MOC_LITERAL(7, 80, 9), // "DataInput"
QT_MOC_LITERAL(8, 90, 4), // "data"
QT_MOC_LITERAL(9, 95, 9), // "slot_load"
QT_MOC_LITERAL(10, 105, 9), // "slot_play"
QT_MOC_LITERAL(11, 115, 3), // "row"
QT_MOC_LITERAL(12, 119, 11), // "slot_search"
QT_MOC_LITERAL(13, 131, 11), // "slot_cancel"
QT_MOC_LITERAL(14, 143, 16), // "slot_removeTrack"
QT_MOC_LITERAL(15, 160, 18), // "slot_clearDatabase"
QT_MOC_LITERAL(16, 179, 13), // "slot_copyLink"
QT_MOC_LITERAL(17, 193, 14), // "slot_copyTitle"
QT_MOC_LITERAL(18, 208, 13), // "slot_setState"
QT_MOC_LITERAL(19, 222, 5), // "state"
QT_MOC_LITERAL(20, 228, 22), // "slot_onModulesFinished"
QT_MOC_LITERAL(21, 251, 16), // "addTracksToModel"
QT_MOC_LITERAL(22, 268, 16), // "QList<TrackInfo>"
QT_MOC_LITERAL(23, 285, 6) // "tracks"

    },
    "Worker\0signal_stateChanged\0\0"
    "signal_pageFetched\0signal_play\0TrackInfo\0"
    "slot_fetch\0DataInput\0data\0slot_load\0"
    "slot_play\0row\0slot_search\0slot_cancel\0"
    "slot_removeTrack\0slot_clearDatabase\0"
    "slot_copyLink\0slot_copyTitle\0slot_setState\0"
    "state\0slot_onModulesFinished\0"
    "addTracksToModel\0QList<TrackInfo>\0"
    "tracks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    2,   92,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,  100,    2, 0x0a /* Public */,
       9,    1,  103,    2, 0x0a /* Public */,
      10,    1,  106,    2, 0x0a /* Public */,
      12,    1,  109,    2, 0x0a /* Public */,
      13,    0,  112,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    1,  117,    2, 0x0a /* Public */,
      17,    1,  120,    2, 0x0a /* Public */,
      18,    1,  123,    2, 0x0a /* Public */,
      20,    0,  126,    2, 0x0a /* Public */,
      21,    1,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signal_pageFetched((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signal_play((*reinterpret_cast< TrackInfo(*)>(_a[1]))); break;
        case 3: _t->slot_fetch((*reinterpret_cast< const DataInput(*)>(_a[1]))); break;
        case 4: _t->slot_load((*reinterpret_cast< const DataInput(*)>(_a[1]))); break;
        case 5: _t->slot_play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_search((*reinterpret_cast< const DataInput(*)>(_a[1]))); break;
        case 7: _t->slot_cancel(); break;
        case 8: _t->slot_removeTrack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slot_clearDatabase(); break;
        case 10: _t->slot_copyLink((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->slot_copyTitle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->slot_setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_onModulesFinished(); break;
        case 14: _t->addTracksToModel((*reinterpret_cast< const QList<TrackInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TrackInfo >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataInput >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataInput >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DataInput >(); break;
            }
            break;
        case 14:
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
            typedef void (Worker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::signal_stateChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (Worker::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::signal_pageFetched)) {
                *result = 1;
            }
        }
        {
            typedef void (Worker::*_t)(TrackInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::signal_play)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker.data,
      qt_meta_data_Worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(const_cast< Worker*>(this));
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Worker::signal_stateChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::signal_pageFetched(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::signal_play(TrackInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
