#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
	
#include "menu2.h"
#include "mainwindow.h"

Menu2::Menu2(MainWindow *parent) : QWidget(parent)
{	
	backButton = new QPushButton("GO BACK", this);

	QVBoxLayout *layout = new QVBoxLayout();
	QLabel *message = new QLabel("Select a song", this);
	layout -> addWidget(message);
	layout -> addWidget(backButton);
	setLayout(layout);

	connect(backButton, SIGNAL(released()), parent, SLOT(goToMenu()));
}
