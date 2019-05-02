#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//Each song needs its ID3 information
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


void remove_new_line(char *s);
void LL_AddSong(queue_info * node_queue, char * input_song_name);
Node *getNode(Node * head_node, char *search_song_name);
void init_queue_info(queue_info * node_queue);
void deleteNode(queue_info * node_queue);
Node *getNextNode(Node * current_node);
Node *getPrevNode(Node * current_node);
