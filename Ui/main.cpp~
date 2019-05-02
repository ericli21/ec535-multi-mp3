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

//Class for a button

int main(int argc, char * argv[]){

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

	//char message[128];
	
	//Create a button
	//MyButton window;

	//Create a menu
	MainWindow *window = new MainWindow();
	window -> setWindowState(Qt::WindowFullScreen);
	
	

  	//window.resize(250, 150);  
  	//window.setWindowTitle("Play button test");
  	window -> show();

		
	QCoreApplication::processEvents();

	
  	return app.exec();
}
