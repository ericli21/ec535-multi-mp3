/****************************************************************************
** Meta object code from reading C++ file 'menu2.h'
**
** Created: Wed May 1 20:14:05 2019
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "menu2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menu2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Menu2[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      18,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Menu2[] = {
    "Menu2\0\0addUser1()\0addUser2()\0"
};

const QMetaObject Menu2::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Menu2,
      qt_meta_data_Menu2, 0 }
};

const QMetaObject *Menu2::metaObject() const
{
    return &staticMetaObject;
}

void *Menu2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Menu2))
        return static_cast<void*>(const_cast< Menu2*>(this));
    return QWidget::qt_metacast(_clname);
}

int Menu2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addUser1(); break;
        case 1: addUser2(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
