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

//Main Menu shows up after first logging into the device
MainMenu::MainMenu(MainWindow *parent) : QWidget(parent) {

	//Initial state of the MP3 player is paused (no songs playing)
	state = 0;

	//Initialize buttons for logging out, next song, previous song, and pause/play
	backButton = new QPushButton("Log out", this);
	skipButton = new QPushButton("Forward", this);
	my_Button = new QPushButton("Play", this);	
	previousButton = new QPushButton("Back", this);

	//Initialize a signalmapper for going to the correct page depending on the button
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));

	//Initialize layout and display currently playing song (+ artist and album)
	//No song is playing initially
	layout = new QGridLayout();
	current_song = new QLabel("No song playing currently", this);
	current_artist = new QLabel(" ", this);
	current_album = new QLabel(" ", this);

	//Add buttons in a grid style layout (widget, row, column, row length, column length)
	layout -> addWidget(current_song, 1, 0, 1, 1);
	layout -> addWidget(current_artist, 2, 0, 1, 1);
	layout -> addWidget(current_album, 3, 0, 1, 1);
	layout -> addWidget(previousButton, 0, 0, 1, 1);
	layout -> addWidget(my_Button, 0, 1, 1, 1);
	layout -> addWidget(skipButton, 0, 2, 1, 1);
	layout -> addWidget(backButton, 5, 0, 1, 3);
	setLayout(layout);

	//Back (logout) button triggers MainWindow to switch
	connect(backButton, SIGNAL(released()), parent, SLOT(goToLock()));

	//Pause/play button triggers MainWindow to check if there are songs in the queue. If there are, we call handleButton to emit a signal to MainWindow to play or pause a song.
	connect(my_Button, SIGNAL (released()), parent, SLOT(checkNodes()));
	connect(parent, SIGNAL (notZero()), this, SLOT (handleButton()));
	connect(this, SIGNAL (play_to_pause(int)), parent, SLOT(pauseSong(int)));
	connect(this, SIGNAL (pause_to_play(int)), parent, SLOT(playSong(int)));

	//Previous button triggers MainWindow to check if is a Node (song) in the queue before the current Node (song). If there is, call backSig to emit a signal to MainWindow to play the previous song.
	//Set state to 1 as the previous song will play regardless of paused or playing state
	connect(previousButton, SIGNAL (released()), parent, SLOT (checkPrev()));
	connect(parent, SIGNAL (hasPrev()), this, SLOT (handlePrevious()));
	connect(this, SIGNAL(backSig()), parent, SLOT(backSong()));

	//Skip button triggers MainWindow to check if is a Node (song) in the queue after the current Node (song). If there is, call forwardSig to emit a signal to MainWindow to play the previous song.
	//Set state to 1 as the next song will play regardless of paused or playing state
	connect(skipButton, SIGNAL (released()), parent, SLOT (checkNext()));
	connect(parent, SIGNAL (hasNext()), this, SLOT (handleSkip()));	
	connect(this, SIGNAL(forwardSig()), parent, SLOT(forwardSong()));

	//For all buttons pressed, refresh the user timeout in MainWindow
	connect(signalMapper, SIGNAL (mapped(int)), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(my_Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(previousButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(skipButton, SIGNAL (released()), parent, SLOT (updateTimeout()));

	//MainWindow may emit a signal when a song (+info) has changed. When it does, call updateName to update the song descriptions in the display
	connect(parent, SIGNAL(changeSongName(std::string,std::string,std::string)), this, SLOT(updateName(std::string,std::string,std::string)));

	//For intially setting up Menu1 (add a song) and Menu2 (add a user)
	nButtons = 0;
}

//Add a button (that leads to another menu) to the main menu, and map these buttons to the correct pages
void MainMenu::addButton(QString name) {
	nButtons += 1;
	QPushButton *button = new QPushButton(name, this);
	layout -> addWidget(button, 4, nButtons - 1, 1, 1);
	signalMapper -> setMapping(button, nButtons);
	connect(button, SIGNAL(released()), signalMapper, SLOT(map()));
}

//Check the state of the MP3 player, and emit the correct signal to switch from pause to play or vice versa. Also, change the state variable and button text display when doing so.
void MainMenu::handleButton()
{
	if (state) {
		emit play_to_pause(state);
		state = 0;
		my_Button->setText("Play");
	}
	else {
		emit pause_to_play(state);
		state = 1;
		my_Button->setText("Pause");
	}
}

//Set state to playing (and displaying a pause button), and emit backSig to go to previous song
void MainMenu::handlePrevious() {
	state = 1;
	my_Button->setText("Pause");
	emit backSig();
}

//Set state to playing (and displaying a pause button), and emit forwardSig to go to next song
void MainMenu::handleSkip() {
	state = 1;
	my_Button->setText("Pause");
	emit forwardSig();
}

//Update the song name, artist name, and album name in the display
void MainMenu::updateName(std::string songName, std::string artistName, std::string albumName) {
	current_song->setText(QString::fromStdString(songName));
	current_artist->setText(QString::fromStdString(artistName));
	current_album->setText(QString::fromStdString(albumName));
}
