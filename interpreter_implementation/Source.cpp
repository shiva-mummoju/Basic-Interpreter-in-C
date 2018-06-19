#include "Header.h"
//#include "helper_functions.h"

void load_all_global_structures();
void load_opcodes_table();
void show_opcode_table();
void load_intermeditate_code_table(char* filename);
int return_opcode(char* str);
void add_to_symbol_table(char* var,int flag);
void show_symbol_table();
void add_to_intermediate_table(char* buff);
void show_intermediate_code_table();
int isRegister(char* str);
int get_the_address_of_variable(char* token);
void show_label_table();
int find_label_in_table(char* token);
void execute_code();
char* substring(char* source, int start, int end);
int get_value_of_constant(char* token);
void load_code();
void save_my_data1();
void load_save_data1();
void free_the_data();


int main(){
	load_all_global_structures();
	load_opcodes_table();
	int choice =0;
	while (true){
		printf("\n 1: Load and Execute\n");
		printf("\n 2: Generate output file\n");
		printf("\n 3: Execute output file\n");
		printf("\n 4: Generate c file\n");
		printf("\n 5: exit\n");
		printf("\nEnter choice: ");
		scanf("%d", &choice);

		if (choice == 1){
			load_code();
			execute_code();
		}
		else if (choice == 2){
			load_code();
			save_my_data1();
		}
		else if (choice == 3){
			//load_code();
			load_save_data1();
			execute_code();
		}
		else if (choice == 4){
			
		}
		else{
			free_the_data();
			return 0;
		}
	}



	int k;
	scanf("%d", &k);
}

void free_the_data(){
	//free(intermediate_code_table);
	///free(label_table);
	//free(symbol_table);
	//free(mystack);
}

void load_save_data1(){
	char* delim = ",";
	char* token;
	char* file_name = (char*)malloc(sizeof(char) * 10);
	printf("Enter object filename: ");
	scanf("%s", file_name);
	char* buff = (char*)malloc(sizeof(char)*30);
	FILE* f = fopen(file_name, "r");
	fscanf(f, "%s", buff);
	
	intermediate_code_table_count = atoi(strtok(buff, delim));
	for (int i = 0; i < intermediate_code_table_count; i++){
		fscanf(f, "%s", buff);
		intermediate_code_table[i]->code = atoi(strtok(buff,delim));
		intermediate_code_table[i]->param1 = atoi(strtok(NULL, delim));
		intermediate_code_table[i]->param2 = atoi(strtok(NULL, delim));
		intermediate_code_table[i]->param3 = atoi(strtok(NULL, delim));
		intermediate_code_table[i]->param4 = atoi(strtok(NULL, delim));
	}
	fscanf(f, "%s", buff);
	symbol_table_count = atoi(strtok(buff, delim));
	for (int i = 0; i < symbol_table_count; i++){
		fscanf(f, "%s", buff);
		symbol_table[i]->address = atoi(strtok(buff, delim));
		symbol_table[i]->constant = atoi(strtok(NULL, delim));
		symbol_table[i]->name = (char*)malloc(sizeof(char) * 20);
		strcpy(symbol_table[i]->name, strtok(NULL, delim));
		symbol_table[i]->size = atoi(strtok(NULL, delim));
	}
	fscanf(f, "%s", buff);
	label_table_count = atoi(strtok(buff, delim));

	for (int i = 0; i < label_table_count; i++){
		fscanf(f, "%s", buff);
		label_table[i]->address = atoi(strtok(buff, delim));
		label_table[i]->name = (char*)malloc(sizeof(char) * 20);
		strcpy(label_table[i]->name, strtok(NULL, delim));
	}
	fclose(f);
}

