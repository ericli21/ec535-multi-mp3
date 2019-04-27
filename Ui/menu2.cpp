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
	id_count = 0;
	userButton = new QPushButton("Add a user", this);
	backButton = new QPushButton("Go back", this);
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();
	QLabel *message = new QLabel("Add a user", this);
	layout -> addWidget(message);
	layout2 -> addWidget(userButton);
	layout2 -> addWidget(backButton);
	layout -> addLayout(layout2);
	setLayout(layout);
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
	connect(userButton, SIGNAL(released()), this, SLOT(addUser()));

	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(userButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
}

void Menu2::addUser() {
	id_count++;
	int device = scanner_open();
	add_fingerprint(device, id_count, '1', 0);
}
