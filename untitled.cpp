if(second[1] == 'M' && second[2] == 'O' ) //Move Instruction -26
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"MOV") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "MOV %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'A' && second[2] == 'D') //Add Instruction -3
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"ADD") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "ADD %s\n" , opcodeArray[i].opcode);
					}
				}
				
			}

			if(second[1] == 'S' && second[2] == 'U') //Subtract Instruction -38
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"SUB") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "SUB %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'M' && second[2] == 'U') //Multiply Instruction -32
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"MUL") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "MUL %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'C' && second[2] == 'M') //Comparator Instruction -14
			{

				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"CMP") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "CMP %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'A' && second[2] == 'N') //And Instruction -13
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"AND") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "AND %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'O' && second[2] == 'R') //Or Instruction -31
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"OR") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "OR %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'N' && second[2] == 'O') //Not Instruction -27
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"NOT") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "NOT %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'J' && second[2] == 'M') //Jump Instruction -21
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"JMP") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "JMP %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			//Must be handled separately
			if(second[1] == 'L' && second[2] == 'O') //Loop Instruction -25
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

			if(second[1] == 'H' && second[2] == 'L') //Halt Instruction -18
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"HLT") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "HLT %s\n" , opcodeArray[i].opcode);
					}
				}
			}

			if(second[1] == 'J' && second[2] == 'N') //Jump if Negative Instruction -22
			{
				for(int i=0;i<12;i++)
				{
					if( strcmp(opcodeArray[i].instr,"JNZ") == 0 && !opcodeArray[i].checked2)
					{
						opcodeArray[i].checked2 = true;
						fprintf(outputOpcode, "JNZ %s\n" , opcodeArray[i].opcode);
					}
				}
			}