void save_my_data1(){
	char* file_name = (char*)malloc(sizeof(char) * 10);
	printf("Enter destination filename: ");
	scanf("%s", file_name);

	FILE* f = fopen(file_name, "w");
	fprintf(f, "%d,\n", intermediate_code_table_count);
	for (int i = 0; i < intermediate_code_table_count; i++){
		fprintf(f, "%d,%d,%d,%d,%d,\n", intermediate_code_table[i]->code,
			intermediate_code_table[i]->param1,
			intermediate_code_table[i]->param2,
			intermediate_code_table[i]->param3,
			intermediate_code_table[i]->param4);
	}
	fprintf(f, "%d,\n", symbol_table_count);
	for (int i = 0; i < symbol_table_count; i++){
		fprintf(f, "%d,%d,%s,%d,\n", symbol_table[i]->address,
			symbol_table[i]->constant,
			symbol_table[i]->name,
			symbol_table[i]->size);
	}
	fprintf(f, "%d,\n", label_table_count);
	for (int i = 0; i < label_table_count; i++){
		fprintf(f, "%d,%s,\n", label_table[i]->address, label_table[i]->name);
	}
	//free_the_data();
	fclose(f);



}

void load_code(){
	

	

	char* file_name = (char*)malloc(sizeof(char) * 10);
	printf("Enter source filename: ");
	scanf("%s", file_name);

	load_intermeditate_code_table(file_name);
	//show_opcode_table();
//	show_label_table();
	//show_symbol_table();
	//show_intermediate_code_table();

	free(file_name);

}


void load_all_global_structures(){
	int i;
	intermediate_code_table = (struct codeTable**)malloc(sizeof(struct codeTable*) * 500);
	for (i = 0; i < 500; i++){
		intermediate_code_table[i] = (struct codeTable*)malloc(sizeof(codeTable));
	}

	

	label_table = (struct label**)malloc(sizeof(struct label*) * 100);
	for (i = 0; i < 100; i++){
		label_table[i] = (label*)malloc(sizeof(struct label));
	}
	memory_word = (char*)malloc(sizeof(char) * 1000);
	for (i = 0; i < 1000; i++){
		memory_word[i] = 0;
	}
	symbol_table = (struct symbol**)malloc(sizeof(symbol*) * 100);
	for (i = 0; i < 100; i++){
		symbol_table[i] = (symbol*)malloc(sizeof(symbol));
	}
	opcodes = (opcode**)malloc(sizeof(opcode*) * 20);
	for ( i = 0; i < 20; i++)
	{
		opcodes[i] = (opcode*)malloc(sizeof(opcode));
	}
	
	
	//show_opcode_table();


}




void load_opcodes_table(){
	FILE* f = fopen("opcodes.txt","r");
	char* buff = (char*)malloc(sizeof(char)*30);
	int i = 0;
	while (fscanf(f, "%s", buff) != EOF){
		opcodes[opcodes_count]->instruction = (char*)malloc(sizeof(char)*strlen(buff));
		for ( i = 0; i < strlen(buff) && buff[i]!='\n'; i++){
			opcodes[opcodes_count]->instruction[i] = buff[i];
		}
		opcodes[opcodes_count]->instruction[i] = '\0';
		//strcpy(opcodes[opcodes_count]->instruction , buff);
		//printf("%s", buff);
		
		fscanf(f, "%s", buff);
		opcodes[opcodes_count]->code = atoi(buff);
		opcodes_count++;
	}

	fclose(f);

}



void show_opcode_table(){
	for (int i = 0; i < opcodes_count; i++){
		printf("%s %d\n", opcodes[i]->instruction, opcodes[i]->code);
	}
	int k;
	scanf("%d", &k);
}

void load_intermeditate_code_table(char* file_name){
	FILE* f = fopen(file_name, "r");
	char* buff =(char*)malloc(sizeof(char)*20);
	char temp[20];
	while (fscanf(f, "%s", buff) != EOF && strcmp(buff, "START:")){
		//declaration part
		//printf("%s\n", buff);
		if (!strcmp(buff, "DATA")){
			fscanf(f, "%s", buff);
			//add the symbol to the symbol table
			add_to_symbol_table(buff,0);
		}if (!strcmp(buff, "CONST")){
			fscanf(f, "%s", buff);
			add_to_symbol_table(buff, 1);
		}

	}
	//show_symbol_table();
	printf("\n****************\n");
	while (fgets(buff, 300, f) && strcmp(buff, "END")){
		//execution part
		if (buff[0] == '\t'){
			buff = buff + 1;
		}
		
		buff[strlen(buff) - 1] = '\0';
		if (strlen(buff) == 0){
			continue;
		}
		add_to_intermediate_table(buff);
		//printf("%s\n", buff);
	}
		fclose(f);
	//	show_intermediate_code_table();
}




