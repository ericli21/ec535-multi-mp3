#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <iostream>
#include <QTimer>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cstdlib>

#include "mainwindow.h"
#include "lockmenu.h"
#include "mainmenu.h"
#include "menu1.h"
#include "menu2.h"
#include "UART.h"

//struct Node
//{
//	std::string songName;
//	int duration;
//	struct Node *next;
//};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	std::cout << "Test1\n";
	mainID3_info = new ID3_info();	
	mainNode = new Node();
	mainqueue_info = new queue_info();
	current_song_node = new Node();
	int MAX_QUEUE_LENGTH = 15;	

	std::cout << "Test2\n";
	priority = 0;
	setWindowTitle("Application:");
	layout = new QStackedLayout();
	LockMenu *lockMenu = new LockMenu(this);	
	MainMenu *mainMenu = new MainMenu(this);
	Menu1 *page1 = new Menu1(this);
	Menu2 *page2 = new Menu2(this);
	std::cout << "Test3\n";
	layout -> addWidget(mainMenu);	
	layout -> addWidget(page1);
	layout -> addWidget(page2);
	layout -> addWidget(lockMenu);
	layout -> setCurrentIndex(3);
	this   -> setLayout(layout);
	std::cout << "Test4\n";
	mainMenu -> addButton("Add song to playlist");
	mainMenu -> addButton("Add a user");
	timer = new QTimer();
	timer -> start(30000);

	songTimer = new QTimer();	

	current_interval = 0;
	elapsedMSeconds = 0;
	elapsedTimer = new QTimer();

	std::cout << "Test5\n";
	
	connect(elapsedTimer, SIGNAL(timeout()), this, SLOT(tick()));
	connect(timer, SIGNAL(timeout()), this, SLOT(goToLock()));
	connect(songTimer, SIGNAL(timeout()), this, SLOT(transition()));
	std::cout << "Test6\n";
}

void MainWindow::setPage(int index)
{
	if (index == 1 && priority > 1 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else if (index == 2 && priority > 2 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else {
		std::cout << "error: index = " << index << "priority = " << priority << "\n";
	}
}


//Go back to menu (page 0)
void MainWindow::goToMenu()
{
	layout -> setCurrentIndex(0);
}

//Go back to the lockscreen (page 3)
void MainWindow::goToLock()
{
	layout -> setCurrentIndex(3);
	priority = 0;
}

//After registering, set the current priority
void MainWindow::menuSetPriority1()
{
	layout -> setCurrentIndex(0);
	priority = 1;
}
void MainWindow::menuSetPriority2()
{
	layout -> setCurrentIndex(0);
	priority = 2;
}
void MainWindow::menuSetPriority3()
{
	layout -> setCurrentIndex(0);
	priority = 3;
}
void MainWindow::checkPriority()
{
	if (priority == 1) {
		emit(priority1());
	}
	else if (priority == 2) {
		emit(priority2());
	}
	else if (priority == 3) {
		emit(priority3());
	}
	else {
		//Do nothing (shouldn't get here)
	}
}
void MainWindow::updateTimeout() {
	timer -> setInterval(30000);
}

void MainWindow::pushSong(std::string songName) {
	std::string fN;
	std::cout << "Song name: " << songName << "\n"; 
	fN += "/media/card/songs/";
	fN += songName;
	char * fileName = new char[fN.length()+1];
	strcpy(fileName, fN.c_str());
	
	bool reset_head = false;
	if (mainqueue_info->num_nodes >= 15) {
		if (current_song_node == mainqueue_info->head) {
			reset_head = true;
		}
		deleteNode(mainqueue_info);
		LL_AddSong(mainqueue_info, fileName);
		if (reset_head == true) {
			current_song_node = mainqueue_info->head;
		}
	}
	else if (mainqueue_info->num_nodes == 0) {
		LL_AddSong(mainqueue_info, fileName);
		std::cout << "Song added\n";
		current_song_node = mainqueue_info->head;
		std::cout << "Update current node\n";
	}
	else {
		LL_AddSong(mainqueue_info, fileName);
	}
	//Node * test = getNode(mainqueue_info->head, fileName);
	//std::string command;
	//command += "ash speaker_interface.sh next ";
	//command += test->song_name;
	//char * command2 = new char[command.length()+1];
	//strcpy(command2, command.c_str());
	//std::cout << command << "\n";
	//system(command2);
	std::cout << "Done1\n";
}

void MainWindow::playSong(int state) {
	if (mainqueue_info->head == NULL) {
		//Do nothing
	}
	else {
		std::string command;
		
		if (state == 1) {
			command += "ash speaker_interface.sh next ";
			command += current_song_node->song_name;
			command += " &";
			char * command2 = new char[command.length()+1];
			strcpy(command2, command.c_str());
			std::cout << "play button activate: " << command << "\n";
			system(command2);
			current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
			std::cout << current_interval << "= current interval\n";

			emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);

			songTimer -> setInterval(current_interval);
			//songTimer -> start(current_interval);
			elapsedMSeconds = 0;
			elapsedTimer -> start(1000);
			//Shouldn't get here
			std::cout << "Shouldn't get here\n";
		} 
		else {
			//songTime -> setInterval(current_interval);
			command += "ash speaker_interface.sh play ";
			command += current_song_node->song_name;
			command += " &";
			char * command2 = new char[command.length()+1];
			strcpy(command2, command.c_str());
			std::cout << "play button activate: " << command << "\n";
			system(command2);

			emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);

			current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
			std::cout << current_interval << "= current interval\n";
			songTimer -> start(current_interval);
			elapsedMSeconds = 0;
			elapsedTimer -> start(1000);
		}
		
	}
}


