#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
	Things to be done
	1) Whitespaces bakchodi (DONE) //Double check from Lavish
	2) H and D and B (DONE)
	3) Comments (DONE)
*/
FILE *outputMachine;
int global_address = 0;
struct instruction{
    char instr[10];
    char opcode[10];
    bool checked2;
};

void upper_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}

char* HexToBin(char* hexdec) 
{ 
	int len = strlen(hexdec);

	hexdec[len-1] = '\0'; //Now the string contains 5 or less numbers
	len = strlen(hexdec);
	//fprintf(outputMachine, "LENGTH:%d----%s---", len,hexdec );
	int j =0;
	int i = 0;
	if(len == 5)
		j=1;
	if(len == 4)
		j=0;
	if(len == 3)
		i=1;
	if(len == 2)
		i=2;
	if(len == 1)
		i=3;


	char *hex = (char *)malloc(18*sizeof(char));
	for(int i=0;i<17;i++)
		hex[i] = '0';
	hex[17] = '\0';
    int idx0;
    int idx1;
    int idx2;
    int idx3;
    while(1) 
    { 
    	idx0 = i*4+0;
    	idx1 = i*4+1;
    	idx2 = i*4+2;
    	idx3 = i*4+3;
    	if(i == 2 || i == 3)
    	{
    		idx0++;idx1++;idx2++;idx3++;
    	}
    	if(i == 4)
    		break;
    	if(hexdec[j] == '0')
    	{
    		hex[idx0] = '0';hex[idx1] = '0';hex[idx2] = '0';hex[idx3] = '0';
    	}
    	if(hexdec[j] == '1')
    	{
    		hex[idx0] = '0';hex[idx1] = '0';hex[idx2] = '0';hex[idx3] = '1';
    	}
    	if(hexdec[j] == '2')
    	{
    		hex[idx0] = '0';hex[idx1] = '0';hex[idx2] = '1';hex[idx3] = '0';
    	}
    	if(hexdec[j] == '3')
    	{
    		hex[idx0] = '0';hex[idx1] = '0';hex[idx2] = '1';hex[idx3] = '1';
    	}
    	if(hexdec[j] == '4')
    	{
    		hex[idx0] = '0';hex[idx1] = '1';hex[idx2] = '0';hex[idx3] = '0';
    	}
    	if(hexdec[j] == '5')
    	{
    		hex[idx0] = '0';hex[idx1] = '1';hex[idx2] = '0';hex[idx3] = '1';
    	}
    	if(hexdec[j] == '6')
    	{
    		hex[idx0] = '0';hex[idx1] = '1';hex[idx2] = '1';hex[idx3] = '0';
    	}
    	if(hexdec[j] == '7')
    	{
    		hex[idx0] = '0';hex[idx1] = '1';hex[idx2] = '1';hex[idx3] = '1';
    	}
    	if(hexdec[j] == '8')
    	{
    		hex[idx0] = '1';hex[idx1] = '0';hex[idx2] = '0';hex[idx3] = '0';
    	}
    	if(hexdec[j] == '9')
    	{
    		hex[idx0] = '1';hex[idx1] = '0';hex[idx2] = '0';hex[idx3] = '1';
    	}
    	if(hexdec[j] == 'A')
    	{
    		hex[idx0] = '1';hex[idx1] = '0';hex[idx2] = '1';hex[idx3] = '0';
    	}
    	if(hexdec[j] == 'B')
    	{
    		hex[idx0] = '1';hex[idx1] = '0';hex[idx2] = '1';hex[idx3] = '1';
    	}
    	if(hexdec[j] == 'C')
    	{
    		hex[idx0] = '1';hex[idx1] = '1';hex[idx2] = '0';hex[idx3] = '0';
    	}
    	if(hexdec[j] == 'D')
    	{
    		hex[idx0] = '1';hex[idx1] = '1';hex[idx2] = '0';hex[idx3] = '1';
    	}
    	if(hexdec[j] == 'E')
    	{
    		hex[idx0] = '1';hex[idx1] = '1';hex[idx2] = '1';hex[idx3] = '0';
    	}
    	if(hexdec[j] == 'F')
    	{
    		hex[idx0] = '1';hex[idx1] = '1';hex[idx2] = '1';hex[idx3] = '1';
    	}
        i++;
        j++; 
    } 

    hex[8] = ' ';
    //fprintf(outputMachine, "AAAAAA----%s---AAAAAA", hex );
    return hex;
} 