int return_opcode(char* str){
	for (int i = 0; i < opcodes_count; i++){
		if (!strcmp(opcodes[i]->instruction, str)){
			return opcodes[i]->code;
		}
	}
	return -1;

}



void add_to_symbol_table(char* var,int flag){
	int i;
	char* token;
	int array_check = 0;
	if (flag == 0){
		for (i = 0; i < strlen(var); i++){
			if (var[i] == '['){
				array_check = 1;
			}
		}
		if (array_check == 0){
			symbol_table[symbol_table_count]->name = (char*)malloc(sizeof(char)*strlen(var));
			for (i = 0; i < strlen(var); i++){
				symbol_table[symbol_table_count]->name[i] = var[i];
			}
			symbol_table[symbol_table_count]->name[i] = '\0';
			symbol_table[symbol_table_count]->constant = 0;
			symbol_table[symbol_table_count]->address = memory_word_count;
			symbol_table[symbol_table_count]->size = 1;
			memory_word_count = memory_word_count + 1;
			symbol_table_count++;
		}
		else{
			token = strtok(var, "[]");
			symbol_table[symbol_table_count]->name = (char*)malloc(sizeof(char)*strlen(token));
			for (i = 0; i < strlen(token); i++){
				symbol_table[symbol_table_count]->name[i] = token[i];
			}
			symbol_table[symbol_table_count]->name[i] = '\0';
			symbol_table[symbol_table_count]->constant = 0;
			symbol_table[symbol_table_count]->address = memory_word_count;
			token = strtok(NULL, "[]");
			symbol_table[symbol_table_count]->size = atoi(token);
			memory_word_count = memory_word_count + atoi(token);
			symbol_table_count++;

		}
		
	}
	else{

		//considering constants as only smallvariablesand not as arrays
		token = strtok(var, "=");
		symbol_table[symbol_table_count]->name = (char*)malloc(sizeof(char)*strlen(token));
		for (i = 0; i < strlen(token); i++){
			symbol_table[symbol_table_count]->name[i] = token[i];
		}
		symbol_table[symbol_table_count]->name[i] = '\0';
		//strcpy(symbol_table[symbol_table_count]->name, token);
		
		symbol_table[symbol_table_count]->address = -1;
		symbol_table[symbol_table_count]->size = 0;
		token = strtok(NULL, " ,");
		symbol_table[symbol_table_count]->constant = atoi(token);
		symbol_table_count++;

	}

}


void show_symbol_table(){
	int i;
	printf("\n*** symbol table*** \n");
	printf("\n index name address constant size\n");
	for (i = 0; i < symbol_table_count; i++){
		printf(" %d %s %d %d %d\n",i, symbol_table[i]->name, symbol_table[i]->address, symbol_table[i]->constant, symbol_table[i]->size);
	}
}



