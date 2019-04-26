/****************************************************************************
** Meta object code from reading C++ file 'mainmenu.h'
**
** Created: Fri Apr 26 12:18:45 2019
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainMenu[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x0a,
      34,    9,    9,    9, 0x0a,
      49,    9,    9,    9, 0x0a,
      62,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainMenu[] = {
    "MainMenu\0\0name\0addButton(QString)\0"
    "handleButton()\0handleSkip()\0"
    "handlePrevious()\0"
};

const QMetaObject MainMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainMenu,
      qt_meta_data_MainMenu, 0 }
};

const QMetaObject *MainMenu::metaObject() const
{
    return &staticMetaObject;
}

void *MainMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainMenu))
        return static_cast<void*>(const_cast< MainMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addButton((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: handleButton(); break;
        case 2: handleSkip(); break;
        case 3: handlePrevious(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
