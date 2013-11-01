/****************************************************************************
** Meta object code from reading C++ file 'gui_login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/gui/gui_login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MqsLogin_t {
    QByteArrayData data[6];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MqsLogin_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MqsLogin_t qt_meta_stringdata_MqsLogin = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 20),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 4),
QT_MOC_LITERAL(4, 36, 20),
QT_MOC_LITERAL(5, 57, 10)
    },
    "MqsLogin\0clickRecoverPassword\0\0link\0"
    "clickRegisterAccount\0clickLogin\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MqsLogin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a,
       4,    1,   32,    2, 0x0a,
       5,    0,   35,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

       0        // eod
};

void MqsLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MqsLogin *_t = static_cast<MqsLogin *>(_o);
        switch (_id) {
        case 0: _t->clickRecoverPassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->clickRegisterAccount((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->clickLogin(); break;
        default: ;
        }
    }
}

const QMetaObject MqsLogin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MqsLogin.data,
      qt_meta_data_MqsLogin,  qt_static_metacall, 0, 0}
};


const QMetaObject *MqsLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MqsLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MqsLogin.stringdata))
        return static_cast<void*>(const_cast< MqsLogin*>(this));
    return QWidget::qt_metacast(_clname);
}

int MqsLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
