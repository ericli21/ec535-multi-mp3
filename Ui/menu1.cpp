#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
	
#include "menu1.h"
#include "mainwindow.h"

Menu1::Menu1(MainWindow *parent) : QWidget(parent)
{	
	backButton = new QPushButton("Go Back", this);

	QVBoxLayout *layout = new QVBoxLayout();
	QLabel *message = new QLabel("Goodbye", this);
	layout -> addWidget(message);
	layout -> addWidget(backButton);
	setLayout(layout);

	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
}
