/****************************************************************************
** Meta object code from reading C++ file 'iencoder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/encoder/iencoder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iencoder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IEncoder_t {
    QByteArrayData data[14];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_IEncoder_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_IEncoder_t qt_meta_stringdata_IEncoder = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 14),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5),
QT_MOC_LITERAL(4, 31, 4),
QT_MOC_LITERAL(5, 36, 8),
QT_MOC_LITERAL(6, 45, 21),
QT_MOC_LITERAL(7, 67, 11),
QT_MOC_LITERAL(8, 79, 14),
QT_MOC_LITERAL(9, 94, 5),
QT_MOC_LITERAL(10, 100, 5),
QT_MOC_LITERAL(11, 106, 5),
QT_MOC_LITERAL(12, 112, 5),
QT_MOC_LITERAL(13, 118, 6)
    },
    "IEncoder\0onFrameEncoded\0\0char*\0data\0"
    "data_len\0onChannelDisconnected\0"
    "encodeFrame\0unsigned char*\0yuv_y\0yuv_u\0"
    "yuv_v\0width\0height\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IEncoder[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    0,   34,    2, 0x0a,
       7,    5,   35,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 8, QMetaType::UInt, QMetaType::UInt,    9,   10,   11,   12,   13,

       0        // eod
};

void IEncoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IEncoder *_t = static_cast<IEncoder *>(_o);
        switch (_id) {
        case 0: _t->onFrameEncoded((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 1: _t->onChannelDisconnected(); break;
        case 2: _t->encodeFrame((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< unsigned char*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IEncoder::*_t)(char * , unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IEncoder::onFrameEncoded)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject IEncoder::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IEncoder.data,
      qt_meta_data_IEncoder,  qt_static_metacall, 0, 0}
};


const QMetaObject *IEncoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IEncoder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IEncoder.stringdata))
        return static_cast<void*>(const_cast< IEncoder*>(this));
    return QObject::qt_metacast(_clname);
}

int IEncoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void IEncoder::onFrameEncoded(char * _t1, unsigned int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
