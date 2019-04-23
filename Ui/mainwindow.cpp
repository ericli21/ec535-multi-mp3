#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>

#include "mainwindow.h"
#include "mainmenu.h"
#include "menu1.h"
#include "menu2.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	setWindowTitle("Application");
	layout = new QStackedLayout();
	MainMenu *mainMenu = new MainMenu(this);
	Menu1 *page1 = new Menu1(this);
	Menu2 *page2 = new Menu2(this);
	layout -> addWidget(mainMenu);
	layout -> addWidget(page1);
	layout -> addWidget(page2);
	layout -> setCurrentIndex(0);
	this   -> setLayout(layout);
	mainMenu -> addButton("Play a song");
	mainMenu -> addButton("Select a song");
}

void MainWindow::setPage(int index)
{
	layout -> setCurrentIndex(index);
}

void MainWindow::goToMenu()
{
	layout -> setCurrentIndex(0);
}