void add_to_intermediate_table(char* line){
	if (line == NULL || line == ""){
		return;
	}
	if (strlen(line) == 1){
		return;
	}
	//printf("Adding to I table %s", line);
	char* delim = " ,:";
	char* temp1;
	int register_code = 0;
	char* token = strtok(line, delim);

	//printf("%s %d\n", token, strlen(token));
	if (!strcmp(token, "READ")){
		//printf("doing read\n");
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("READ");
		token = strtok(NULL, delim);
		//token[strlen(token) - 1] = '\0';
		if (token == NULL){
			return;
		}
		register_code = isRegister(token);

		///reading into register
		if (register_code>=0){
			//creatign 17 as new opcode which says that we have to read into the register value;
			intermediate_code_table[intermediate_code_table_count]->code = 17;
			intermediate_code_table[intermediate_code_table_count]->param1 = register_code;
			intermediate_code_table[intermediate_code_table_count]->param2 = -1;
			intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
			intermediate_code_table_count++;
			return;
		}//reading into a normal variable
		else{
			intermediate_code_table[intermediate_code_table_count]->param1 = get_the_address_of_variable(substring(token,0,strlen(token)-1));
			intermediate_code_table[intermediate_code_table_count]->param2 = -1;
			intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
			intermediate_code_table_count++;
			return;
		}
		
	} else if (!strcmp(token, "MOV")){
		//printf("doing mov\n");
		
		token = strtok(NULL, " ,");
		if (token == NULL){
			return;
		}
		//printf("token recieved is %s\n", token);
		register_code = isRegister(token);
		// if in the mov, first is register
		if (register_code >= 0){
			intermediate_code_table[intermediate_code_table_count]->code = 1;
			intermediate_code_table[intermediate_code_table_count]->param1 = register_code;
			token = strtok(NULL, delim);
			//token[strlen(token) - 1] = '\0';
			intermediate_code_table[intermediate_code_table_count]->param2 = get_the_address_of_variable(token);
			int k = intermediate_code_table[intermediate_code_table_count]->param2;
			if (k == -1){
				intermediate_code_table[intermediate_code_table_count]->param3 = get_value_of_constant(token);
			}
			else{
				intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			}
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
			intermediate_code_table_count++;
			return;
		}
		else{
			intermediate_code_table[intermediate_code_table_count]->code = 2;
			char* first_token_copy = (char*)malloc(sizeof(char*)*strlen(token));
			
			strcpy(first_token_copy, token);
			token = strtok(NULL, " ,");
			char* second_token_copy = (char*)malloc(sizeof(char*)*strlen(token));
			strcpy(second_token_copy, token);
		//	second_token_copy[strlen(second_token_copy) - 1] = '\0';
			register_code = isRegister(second_token_copy);
			intermediate_code_table[intermediate_code_table_count]->param1 = get_the_address_of_variable(first_token_copy);
			intermediate_code_table[intermediate_code_table_count]->param2 = register_code;
			intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
			intermediate_code_table_count++;
			free(first_token_copy);
			free(second_token_copy);
			return;
		}
	}
	else if (!strcmp(token, "ADD")){
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("ADD");
		intermediate_code_table[intermediate_code_table_count]->param1 = isRegister(token);
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->param2 = isRegister(token);
		token = strtok(NULL, " ,");
		//token[strlen(token) - 1] = '\0';
		intermediate_code_table[intermediate_code_table_count]->param3 = isRegister(token);
		intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		intermediate_code_table_count++;
		return;
	}
	else if (!strcmp(token, "SUB")){
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("SUB");
		intermediate_code_table[intermediate_code_table_count]->param1 = isRegister(token);
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->param2 = isRegister(token);
		token = strtok(NULL, " ,");
	//	token[strlen(token) - 1] = '\0';
		intermediate_code_table[intermediate_code_table_count]->param3 = isRegister(token);
		intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		intermediate_code_table_count++;
		return;
	}
	else if (!strcmp(token, "MUL")){
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("MUL");
		intermediate_code_table[intermediate_code_table_count]->param1 = isRegister(token);
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->param2 = isRegister(token);
		token = strtok(NULL, " ,");
		//token[strlen(token) - 1] = '\0';
		intermediate_code_table[intermediate_code_table_count]->param3 = isRegister(token);
		intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		intermediate_code_table_count++;
		return;
	}
	else if (!strcmp(token, "IF")){
		//do if
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("IF");
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->param1 = isRegister(token);
		token = strtok(NULL, " ,");
		intermediate_code_table[intermediate_code_table_count]->param3 = return_opcode(token);
		token = strtok(NULL, " ,");
		//token[strlen(token) - 1] == '\0';
		intermediate_code_table[intermediate_code_table_count]->param2 = isRegister(token);
		intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		mystack[++mystack_top] = intermediate_code_table_count;
		intermediate_code_table_count++;

		return;

	}

	else if (!strcmp(token, "PRINT")){
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("PRINT");
		token = strtok(NULL, " ,");
			
		if (isRegister(token) >= 0){
			//token[strlen(token) - 1] = '\0';
			intermediate_code_table[intermediate_code_table_count]->code = 16;
			intermediate_code_table[intermediate_code_table_count]->param1 = isRegister(token);
			intermediate_code_table[intermediate_code_table_count]->param2 = -1;
			intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
			intermediate_code_table_count++;
		}
		else{
				intermediate_code_table[intermediate_code_table_count]->code = return_opcode("PRINT");
				if (strlen(token) == 1){
					intermediate_code_table[intermediate_code_table_count]->param1 = get_the_address_of_variable(token);
					if (intermediate_code_table[intermediate_code_table_count]->param1 == -1){
						//get the value of the constant. the lengh of the token is not giving any problem
						intermediate_code_table[intermediate_code_table_count]->param2 = get_value_of_constant(token);
					}
					else{
						//the returned is a normal variable
						intermediate_code_table[intermediate_code_table_count]->param2 = -1;
					}
				}
				else{
					intermediate_code_table[intermediate_code_table_count]->param1 = get_the_address_of_variable(token);
					if (intermediate_code_table[intermediate_code_table_count]->param1 == -1){
						//get the value of the constant. token len is diff
						intermediate_code_table[intermediate_code_table_count]->param2 = get_value_of_constant(token);
					}
					else{
						intermediate_code_table[intermediate_code_table_count]->param2 = -1;
					}
				}


				intermediate_code_table[intermediate_code_table_count]->param3 = -1;
				intermediate_code_table[intermediate_code_table_count]->param4 = -1;
				intermediate_code_table_count++;
			
		}


		return;
	}else if (!strcmp(token, "JUMP")){
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("JUMP");
		token = strtok(NULL, " ,");
		//token[strlen(token) -1] = '\0';
		intermediate_code_table[intermediate_code_table_count]->param1 = find_label_in_table(token);
		intermediate_code_table[intermediate_code_table_count]->param2 = -1;
		intermediate_code_table[intermediate_code_table_count]->param3 = -1;
			intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		intermediate_code_table_count++;

		return;
	}else if (token[0]=='E' && token[1]=='L' && token[2]=='S' && token[3]=='E'){
		intermediate_code_table[intermediate_code_table_count]->code = return_opcode("JUMP");
		int intial_if = mystack[mystack_top];
		intermediate_code_table[intial_if]->param4 = intermediate_code_table_count+1;
		mystack_top--;
		mystack[++mystack_top] = intermediate_code_table_count;
		intermediate_code_table[intermediate_code_table_count]->param1 = -1;
		intermediate_code_table[intermediate_code_table_count]->param2 = -1;
		intermediate_code_table[intermediate_code_table_count]->param3 = -1;
		intermediate_code_table[intermediate_code_table_count]->param4 = -1;
		intermediate_code_table_count++;

		return;
	}
	else if (strlen(token) >= 5 && token[0] == 'E' && token[1] == 'N' && token[2] == 'D' && token[3] == 'I' && token[4] == 'F'){
		//pop the corresponding else
		int else_code = mystack[mystack_top--];
		intermediate_code_table[else_code]->param1 = intermediate_code_table_count;
		return;
	}
	else{
		//this is for labels
		//token[strlen(token) - 1] = '\0';
		int f;
		label_table[label_table_count]->name = (char*)malloc(sizeof(char)*strlen(token));
		for (f = 0; f < strlen(token); f++){
			label_table[label_table_count]->name[f] = token[f];
		}
		label_table[label_table_count]->name[f] = '\0';
		
		label_table[label_table_count]->address = intermediate_code_table_count;
		label_table_count++;
		return;
	}

}


