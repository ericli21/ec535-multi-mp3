#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <string>

#include "mainmenu.h"

MainMenu::MainMenu(MainWindow *parent) : QWidget(parent) {
	backButton = new QPushButton("Log out", this);
	skipButton = new QPushButton("Forward", this);
	my_Button = new QPushButton("Pause", this);	
	previousButton = new QPushButton("Back", this);
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));
	

	//layout = new QHBoxLayout();
	layout = new QGridLayout();
	
	QLabel *message = new QLabel("Main Menu", this);
	layout -> addWidget(message, 0, 0, 1, 1);
	layout -> addWidget(previousButton, 3, 0, 1, 1);
	layout -> addWidget(my_Button, 3, 1, 1, 1);
	layout -> addWidget(skipButton, 3, 2, 1, 1);
	layout -> addWidget(backButton, 1, 0, 1, 1);

	setLayout(layout);

	connect(backButton, SIGNAL(released()), parent, SLOT(goToLock()));
	connect(my_Button, SIGNAL (released()), this, SLOT (handleButton()));
	connect(previousButton, SIGNAL (released()), this, SLOT (handlePrevious()));
	connect(skipButton, SIGNAL (released()), this, SLOT (handleSkip()));

	nButtons = 0;
}

void MainMenu::addButton(QString name) {
	nButtons += 1;
	QPushButton *button = new QPushButton(name, this);
	layout -> addWidget(button, 2, nButtons - 1, 1, 1);
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
	std::string nextSong = "blank";
	std::string line = "ash speaker_interface.sh next ";
	line += nextSong;
	line += " &";
	//line <<  "ash speaker_interface.sh next " << nextSong << " &"; 
			
	system(line.c_str());
}

void MainMenu::handleSkip() {
	std::string previousSong = "blank1";
	std::string line = "ash speaker_interface.sh next ";
	line += previousSong;
	line += " &";
	//line <<  "ash speaker_interface.sh next " << previousSong << " &"; 
			
	system(line.c_str());
}
