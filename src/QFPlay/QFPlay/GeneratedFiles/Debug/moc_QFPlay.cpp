/****************************************************************************
** Meta object code from reading C++ file 'QFPlay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QFPlay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QFPlay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QFPlay_t {
    QByteArrayData data[6];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QFPlay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QFPlay_t qt_meta_stringdata_QFPlay = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QFPlay"
QT_MOC_LITERAL(1, 7, 4), // "open"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 4), // "play"
QT_MOC_LITERAL(4, 18, 11), // "sliderPress"
QT_MOC_LITERAL(5, 30, 13) // "sliderRelease"

    },
    "QFPlay\0open\0\0play\0sliderPress\0"
    "sliderRelease"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFPlay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QFPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QFPlay *_t = static_cast<QFPlay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->play(); break;
        case 2: _t->sliderPress(); break;
        case 3: _t->sliderRelease(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QFPlay::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QFPlay.data,
      qt_meta_data_QFPlay,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QFPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QFPlay.stringdata0))
        return static_cast<void*>(const_cast< QFPlay*>(this));
    return QWidget::qt_metacast(_clname);
}

int QFPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE