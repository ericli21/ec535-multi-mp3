#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <QCoreApplication>
	
#include "menu2.h"
#include "mainwindow.h"
extern "C" {
  #include "UART.h"
}

Menu2::Menu2(MainWindow *parent) : QWidget(parent)
{	
	//Initialize buttons to be used, as well as the message and layout
	user1Button = new QPushButton("Priority 1", this);
	user2Button = new QPushButton("Priority 2", this);
	backButton = new QPushButton("Go back", this);
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();
	message = new QLabel("Add a user", this);
	std::cout << "TestMenu2a\n";

	//Add message and buttons to the layout
	layout -> addWidget(message);
	layout2 -> addWidget(user1Button);
	layout2 -> addWidget(user2Button);
	layout2 -> addWidget(backButton);
	layout -> addLayout(layout2);
	setLayout(layout);
	std::cout << "TestMenu2b\n";

	//Connect the buttons to their respective functions
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
	connect(user1Button, SIGNAL(released()), this, SLOT(addUser1()));
	connect(user2Button, SIGNAL(released()), this, SLOT(addUser2()));

	//Pressing buttons will reset the timeout time back to 30 sec
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(user1Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(user2Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
}

//Add a user with priority 1 by calling add_fingerprint, increment the user ID
void Menu2::addUser1() {
	message -> setText("Please keep your finger on the scanner for at least 3 seconds.");
	QCoreApplication::processEvents();
	int device = scanner_open();
	int id_count = get_user_number(device);
	add_fingerprint(device, id_count + 1, 0x01, 0);
	//Once done, go back to original message
	std::cout << "Added user" << id_count + 1 << "\n";
	message -> setText("Add a user");
	QCoreApplication::processEvents();
}

//Add a user with priority 2 by calling add_fingerprint, increment the user ID
void Menu2::addUser2() {
	message -> setText("Please keep your finger on the scanner for at least 3 seconds.");
	QCoreApplication::processEvents();
	int device = scanner_open();
	int id_count = get_user_number(device);
	add_fingerprint(device, id_count + 1, 0x02, 0);
	//Once done, go back to original message
	std::cout << "Added user" << id_count + 1 << "\n";
	message -> setText("Add a user");
	QCoreApplication::processEvents();
}
