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
#include <iostream>



#include "mainmenu.h"

MainMenu::MainMenu(MainWindow *parent) : QWidget(parent) {
	std::cout << "Test7\n";
	state = 0;
	backButton = new QPushButton("Log out", this);
	skipButton = new QPushButton("Forward", this);
	my_Button = new QPushButton("Pause", this);	
	previousButton = new QPushButton("Back", this);
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));

	//layout = new QHBoxLayout();
	layout = new QGridLayout();
	std::cout << "Test8\n";
	QLabel *message = new QLabel("Main Menu", this);
	layout -> addWidget(message, 1, 0, 1, 1);
	layout -> addWidget(previousButton, 0, 0, 1, 1);
	layout -> addWidget(my_Button, 0, 1, 1, 1);
	layout -> addWidget(skipButton, 0, 2, 1, 1);
	layout -> addWidget(backButton, 3, 0, 1, 3);
	std::cout << "Test9\n";
	setLayout(layout);
	connect(backButton, SIGNAL(released()), parent, SLOT(goToLock()));
	connect(my_Button, SIGNAL (released()), this, SLOT (handleButton()));
	connect(previousButton, SIGNAL (released()), parent, SLOT (backSong()));
	connect(skipButton, SIGNAL (released()), parent, SLOT (forwardSong()));
	std::cout << "Test10\n";
	connect(signalMapper, SIGNAL (mapped(int)), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(my_Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(previousButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(skipButton, SIGNAL (released()), parent, SLOT (updateTimeout()));

	connect(this, SIGNAL (play_to_pause(int)), parent, SLOT(pauseSong(int)));
	connect(this, SIGNAL (pause_to_play(int)), parent, SLOT(playSong(int)));
	//connect(skipButton, SIGNAL (released()), parent SLOT (checkPriority()));
	//connect(previousButton, SIGNAL (released()), parent, SLOT (checkPriority()));

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
		
		//system("ash speaker_interface.sh pause &");
		emit play_to_pause(state);

		state = 0;
		my_Button->setText("Play");
		//QCoreApplication::processEvents();
	}
	else {
		//system("ash speaker_interface.sh play &");
		emit pause_to_play(state);
	
		state = 1;
		my_Button->setText("Pause");
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
