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

//Central class for controlling global variables needed by every menu (and lock) page
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	//Initialize queue components
	mainID3_info = new ID3_info();	
	mainNode = new Node();
	mainqueue_info = new queue_info();
	current_song_node = new Node();
	int MAX_QUEUE_LENGTH = 15;	

	//Initalize the priority as 0 (no one using it initally)
	priority = 0;

	//Intialize the pages, and use a StackedLayout to stack the menu pages together
	setWindowTitle("Application:");
	layout = new QStackedLayout();
	LockMenu *lockMenu = new LockMenu(this);	
	MainMenu *mainMenu = new MainMenu(this);
	Menu1 *page1 = new Menu1(this);
	Menu2 *page2 = new Menu2(this);
	layout -> addWidget(mainMenu);	
	layout -> addWidget(page1);
	layout -> addWidget(page2);
	layout -> addWidget(lockMenu);

	//Set the initial page to page 3 (locked screen)
	layout -> setCurrentIndex(3);
	this   -> setLayout(layout);

	//Add buttons to mainMenu to connect to menu 1 (add a song) and menu 2 (add a user)
	mainMenu -> addButton("Add song to playlist");
	mainMenu -> addButton("Add a user");

	//Initalize a QTimer for a 30 second timeout if no interactions happen
	timer = new QTimer();
	timer -> start(30000);
	connect(timer, SIGNAL(timeout()), this, SLOT(goToLock()));

	//Initialize a QTimer for the duration (current_interval) of the song (timeout triggers a transition to the next song)
	songTimer = new QTimer();
	connect(songTimer, SIGNAL(timeout()), this, SLOT(transition()));
	current_interval = 0;

	//Initialize a QTimer to increment elapsedMSeconds to calculate remain duration of a song (= total duration - elasped time)
	elapsedMSeconds = 0;
	elapsedTimer = new QTimer();
	connect(elapsedTimer, SIGNAL(timeout()), this, SLOT(tick()));
	
	//Flag for a specfic scenario when last song in queue is done playing
	lastSongPlayed = false;
	

}

//Input a specific page, and check the user's priority if it has the correct priority to access the page. If they do, switch to the page. If they don't, stay at the current page (main menu).
void MainWindow::setPage(int index)
{
	if (index == 1 && priority > 1 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else if (index == 2 && priority > 2 && priority < 4) {
		layout -> setCurrentIndex(index);
	}
	else {
		std::cout << "error: index = " << index << ", priority = " << priority << "\n";
	}
}


//Go back to menu (page 0)
void MainWindow::goToMenu()
{
	layout -> setCurrentIndex(0);
}

//Go back to the lockscreen (page 3) and reset the priority (no user logged in)
void MainWindow::goToLock()
{
	layout -> setCurrentIndex(3);
	priority = 0;
}

//After signing in via lock screen, set the current priority variable and switch to the main menu page
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

//Check the priority of the user, and emit one of three unique signals
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

//Once a button has been pressed, reset timer to 30 seconds
void MainWindow::updateTimeout() {
	timer -> setInterval(30000);
}

//Push new song to the queue
void MainWindow::pushSong(std::string songName) {

	//Combine the songName into a string
	std::string fN;
	std::cout << "Song name: " << songName << "\n"; 
	fN += "/media/card/songs/";
	fN += songName;
	char * fileName = new char[fN.length()+1];
	strcpy(fileName, fN.c_str());
	
	//If the queue is greater than 15 songs, we must delete the oldest (front) song in the queue.
	//If the current song is the oldest song, we delete this song from the queue (still is playing) and set the head pointer to the new front of the queue.
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

	//If there are no nodes in the queue, add song to queue and set this song as the current song
	else if (mainqueue_info->num_nodes == 0) {
		LL_AddSong(mainqueue_info, fileName);
		current_song_node = mainqueue_info->head;
	}

	//Add the song to queue if not the previous two conditions
	else {
		LL_AddSong(mainqueue_info, fileName);
	}

}

//Play song when play song is left (input as current state of song: paused (0) or playing (1))
void MainWindow::playSong(int state) {

	//If there are no songs in the queue, do nothing
	if (mainqueue_info->head == NULL) {
		//Do nothing
	}

	//If there are songs in the queue, initialize a string to a system call for pausing/playing
	else {
		std::string command;
		
		//If a song is currently playing and the play button is pressed (this should never happen, but just in case)
		if (state == 1) {
			//Concatenate the command into a string, execute the system call to play the current song
			command += "ash speaker_interface.sh next ";
			command += current_song_node->song_name;
			command += " &";
			char * command2 = new char[command.length()+1];
			strcpy(command2, command.c_str());
			std::cout << "play button activate: " << command << "\n";
			system(command2);

			//Update the current_interval and song timer with the new duration with a 2 second buffer, and update song information to display
			current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
			emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);			
			songTimer -> setInterval(current_interval);
			
			//Reset elapsed timer counter and clock
			elapsedMSeconds = 0;
			elapsedTimer -> start(1000);
		} 
		//If a song is paused and play button is pressed
		else {
			//Concatenate the command into a string, execute the system call to play the current song
			command += "ash speaker_interface.sh play ";
			command += current_song_node->song_name;
			command += " &";
			char * command2 = new char[command.length()+1];
			strcpy(command2, command.c_str());
			std::cout << "play button activate: " << command << "\n";
			system(command2);

			//Update the current_interval and song timer with the remaining duration with a 2 second buffer, and update song information to display
			emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);
			current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
			songTimer -> start(current_interval);

			//Reset elapsed timer counter and clock
			elapsedMSeconds = 0;
			elapsedTimer -> start(1000);
		}
		
	}
}


