/****************************************************************************
** Meta object code from reading C++ file 'dbviewwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/dbviewwidget/dbviewwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbviewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DbViewWidget_t {
    QByteArrayData data[11];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DbViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DbViewWidget_t qt_meta_stringdata_DbViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DbViewWidget"
QT_MOC_LITERAL(1, 13, 13), // "executeAction"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "DbViewWidget::Action"
QT_MOC_LITERAL(4, 49, 6), // "action"
QT_MOC_LITERAL(5, 56, 8), // "setState"
QT_MOC_LITERAL(6, 65, 5), // "state"
QT_MOC_LITERAL(7, 71, 29), // "on_customContextMenuRequested"
QT_MOC_LITERAL(8, 101, 8), // "position"
QT_MOC_LITERAL(9, 110, 10), // "sendAction"
QT_MOC_LITERAL(10, 121, 2) // "id"

    },
    "DbViewWidget\0executeAction\0\0"
    "DbViewWidget::Action\0action\0setState\0"
    "state\0on_customContextMenuRequested\0"
    "position\0sendAction\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DbViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a /* Public */,
       7,    1,   40,    2, 0x08 /* Private */,
       9,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QPoint,    8,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void DbViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DbViewWidget *_t = static_cast<DbViewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->executeAction((*reinterpret_cast< DbViewWidget::Action(*)>(_a[1]))); break;
        case 1: _t->setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_customContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->sendAction((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DbViewWidget::*_t)(DbViewWidget::Action );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DbViewWidget::executeAction)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject DbViewWidget::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_DbViewWidget.data,
      qt_meta_data_DbViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DbViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DbViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DbViewWidget.stringdata0))
        return static_cast<void*>(const_cast< DbViewWidget*>(this));
    return QTableView::qt_metacast(_clname);
}

int DbViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DbViewWidget::executeAction(DbViewWidget::Action _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