void show_intermediate_code_table(){
	printf("\n ******* table ***** \n");
	printf("\n index opcode param1 param2 param3 param4 \n");
	for (int i = 0; i < intermediate_code_table_count; i++){
	
		printf("%d %d %d %d %d %d\n",i, intermediate_code_table[i]->code,
			intermediate_code_table[i]->param1,
			intermediate_code_table[i]->param2,
			intermediate_code_table[i]->param3,
			intermediate_code_table[i]->param4);
	}
}



int isRegister(char* str){
	//printf("\n retrieving register code %s", str);
	if (strlen(str) == 2 && (str[0] >= 'A' && str[0] <= 'H') && str[1] == 'X'){
		//printf("%d\n", str[0] - 'A');

		return str[0] - 'A';
	}
	else{
		//printf("-1\n");
		return -1;
	}
}


int get_value_of_constant(char* token){

	//printf("\n get address of variable %s ", token);
	int k;
	char* token_copy = (char*)malloc(sizeof(char)*strlen(token));
	for (k = 0; k < strlen(token); k++){
		token_copy[k] = token[k];
	}
	token_copy[k] = '\0';
	int check = 1;

	char* local_token;

	local_token = strtok(token_copy, "[");


	/*local_token[strlen(local_token) - 1] = '\0';*/

	for (int i = 0; i < symbol_table_count; i++){
		if (!strcmp(symbol_table[i]->name, local_token)){

			if (symbol_table[i]->address == -1){
				//printf("%d", symbol_table[i]->constant);
				//return -1;
				return symbol_table[i]->constant;
			}

			//if the variable is not array

			if (symbol_table[i]->size == 1){
				//printf("%d\n", symbol_table[i]->address);
				return symbol_table[i]->address;
			}
			else{
				local_token = strtok(NULL, "[]");
				//printf("%d\n", symbol_table[i]->address + atoi(local_token));
				return symbol_table[i]->address + atoi(local_token);
			}

			// if the variable is a not array
		}
		if (symbol_table[i]->address == -1){
			check = 1;
			for (k = 0; k < strlen(symbol_table[i]->name) && k < strlen(token_copy); k++){
				if (symbol_table[i]->name[k] != token_copy[k]){
					check = 0;
				}
			}
			if (check == 1){
				//local_token = strtok(NULL, " ");
				//printf("%d\n", symbol_table[i]->address + atoi(local_token));
				return i;
			}

		}
	}
	//printf("1\n");

	return -1;
}


