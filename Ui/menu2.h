#ifndef MENU2_H
#define MENU2_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <QCoreApplication>

#include "mainwindow.h"

namespace Ui {
	class Menu2;
}

class Menu2 : public QWidget
{
	Q_OBJECT
public:
	explicit Menu2(MainWindow *parent);
private slots:
	void addUser1();
	void addUser2();	
private:
	QLabel *message;
	QPushButton *user1Button;
	QPushButton *user2Button;
	QPushButton *backButton;
	
};

#endif
