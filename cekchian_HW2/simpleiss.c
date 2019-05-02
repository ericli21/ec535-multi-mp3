#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Node
{
	char instr_wo_addr[128];
	char instr_addr[128];
	char in1[5];
	char in2[5];
	char instr_name[128];
	struct Node *next;
} Node;


typedef struct key_value_pair
{
	char key[5];
	int8_t *value;
	struct Key_Value_Pair *kv_next;
} KeyValuePair;

Node *head = NULL;
Node *end = NULL;
KeyValuePair *kv_head = NULL;
KeyValuePair *kv_end = NULL;

bool latest_cmp_val = false;

int total_instructions = 0;
int total_instructions_executed = 0;
int total_clock_cycles = 0;
int total_hits_to_local_mem = 0;
int total_LD_ST_executed = 0;

void add_key_value_pair(char *key, int8_t *value) {

	KeyValuePair *kv_pair_intermediate = (KeyValuePair*) malloc(sizeof(KeyValuePair));
	strcpy(kv_pair_intermediate->key, key);
	kv_pair_intermediate->value = value;
	kv_pair_intermediate->kv_next = NULL;

	if (kv_head == NULL) {
		kv_head = kv_pair_intermediate;
		kv_end = kv_pair_intermediate;
		return;
	}

	kv_end->kv_next = kv_pair_intermediate;
	kv_end = kv_pair_intermediate;

	return;

}

int8_t *get_value(char *key) {
	KeyValuePair *kv_temp = kv_head;
	while (kv_temp != NULL) {
		if (strcmp(kv_temp->key, key) == 0) {
			return kv_temp->value;
		} else {
			kv_temp = kv_temp->kv_next;
		}
	}
	return NULL;
}

//Adds a node to the end of the linked list
void LL_AddNode(char* input_instr_addr, char* input_instr_name, char* input_in1, char* input_in2, char *input_instr_wo_addr)
{
	total_instructions++;
	Node *node_intermediate = (Node*) malloc(sizeof(Node));
	strcpy(node_intermediate->instr_wo_addr, input_instr_wo_addr);
	strcpy(node_intermediate->instr_addr, input_instr_addr);
	strcpy(node_intermediate->instr_name, input_instr_name);
	strcpy(node_intermediate->in1, input_in1);
	strcpy(node_intermediate->in2, input_in2);
	node_intermediate->next = NULL;

	if (head == NULL) {
		head = node_intermediate;
		end = node_intermediate;
		return;
	}

	end->next = node_intermediate;
	end = node_intermediate;

	return;

}

//load
void LD(uint8_t local_mem_ind, int8_t *local_mem, int8_t *local_mem_status, int8_t *reg_dst) {
	if (local_mem_status[local_mem_ind] == 0) {
		local_mem_status[local_mem_ind] = 1;
		total_clock_cycles += 45;
	} else {
		total_hits_to_local_mem++;
		total_clock_cycles += 2;
	}
	(*reg_dst) = local_mem[local_mem_ind];
	return;
}

//store
void ST(uint8_t local_mem_ind, int8_t *local_mem, int8_t *local_mem_status, int8_t *reg_src) {
	if (local_mem_status[local_mem_ind] == 0) {
		local_mem_status[local_mem_ind] = 1;
		total_clock_cycles += 45;
	} else {
		total_hits_to_local_mem++;
		total_clock_cycles += 2;
	}
	local_mem[local_mem_ind] = *(reg_src);
	return;
}

//move
void MOV(int8_t *reg, int8_t num) {
	(*reg) = num;
	return;
}

//add
void ADD(int8_t *reg_dst, int8_t num) {
	(*reg_dst) = (*reg_dst) + num;
	return;
}

//compare
bool CMP(int8_t *reg1, int8_t* reg2) {
	if ((*reg1) == (*reg2)) {
		return true;
	} else {
		return false;
	}
}

