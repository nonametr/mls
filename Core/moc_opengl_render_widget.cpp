/****************************************************************************
** Meta object code from reading C++ file 'opengl_render_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/render/opengl_render_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'opengl_render_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLRenderWidget_t {
    QByteArrayData data[17];
    char stringdata[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GLRenderWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GLRenderWidget_t qt_meta_stringdata_GLRenderWidget = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 10),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 6),
QT_MOC_LITERAL(4, 34, 10),
QT_MOC_LITERAL(5, 45, 13),
QT_MOC_LITERAL(6, 59, 13),
QT_MOC_LITERAL(7, 73, 14),
QT_MOC_LITERAL(8, 88, 5),
QT_MOC_LITERAL(9, 94, 5),
QT_MOC_LITERAL(10, 100, 5),
QT_MOC_LITERAL(11, 106, 5),
QT_MOC_LITERAL(12, 112, 6),
QT_MOC_LITERAL(13, 119, 15),
QT_MOC_LITERAL(14, 135, 14),
QT_MOC_LITERAL(15, 150, 7),
QT_MOC_LITERAL(16, 158, 7)
    },
    "GLRenderWidget\0surfaceAdd\0\0string\0"
    "surfaceDel\0initMainScene\0frameReadyAll\0"
    "unsigned char*\0yuv_y\0yuv_u\0yuv_v\0width\0"
    "height\0surfaceSelected\0surface_handle\0"
    "paintGL\0calcFPS\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLRenderWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x05,
       4,    1,   52,    2, 0x05,
       5,    0,   55,    2, 0x05,
       6,    5,   56,    2, 0x05,
      13,    1,   67,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      15,    0,   70,    2, 0x09,
      16,    0,   71,    2, 0x09,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 7, QMetaType::UInt, QMetaType::UInt,    8,    9,   10,   11,   12,
    QMetaType::Void, 0x80000000 | 3,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GLRenderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLRenderWidget *_t = static_cast<GLRenderWidget *>(_o);
        switch (_id) {
        case 0: _t->surfaceAdd((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 1: _t->surfaceDel((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->initMainScene(); break;
        case 3: _t->frameReadyAll((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< unsigned char*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        case 4: _t->surfaceSelected((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 5: _t->paintGL(); break;
        case 6: _t->calcFPS(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GLRenderWidget::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLRenderWidget::surfaceAdd)) {
                *result = 0;
            }
        }
        {
            typedef void (GLRenderWidget::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLRenderWidget::surfaceDel)) {
                *result = 1;
            }
        }
        {
            typedef void (GLRenderWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLRenderWidget::initMainScene)) {
                *result = 2;
            }
        }
        {
            typedef void (GLRenderWidget::*_t)(unsigned char * , unsigned char * , unsigned char * , uint , uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLRenderWidget::frameReadyAll)) {
                *result = 3;
            }
        }
        {
            typedef void (GLRenderWidget::*_t)(string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GLRenderWidget::surfaceSelected)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject GLRenderWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GLRenderWidget.data,
      qt_meta_data_GLRenderWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *GLRenderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLRenderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLRenderWidget.stringdata))
        return static_cast<void*>(const_cast< GLRenderWidget*>(this));
    if (!strcmp(_clname, "IMqsRenderWidget"))
        return static_cast< IMqsRenderWidget*>(const_cast< GLRenderWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int GLRenderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GLRenderWidget::surfaceAdd(string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GLRenderWidget::surfaceDel(string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLRenderWidget::initMainScene()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GLRenderWidget::frameReadyAll(unsigned char * _t1, unsigned char * _t2, unsigned char * _t3, uint _t4, uint _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLRenderWidget::surfaceSelected(string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
