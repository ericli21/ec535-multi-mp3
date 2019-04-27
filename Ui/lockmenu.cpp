#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QCoreApplication>

#include "lockmenu.h"
extern "C" {
  #include "UART.h" //a C header, so wrap it in extern "C" 
}


//Authenticate user menu screen
LockMenu::LockMenu(MainWindow *parent) : QWidget(parent) {
	//signalMapper = new QSignalMapper(this);
	//connect(signalMapper, SIGNAL(mapped(int)), parent, SLOT(setPage(int)));
	id = 1;
	layout = new QVBoxLayout();
	setLayout(layout);
	QPushButton *button = new QPushButton("Log in via fingerprint", this);
	layout -> addWidget(button);
	connect(button, SIGNAL(released()), this, SLOT(auth()));
	connect(this, SIGNAL(correct()), parent, SLOT(goToMenu()));
	//nButtons = 0;
}

void LockMenu::auth() {

	id++;
	int device = scanner_open();
	//delete_user(device, 0);
	//add_fingerprint(device, 15, 0x02, 0);
	int level = authenticate_user(device, 0);
	printf("Level: %d\n", level);
	sleep(3);
	int level2 = authenticate_user(device, 0);
	printf("Level2: %d\n", level2);

	int num_users = get_user_number(device);
	printf("Num users: %d\n", num_users);


	if (id == 2) {
		emit(correct());
	}
}
