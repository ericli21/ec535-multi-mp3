#ifndef MENU1_H
#define MENU1_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "mainwindow.h"

namespace Ui {
	class Menu1;
}

class Menu1 : public QWidget
{
	Q_OBJECT
public:
	explicit Menu1(MainWindow *parent);	
private:
	//QLabel *message;
	QPushButton *backButton;
};

#endif
