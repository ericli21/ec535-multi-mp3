//Qt Includes
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QLabel>
#include <QMainWindow>
#include <QTextStream>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAbstractButton>
#include "mainwindow.h"

//Misc includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

//Run QT
int main(int argc, char * argv[]){

	//System calls needed to initialize project
	system("rm temp.txt");
	system("touch temp.txt");
	
	//Start QApplication
	QApplication app(argc, argv);

	//Variable declarations
  	QWidget w;
	QString info;
  	QPalette p = w.palette();
	QLabel * label = new QLabel(&w);

	//Set object parameters
  	p.setColor(QPalette::Window, Qt::blue);
  	w.setPalette(p);
  	w.setAutoFillBackground(true);

	//Show objects
  	w.showFullScreen();

	//Create a menu
	MainWindow *window = new MainWindow();
	window -> setWindowState(Qt::WindowFullScreen);
	
	//Show our window
  	window -> show();

	//Set up events
	QCoreApplication::processEvents();

	
  	return app.exec();
}
