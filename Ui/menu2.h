#ifndef MENU2_H
#define MENU2_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
	void addUser();	
private:
	int id_count;
	//QLabel *message;
	QPushButton *userButton;
	QPushButton *backButton;
};

#endif
