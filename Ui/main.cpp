//Qt Includes
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QLabel>
#include <QMainWindow>
#include <QTextStream>
#include <QFont>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAbstractButton>

//Misc includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

//Class for a button
class MyButton : public QWidget {
    
 public:
     MyButton(QWidget *parent = 0);
};

MyButton::MyButton(QWidget *parent)
    : QWidget(parent) {
           
  QPushButton *quitBtn = new QPushButton("Play", this);
  quitBtn->setGeometry(50, 40, 75, 30);

  //QObject::connect(quitBtn, &QToolButton::clicked, qApp, &QApplication::quit);
}

int main(int argc, char * argv[]){


	//Start QApplication
	QApplication app(argc, argv);

	//Variable declarations
  	QWidget w;
	QString info;
  	QPalette p = w.palette();
	QLabel * label = new QLabel(&w);

	//Set object parameters
  	p.setColor(QPalette::Window, Qt::blue);
	p.setColor(QPalette::WindowText, Qt::white);
	p.setColor(QPalette::Window, Qt::green);

  	w.setPalette(p);
  	w.setAutoFillBackground(true);

	//Show objects
  	w.showFullScreen();

	char message[128];
	
	//Create a button
	MyButton window;

  	window.resize(250, 150);  
  	window.setWindowTitle("Play button test");
  	window.show();


	//Create string with data from kernel module
	//sprintf(message, "Test");
	//std::string str(message);
	//info = str.c_str();

	//label->setText(info);
	//label->setFont(QFont("Veranda", 14, QFont::Bold, true));
	//label->adjustSize();
		
	QCoreApplication::processEvents();

	
  	return app.exec();
}
