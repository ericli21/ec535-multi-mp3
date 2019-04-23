#ifndef MENU1_H
#define MENU1_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "mainwindow.h"

namespace Ui {
	class Menu1;
}

class Menu1 : public QWidget
{
	Q_OBJECT
public:
	explicit Menu1(MainWindow *parent);	
public slots:
	void handleButton(int state);
private:
	//QLabel *message;
	QPushButton *my_Button;
	QPushButton *backButton;
	int *state;
};

#endif
