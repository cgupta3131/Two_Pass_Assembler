gcc pass.c 
./a.out
printf "\n-----OPCODE TABLE-----\n"
cat opTable.txt
printf "\n\n-----SYMBOL TABLE-----\n"
cat symTable.txt
printf "\n\n-----MACHINE LEVEL CODE-----\n"
cat output.o