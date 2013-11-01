/****************************************************************************
** Meta object code from reading C++ file 'rtmp_proxy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/rtmp_proxy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rtmp_proxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RtmpProxy_t {
    QByteArrayData data[5];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_RtmpProxy_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_RtmpProxy_t qt_meta_stringdata_RtmpProxy = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 14),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 18),
QT_MOC_LITERAL(4, 45, 15)
    },
    "RtmpProxy\0readRtmpServer\0\0newProxyConnection\0"
    "readProxyClient\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RtmpProxy[] = {

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
       1,    0,   29,    2, 0x09,
       3,    0,   30,    2, 0x09,
       4,    0,   31,    2, 0x09,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RtmpProxy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RtmpProxy *_t = static_cast<RtmpProxy *>(_o);
        switch (_id) {
        case 0: _t->readRtmpServer(); break;
        case 1: _t->newProxyConnection(); break;
        case 2: _t->readProxyClient(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RtmpProxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RtmpProxy.data,
      qt_meta_data_RtmpProxy,  qt_static_metacall, 0, 0}
};


const QMetaObject *RtmpProxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RtmpProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RtmpProxy.stringdata))
        return static_cast<void*>(const_cast< RtmpProxy*>(this));
    return QObject::qt_metacast(_clname);
}

int RtmpProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
