# CPU_DESIGN


This is a C program, implemented to logically perform the tasks of a real CPU. The CPU is designed based on x86 architecture

Features:
1. 32-bit word size
2. 1024 Bytes addressable memory
3. 32-bit ultra-fast registers
4. Register-register CPU

Steps to execute the code:

1. Copy all the header files to includes folder and use 'make' file to run the program.
2. <./cpu > to execute the code
3. A prompt with few options appears.Choose an option
4. If you want to give your own assembly instruction, input it at the command line. 
5. After successful execution of every instruction, the memory and register values will be printed.



Instruction format for the R-type, I-type, J-type instructions is considered while designing the CPU. Based on the instruction, parsing takes place. Based on the opcode, the fuction to execute the instruction is called from ALU.c

The program is tested by implementing Binary Search.


