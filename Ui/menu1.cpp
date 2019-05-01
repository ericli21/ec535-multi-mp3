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
	std::cout << "Test11\n";
	addButton = new QPushButton("Add a song", this);
	backButton = new QPushButton("Menu", this);

	QListWidget *listWidget = new QListWidget(this);
	
	std::cout << "Test12\n";
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();
	QDir fdir("/media/card/songs/");
	QStringList allSongs = fdir.entryList();
	for (int i = 0; i < allSongs.size(); ++i) {
		std::cout << qPrintable(allSongs.at(i)) << "\n";
		if(strstr(qPrintable(allSongs.at(i)), ".mp3") != NULL) {
			//if (qPrintable(allSongs.at(i)) != ".." || qPrintable(allSongs.at(i)) != ".") {
			QListWidgetItem *newItem = new QListWidgetItem;
			newItem->setText(qPrintable(allSongs.at(i)));
			listWidget->insertItem(i, newItem);
		}
	}
	std::cout << "Test13\n";
	QLabel *message = new QLabel("Play a song", this);
	layout -> addWidget(message);
	layout -> addWidget(listWidget);
	

	std::cout << "Test14\n";
	layout2 -> addWidget(addButton);
	layout2 -> addWidget(backButton);
	layout -> addLayout(layout2);
	setLayout(layout);

	std::cout << "Test15\n";
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotTest(QListWidgetItem*)));


	connect(addButton, SIGNAL(released()), this, SLOT(confirmSong()));
	connect(this, SIGNAL(addSong(std::string)), parent, SLOT(pushSong(std::string)));
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));

	std::cout << "Test17\n";
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), parent, SLOT(updateTimeout()));
	connect(addButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));

}


void Menu1::slotTest(QListWidgetItem* song) {
	selected = qPrintable(song->text());
}

void Menu1::confirmSong() {
	std::cout << selected << "added to queue.\n";
	emit addSong(selected);
}