//Pause song when the pause button is pressed
void MainWindow::pauseSong(int state) {
	if (state == 1) {
		//Concatenate the command into a string, execute the system call to pause the current song
		std::string command;
		command += "ash speaker_interface.sh pause ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << command << "\n";
		system(command2);
		
		//Update the current_interval with the remaining duration, and set the interval for when the song plays again
		current_interval = current_interval - elapsedMSeconds + 2000;
		songTimer -> stop();
		songTimer -> setInterval(current_interval);
	}
	else {
		//Do nothing
	}
}

//Go to previous song in the queue when the forward button is pressed
void MainWindow::forwardSong() {

	//If there are no songs in the queue, do nothing and return
	if (mainqueue_info->head == NULL) {
		//Do nothing		
		return;
	}	
	
	//If there is a next song from the currently playing song, go to the next song
	if (current_song_node->next != NULL) {
		
		//Concatenate the command into a string, execute the system call to play the current song
		//Update the current_interval and song timer with the new duration with a 2 second buffer, and update song information to display
		//Reset elapsed timer counter and clock
		current_song_node = current_song_node->next;
		std::string command;
		command += "ash speaker_interface.sh next ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		std::cout << command << "\n";
		current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
		elapsedMSeconds = 0;
		system(command2);
		emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);
		songTimer -> start(current_interval);
		elapsedTimer -> start(1000);
	}
}

//Go to previous song in the queue when the back button is pressed
void MainWindow::backSong() {

	//If there are no songs in the queue, do nothing and return
	if (mainqueue_info->head == NULL) {
		//Do nothing		
		return;
	}	
	
	//If the last song ended in the queue
	if (current_song_node->next == NULL) {
		if (lastSongPlayed == true) {
			//We play the last song again (lastSongPlayed set to false until the last song ends again)
			lastSongPlayed = false;
			//Concatenate the command into a string, execute the system call to play the current song
			//Update the current_interval and song timer with the new duration with a 2 second buffer, and update song information to display
			//Reset elapsed timer counter and clock
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
			songTimer -> start(current_interval);
			elapsedTimer -> start(1000);
			return;
			
		}
	}

	//If there is a previous song in the queue from the currently playing song
	if (current_song_node->prev != NULL) {
		//Concatenate the command into a string, execute the system call to play the current song
		//Update the current_interval and song timer with the new duration with a 2 second buffer, and update song information to display
		//Reset elapsed timer counter and clock
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
		songTimer -> start(current_interval);
		elapsedTimer -> start(1000);
	}
}

