#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

/*
typedef struct ID3_info
{
	char song_title[128];
	char song_artist[128];
	char song_album[128];
	char song_genre[128];
	int year;
	
	int length_seconds;

} ID3_info;

//Each song is a node
typedef struct Node
{
	char song_name[128];
	struct Node *next;
	struct Node *prev;
	struct ID3_info * info;
} Node;

//A list of songs is a queue
typedef struct queue_info
{
	int num_nodes;
	struct Node *head;
	struct Node *end;
} queue_info;
*/


typedef struct ID3_info
{
	char song_title[128];
	char song_artist[128];
	char song_album[128];
	int length_seconds;

} ID3_info;

//Each song is a node
typedef struct Node
{
	char song_name[128];
	struct Node *next;
	struct Node *prev;
	struct ID3_info * info;
} Node;

//A list of songs is a queue
typedef struct queue_info
{
	int num_nodes;
	struct Node *head;
	struct Node *end;
} queue_info;

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
	void changeSongName(std::string);
	void notZero();
	void hasPrev();
	void hasNext();
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
	void pushSong(std::string songName);
	void playSong(int state);
	void pauseSong(int state);
	void backSong();
	void forwardSong();
	void transition();
	void tick();
	void checkNodes();
	void checkPrev();
	void checkNext();
private:
	QStackedLayout *layout;
	ID3_info *mainID3_info;
	Node *mainNode;
	queue_info *mainqueue_info;
	QTimer *timer;
	QTimer *songTimer;
	int elapsedMSeconds;
	QTimer *elapsedTimer;
	Node *current_song_node;
	int current_interval;
};

/*
void remove_new_line(char *s);
void LL_AddSong(queue_info * node_queue, char * input_song_name);
Node *getNode(Node * head_node, char *search_song_name);
void init_queue_info(queue_info * node_queue);
void deleteNode(queue_info * node_queue);
Node *getNextNode(Node * current_node);
Node *getPrevNode(Node * current_node);
*/

void remove_new_line(char *s);
void LL_AddSong(queue_info * node_queue, char * input_song_name);
Node *getNode(Node * head_node, char *search_song_name);
void init_queue_info(queue_info * node_queue);
void deleteNode(queue_info * node_queue);
Node *getNextNode(Node * current_node);
Node *getPrevNode(Node * current_node);

#endif
