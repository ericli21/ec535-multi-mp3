#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> //int8_t
#include <math.h>
#include <unistd.h> //sleep
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h> // serial ports


//Device settings
#define BAUDRATE B19200        
#define DEVICEPORT "/dev/ttyS2"
#define HEADER 0xF5

//Command definitions
#define ADD_FP_1 	0x01
#define ADD_FP_2 	0x02
#define ADD_FP_3 	0x03
#define DEL_FP_USER 	0x04
#define DEL_FP_ALL 	0x05
#define NUM_USERS	0x09
#define GET_USER_LEVEL	0x0A
#define CMP_USER	0x0B
#define CMP_ALL		0x0C

void add_fingerprint(int device, int user_id, char user_level, int scanNumber);
void delete_user(int device, int user_id);
int authenticate_user(int device, int user_id);
void send_command(int device, char CMD, char param1, char param2, char param3);
int get_response(int device, char * response);
int get_user_number(int device);

#endif
