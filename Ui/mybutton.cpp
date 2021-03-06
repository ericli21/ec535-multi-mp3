#include "mybutton.h"
 
#include <QCoreApplication>
 
//Button prototype, not used or called in Ui
MyButton::MyButton(QWidget *parent)
	: QWidget(parent)
{
	// Create the button, make "this" the parent
	my_button = new QPushButton("Pause", this);
	int state = 1;

	// Set size and location of the button
	my_button->setGeometry(QRect(QPoint(100, 100),
	QSize(200, 50)));
 
	// Connect button signal to appropriate slot
	connect(my_button, SIGNAL (released()), this, SLOT (handleButton(state)));
}
 
//Handle switching between Play and Pause buttons
void MyButton::handleButton(int state)
{
	// Change the text
	if (state) {
		my_button->setText("Play");
	}
	else {
		my_button->setText("Pause");
	}

	//Update the state
	state = ~state;
}
