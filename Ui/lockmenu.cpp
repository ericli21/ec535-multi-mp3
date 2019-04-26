#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>

#include "lockmenu.h"

LockMenu::LockMenu(MainWindow *parent) : QWidget(parent) {
	//signalMapper = new QSignalMapper(this);
	//connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));
	id = 1;
	layout = new QVBoxLayout();
	setLayout(layout);
	QPushButton *button = new QPushButton("Log in via fingerprint", this);
	layout -> addWidget(button);
	connect(button, SIGNAL(released()), this, SLOT(auth()));
	connect(this, SIGNAL(correct()), parent, SLOT(goToMenu()));
	//nButtons = 0;
}

void LockMenu::auth() {
	id++;
	if (id == 2) {
		emit(correct());
	}
}
