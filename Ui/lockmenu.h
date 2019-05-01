#ifndef LOCKMENU_H
#define LOCKMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QLabel>

#include "mainwindow.h"

namespace Ui {
	class LockMenu;
}

class LockMenu : public QWidget
{
	Q_OBJECT
signals:
	void correct1();
	void correct2();
	void correct3();
public:
	explicit LockMenu(MainWindow *parent);
public slots:
	void auth();
	void updateName(std::string songName);
private:
	QVBoxLayout *layout;
	int id;
	QLabel *current_song;
};

#endif
