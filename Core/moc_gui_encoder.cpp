/****************************************************************************
** Meta object code from reading C++ file 'gui_encoder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/gui/gui_encoder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_encoder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MqsEncoder_t {
    QByteArrayData data[5];
    char stringdata[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MqsEncoder_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MqsEncoder_t qt_meta_stringdata_MqsEncoder = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 22),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 9),
QT_MOC_LITERAL(4, 45, 13)
    },
    "MqsEncoder\0updateEncodersListView\0\0"
    "okClicked\0cancelClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MqsEncoder[] = {

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
       1,    0,   29,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a,
       4,    0,   31,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MqsEncoder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MqsEncoder *_t = static_cast<MqsEncoder *>(_o);
        switch (_id) {
        case 0: _t->updateEncodersListView(); break;
        case 1: _t->okClicked(); break;
        case 2: _t->cancelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MqsEncoder::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MqsEncoder::updateEncodersListView)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MqsEncoder::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MqsEncoder.data,
      qt_meta_data_MqsEncoder,  qt_static_metacall, 0, 0}
};


const QMetaObject *MqsEncoder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MqsEncoder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MqsEncoder.stringdata))
        return static_cast<void*>(const_cast< MqsEncoder*>(this));
    return QWidget::qt_metacast(_clname);
}

int MqsEncoder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MqsEncoder::updateEncodersListView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
