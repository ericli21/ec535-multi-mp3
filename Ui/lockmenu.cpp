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
	//signalMapper = new QSignalMapper(this);
	//connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));
	id = 1;
	layout = new QVBoxLayout();
	setLayout(layout);
	current_song = new QLabel("No song playing currently", this);
	current_artist = new QLabel(" ", this);
	current_album = new QLabel(" ", this);
	QPushButton *button = new QPushButton("Log in via fingerprint", this);
	layout -> addWidget(current_song);
	layout -> addWidget(current_artist);
	layout -> addWidget(current_album);
	layout -> addWidget(button);
	connect(button, SIGNAL(released()), this, SLOT(auth()));
	connect(this, SIGNAL(correct1()), parent, SLOT(menuSetPriority1()));
	connect(this, SIGNAL(correct2()), parent, SLOT(menuSetPriority2()));
	connect(this, SIGNAL(correct3()), parent, SLOT(menuSetPriority3()));

	connect(this, SIGNAL(correct1()), parent, SLOT(updateTimeout()));
	connect(this, SIGNAL(correct2()), parent, SLOT(updateTimeout()));
	connect(this, SIGNAL(correct3()), parent, SLOT(updateTimeout()));


	connect(parent, SIGNAL(changeSongName(std::string,std::string,std::string)), this, SLOT(updateName(std::string,std::string,std::string)));
	
	//nButtons = 0;
}

void LockMenu::auth() {

	id++;
	int device = scanner_open();
	//delete_user(device, 0);
	//add_fingerprint(device, 15, 0x02, 0);
	int level = authenticate_user(device, 0);
	printf("Level: %d\n", level);

	int num_users = get_user_number(device);
	printf("Num users: %d\n", num_users);

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

void LockMenu::updateName(std::string songName, std::string artistName, std::string albumName) {
	current_song->setText(QString::fromStdString(songName));
	current_artist->setText(QString::fromStdString(artistName));
	current_album->setText(QString::fromStdString(albumName));
}
