#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <iostream>
#include <QTimer>

struct Node;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT
signals:
	void priority1();
	void priority2();
	void priority3();
public:
	explicit MainWindow(QWidget *parent = 0);
	int priority;
public slots:
	void setPage(int index);
	void goToMenu();
	void goToLock();
	void menuSetPriority1();
	void menuSetPriority2();
	void menuSetPriority3();
	void checkPriority();
	void updateTimeout();
private:
	QStackedLayout *layout;
	Node *head;
	QTimer *timer;
};

#endif
