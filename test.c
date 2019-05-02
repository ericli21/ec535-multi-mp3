#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct ID3_info
{
	char song_name[128];
	char song_artist[128];
	char song_album[128];
	char song_genre[128];
	int year;
	int track_num;
	int length_seconds;

} ID3_info;


int main(int argc, char **argv) {

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	char * min;
	char * sec;
	char * delim1 = ":";
	char * delim2 = " ";

	ID3_info * song_info = (ID3_info*) malloc(sizeof(ID3_info));
	

	fp = fopen("song_info.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);


	while ((read = getline(&line, &len, fp)) != -1) {
		if(strstr(line, "Layer") != NULL){
			printf("%s", line);
			break;
		}	
        	
    	}


	min = strsep(&line, delim1);
	min = strsep(&line, delim1);
	sec = strsep(&line, delim2);

	printf("%s minutes %s seconds \n", min, sec);

	int minutes = atoi(min);
	int seconds = atoi(sec);

	song_info->length_seconds = minutes * 60 + seconds;
	

	printf("%d seconds \n", song_info->length_seconds);


	fclose(fp);
}