void MainWindow::pauseSong(int state) {
	if (state == 1) {
		std::string command;
		command += "ash speaker_interface.sh pause ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << command << "\n";
		system(command2);
		
		current_interval = current_interval - elapsedMSeconds;
		std::cout << current_interval << "= current interval\n";
		songTimer -> stop();
		songTimer -> setInterval(current_interval);
	}
	else {
		//Do nothing
	}
}

void MainWindow::forwardSong() {
	if (mainqueue_info->head == NULL) {
		//Do nothing		
		return;
	}	
	
	if (current_song_node->next != NULL) {
		
		current_song_node = current_song_node->next;
		std::string command;
		command += "ash speaker_interface.sh next ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << command << "\n";
		std::cout << current_interval << "= current interval\n";
		current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
		elapsedMSeconds = 0;
		

		system(command2);
		
		emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);

		//songTimer -> setInterval(current_song_node->info->length_seconds * 1000);
		songTimer -> start(current_interval);
		elapsedTimer -> start(1000);
	}
}

void MainWindow::backSong() {
	if (mainqueue_info->head == NULL) {
		//Do nothing		
		return;
	}	

	if (current_song_node->prev != NULL) {
		current_song_node = current_song_node->prev;
		std::string command;
		command += "ash speaker_interface.sh next ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << command << "\n";
		std::cout << current_interval << "= current interval\n";
		current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
		elapsedMSeconds = 0;
		


		system(command2);
		
		emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);
		//songTimer -> setInterval(current_song_node->info->length_seconds * 1000);
		songTimer -> start(current_interval);
		elapsedTimer -> start(1000);
	}
}

void MainWindow::transition() {
	if (current_song_node->next != NULL) {
		current_song_node = current_song_node->next;
		std::string command;
		command += "ash speaker_interface.sh next ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << "transition active: " << command << "\n";
		std::cout << current_interval << "= current interval\n";
		current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
		elapsedMSeconds = 0;
		

		system(command2);
				
		emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);
		
		//songTimer -> setInterval(current_song_node->info->length_seconds * 1000);
		songTimer -> start(current_interval);	
		elapsedTimer -> start(1000);	
	}
	else {
		emit changeSongName("No song playing currently", " ", " ");
		std::cout << "No unplayed songs left in queue\n";
	}
}

void MainWindow::tick() {
	elapsedMSeconds++;
	timer -> setInterval(1000);
	//std::cout << "counting..\n";
}

void MainWindow::checkNodes() {
	if (mainqueue_info->num_nodes > 0) {
		emit notZero();
	}
}

void MainWindow::checkPrev() {
	if (current_song_node->prev != NULL) {
		emit hasPrev();
	}
}

void MainWindow::checkNext() {
	if (current_song_node->next != NULL) {
		emit hasNext();
	}
}

