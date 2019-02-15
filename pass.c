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

/*char* HexToBin(char* hexdec, int idx) 
{ 
	char *hex = (char *)malloc(17*sizeof(char));
	for(int i=0;i<16;i++)
		hex[i] = '0';
	hex[16] = '\0';
	printf("%s ", hexdec);

	int j = idx; 
    int i = 0;

    while(1) 
    { 
    	if(i == 4)
    		break;

    	if(hexdec[j] == '0')
    		hex[i*4+0] = '0';hex[i*4+1] = '0';hex[i*4+2] = '0';hex[i*4+3] = '0';
    	else if(hexdec[j] == '1')
    		hex[i*4+0] = '0';hex[i*4+1] = '0';hex[i*4+2] = '0';hex[i*4+3] = '1';
    	else if(hexdec[j] == '2')
    		hex[i*4+0] = '0';hex[i*4+1] = '0';hex[i*4+2] = '1';hex[i*4+3] = '0';
    	else if(hexdec[j] == '3')
    		hex[i*4+0] = '0';hex[i*4+1] = '0';hex[i*4+2] = '1';hex[i*4+3] = '1';
    	else if(hexdec[j] == '4')
    		hex[i*4+0] = '0';hex[i*4+1] = '1';hex[i*4+2] = '0';hex[i*4+3] = '0';
    	else if(hexdec[j] == '5')
    		hex[i*4+0] = '0';hex[i*4+1] = '1';hex[i*4+2] = '0';hex[i*4+3] = '1';
        i++;
        j++; 
    } 

    return hex;
} */

char *func4(char hex[6]){
    char *bin=(char *)malloc(sizeof(char)*17);
    for(int i=0; hex[i]!='H'; i++)
    {
        switch(hex[i])
        {
            case '0':
                strcat(bin, "0000");
                break;
            case '1':
                strcat(bin, "0001");
                break;
            case '2':
                strcat(bin, "0010");
                break;
            case '3':
                strcat(bin, "0011");
                break;
            case '4':
                strcat(bin, "0100");
                break;
            case '5':
                strcat(bin, "0101");
                break;
            case '6':
                strcat(bin, "0110");
                break;
            case '7':
                strcat(bin, "0111");
                break;
            case '8':
                strcat(bin, "1000");
                break;
            case '9':
                strcat(bin, "1001");
                break;
            case 'a':
            case 'A':
                strcat(bin, "1010");
                break;
            case 'b':
            case 'B':
                strcat(bin, "1011");
                break;
            case 'c':
            case 'C':
                strcat(bin, "1100");
                break;
            case 'd':
            case 'D':
                strcat(bin, "1101");
                break;
            case 'e':
            case 'E':
                strcat(bin, "1110");
                break;
            case 'f':
            case 'F':
                strcat(bin, "1111");
                break;
            default:
                printf("Invalid hexadecimal input.");
        }
    }
    return bin;
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

		if(strcmp(second,"END") == 0)
			break;

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

		char *memeory_address = decToHexa(global_address);


		if(second[0] == 'L' && second[1] == 'O') //LOOP
		{
			printf("%d %s", global_address, memeory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"SUB") == 0)
					printf(" %s 11111 0001H\n" , opcodeArray[i].opcode);
			}
			global_address += 4; 

			memeory_address = decToHexa(global_address);
			printf("%d %s", global_address, memeory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,"JNZ") == 0 )
					printf(" %s %s\n" , opcodeArray[i].opcode, third);
			}
			global_address += check4(third); 
			continue;
		}

		else if(second[0] == 'J') //JNZ or JMP
		{
			printf("%d %s", global_address, memeory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
					printf(" %s %s %s\n" , opcodeArray[i].opcode, third, fourth);
			}
		}

		else if(second[0] == 'M' && second[1] == 'U') // Multiplier
		{
			printf("%d %s", global_address, memeory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
				{
					printf(" %s 00001 " , opcodeArray[i].opcode);

					if(third[0] == 'R')
					{
						char *third_address;
						if(strlen(third) == 2)
						{
							int num = 0;
							num += third[1]-'0';
							third_address = decToBin_5(num);
						}
						else
						{
							int num = 0;
							num += third[2]-'0';
							num += 10*(third[1]-'0');
							third_address = decToBin_5(num);
						}
						printf(" %s " , third_address);

					}
					else
					{
						printf(" %s " , third);
					}

					if(fourth[0] == 'R')
					{
						char *fourth_address;
						if(strlen(fourth) == 2)
						{
							int num = 0;
							num += fourth[1]-'0';
							fourth_address = decToBin_5(num);
						}
						else
						{
							int num = 0;
							num += fourth[2]-'0';
							num += 10*(fourth[1]-'0');
							fourth_address = decToBin_5(num);
						}
						printf(" %s \n" , fourth_address);

					}

					else
					{
						printf(" %s\n" , fourth);
						//fourth_address = fourth;
						
					}
					//printf(" %s %s\n" , third_address, fourth_address);
				}
			}
		}

		else //Other cases
		{
			printf("%d %s", global_address, memeory_address);
			for(int i=0;i<12;i++)
			{
				if( strcmp(opcodeArray[i].instr,second) == 0)
				{
					printf(" %s " , opcodeArray[i].opcode);

					if(third[0] == 'R')
					{
						char *third_address;
						if(strlen(third) == 2)
						{
							int num = 0;
							num += third[1]-'0';
							third_address = decToBin_5(num);
						}
						else 
						{
							int num = 0;
							num += third[2]-'0';
							num += 10*(third[1]-'0');
							third_address = decToBin_5(num);
						}
						printf(" %s " , third_address);

					}
					else 
					{/*
						if(third[0] == '0')
						{
							char *third_address;
							third[5] = '\0';
							printf(" JMD%s\n", third );
							if(third[4] == 'H')
								third_address = HexToBin(third,0);
							else
								third_address = HexToBin(third,1);
						}*/
						//third_address = third;
						//printf(" %s " , third_address);

					}

					if(fourth[0] == 'R')
					{
						char *fourth_address;
						if(strlen(fourth) == 2)
						{
							int num = 0;
							num += fourth[1]-'0';
							fourth_address = decToBin_5(num);
						}
						else
						{
							int num = 0;
							num += fourth[2]-'0';
							num += 10*(fourth[1]-'0');
							fourth_address = decToBin_5(num);
						}
						printf(" %s \n" , fourth_address);

					}

					else
					{
						if(fourth[0] == '0')
						{
							char *fourth_address;
							fourth[5] = '\0';
							printf(" ----- ");
							if(fourth[4] == 'H')
							{
								fourth_address = func4(fourth);
							}
							/*else
								fourth_address = HexToBin(fourth,1);*/
							printf(" %s \n" , fourth_address);
						}
						
					}
				}
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