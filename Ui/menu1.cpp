#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDir>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
	
#include "menu1.h"
#include "mainwindow.h"

Menu1::Menu1(MainWindow *parent) : QWidget(parent)
{	
	if (parent->priority < 2) {
		std::cout << "Cannot access\n";
		return;
	} else {
		std::cout << "Accessed\n";
	}
		
	backButton = new QPushButton("Menu", this);
	//skipButton = new QPushButton("Forward", this);
	//my_Button = new QPushButton("Pause", this);	
	//previousButton = new QPushButton("Back", this);
	QListWidget *listWidget = new QListWidget(this);
	
	//state = 0;
	QVBoxLayout *layout = new QVBoxLayout();
	QDir fdir("/media/card/songs/");
	QStringList allSongs = fdir.entryList();
	for (int i = 0; i < allSongs.size(); ++i) {
		std::cout << qPrintable(allSongs.at(i)) << "\n";
		QListWidgetItem *newItem = new QListWidgetItem;
		newItem->setText(qPrintable(allSongs.at(i)));
		listWidget->insertItem(i, newItem);
		//listWidget->addItem(qPrintable(allSongs.at(i)));
	}
	QLabel *message = new QLabel("Play a song", this);
	layout -> addWidget(message);
	layout -> addWidget(listWidget);
	//layout -> addWidget(previousButton);
	//layout -> addWidget(my_Button);
	//layout -> addWidget(skipButton);
	layout -> addWidget(backButton);
	setLayout(layout);

	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
	//connect(my_Button, SIGNAL (released()), this, SLOT (handleButton()));
	//connect(previousButton, SIGNAL (released()), this, SLOT (handlePrevious()));
	//connect(skipButton, SIGNAL (released()), this, SLOT (handleSkip()));
}

void Menu1::handleButton()
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

void Menu1::handlePrevious() {

}

void Menu1::handleSkip() {
	
}
