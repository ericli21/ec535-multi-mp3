#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QSignalMapper>
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
	//Initialize buttons, listWidget to display songs, layouts
	addButton = new QPushButton("Add a song", this);
	backButton = new QPushButton("Menu", this);
	QListWidget *listWidget = new QListWidget(this);
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();

	//Search directory for songs
	//If there is an mp3, display it on the listWidget
	QDir fdir("/media/card/songs/");
	QStringList allSongs = fdir.entryList();
	for (int i = 0; i < allSongs.size(); ++i) {
		if(strstr(qPrintable(allSongs.at(i)), ".mp3") != NULL) {
			QListWidgetItem *newItem = new QListWidgetItem;
			newItem->setText(qPrintable(allSongs.at(i)));
			listWidget->insertItem(i, newItem);
		}
	}

	//Set up layout
	QLabel *message = new QLabel("Choose a song", this);
	layout -> addWidget(message);
	layout -> addWidget(listWidget);
	layout2 -> addWidget(addButton);
	layout2 -> addWidget(backButton);
	layout -> addLayout(layout2);
	setLayout(layout);

	//Update currently selected song
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotTest(QListWidgetItem*)));

	//Map signals from add and back buttons to correct 
	connect(addButton, SIGNAL(released()), this, SLOT(confirmSong()));
	connect(this, SIGNAL(addSong(std::string)), parent, SLOT(pushSong(std::string)));
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));

	//Update timeout once a button or scroll through the list has been activated
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), parent, SLOT(updateTimeout()));
	connect(addButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
}

//Set selected variable as the selected song from listWidget
void Menu1::slotTest(QListWidgetItem* song) {
	selected = qPrintable(song->text());
}

//Confirm that the song is just a empty string
void Menu1::confirmSong() {
	if (!selected.empty()) {
		std::cout << selected << "added to queue.\n";
		emit addSong(selected);
	}
	else {
		std::cout << "please touch a song (don't drag your finger)\n";
	}
}