//Transition to next song in the queue when the current song is done playing
void MainWindow::transition() {
	//If there is a song next in the queue
	if (current_song_node->next != NULL) {
		//Concatenate the command into a string, execute the system call to play the current song
		//Update the current_interval and song timer with the new duration with a 2 second buffer, and update song information to display
		//Reset elapsed timer counter and clock
		current_song_node = current_song_node->next;
		std::string command;
		command += "ash speaker_interface.sh next ";
		command += current_song_node->song_name;
		command += " &";
		char * command2 = new char[command.length()+1];
		strcpy(command2, command.c_str());
		current_interval = (current_song_node->info->length_seconds * 1000) + 2000;
		elapsedMSeconds = 0;
		system(command2);
		emit changeSongName(current_song_node->info->song_title, current_song_node->info->song_artist, current_song_node->info->song_album);
		songTimer -> start(current_interval);	
		elapsedTimer -> start(1000);	
	}
	//If the last song has been played
	else {
		//Set the lastSongPlayed flag to true (handled by previousSong)
		lastSongPlayed = true;
		emit changeSongName("No song playing currently", " ", " ");
	}
}

//Increment elapsed time (seconds) and re-run the timer
void MainWindow::tick() {
	elapsedMSeconds++;
	timer -> setInterval(1000);
}

//Check if there are songs in the queue, emit signal if there is
void MainWindow::checkNodes() {
	if (mainqueue_info->num_nodes > 0) {
		emit notZero();
	}
}

//Check if there is a previous song from the current song in the queue, and emit signal if it does
void MainWindow::checkPrev() {
	if (current_song_node->prev != NULL) {
		emit hasPrev();
	}
}

//Check if there is a next song from the current song in the queue, and emit signal if it does
void MainWindow::checkNext() {
	if (current_song_node->next != NULL) {
		emit hasNext();
	}
}


void remove_new_line(char *s) {
    while (*s) {
        if (*s == '\n') {
            *s='\0';
        }
        s++;
    }
}

//Add a song to the queue (linked list)
void LL_AddSong(queue_info * node_queue, char * input_song_name)
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("Added %s to queue.\n", input_song_name);

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
		else if(strstr(line, "Layer") != NULL){
			break;
		}	
        	
    	}
	

	//Get minutes and seconds
	min = strsep(&line, delim1);
	min = strsep(&line, delim1);
	sec = strsep(&line, delim2);

	printf("made it add %s %s\n", min, sec);

	int minutes = atoi(min);
	int seconds = atoi(sec);

	seconds = minutes * 60 + seconds;

	fclose(fp);
	
	//Create node
	Node *node_intermediate = (Node*) malloc(sizeof(Node));

	//Copy song name to node
	strcpy(node_intermediate->song_name, input_song_name);

	//Next song is null
	node_intermediate->next = NULL;
	node_intermediate->prev = NULL;

	node_intermediate->info = song_info;
	node_intermediate->info->length_seconds = seconds;
	printf("length_seconds = %d\n", node_intermediate->info->length_seconds);

	//First song in queue
	if (node_queue->head == NULL) {
		node_queue->head = node_intermediate;
		node_queue->end = node_intermediate;
		node_queue->num_nodes += 1;
		printf("made it add first\n");
		return;
	}

	//Not the first song, add to end
	node_intermediate->prev = node_queue->end;

	node_queue->end->next = node_intermediate;


	//Make current node end
	node_queue->end = node_intermediate;

	node_queue->num_nodes += 1;

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