int get_the_address_of_variable(char* token){
	//printf("\n get address of variable %s ", token);
	int k;
	char* token_copy = (char*)malloc(sizeof(char)*strlen(token));
	for ( k = 0; k < strlen(token); k++){
		token_copy[k] = token[k];
	}
	token_copy[k] = '\0';
	int check = 1;

	char* local_token;

		local_token = strtok(token_copy, "[");
	

	/*local_token[strlen(local_token) - 1] = '\0';*/

	for (int i = 0; i < symbol_table_count; i++){
		if (!strcmp(symbol_table[i]->name, local_token)){
			
			if (symbol_table[i]->address == -1){
				//printf("%d", symbol_table[i]->constant);
				return -1;
				//return symbol_table[i]->constant;
			}

			//if the variable is not array

			if (symbol_table[i]->size == 1){
				//printf("%d\n", symbol_table[i]->address);
				return symbol_table[i]->address;
			}
			else{
				local_token = strtok(NULL, "[]");
				//printf("%d\n", symbol_table[i]->address + atoi(local_token));
				return symbol_table[i]->address + atoi(local_token);
			}

			// if the variable is a not array
		}
		if (symbol_table[i]->address == -1){
			check = 1;
			for (k = 0; k < strlen(symbol_table[i]->name) && k < strlen(token_copy); k++){
				if (symbol_table[i]->name[k] != token_copy[k]){
					check = 0;
				}
			}
			if (check == 1){
				//local_token = strtok(NULL, " ");
				//printf("%d\n", symbol_table[i]->address + atoi(local_token));
				return i;
			}

		}
	}
	//printf("1\n");
	
	return -1;
}


int give_back_correct_value(char* str){
	if (isRegister(str) >= 0){
		return isRegister(str);
	}
	else{
		get_the_address_of_variable(str);
	}
}


