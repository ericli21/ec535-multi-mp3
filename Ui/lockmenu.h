#ifndef LOCKMENU_H
#define LOCKMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSignalMapper>

#include "mainwindow.h"

namespace Ui {
	class LockMenu;
}

class LockMenu : public QWidget
{
	Q_OBJECT
public:
	explicit LockMenu(MainWindow *parent);	
private:
	QVBoxLayout *layout;
};

#endif
