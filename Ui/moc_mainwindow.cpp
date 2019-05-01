/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed May 1 19:36:34 2019
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,
      36,   11,   11,   11, 0x05,
      51,   48,   11,   11, 0x05,
     103,   11,   11,   11, 0x05,
     113,   11,   11,   11, 0x05,
     123,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     139,  133,   11,   11, 0x0a,
     152,   11,   11,   11, 0x0a,
     163,   11,   11,   11, 0x0a,
     174,   11,   11,   11, 0x0a,
     193,   11,   11,   11, 0x0a,
     212,   11,   11,   11, 0x0a,
     231,   11,   11,   11, 0x0a,
     247,   11,   11,   11, 0x0a,
     272,  263,   11,   11, 0x0a,
     300,  294,   11,   11, 0x0a,
     314,  294,   11,   11, 0x0a,
     329,   11,   11,   11, 0x0a,
     340,   11,   11,   11, 0x0a,
     354,   11,   11,   11, 0x0a,
     367,   11,   11,   11, 0x0a,
     374,   11,   11,   11, 0x0a,
     387,   11,   11,   11, 0x0a,
     399,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0priority1()\0priority2()\0"
    "priority3()\0,,\0"
    "changeSongName(std::string,std::string,std::string)\0"
    "notZero()\0hasPrev()\0hasNext()\0index\0"
    "setPage(int)\0goToMenu()\0goToLock()\0"
    "menuSetPriority1()\0menuSetPriority2()\0"
    "menuSetPriority3()\0checkPriority()\0"
    "updateTimeout()\0songName\0pushSong(std::string)\0"
    "state\0playSong(int)\0pauseSong(int)\0"
    "backSong()\0forwardSong()\0transition()\0"
    "tick()\0checkNodes()\0checkPrev()\0"
    "checkNext()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: priority1(); break;
        case 1: priority2(); break;
        case 2: priority3(); break;
        case 3: changeSongName((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 4: notZero(); break;
        case 5: hasPrev(); break;
        case 6: hasNext(); break;
        case 7: setPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: goToMenu(); break;
        case 9: goToLock(); break;
        case 10: menuSetPriority1(); break;
        case 11: menuSetPriority2(); break;
        case 12: menuSetPriority3(); break;
        case 13: checkPriority(); break;
        case 14: updateTimeout(); break;
        case 15: pushSong((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 16: playSong((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: pauseSong((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: backSong(); break;
        case 19: forwardSong(); break;
        case 20: transition(); break;
        case 21: tick(); break;
        case 22: checkNodes(); break;
        case 23: checkPrev(); break;
        case 24: checkNext(); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::priority1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::priority2()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::priority3()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::changeSongName(std::string _t1, std::string _t2, std::string _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::notZero()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainWindow::hasPrev()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MainWindow::hasNext()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