char *decToHexa(int n) 
{    
    char *hexaDeciNum = (char *)malloc(5*sizeof(char));
    hexaDeciNum[0] = '0';
    hexaDeciNum[1] = '0';
    hexaDeciNum[2] = '0';
    hexaDeciNum[3] = '0';
    hexaDeciNum[4] = '\0';
    int i = 3; 
    while( n!=0 ) 
    {    
        int temp  = 0; 
        temp = n % 16; 
        if(temp < 10) 
        { 
            hexaDeciNum[i] = temp + 48; 
            i--; 
        } 
        else
        { 
            hexaDeciNum[i] = temp + 55; 
            i--; 
        } 
        n = n/16; 
    } 
    return hexaDeciNum;
} 

char *decToBin_5(int n) 
{    
    char *BinDeciNum = (char *)malloc(6*sizeof(char));
    BinDeciNum[0] = '0';
    BinDeciNum[1] = '0';
    BinDeciNum[2] = '0';
    BinDeciNum[3] = '0';
    BinDeciNum[4] = '0';
    BinDeciNum[5] = '\0';

    int i = 4; 
    while( n!=0 ) 
    {    
        int temp  = 0; 
        temp = n % 2; 
           BinDeciNum[i] = temp + 48; 
            i--; 
        n = n/2; 
    } 
    return BinDeciNum;
}

char *decToBin_16(int n) 
{    
    char *BinDeciNum = (char *)malloc(18*sizeof(char));
    for(int i=0;i<=16;i++)
    	BinDeciNum[i] = '0';
    BinDeciNum[17] = '\0'; 

    int i = 16;
    int idx = i; 
    while( n!=0 ) 
    {    
    	if(i > 8)
    		idx = i;
    	else
    		idx = i-1;
        int temp  = 0; 
        temp = n % 2; 
        BinDeciNum[idx] = temp + 48; 
        i--; 
        n = n/2; 
    } 
    BinDeciNum[8] = ' ';
    return BinDeciNum;
}

char *binToBin_16(char *input_str)
{

	input_str[strlen(input_str)-1] = '\0';
	char *Bin = (char *)malloc(18*sizeof(char));
    for(int i=0;i<=16;i++)
    	Bin[i] = '0';
    Bin[17] = '\0'; 

    int idx = 16;
    for(int i=strlen(input_str)-1;i>=0;i--)
    {
    	if(idx > 8)
			Bin[idx] = input_str[i];
		else
			Bin[idx-1] = input_str[i];
		idx--; 
    }

    Bin[8] = ' ';

    return Bin;
}

int strToDec(char *decstring)
{

	int value = 0; //to be returned
	decstring[strlen(decstring) - 1] = '\0';
	if(strlen(decstring) == 5)
	{	
		value += (decstring[1]-'0')*1000;
		value += (decstring[2]-'0')*100;
		value += (decstring[3]-'0')*10;
		value += (decstring[4]-'0')*1;

		
	} 

	else 
	{
		int len = strlen(decstring);
		len = len-1;
		int mul = 1;
		while(len>=0)
		{	
			value += (decstring[len]-'0')*mul;
			//printf("%d\n", value );
			mul *= 10;
			len--;
		}

		/*value += (decstring[0]-'0')*1000;
		value += (decstring[1]-'0')*100;
		value += (decstring[2]-'0')*10;
		value += (decstring[3]-'0')*1;*/
	}

	return value;
}  


