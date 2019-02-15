#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int global_address = 0;
struct instruction{
    char instr[10];
    char opcode[10];
    bool checked2;
};

struct instruction *opcodeArray;
char arr[50][5];
bool checked[50] = {false};

void getOpcodeArray(FILE *inputOpcodeFile)
{
	opcodeArray = (struct instruction *)malloc(12*sizeof(struct instruction));
	for(int i=0;i<12;i++)
		opcodeArray[i].checked2 = false;	

    char s[15];    
    int n = 15;    
    for(int i = 0; i < 12; i++)
    {
        fgets(s, n, inputOpcodeFile);
        char _opcode[10] = {'\0'};
        char _instruction[10] = {'\0'};
        sscanf(s,"%s %s", _instruction, _opcode);
        strcpy(opcodeArray[i].instr, _instruction);
        strcpy(opcodeArray[i].opcode, _opcode);
    }

    //for(int i=0;i<12;i++)
    	//printf("%s %s\n", opcodeArray[i].instr, opcodeArray[i].opcode );
}


int check1(char a[100], char b[100]) //for MOV, ADD, SUB, AND, OR, CMP
{
	if(a[0] == 'R' && b[0] == 'R') //both are registers
		return 2; //14
	if(a[0] == 'R' && b[0] != 'R') //one of them is register
		return 4; //25
	if(a[0] != 'R' && b[0] == 'R') //one of them is register
		return 4; //25;
	if(a[0] != 'R' && b[0] != 'R') //none of them are registers
		return 5; //36
}

int check2(char a[100]) //for MUL
{
	if(a[0] == 'R') // If it is a register
		return 2; //14
	if(a[0] != 'R')
		return 4; //25
}

int check3(char a[100]) //for NOT
{
	if(a[0] == 'R') // If it is a register
		return 2; //9
	if(a[0] != 'R')
		return 3; //20
}

int check4(char a[100]) //for LOOP, JMP, JNZ -> will always be followed by a label
{
	return 3; //20
}

int check5() //for HLT
{
	return 1; //4
}	


void pass1(FILE *inputFile)
{
	FILE *outputOpcode = fopen("Table.txt", "w");
	FILE *outputSymbol = fopen("Symbol.txt", "w");
	char s[300];
	int n=300;

	int x=1;
	int start = 0;
	while( fgets(s,n,inputFile) )
	{	
		int colon_flag = 0;
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ':')
				colon_flag = 1;

			if(s[i] == ',' || s[i] == ':')
				s[i] = ' ';
			
		}
		int read = 0;
		int len = strlen(s);
		char first[100] = {'\0'};
		char second[100] = {'\0'};
		char third[100] = {'\0'};
		char fourth[100] = {'\0'};

		if(colon_flag == 1)
			read = sscanf(s," %s %s %s %s ", first, second, third, fourth);
		else
			read = sscanf(s," %s %s %s ", second, third, fourth);

		if(start == 0)
		{	
			if( strcmp(second,"START") == 0)
				start =1;
			continue;
		}

		if(colon_flag == 1) //this means there is a label and I need to print the address
		{
			printf("%s %d\n", first, global_address );
		}

		if(second[0] == 'L' && second[1] == 'O' && second[2] == 'O')
		{
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"SUB") == 0 && !opcodeArray[i].checked2)
				{
					opcodeArray[i].checked2 = true;
					fprintf(outputOpcode, "SUB %s\n" , opcodeArray[i].opcode);
				}
			}

			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"JNZ") == 0 && !opcodeArray[i].checked2)
				{
					opcodeArray[i].checked2 = true;
					fprintf(outputOpcode, "JNZ %s\n" , opcodeArray[i].opcode);
				}
			}
		}
		
		for(int i=0;i<12;i++)
		{
			if( strcmp(opcodeArray[i].instr,second) == 0 && !opcodeArray[i].checked2)
			{
				opcodeArray[i].checked2 = true;
				fprintf(outputOpcode, "%s %s\n" , second, opcodeArray[i].opcode);
			}
		}	

		if(second[0] == 'M' && second[1] == 'O' ) //Move  
			global_address += check1(third,fourth);

		if(second[0] == 'A' && second[1] == 'D') //Add
			global_address += check1(third,fourth);

		if(second[0] == 'S' && second[1] == 'U') //Subtract 
			global_address += check1(third,fourth);

		if(second[0] == 'M' && second[1] == 'U') //Multiply 
			global_address += check2(third);

		if(second[0] == 'C' && second[1] == 'M') //Comparator 
			global_address += check1(third,fourth);

		if(second[0] == 'A' && second[1] == 'N') //And
			global_address += check1(third,fourth);

		if(second[0] == 'O' && second[1] == 'R') //Or
			global_address += check1(third,fourth);

		if(second[0] == 'N' && second[1] == 'O') //Not
			global_address += check3(third);

		if(second[0] == 'J' && second[1] == 'M') //Jump 
			global_address += check4(third);

		//Must be handled separately
		if(second[0] == 'L' && second[1] == 'O') //Loop 
		{
			global_address += check4(third); //for the JNZ part
			global_address += 4; //for the subtract part of LOOP (Subtracting one from Reg31)
		}

		if(second[0] == 'H' && second[1] == 'L') //Halt  
			global_address += check5();

		if(second[0] == 'J' && second[1] == 'N') //Jump if Negative  
			global_address += check4(third);
	}
	fclose(outputOpcode);
	fclose(outputSymbol);
}


