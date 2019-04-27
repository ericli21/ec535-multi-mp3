#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT
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
private:
	QStackedLayout *layout;
};

#endif
