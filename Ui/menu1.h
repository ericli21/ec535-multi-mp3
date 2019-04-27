#ifndef MENU1_H
#define MENU1_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QDir>
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
	void slotTest(QListWidgetItem* song);
	void addSong();
private:
	//QLabel *message;
	QPushButton *addButton;
	QPushButton *backButton;
	int state;
	std::string selected;
};

#endif
