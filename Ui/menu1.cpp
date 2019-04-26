#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
	
#include "menu1.h"
#include "mainwindow.h"

Menu1::Menu1(MainWindow *parent) : QWidget(parent)
{	
	backButton = new QPushButton("Menu", this);
	//skipButton = new QPushButton("Forward", this);
	//my_Button = new QPushButton("Pause", this);	
	//previousButton = new QPushButton("Back", this);
	
	//state = 0;
	QHBoxLayout *layout = new QHBoxLayout();
	QLabel *message = new QLabel("Play a song", this);
	layout -> addWidget(message);
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