//loop through and get the node based on the instruction address
Node *getNode(char *instr_addr) {
	Node *temp = head;
	while (temp != NULL) {
		if (strcmp(temp->instr_addr,instr_addr) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;

}

//jump
Node* JMP(char *instr_addr) {
	Node *go_to_instr = getNode(instr_addr);
	return go_to_instr;
}

//Prints unknown instructions
void print_unknown_instr(char *instr_wo_addr) {
	printf("Unknown instruction: %s\n", instr_wo_addr);
	exit(1);
}

//Loop through the linked list and execute each instruction
//If the instruction is not valid, print error message and exit application
void execute_instructions(int8_t *local_mem, int8_t *local_mem_status) {
	Node *temp = head;

	while (temp != NULL) {
		total_instructions_executed++;
		if (strcmp(temp->instr_name, "MOV") == 0) {
			total_clock_cycles++;
			int8_t *reg1;
			reg1 = get_value(temp->in1);
			if (reg1 != NULL) {
				MOV(reg1, atoi(temp->in2));
			} else {
				print_unknown_instr(temp->instr_wo_addr);
			}
			temp= temp->next;
			
		} else if (strcmp(temp->instr_name, "ST") == 0) {
			total_LD_ST_executed++;
			int8_t *reg1, *reg2;
			if ((strlen(temp->in1) == 4) && (temp->in1[0] == '[')) {
				reg1 = get_value(temp->in1);
				reg2 = get_value(temp->in2);
				if (reg1 != NULL && reg2 !=NULL) {
					int8_t local_mem_ind = *(reg1);
					ST((uint8_t) local_mem_ind, local_mem, local_mem_status, reg2);
				} else {
					print_unknown_instr(temp->instr_wo_addr);
				}
			} else {
				print_unknown_instr(temp->instr_wo_addr);
			}
			temp= temp->next;
		} else if (strcmp(temp->instr_name, "LD") == 0) {
			total_LD_ST_executed++;
			if ((strlen(temp->in2) == 4) && (temp->in2[0] == '[')) {
				int8_t *reg1, *reg2;
				reg1 = get_value(temp->in2);
				reg2 = get_value(temp->in1);
				if (reg1 != NULL && reg2 != NULL) {
					int8_t local_mem_ind = *(reg1);
					LD((uint8_t) local_mem_ind, local_mem, local_mem_status, reg2);
				} else {
					print_unknown_instr(temp->instr_wo_addr);
				}
			} else {
				print_unknown_instr(temp->instr_wo_addr);
			}
			temp= temp->next;
			
		} else if (strcmp(temp->instr_name, "ADD") == 0) {
			total_clock_cycles++;
			int8_t *reg1, *reg2;
			reg1 = get_value(temp->in1);
			if (temp->in2[0] == 'R') {
				reg2 = get_value(temp->in2);
				if (reg1 != NULL && reg2 != NULL) {
					ADD(reg1, (*reg2));
				} else {
					print_unknown_instr(temp->instr_wo_addr);
				}
			} else {
				if (reg1 != NULL) {
					ADD(get_value(temp->in1), atoi(temp->in2));
				} else {
					print_unknown_instr(temp->instr_wo_addr);
				}
			}
			temp= temp->next;
			
		} else if (strcmp(temp->instr_name, "CMP") == 0) {
			total_clock_cycles++;
			int8_t *reg1, *reg2;
			reg1 = get_value(temp->in1);
			reg2 = get_value(temp->in2);
			if (reg1 != NULL && reg2 != NULL) {
				latest_cmp_val = CMP(reg1, reg2);
			} else {
				print_unknown_instr(temp->instr_wo_addr);
			}
			temp= temp->next;
		} else if (strcmp(temp->instr_name, "JE") == 0) {
			total_clock_cycles++;
			if (atoi(temp->in1) < 0) {
				print_unknown_instr(temp->instr_wo_addr);
			}
			if (latest_cmp_val == true) {
				temp= JMP(temp->in1);
			} else {
				temp= temp->next;
			}
			if (temp->in1 < 0) {
				print_unknown_instr(temp->instr_wo_addr);
			}
		} else if (strcmp(temp->instr_name, "JMP") == 0) {
			total_clock_cycles++;
			if (atoi(temp->in1) < 0) {
				print_unknown_instr(temp->instr_wo_addr);
			}
			temp = JMP(temp->in1);
		} else {
			print_unknown_instr(temp->instr_wo_addr);
		}
	}
}

void print_console_output(){
	printf("Total number of instructions in code: %d\n", total_instructions);
	printf("Total number of executed instructions: %d\n", total_instructions_executed);
	printf("Total number of clock cycles: %d\n", total_clock_cycles); 
	printf("Number of hits to local memory: %d\n", total_hits_to_local_mem);
	printf("Total number of executed LD/ST instructions: %d\n", total_LD_ST_executed);
}

int main(int argc, char **argv) {
	char* instr_filename = argv[1];

	int8_t R1 = 0;
	int8_t R2 = 0;
	int8_t R3 = 0;
	int8_t R4 = 0;
	int8_t R5 = 0;
	int8_t R6 = 0;

	//Create linked list of key value pairs for register strings and their memory addresses
	add_key_value_pair("R1", &R1);
	add_key_value_pair("R2", &R2);
	add_key_value_pair("R3", &R3);
	add_key_value_pair("R4", &R4);
	add_key_value_pair("R5", &R5);
	add_key_value_pair("R6", &R6);
	add_key_value_pair("[R1]", &R1);
	add_key_value_pair("[R2]", &R2);
	add_key_value_pair("[R3]", &R3);
	add_key_value_pair("[R4]", &R4);
	add_key_value_pair("[R5]", &R5);
	add_key_value_pair("[R6]", &R6);

	FILE *instr_fp;

	//unsigned int instr_addr;
	char instr_addr[128];
	char instr_whole[256];
	char instr_name[128];
	char in1[128];
	char in2[128];
	int vars_filled = 0;
	char instr_wo_addr[128];

	int8_t local_mem[256]= {0};
	int8_t local_mem_status[256]= {0};
	char* in2_str_empty = "";

	instr_fp = fopen(instr_filename, "r");

	//Read through the file line by line
	while(fgets(instr_whole, 256, instr_fp) != NULL) {
		sscanf(instr_whole, "%s    %[^\r\n]", instr_addr, instr_wo_addr);
		vars_filled = sscanf(instr_whole, "%s    %s %[^,], %[^\r\n]", instr_addr, instr_name, in1, in2);
		if (vars_filled == 3) {
			vars_filled = sscanf(instr_whole, "%s    %s %[^\r\n]", instr_addr, instr_name, in1);
		}
		if (vars_filled == 3) {
			strcpy(in2, in2_str_empty);
		}
		LL_AddNode(instr_addr, instr_name, in1, in2, instr_wo_addr);
	}

	//execute all of the instructions
	execute_instructions(local_mem, local_mem_status);
	fclose(instr_fp);

	print_console_output();

	return 0;

}

