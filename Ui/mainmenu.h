#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSignalMapper>

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
private:
	QVBoxLayout *layout;
	QSignalMapper *signalMapper;
	int nButtons;
};

#endif
