/****************************************************************************
** Meta object code from reading C++ file 'searchresultform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/forms/searchresultform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchresultform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchResultForm_t {
    QByteArrayData data[9];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchResultForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchResultForm_t qt_meta_stringdata_SearchResultForm = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SearchResultForm"
QT_MOC_LITERAL(1, 17, 10), // "addClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "QList<MediaInfo>"
QT_MOC_LITERAL(4, 46, 3), // "add"
QT_MOC_LITERAL(5, 50, 6), // "tracks"
QT_MOC_LITERAL(6, 57, 12), // "exportTracks"
QT_MOC_LITERAL(7, 70, 21), // "checkUncheckAllTracks"
QT_MOC_LITERAL(8, 92, 2) // "ok"

    },
    "SearchResultForm\0addClicked\0\0"
    "QList<MediaInfo>\0add\0tracks\0exportTracks\0"
    "checkUncheckAllTracks\0ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchResultForm[] = {

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
       4,    1,   37,    2, 0x0a /* Public */,
       6,    0,   40,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void SearchResultForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchResultForm *_t = static_cast<SearchResultForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addClicked((*reinterpret_cast< const QList<MediaInfo>(*)>(_a[1]))); break;
        case 1: _t->add((*reinterpret_cast< const QList<MediaInfo>(*)>(_a[1]))); break;
        case 2: _t->exportTracks(); break;
        case 3: _t->checkUncheckAllTracks((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<MediaInfo> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<MediaInfo> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SearchResultForm::*_t)(const QList<MediaInfo> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SearchResultForm::addClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SearchResultForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SearchResultForm.data,
      qt_meta_data_SearchResultForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SearchResultForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchResultForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SearchResultForm.stringdata0))
        return static_cast<void*>(const_cast< SearchResultForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int SearchResultForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SearchResultForm::addClicked(const QList<MediaInfo> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
