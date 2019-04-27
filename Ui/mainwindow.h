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
public slots:
	void setPage(int index);
	void goToMenu();
	void goToLock();
private:
	QStackedLayout *layout;
};

#endif