void show_label_table(){
	printf("\n****** label table  ********\n");
	printf("Name Adress\n");
	for (int i = 0; i < label_table_count; i++){
		printf("%s %d\n", label_table[i]->name, label_table[i]->address);
	}
}



void execute_code(){

	printf("\n****** Execution ********\n");
	int register_code;
	int symbol_index_1;
	int symbol_index_2;

	char a, b;
	int choice = 0;
	for (int i = 0; i < intermediate_code_table_count; i++){
		choice = intermediate_code_table[i]->code;
		if (choice == 1){
			//printf("MOV from var to register\n");
			register_code = intermediate_code_table[i]->param1;
			symbol_index_1 = intermediate_code_table[i]->param2;
			if (symbol_index_1 == -1){
				register_array[register_code] = intermediate_code_table[i]->param3;
			}
			else{
				register_array[register_code] = memory_word[symbol_table[symbol_index_1]->address];
			}

		}
		else if (choice == 2){
			//printf("MOV register to var\n");
			register_code = intermediate_code_table[i]->param2;
			symbol_index_1 = intermediate_code_table[i]->param1;
			memory_word[symbol_table[symbol_index_1]->address] = register_array[register_code]  ;
		}
		else if (choice == 3){
			//printf("Add\n");
			a = register_array[intermediate_code_table[i]->param2];
			b = register_array[intermediate_code_table[i]->param3];
			register_code = intermediate_code_table[i]->param1;
			int c = a - '0';
			int d = b - '0';
			register_array[register_code] = a+b ;
		}
		else if (choice == 4){
			//printf("Sub\n");
			a = register_array[intermediate_code_table[i]->param2];
			b = register_array[intermediate_code_table[i]->param3];
			register_code = intermediate_code_table[i]->param1;
			int c = a - '0';
			int d = b - '0';
			register_array[register_code] = a - b;
		}
		else if (choice == 5){
			//printf("Multiply\n");
			a = register_array[intermediate_code_table[i]->param2];
			b = register_array[intermediate_code_table[i]->param3];
			register_code = intermediate_code_table[i]->param1;

			register_array[register_code] = (a * b) ;
		}
		else if (choice == 6){
		//	printf("Jump\n");
			i = intermediate_code_table[i]->param1-1;
		}
		else if (choice == 13){
			//printf("print\n");
			//printing the value
			symbol_index_1 = intermediate_code_table[i]->param1;
			//if arg is constant, take the second param and print
			if (symbol_index_1 == -1){
				printf("%d\n", intermediate_code_table[i]->param2);
			}
			else{//if arg is variable, then normally print from memory word
				printf("%d\n", memory_word[symbol_index_1]);
			}
		}
		else if (choice == 16){
			//printf("mov\n");
			register_code = intermediate_code_table[i]->param1;
			printf("%d\n", register_array[register_code]);
		}
		else if (choice == 14){
			//printf("Readingg into var\n");
			printf("Enter value: ");
			scanf("%c", &memory_word[intermediate_code_table[i]->param1]);
			fflush(stdin);
		}
		else if (choice  == 17){
			//printf("reading into register\n");
			printf("Enter value: ");
			scanf("%d", &register_array[intermediate_code_table[i]->param1]);
			fflush(stdin);
		}
		else if (choice == 7){
			//printf("if\n");
			int  goto_val = intermediate_code_table[i]->param4;
			int a = register_array[intermediate_code_table[i]->param1] ;
			int b = register_array[intermediate_code_table[i]->param2] ;

			int choice = intermediate_code_table[i]->param3;

			if (choice == 8){
				//equals
				if (a != b){
					i = goto_val - 1;
				}
			}
			else if (choice == 9){
				//less than
				if (a >= b){
					i = goto_val - 1;
				}
			}
			else if (choice == 10){
				//greater than
				if (a <= b){
					i = goto_val - 1;
				}
			}
			else if (choice == 11){
				// less that or equal to
				if (a > b){
					i = goto_val - 1;
				}
			}
			else if (choice == 12){
				//greater than or equal to
				if (a < b){
					i = goto_val - 1;
				}
			}

		}
	}

	printf("\n***** End of execution *****\n");
}