/*
void remove_new_line(char *s) {
    while (*s) {
        if (*s == '\n') {
            *s='\0';
        }
        s++;
    }
}


//Adds a node to the end of the linked list
void LL_AddSong(queue_info * node_queue, char * input_song_name)
{
	//Debug
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("%s\n", input_song_name);

	//File variables
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	//Delimeters
	char * min;
	char * sec;
	char * temp;
	char * delim1 = ":";
	char * delim2 = " ";
	char * delim3 = ": "; 

	//Create and populate ID3 struct
	ID3_info * song_info = (ID3_info*) malloc(sizeof(ID3_info));

	//Call shell script
	char buffer[128];

	sprintf(buffer, "ash speaker_interface.sh info %s &", input_song_name);
	printf("%s\n", buffer);
	system(buffer);
	sleep(3);

	printf("after sleep\n");

	//Open info file
	fp = fopen("output.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	printf("after open\n");

	//Create node
	Node *node_intermediate = (Node*) malloc(sizeof(Node));

	printf("node intermediate create\n");

	//Parse information

	while ((read = getline(&line, &len, fp)) != -1) {
		printf("in while loop\n");
		if(strstr(line, "Title:") != NULL){
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_title, line);
		}

		else if(strstr(line, "Artist:") != NULL){
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_artist, line);
		}

		else if(strstr(line, "Album:") != NULL){
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_album, line);
		}

		else if(strstr(line, "Year:") != NULL){
			temp = strsep(&line, delim1);
			int year = atoi(line);
			song_info->year = year;
		}

		else if(strstr(line, "Genre:") != NULL){
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_genre, line);
		}

		else if(strstr(line, "Layer") != NULL){
			break;
		}	
        	
    	}


	printf("after while loop\n");

	//Get minutes and seconds
	min = strsep(&line, delim1);
	min = strsep(&line, delim1);
	sec = strsep(&line, delim2);

	int minutes = atoi(min);
	int seconds = atoi(sec);

	seconds = minutes * 60 + seconds;

	fclose(fp);

	printf("after close\n");

	//Copy song name to node
	strcpy(node_intermediate->song_name, input_song_name);

	printf("after strcpy input song name \n");

	//Set up new node
	node_intermediate->next = NULL;
	node_intermediate->prev = NULL;
	node_intermediate->info = song_info;
	node_intermediate->info->length_seconds = seconds;

	printf("after new node setup\n");

	//First song in queue
	if (node_queue->head == NULL) {
		node_queue->head = node_intermediate;
		node_queue->end = node_intermediate;
		node_queue->num_nodes += 1;
		printf("before return 1\n");
		return;
	}

	printf("after first song in queue check\n");

	//Not the first song, add to the end of the queue
	node_intermediate->prev = node_queue->end;
	node_queue->end->next = node_intermediate;

	//Make current node the end node
	node_queue->end = node_intermediate;
	node_queue->num_nodes += 1;
	printf("before return 2\n");
	return;

}

//Loop through and get the node based on the song name
Node *getNode(Node * head_node, char *search_song_name) {
	
	//Start at the head of the list
	Node *temp = head_node;

	//Go through list
	while (temp != NULL) {
		if (strcmp(temp->song_name, search_song_name) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;

}

//Get the next node in the list given a current node
Node *getNextNode(Node * current_node) {

	//Make sure there is a next song
	if(current_node->next != NULL) {
		return current_node->next;
	}
	return NULL;

}

//Get the next node in the list given a current node
Node *getPrevNode(Node * current_node) {

	//Make sure there is a next song
	if(current_node->prev != NULL) {
		return current_node->prev;
	}
	return NULL;

}


//Initialize queue
void init_queue_info(queue_info * node_queue){

	node_queue->num_nodes = 0;
	node_queue->head = NULL;
	node_queue->end = NULL;
}


//Delete the head node from the linked list
void deleteNode(queue_info * node_queue){

	//Temporary node
	Node *temp = node_queue->head;

	//Set up next node as head
	node_queue->head->next->prev = NULL;
	node_queue->head = node_queue->head->next;

	//Free memory used by previous head node
	free(temp);
	node_queue->num_nodes -= 1;

}
*/

void remove_new_line(char *s) {
    while (*s) {
        if (*s == '\n') {
            *s='\0';
        }
        s++;
    }
}