void pass2(FILE *inputFile)
{
	global_address = 0;
	char s[300];
	int n=300;

	int x=1;
	int start = 0;
	while( fgets(s,n,inputFile) )
	{	
		int colon_flag = 0;
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ':')
				colon_flag = 1;

			if(s[i] == ',' || s[i] == ':')
				s[i] = ' ';
			
		}
		int read = 0;
		int len = strlen(s);
		char first[100] = {'\0'};
		char second[100] = {'\0'};
		char third[100] = {'\0'};
		char fourth[100] = {'\0'};

		if(colon_flag == 1)
			read = sscanf(s," %s %s %s %s ", first, second, third, fourth);
		else
			read = sscanf(s," %s %s %s ", second, third, fourth);

		if(start == 0)
		{	
			if( strcmp(second,"START") == 0)
				start =1;
			continue;
		}

		if(strcmp(second,"END") == 0)
			break;


		if(second[0] == 'L' && second[1] == 'O')
		{
			printf("%d ", global_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"SUB") == 0)
					printf(" %s R31 0001H\n" , opcodeArray[i].opcode);
			}
			global_address += 4; 

			printf("%d ", global_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"JNZ") == 0 )
					printf(" %s %s\n" , opcodeArray[i].opcode, third);
			}
			global_address += check4(third); 
			continue;
		}
		
		else if(second[0] == 'J')
		{
			printf("%d ", global_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
					printf(" %s %s %s\n" , opcodeArray[i].opcode, third, fourth);
			}
		}

		else
		{
			printf("%d ", global_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
					printf(" %s %s %s\n" , opcodeArray[i].opcode, third, fourth);
			}
		}


		if(second[0] == 'M' && second[1] == 'O' ) //Move  
			global_address += check1(third,fourth);

		if(second[0] == 'A' && second[1] == 'D') //Add
			global_address += check1(third,fourth);

		if(second[0] == 'S' && second[1] == 'U') //Subtract 
			global_address += check1(third,fourth);

		if(second[0] == 'M' && second[1] == 'U') //Multiply 
			global_address += check2(third);

		if(second[0] == 'C' && second[1] == 'M') //Comparator 
			global_address += check1(third,fourth);

		if(second[0] == 'A' && second[1] == 'N') //And
			global_address += check1(third,fourth);

		if(second[0] == 'O' && second[1] == 'R') //Or
			global_address += check1(third,fourth);

		if(second[0] == 'N' && second[1] == 'O') //Not
			global_address += check3(third);

		if(second[0] == 'J' && second[1] == 'M') //Jump 
			global_address += check4(third);

		//Must be handled separately
		if(second[0] == 'L' && second[1] == 'O') //Loop 
		{
			global_address += check4(third); //for the JNZ part
			global_address += 4; //for the subtract part of LOOP (Subtracting one from Reg31)
		}

		if(second[0] == 'H' && second[1] == 'L') //Halt  
			global_address += check5();

		if(second[0] == 'J' && second[1] == 'N') //Jump if Negative  
			global_address += check4(third);
	}



}

int main(){
    FILE *inputFile, *inputOpcodeFile;
    inputFile = fopen("input_assembly_code.txt", "r");
    inputOpcodeFile = fopen("input_opcode_table.txt", "r");

    getOpcodeArray(inputOpcodeFile);
    pass1(inputFile);
    rewind(inputFile);
    pass2(inputFile);

    fclose(inputOpcodeFile);

   	

}