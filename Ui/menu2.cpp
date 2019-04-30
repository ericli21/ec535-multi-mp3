#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
	
#include "menu2.h"
#include "mainwindow.h"
extern "C" {
  #include "UART.h" //a C header, so wrap it in extern "C" 
}

Menu2::Menu2(MainWindow *parent) : QWidget(parent)
{	
	std::cout << "Test18\n";
	id_count = 0;
	user1Button = new QPushButton("Priority 1", this);
	user2Button = new QPushButton("Priority 2", this);
	backButton = new QPushButton("Go back", this);
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();
	QLabel *message = new QLabel("Add a user", this);
	std::cout << "Test19\n";
	layout -> addWidget(message);
	std::cout << "Test19a\n";
	layout2 -> addWidget(user1Button);
	std::cout << "Test19b\n";
	layout2 -> addWidget(user2Button);
	std::cout << "Test19c\n";
	layout2 -> addWidget(backButton);
	std::cout << "Test19d\n";
	layout -> addLayout(layout2);
	std::cout << "Test19e\n";
	setLayout(layout);
	std::cout << "Test20\n";
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
	connect(user1Button, SIGNAL(released()), this, SLOT(addUser1()));
	connect(user2Button, SIGNAL(released()), this, SLOT(addUser2()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(user1Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(user2Button, SIGNAL (released()), parent, SLOT (updateTimeout()));
}

void Menu2::addUser1() {
	id_count++;
	int device = scanner_open();
	add_fingerprint(device, id_count, '1', 0);
}

void Menu2::addUser2() {
	id_count++;
	int device = scanner_open();
	add_fingerprint(device, id_count, '2', 0);
}
