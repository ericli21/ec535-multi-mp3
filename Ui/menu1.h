#ifndef MENU1_H
#define MENU1_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QSignalMapper>
#include <QDir>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "mainwindow.h"

namespace Ui {
	class Menu1;
}

//Menu 1 class
class Menu1 : public QWidget
{
	Q_OBJECT
signals:
	void addSong(std::string);
public:
	explicit Menu1(MainWindow *parent);	
private slots:
	void slotTest(QListWidgetItem* song);
	void confirmSong();
private:
	QPushButton *addButton;
	QPushButton *backButton;
	int state;
	std::string selected;
};

#endif
