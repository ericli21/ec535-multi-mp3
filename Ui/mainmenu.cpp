#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>

#include "mainmenu.h"

MainMenu::MainMenu(MainWindow *parent) : QWidget(parent) {
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));

	layout = new QVBoxLayout();
	setLayout(layout);

	nButtons = 0;
}

void MainMenu::addButton(QString name) {
	nButtons += 1;
	QPushButton *button = new QPushButton(name, this);
	layout -> addWidget(button);
	signalMapper -> setMapping(button, nButtons);
	connect(button, SIGNAL(released()), signalMapper, SLOT(map()));
}
