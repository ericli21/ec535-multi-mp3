/****************************************************************************
** Meta object code from reading C++ file 'mainmenu.h'
**
** Created: Wed May 1 20:27:02 2019
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
       9,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      29,    9,    9,    9, 0x05,
      48,    9,    9,    9, 0x05,
      58,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   71,    9,    9, 0x0a,
      95,    9,    9,    9, 0x0a,
     110,    9,    9,    9, 0x0a,
     123,    9,    9,    9, 0x0a,
     170,  140,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainMenu[] = {
    "MainMenu\0\0play_to_pause(int)\0"
    "pause_to_play(int)\0backSig()\0forwardSig()\0"
    "name\0addButton(QString)\0handleButton()\0"
    "handleSkip()\0handlePrevious()\0"
    "songName,artistName,albumName\0"
    "updateName(std::string,std::string,std::string)\0"
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
        case 0: play_to_pause((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pause_to_play((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: backSig(); break;
        case 3: forwardSig(); break;
        case 4: addButton((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: handleButton(); break;
        case 6: handleSkip(); break;
        case 7: handlePrevious(); break;
        case 8: updateName((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainMenu::play_to_pause(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainMenu::pause_to_play(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainMenu::backSig()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainMenu::forwardSig()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