void value_to_memory(char *input_str)
{
	char *address;
	if(input_str[strlen(input_str)-1] == 'H') //for hexadecimal types
	{	
		address = HexToBin(input_str);
		/*input_str[5] = '\0';
		if(input_str[4] == 'H')
		{
			address = HexToBin(input_str,0);
		}
		else
			address = HexToBin(input_str,1);*/
		fprintf(outputMachine,"%s" , address);
	}

	else if(input_str[strlen(input_str)-1] == 'D') //for Decimal(Base 10) types
	{
		int equ_val = strToDec(input_str);
		char *address = decToBin_16(equ_val);
		fprintf(outputMachine,"%s" , address);
	}

	else if(input_str[strlen(input_str)-1] == 'B') //for Binary input
	{
		char *address = binToBin_16(input_str);
		fprintf(outputMachine,"%s" , address);
	}

	return;
}

void register_to_memory(char *input_str)
{
	char *address;
	if(strlen(input_str) == 2)
	{
		int num = 0;
		num += input_str[1]-'0';
		address = decToBin_5(num);
	}
	else
	{
		int num = 0;
		num += input_str[2]-'0';
		num += 10*(input_str[1]-'0');
		address = decToBin_5(num);
	}
	fprintf(outputMachine,"%s" , address);
}

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
	{
		//printf("%s %s\n", a, b );
		return 5; //36
	}
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
	FILE *outputOpcode = fopen("opTable.txt", "w");
	FILE *outputSymbol = fopen("symTable.txt", "w");
	char s[300];
	int n=300;

	int x=1;
	int start = 0;
	while( fgets(s,n,inputFile) )
	{	

		int ii=0;
		int flag_white = 0;
		while(s[ii] != '\0')
		{
			int var = isspace(s[ii]);
			if(var == 0) //means that is not a whitespace
			{
				if(s[ii] == ';' || s[ii] == '#') //means that after alot of spaces we get ;->for comments
					break;
				flag_white = 1;
				break;
			}
			ii++;
		}
		if(flag_white == 0)
			continue;

		int colon_flag = 0;
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ':')
				colon_flag = 1;

			if(s[i] == ',' || s[i] == ':')
				s[i] = ' ';
			
		}
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ';' || s[i] == '#')
			{
				s[i] = '\0';
				break;
			}
			
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
		{
			read = sscanf(s," %s %s %s ", second, third, fourth);
		}

		char original_third[100] = {'\0'}; //this might be label also
		strcpy(original_third,third);	
		//upper_string(first);
		upper_string(second);
		upper_string(third);
		upper_string(fourth);

		if(start == 0)
		{	
			if( strcmp(second,"START") == 0)
				start =1;
			continue;
		}

		if(strcmp(second,"END") == 0)
			break;

		if(colon_flag == 1) //this means there is a label and I need to print the address
		{
			//printf("%d\n", global_address );
			char *dec = decToHexa(global_address);
			//printf("%s %sH	\n", first, dec);
			fprintf(outputSymbol, "%s %sH\n", first, dec);
			if(read == 1)
				global_address += 0;	
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
	FILE *Labels = fopen("symTable.txt", "r");
	outputMachine =fopen("output.o", "w");	char t[300];
	int n2 =300;

	int x=1;
	int start = 0;

	while( fgets(s,n,inputFile) )
	{	

		int ii=0;
		int flag_white = 0;
		while(s[ii] != '\0')
		{
			int var = isspace(s[ii]);
			if(var == 0) //means that is not a whitespace
			{
				if(s[ii] == ';' || s[ii] == '#') //means that after alot of spaces we get ;->for comments
					break;
				flag_white = 1;
				break;
			}
			ii++;
		}
		if(flag_white == 0)
			continue;

		int colon_flag = 0;
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ':')
				colon_flag = 1;

			if(s[i] == ',' || s[i] == ':')
				s[i] = ' ';
		}

		for(int i=0;i<strlen(s);i++)
		{
			if(s[i] == ';' || s[i] == '#')
			{
				s[i] = '\0';
				break;
			}
			
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

		//upper_string(first);
		char original_third[100] = {'\0'}; //this might be label also
		strcpy(original_third,third);
		upper_string(second);
		upper_string(third);
		upper_string(fourth);
		
		if(start == 0)
		{	
			if( strcmp(second,"START") == 0)
				start =1;
			continue;
		}

		if(strcmp(second,"END") == 0)
			break;

		char *memory_address = decToHexa(global_address);


		if(second[0] == 'L' && second[1] == 'O') //LOOP
		{
			fprintf(outputMachine,"%s\t\t", memory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"SUB") == 0)
					fprintf(outputMachine,"%s 11111 00000000 00000001\n" , opcodeArray[i].opcode);
			}
			global_address += 4; 

			memory_address = decToHexa(global_address);
			fprintf(outputMachine,"%s\t\t", memory_address);

			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"JNZ") == 0 )
				{
					while( fgets(t,n2,Labels) )
					{
						char symbol[100] = {'\0'};
						char address[100] = {'\0'};
						sscanf(t,"%s %s ", symbol, address);
						if(strcmp(original_third, symbol) == 0)
						{
							//printf("%s ----", address );
							char *third_address = HexToBin(address);
							//printf("%s ---", third_address );
							/*if(address[4] == 'H') //Finding this is Symbol table
							{
								third_address = HexToBin(address,0);
							}
							else
								third_address = HexToBin(address,1);*/
							fprintf(outputMachine,"%s %s\n" , opcodeArray[i].opcode, third_address);

						}
					}
					rewind(Labels);
				}
			}
			global_address += check4(third); 
			continue;
		}

		else if(second[0] == 'J') //JNZ or JMP
		{
			fprintf(outputMachine,"%s\t\t", memory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
				{
					while( fgets(t,n2,Labels) )
					{

						char symbol[100] = {'\0'};
						char address[100] = {'\0'};
						sscanf(t," %s %s ", symbol, address);

						if(strcmp(original_third, symbol) == 0)
						{
							char *third_address = HexToBin(address);
							/*if(address[4] == 'H')
							{
								third_address = HexToBin(address,0);
							}
							else
								third_address = HexToBin(address,1);*/
							fprintf(outputMachine,"%s %s\n" , opcodeArray[i].opcode, third_address);

						}
					}
					rewind(Labels);
				}
			}
		}

		else if(second[0] == 'M' && second[1] == 'U') // Multiplier
		{
			fprintf(outputMachine,"%s\t\t", memory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
				{
					fprintf(outputMachine,"%s 00001 " , opcodeArray[i].opcode);

					if(third[0] != '\0')
					{
						if(third[0] == 'R')
							register_to_memory(third);
						else
							value_to_memory(third);
					}
				}
			}
			fprintf(outputMachine,"\n");
		}


		else //Other cases
		{
			
			if(read == 1) //means that was just a label
			{
				//global_address++;
				//fprintf(outputMachine,"\n");
				continue;
			}
			fprintf(outputMachine,"%s\t\t", memory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
				{
					fprintf(outputMachine,"%s " , opcodeArray[i].opcode);

					if(third[0] != '\0')
					{
						if(third[0] == 'R') //If the operand is a register
							register_to_memory(third);

						else //If it is given in Bits and bytes
							value_to_memory(third);
						fprintf(outputMachine," ");
					}

					if(fourth[0] != '\0')
					{
						if(fourth[0] == 'R') //If second operand is a register
							register_to_memory(fourth);

						else //else if it is of type bits and bytes
							value_to_memory(fourth);
					}
				}
			}
			fprintf(outputMachine,"\n");
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

	fclose(Labels);
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