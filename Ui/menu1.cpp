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
	//skipButton = new QPushButton("Forward", this);
	//my_Button = new QPushButton("Pause", this);	
	//previousButton = new QPushButton("Back", this);
	QListWidget *listWidget = new QListWidget(this);
	
	//state = 0;
	std::cout << "Test12\n";
	QVBoxLayout *layout = new QVBoxLayout();
	QHBoxLayout *layout2 = new QHBoxLayout();
	QDir fdir("/media/card/songs/");
	QStringList allSongs = fdir.entryList();
	for (int i = 0; i < allSongs.size(); ++i) {
		std::cout << qPrintable(allSongs.at(i)) << "\n";
		QListWidgetItem *newItem = new QListWidgetItem;
		newItem->setText(qPrintable(allSongs.at(i)));
		listWidget->insertItem(i, newItem);
		//listWidget->addItem(qPrintable(allSongs.at(i)));
	}
	std::cout << "Test13\n";
	QLabel *message = new QLabel("Play a song", this);
	layout -> addWidget(message);
	layout -> addWidget(listWidget);
	
	//layout -> addWidget(previousButton);
	//layout -> addWidget(my_Button);
	//layout -> addWidget(skipButton);
	std::cout << "Test14\n";
	layout2 -> addWidget(addButton);
	layout2 -> addWidget(backButton);
	layout -> addLayout(layout2);
	setLayout(layout);
	//QSignalMapper* signalMapper = new QSignalMapper (this) ;
	std::cout << "Test15\n";
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotTest(QListWidgetItem*)));
	//connect(addButton, SIGNAL(released()), this, SLOT(addSong()));
	//connect(addButton, SIGNAL(released()), signalMapper, SLOT(map()));
	std::cout << "Test16\n";
	//signalMapper -> setMapping (addButton, QString::fromStdString(selected));
	//connect(signalMapper, SIGNAL(mapped(const QString &)), parent, SLOT(pushSong(const QString &)));
	connect(addButton, SIGNAL(released()), this, SLOT(confirmSong()));
	connect(this, SIGNAL(addSong(std::string)), parent, SLOT(pushSong(std::string)));
	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));

	std::cout << "Test17\n";
	connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), parent, SLOT(updateTimeout()));
	connect(addButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	connect(backButton, SIGNAL (released()), parent, SLOT (updateTimeout()));
	//connect(my_Button, SIGNAL (released()), this, SLOT (handleButton()));
	//connect(previousButton, SIGNAL (released()), this, SLOT (handlePrevious()));
	//connect(skipButton, SIGNAL (released()), this, SLOT (handleSkip()));
}


void Menu1::slotTest(QListWidgetItem* song) {
	selected = qPrintable(song->text());
//	std::cout << qPrintable(song->text()) << "\n";
}

void Menu1::confirmSong() {
	std::cout << selected << "added to queue.\n";
	emit addSong(selected);
}
