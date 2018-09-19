/****************************************************************************
** Meta object code from reading C++ file 'filtertableheader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/widgets/dbviewwidget/filtertableheader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filtertableheader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FilterTableHeader_t {
    QByteArrayData data[12];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FilterTableHeader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FilterTableHeader_t qt_meta_stringdata_FilterTableHeader = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FilterTableHeader"
QT_MOC_LITERAL(1, 18, 13), // "filterChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "column"
QT_MOC_LITERAL(4, 40, 5), // "value"
QT_MOC_LITERAL(5, 46, 15), // "generateFilters"
QT_MOC_LITERAL(6, 62, 6), // "number"
QT_MOC_LITERAL(7, 69, 15), // "adjustPositions"
QT_MOC_LITERAL(8, 85, 12), // "clearFilters"
QT_MOC_LITERAL(9, 98, 9), // "setFilter"
QT_MOC_LITERAL(10, 108, 12), // "inputChanged"
QT_MOC_LITERAL(11, 121, 9) // "new_value"

    },
    "FilterTableHeader\0filterChanged\0\0"
    "column\0value\0generateFilters\0number\0"
    "adjustPositions\0clearFilters\0setFilter\0"
    "inputChanged\0new_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FilterTableHeader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   49,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x0a /* Public */,
       9,    2,   54,    2, 0x0a /* Public */,
      10,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void FilterTableHeader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FilterTableHeader *_t = static_cast<FilterTableHeader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->filterChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->generateFilters((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->adjustPositions(); break;
        case 3: _t->clearFilters(); break;
        case 4: _t->setFilter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->inputChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FilterTableHeader::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FilterTableHeader::filterChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject FilterTableHeader::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_FilterTableHeader.data,
      qt_meta_data_FilterTableHeader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FilterTableHeader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FilterTableHeader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FilterTableHeader.stringdata0))
        return static_cast<void*>(const_cast< FilterTableHeader*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int FilterTableHeader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FilterTableHeader::filterChanged(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
