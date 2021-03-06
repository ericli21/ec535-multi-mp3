#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QLabel>

#include "lockmenu.h"
extern "C" {
  #include "UART.h" //a C header, so wrap it in extern "C" 
}


//Authenticate user menu screen
LockMenu::LockMenu(MainWindow *parent) : QWidget(parent) {

	//ID not used, but kept in just in case we want to increment ID numbers when adding users
	id = 1;

	//Initialize layout
	layout = new QVBoxLayout();
	setLayout(layout);

	//Song information labels
	current_song = new QLabel("No song playing currently", this);
	current_artist = new QLabel(" ", this);
	current_album = new QLabel(" ", this);

	//Log in button
	QPushButton *button = new QPushButton("Log in via fingerprint", this);

	//Add items to layout
	layout -> addWidget(current_song);
	layout -> addWidget(current_artist);
	layout -> addWidget(current_album);
	layout -> addWidget(button);

	//Signal handling: authenticate a user after pressing log in button
	connect(button, SIGNAL(released()), this, SLOT(auth()));

	//Based on each button, go to the main menu with the correct priority
	connect(this, SIGNAL(correct1()), parent, SLOT(menuSetPriority1()));
	connect(this, SIGNAL(correct2()), parent, SLOT(menuSetPriority2()));
	connect(this, SIGNAL(correct3()), parent, SLOT(menuSetPriority3()));

	//Update timeout timer
	connect(this, SIGNAL(correct1()), parent, SLOT(updateTimeout()));
	connect(this, SIGNAL(correct2()), parent, SLOT(updateTimeout()));
	connect(this, SIGNAL(correct3()), parent, SLOT(updateTimeout()));

	//If there is a song change in MainWindow, detect the signal and update the song information display
	connect(parent, SIGNAL(changeSongName(std::string,std::string,std::string)), this, SLOT(updateName(std::string,std::string,std::string)));
}

//Function to check authentication from scanner
void LockMenu::auth() {

	//ID not used, but kept in just in case we want to increment ID numbers when adding users
	id++;

	//Communicate with UART
	int device = scanner_open();

	//Check authentication against all registered users
	int level = authenticate_user(device, 0);

	//If the user level (priority) returned was valid
	if (level > 0 && level < 4) {
		if (level == 1) {
			emit(correct1());
		}
		else if (level == 2) {
			emit(correct2());
		}
		else if (level == 3) {
			emit(correct3());
		}
 		else {
			//Do nothing (shouldn't get here)
		}
	}
}

//Set display information
void LockMenu::updateName(std::string songName, std::string artistName, std::string albumName) {
	current_song->setText(QString::fromStdString(songName));
	current_artist->setText(QString::fromStdString(artistName));
	current_album->setText(QString::fromStdString(albumName));
}
