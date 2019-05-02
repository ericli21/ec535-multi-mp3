#include "UART.h"


int main(){

	// open port for watch RF Communication
	struct termios  config;
	int wFile;
	wFile = open(DEVICEPORT, O_RDWR | O_NOCTTY | O_NDELAY);
	if(wFile == -1)
	{
		printf( "failed to open port\n" );
		return -1;
	}


	bzero(&config, sizeof(config));
	config.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	config.c_oflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	tcflush(wFile, TCIFLUSH);
	tcsetattr(wFile,TCSANOW,&config);

	char level = 0x03;

	delete_user(wFile,0);

	add_fingerprint(wFile, 1, level, 0);

	int num_users = get_user_number(wFile);
	printf("Num users: %d\n", num_users);

}
//Get the current number of users on the device, use when registering a new user
int get_user_number(int device){

	char response[8];
	int check;

	//Send command to get number of users
	send_command(device, NUM_USERS, 0x0, 0x0, 0x0);
	check = get_response(device, response);

	//ACK_SUCCESS
	if(response[2] == 0x0){
		//Return number of users
		return (int)(response[0] << 8 | response[1]);
	}

	return 0;

}

//Add new fingerprint to device with user ID and user level
void add_fingerprint(int device, int user_id, char user_level, int scanNumber){

	char response[8];
	int check;

	//Convert user ID to high and low bytes
	char UL = user_id & 0xFF;
  	char UH = (user_id >> 8) & 0xFF;

	//Need to do three scan commands to properly add fingerprint
	sleep(1);

	//Add FP 1
	send_command(device, ADD_FP_1, UH, UL, user_level);
	sleep(1);

	printf("FP1\n");
	check = get_response(device, response);
	sleep(1);

	//Add FP 2
	send_command(device, ADD_FP_2, UH, UL, user_level);
	sleep(1);

	printf("FP2\n");
	check = get_response(device, response);
	sleep(1);

	//Add FP 3
	send_command(device, ADD_FP_3, UH, UL, user_level);
	sleep(1);
	printf("FP3\n");
	check = get_response(device, response);

}

//Delete user, delete all users if user_id == 0
void delete_user(int device, int user_id){

	//Get user high and user low bits
	char UL = user_id & 0xFF;
  	char UH = (user_id >> 8) & 0xFF;

	char response[3];
	int check;

	//Delete all users
	if(user_id < 1){
		send_command(device, DEL_FP_ALL, 0x0, 0x0, 0x0);
		check = get_response(device, response);
	}
	//Delete specific user
	else{
		send_command(device, DEL_FP_USER, UH, UL, 0x0);
		check = get_response(device, response);
	}

}

//Check if user is an authenticated user, if yes, then return user level
int authenticate_user(int device, int user_id){

	//Get user high and user low bits
	char UL = user_id & 0xFF;
  	char UH = (user_id >> 8) & 0xFF;

	int check;
	char response[4];

	//Check authentication against all users
	if(user_id < 1){
		send_command(device, CMP_ALL, 0x0, 0x0, 0x0);
		sleep(1);
		check = get_response(device, response);

		if(response[2] != 0x0){
			return (int)response[2];
		}
	}
	//Check authentication against one specific user
	else{
		send_command(device, CMP_ALL, UH, UL, 0x0);
		sleep(1);
		check = get_response(device, response);
		if(response[2] != 0x0){
			return (int)response[2];
		}
	}
	
	sleep(1);

	return 0;
}

//Send a command to the fingerprint scanner
void send_command(int device, char CMD, char param1, char param2, char param3){

	char command[8];

	//Set up command to send to UART
	command[0] = 0xF5;
	command[1] = CMD;
	command[2] = param1; 
	command[3] = param2;
	command[4] = param3; 	
	command[5] = 0x00;
	command[6] = command[1] ^ command[2] ^ command[3] ^ command[4] ^ command[5]; //Check Sum
	command[7] = 0xF5; 

	//Send to device
	int count = write(device, command, sizeof(command));

	//Make sure we write the right number of bytes
	while(count < 8){
		sleep(1);
		count = write(device, command, sizeof(command));
	}

	printf("Sending Command\n");

}

//Print response from scanner, check if valid
int get_response(int device, char * response){

	char check_sum;
	char read_back[8];
	int count, i = 0;

	//Read from UART
	count = read(device, read_back, sizeof(read_back));

	//Make sure we read the right number of bytes
	while(count < 8){
		sleep(1);
		count = read(device, read_back, sizeof(read_back));
	}

	//Print response for dubugging purposes
	for(i = 0; i < 8; i++){
		//Do checksum
		if(i > 0 && i < 6){
			check_sum ^= read_back[i];
		}
		printf("%02x ", read_back[i]);	
	}
	printf("\n");

	//Check if read was valid
	if(read_back[0] == 0xF5 && read_back[7] == 0xF5 && check_sum == read_back[6]){
		printf("Valid Read\n");
		response[0] = read_back[2];
		response[1] = read_back[3];
		response[2] = read_back[4];
		return 0;
	}
	else{
		printf("Invalid Read\n");
		return -1;
	}

}

