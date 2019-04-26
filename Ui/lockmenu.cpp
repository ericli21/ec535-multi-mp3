#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>

#include "lockmenu.h"

LockMenu::LockMenu(MainWindow *parent) : QWidget(parent) {
	//signalMapper = new QSignalMapper(this);
	//connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));

	layout = new QVBoxLayout();
	setLayout(layout);
	QPushButton *button = new QPushButton("Go to menu", this);
	layout -> addWidget(button);
	connect(button, SIGNAL(released()), parent, SLOT(setpage(1)));

	//nButtons = 0;
}
