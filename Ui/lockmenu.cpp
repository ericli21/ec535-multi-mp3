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
	QPushButton *button = new QPushButton("Log in via fingerprint", this);
	layout -> addWidget(button);
	connect(button, SIGNAL(released()), this, SLOT(authenticate(parent)));

	//nButtons = 0;
}

void LockMenu::authenticate(MainWindow *parent) {
	int auth = 1;
	if (auth == 1) {
		parent -> goToMenu();
	}
}