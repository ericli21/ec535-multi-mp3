#include "queue.h"

int main(int argc, char **argv) {

	char * new_song = "/media/card/songs/MinnesotaWI.mp3";
	char * new_song2 = "/media/card/songs/Calgary.mp3";
	char * new_song3 = "/media/card/songs/10.mp3";

	
	queue_info * new_queue = (queue_info*) malloc(sizeof(queue_info));
	init_queue_info(new_queue);


	LL_AddSong(new_queue, new_song);
	sleep(2);

	LL_AddSong(new_queue, new_song2);
	sleep(2);

	LL_AddSong(new_queue, new_song3);
	sleep(2);


	Node * test = getNode(new_queue->head, new_song2);

	if(test != NULL){
		printf("Previous song: %s\n", test->prev->song_name);
		printf("Current song: %s\n", test->song_name);
		printf("Next song: %s\n", test->next->song_name);
		printf("Num nodes: %d\n", new_queue->num_nodes);
		printf("Num seconds: %d\n", test->info->length_seconds);
		printf("Year: %d\n", test->info->year);
		printf("Artist: %s\n", test->info->song_artist);
		printf("Title: %s\n", test->info->song_title);
		printf("Genre: %s\n", test->info->song_genre);
		printf("Album: %s\n", test->info->song_album);
	}


	//deleteNode(new_queue);

	//if delete worked
	/*if(test->prev == NULL){
		printf("Head song: %s\n", new_queue->head->song_name);
		printf("Num nodes: %d\n", new_queue->num_nodes);
	}
	
*/
	free(new_queue);
	printf("made it last\n");
	return 0;

}
