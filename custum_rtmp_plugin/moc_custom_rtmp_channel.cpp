/****************************************************************************
** Meta object code from reading C++ file 'custom_rtmp_channel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/custom_rtmp_channel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'custom_rtmp_channel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomRtmpChannel_t {
    QByteArrayData data[5];
    char stringdata[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CustomRtmpChannel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CustomRtmpChannel_t qt_meta_stringdata_CustomRtmpChannel = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 11),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 14),
QT_MOC_LITERAL(4, 46, 5)
    },
    "CustomRtmpChannel\0onFFmpegSay\0\0"
    "onFinishFFMPEG\0ecode\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomRtmpChannel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a,
       3,    1,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void CustomRtmpChannel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CustomRtmpChannel *_t = static_cast<CustomRtmpChannel *>(_o);
        switch (_id) {
        case 0: _t->onFFmpegSay(); break;
        case 1: _t->onFinishFFMPEG((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CustomRtmpChannel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CustomRtmpChannel.data,
      qt_meta_data_CustomRtmpChannel,  qt_static_metacall, 0, 0}
};


const QMetaObject *CustomRtmpChannel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomRtmpChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomRtmpChannel.stringdata))
        return static_cast<void*>(const_cast< CustomRtmpChannel*>(this));
    return QObject::qt_metacast(_clname);
}

int CustomRtmpChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
