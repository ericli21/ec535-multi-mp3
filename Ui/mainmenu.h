#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QGridLayout>
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
signals:
	void play_to_pause(int);
	void pause_to_play(int);
public:
	explicit MainMenu(MainWindow *parent);
public slots:
	void addButton(QString name);
	void handleButton();
	void handleSkip();
	void handlePrevious();
private:
	QGridLayout *layout;
	//QGridLayout *mainLayout;
	QSignalMapper *signalMapper;
	int nButtons;
	QPushButton *my_Button;
	QPushButton *backButton;
	QPushButton *skipButton;
	QPushButton *previousButton;
	int state;
	int priority;
};

#endif
