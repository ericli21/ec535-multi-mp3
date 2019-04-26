#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "mainmenu.h"

MainMenu::MainMenu(MainWindow *parent) : QWidget(parent) {
	backButton = new QPushButton("Log out", this);
	skipButton = new QPushButton("Forward", this);
	my_Button = new QPushButton("Pause", this);	
	previousButton = new QPushButton("Back", this);
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));
	

	layout = new QVBoxLayout();
	QLabel *message = new QLabel("Main Menu", this);
	layout -> addWidget(message);
	layout -> addWidget(previousButton);
	layout -> addWidget(my_Button);
	layout -> addWidget(skipButton);
	layout -> addWidget(backButton);

	setLayout(layout);

	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
	connect(my_Button, SIGNAL (released()), this, SLOT (handleButton()));
	connect(previousButton, SIGNAL (released()), this, SLOT (handlePrevious()));
	connect(skipButton, SIGNAL (released()), this, SLOT (handleSkip()));

	nButtons = 0;
}

void MainMenu::addButton(QString name) {
	nButtons += 1;
	QPushButton *button = new QPushButton(name, this);
	layout -> addWidget(button);
	signalMapper -> setMapping(button, nButtons);
	connect(button, SIGNAL(released()), signalMapper, SLOT(map()));
}

void MainMenu::handleButton()
{
	// change the text
	if (state) {
		my_Button->setText("Play");
		system("ash speaker_interface.sh pause &");
		state = 0;
		//QCoreApplication::processEvents();
	}
	else {
		my_Button->setText("Pause");
		system("ash speaker_interface.sh play &");
		state = 1;
		//QCoreApplication::processEvents();
	}
	// resize button
	//my_button->resize(100,100);
}

void MainMenu::handlePrevious() {

}

void MainMenu::handleSkip() {
	
}
