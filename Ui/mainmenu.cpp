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
	my_Button = new QPushButton("Play", this);	
	previousButton = new QPushButton("Back", this);
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));

	//layout = new QHBoxLayout();
	layout = new QGridLayout();
	std::cout << "Test8\n";
	current_song = new QLabel("No song playing currently", this);
	current_artist = new QLabel(" ", this);
	current_album = new QLabel(" ", this);
	layout -> addWidget(current_song, 1, 0, 1, 1);
	layout -> addWidget(current_artist, 2, 0, 1, 1);
	layout -> addWidget(current_album, 3, 0, 1, 1);
	layout -> addWidget(previousButton, 0, 0, 1, 1);
	layout -> addWidget(my_Button, 0, 1, 1, 1);
	layout -> addWidget(skipButton, 0, 2, 1, 1);
	layout -> addWidget(backButton, 5, 0, 1, 3);
	std::cout << "Test9\n";
	setLayout(layout);
	connect(backButton, SIGNAL(released()), parent, SLOT(goToLock()));
	connect(my_Button, SIGNAL (released()), parent, SLOT(checkNodes()));

	connect(previousButton, SIGNAL (released()), parent, SLOT (checkPrev()));
	connect(skipButton, SIGNAL (released()), parent, SLOT (checkNext()));
	
	connect(this, SIGNAL(backSig()), parent, SLOT(backSong()));
	connect(this, SIGNAL(forwardSig()), parent, SLOT(forwardSong()));

	std::cout << "Test10\n";
	connect(signalMapper, SIGNAL (mapped(int)), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(my_Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(previousButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(skipButton, SIGNAL (released()), parent, SLOT (updateTimeout()));

	connect(parent, SIGNAL (notZero()), this, SLOT (handleButton()));
	connect(parent, SIGNAL (hasPrev()), this, SLOT (handlePrevious()));
	connect(parent, SIGNAL (hasNext()), this, SLOT (handleSkip()));	

	connect(this, SIGNAL (play_to_pause(int)), parent, SLOT(pauseSong(int)));
	connect(this, SIGNAL (pause_to_play(int)), parent, SLOT(playSong(int)));
	//connect(skipButton, SIGNAL (released()), parent SLOT (checkPriority()));
	//connect(previousButton, SIGNAL (released()), parent, SLOT (checkPriority()));

	connect(parent, SIGNAL(changeSongName(std::string,std::string,std::string)), this, SLOT(updateName(std::string,std::string,std::string)));

	//connect(parent, SIGNAL(noSong()), this, SLOT(correctState()));

	nButtons = 0;
}

void MainMenu::addButton(QString name) {
	nButtons += 1;
	QPushButton *button = new QPushButton(name, this);
	layout -> addWidget(button, 4, nButtons - 1, 1, 1);
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
	state = 1;
	my_Button->setText("Pause");
	emit backSig();
	//std::string nextSong = "blank";
	//std::string line = "ash speaker_interface.sh next ";
	//line += nextSong;
	//line += " &";
	//line <<  "ash speaker_interface.sh next " << nextSong << " &"; 
			
	//system(line.c_str());
}

void MainMenu::handleSkip() {
	state = 1;
	my_Button->setText("Pause");
	emit forwardSig();
	//std::string previousSong = "blank1";
	//std::string line = "ash speaker_interface.sh next ";
	//line += previousSong;
	//line += " &";
	//line <<  "ash speaker_interface.sh next " << previousSong << " &"; 
			
	//system(line.c_str());
}

void MainMenu::updateName(std::string songName, std::string artistName, std::string albumName) {
	current_song->setText(QString::fromStdString(songName));
	current_artist->setText(QString::fromStdString(artistName));
	current_album->setText(QString::fromStdString(albumName));
}

//void MainMenu::correctState() {
//	state = 0;
//	my_Button->setText("Play");
//}