void LL_AddSong(queue_info * node_queue, char * input_song_name)
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("%s\n", input_song_name);

	//File variables
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;


	char * temp;
	char * delim3 = ": "; 

	//Delimeters
	char * min;
	char * sec;
	char * delim1 = ":";
	char * delim2 = " ";

	//Create and populate ID3 struct
	ID3_info * song_info = (ID3_info*) malloc(sizeof(ID3_info));

	//Call shell script
	char buffer[128];

	sprintf(buffer, "ash speaker_interface.sh info %s &", input_song_name);
	printf("%s\n", buffer);
	system(buffer);
	sleep(3);

	//Open info file
	fp = fopen("output.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	

	//Parse to our time line
	
	while ((read = getline(&line, &len, fp)) != -1) {
		printf("%s\n", line);
		if(strstr(line, "Title:") != NULL){
			printf("Line 1: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_title, line);
			printf("Line 1b: %s\n", line);
		}
		else if(strstr(line, "Artist:") != NULL){
			printf("Line 2: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_artist, line);
			printf("Line 2b: %s\n", line);
		}
		else if(strstr(line, "Album:") != NULL){
			printf("Line 3: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_album, line);
			printf("Line 3b: %s\n", line);
		}
		else if(strstr(line, "Layer") != NULL){
			printf("%s\n", line);
			break;
		}	
        	
    	}
	

	/*
	while ((read = getline(&line, &len, fp)) != -1) {
		if(strstr(line, "Title:") != NULL){
			printf("Line 1: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_title, line);
			printf("Line 1b: %s\n", line);
		}

		else if(strstr(line, "Artist:") != NULL){
			printf("Line 2: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_artist, line);
			printf("Line 2b: %s\n", line);
		}

		else if(strstr(line, "Album:") != NULL){
			printf("Line 3: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_album, line);
			printf("Line 3b: %s\n", line);
		}

		else if(strstr(line, "Year:") != NULL){
			printf("Line 4: %s\n", line);
			temp = strsep(&line, delim1);
			int year = atoi(line);
			song_info->year = year;
			printf("Line 4b: %s\n", line);
		}

		else if(strstr(line, "Genre:") != NULL){
			printf("Line 5: %s\n", line);
			temp = strsep(&line, delim1);
			remove_new_line(line);
			strcpy(song_info->song_genre, line);
			printf("Line 5b: %s\n", line);
		}

		else if(strstr(line, "Layer") != NULL){
			printf("Line 6: %s\n", line);
			break;
		}	
        	
    	}

	*/

	printf("%s\n", line);

	//Get minutes and seconds
	min = strsep(&line, delim1);
	min = strsep(&line, delim1);
	sec = strsep(&line, delim2);

	printf("made it add %s %s\n", min, sec);

	int minutes = atoi(min);
	printf("min: %d\n", minutes);
	int seconds = atoi(sec);
	printf("sec: %d\n", seconds);

	seconds = minutes * 60 + seconds;
	printf("sec: %d\n", seconds);

	fclose(fp);
	printf("closed\n");
	
	//Create node
	Node *node_intermediate = (Node*) malloc(sizeof(Node));
	if (node_intermediate == NULL)
		printf("Node intermediate == NULL\n");
	printf("made node intermediate\n");

	//Copy song name to node
	strcpy(node_intermediate->song_name, input_song_name);
	printf("copied\n");

	//Next song is null
	node_intermediate->next = NULL;
	node_intermediate->prev = NULL;

	printf("node intermediate nulls\n");

	node_intermediate->info = song_info;
	node_intermediate->info->length_seconds = seconds;
	printf("%d\n", node_intermediate->info->length_seconds);

	//First song in queue
	if (node_queue->head == NULL) {
		node_queue->head = node_intermediate;
		node_queue->end = node_intermediate;
		node_queue->num_nodes += 1;
		printf("made it add first\n");
		return;
	}

	printf("after if loop\n");

	//Not the first song, add to end
	node_intermediate->prev = node_queue->end;

	printf("intermediate prev = node queue end\n");

	node_queue->end->next = node_intermediate;

	printf("queue end next = node intermediate\n");

	//Make current node end
	node_queue->end = node_intermediate;

	printf("queue end = node intermediate\n");

	node_queue->num_nodes += 1;

	//free(song_info);

	printf("bye\n");
	return;

}

//Loop through and get the node based on the instruction address
Node *getNode(Node * head_node, char *search_song_name) {
	//Start at the head of the list
	Node *temp = head_node;

	//Go through list
	while (temp != NULL) {
		if (strcmp(temp->song_name,search_song_name) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;

}

//Get the next node in the list given a current node
Node *getNextNode(Node * current_node) {

	//Make sure there is a next song
	if(current_node->next != NULL) {
		return current_node->next;
	}
	return NULL;

}

//Get the next node in the list given a current node
Node *getPrevNode(Node * current_node) {

	//Make sure there is a next song
	if(current_node->prev != NULL) {
		return current_node->prev;
	}
	return NULL;

}


//Initialize queue
void init_queue_info(queue_info * node_queue){

	node_queue->num_nodes = 0;
	node_queue->head = NULL;
	node_queue->end = NULL;
}


//Delete the head node from the linked list
void deleteNode(queue_info * node_queue){

	//Temporary node
	Node *temp = node_queue->head;

	//Set up next node as head
	node_queue->head->next->prev = NULL;
	node_queue->head = node_queue->head->next;

	//Free memory used by previous head node
	free(temp);
	node_queue->num_nodes -= 1;

}


