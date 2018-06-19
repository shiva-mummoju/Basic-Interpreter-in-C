#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// opcodes 
//structure for opcode_table
//array for registers
//stack for if and else cases
//structure for label table
//one big char array which acts as memory
//structure for symbol table
struct opcode{
	char* instruction;
	int code;
};
struct codeTable{
	int code;
	int param1;
	int param2;
	int param3;
	int param4;
};
struct label{
	char* name;
	int address;
};

struct symbol{
	char* name;
	int address;
	int size;
	int constant;
};
opcode** opcodes;
int opcodes_count = 0;
int register_array[8];
char mystack[100];
int mystack_top = -1;
char* memory_word;
int memory_word_count;
symbol** symbol_table;
codeTable** intermediate_code_table;
int intermediate_code_table_count = 0;
int symbol_table_count = 0;
struct label** label_table;
int label_table_count = 0;

char* substring(char* source, int start, int end){
	char* result = (char*)malloc(sizeof(char)*(end - start + 1));
	int result_count = 0;
	for (int i = start; i <= end; i++){
		result[result_count++] = source[i];
	}
	result[result_count] = '\0';
	return result;
}


int find_label_in_table(char* token){
	for (int i = 0; i < label_table_count; i++){
		if (!strcmp(label_table[i]->name, token)){
			return label_table[i]->address;
		}
	}
	return -1;
}
