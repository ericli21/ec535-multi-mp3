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
signals:
	void correct();
public:
	explicit LockMenu(MainWindow *parent);
public slots:
	void auth();
private:
	QVBoxLayout *layout;
	int id;
};

#endif
