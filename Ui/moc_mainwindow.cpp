/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Apr 30 09:44:02 2019
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
      18,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,
      36,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   48,   11,   11, 0x0a,
      67,   11,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      89,   11,   11,   11, 0x0a,
     108,   11,   11,   11, 0x0a,
     127,   11,   11,   11, 0x0a,
     146,   11,   11,   11, 0x0a,
     162,   11,   11,   11, 0x0a,
     187,  178,   11,   11, 0x0a,
     215,  209,   11,   11, 0x0a,
     229,  209,   11,   11, 0x0a,
     244,   11,   11,   11, 0x0a,
     255,   11,   11,   11, 0x0a,
     269,   11,   11,   11, 0x0a,
     282,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0priority1()\0priority2()\0"
    "priority3()\0index\0setPage(int)\0"
    "goToMenu()\0goToLock()\0menuSetPriority1()\0"
    "menuSetPriority2()\0menuSetPriority3()\0"
    "checkPriority()\0updateTimeout()\0"
    "songName\0pushSong(std::string)\0state\0"
    "playSong(int)\0pauseSong(int)\0backSong()\0"
    "forwardSong()\0transition()\0tick()\0"
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
        case 3: setPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: goToMenu(); break;
        case 5: goToLock(); break;
        case 6: menuSetPriority1(); break;
        case 7: menuSetPriority2(); break;
        case 8: menuSetPriority3(); break;
        case 9: checkPriority(); break;
        case 10: updateTimeout(); break;
        case 11: pushSong((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 12: playSong((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: pauseSong((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: backSong(); break;
        case 15: forwardSong(); break;
        case 16: transition(); break;
        case 17: tick(); break;
        default: ;
        }
        _id -= 18;
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
QT_END_MOC_NAMESPACE
