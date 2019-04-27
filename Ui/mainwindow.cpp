#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>

#include "mainwindow.h"
#include "lockmenu.h"
#include "mainmenu.h"
#include "menu1.h"
#include "menu2.h"
#include "UART.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	priority = 0;
	setWindowTitle("Application");
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
	mainMenu -> addButton("Select a song");
}

void MainWindow::setPage(int index)
{
	layout -> setCurrentIndex(index);
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
