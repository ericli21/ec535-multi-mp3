#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <iostream>

#include "mainwindow.h"
#include "lockmenu.h"
#include "mainmenu.h"
#include "menu1.h"
#include "menu2.h"
#include "UART.h"

struct Node
{
	std::string songName;
	int duration;
	struct Node *next;
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	head = new Node();
	priority = 0;
	setWindowTitle("Application:");
	layout = new QStackedLayout();
	LockMenu *lockMenu = new LockMenu(this);	
	MainMenu *mainMenu = new MainMenu(this);
	Menu1 *page1 = new Menu1(this);
	Menu2 *page2 = new Menu2(this);
	layout -> addWidget(mainMenu);	
	layout -> addWidget(page1);
	layout -> addWidget(page2);
	layout -> addWidget(lockMenu);
	layout -> setCurrentIndex(3);
	this   -> setLayout(layout);
	mainMenu -> addButton("Add song to playlist");
	mainMenu -> addButton("Add a user");
}

void MainWindow::setPage(int index)
{
	if (index == 1 && priority > 1 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else if (index == 2 && priority > 2 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else {
		std::cout << "error: index = " << index << "priority = " << priority << "\n";
	}
}

void MainWindow::goToMenu()
{
	layout -> setCurrentIndex(0);
	priority = 0;
}

void MainWindow::goToLock()
{
	layout -> setCurrentIndex(3);
}
void MainWindow::menuSetPriority1()
{
	layout -> setCurrentIndex(0);
	priority = 1;
}
void MainWindow::menuSetPriority2()
{
	layout -> setCurrentIndex(0);
	priority = 2;
}
void MainWindow::menuSetPriority3()
{
	layout -> setCurrentIndex(0);
	priority = 3;
}
void MainWindow::checkPriority()
{
	if (priority == 1) {
		emit(priority1());
	}
	else if (priority == 2) {
		emit(priority2());
	}
	else if (priority == 3) {
		emit(priority3());
	}
	else {
		//Do nothing (shouldn't get here)
	}
}
