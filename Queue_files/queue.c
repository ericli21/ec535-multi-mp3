#include "queue.h"

//Remove newline from given string
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

	//Open info file
	fp = fopen("output.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//Create node
	Node *node_intermediate = (Node*) malloc(sizeof(Node));

	//Parse information
	while ((read = getline(&line, &len, fp)) != -1) {
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

	//Get minutes and seconds
	min = strsep(&line, delim1);
	min = strsep(&line, delim1);
	sec = strsep(&line, delim2);

	int minutes = atoi(min);
	int seconds = atoi(sec);

	seconds = minutes * 60 + seconds;

	fclose(fp);

	//Copy song name to node
	strcpy(node_intermediate->song_name, input_song_name);

	//Set up new node
	node_intermediate->next = NULL;
	node_intermediate->prev = NULL;
	node_intermediate->info = song_info;
	node_intermediate->info->length_seconds = seconds;

	//First song in queue
	if (node_queue->head == NULL) {
		node_queue->head = node_intermediate;
		node_queue->end = node_intermediate;
		node_queue->num_nodes += 1;
		return;
	}

	//Not the first song, add to the end of the queue
	node_intermediate->prev = node_queue->end;
	node_queue->end->next = node_intermediate;

	//Make current node the end node
	node_queue->end = node_intermediate;
	node_queue->num_nodes += 1;

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

