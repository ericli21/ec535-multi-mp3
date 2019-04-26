#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QLabel>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "mainwindow.h"

namespace Ui {
	class MainMenu;
}

class MainMenu : public QWidget
{
	Q_OBJECT
public:
	explicit MainMenu(MainWindow *parent);	
public slots:
	void addButton(QString name);
	void handleButton();
	void handleSkip();
	void handlePrevious();
private:
	QHBoxLayout *layout;
	QSignalMapper *signalMapper;
	int nButtons;
	QPushButton *my_Button;
	QPushButton *backButton;
	QPushButton *skipButton;
	QPushButton *previousButton;
	int state;
};

#endif