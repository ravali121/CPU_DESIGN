# CPU_DESIGN


This is a C program, implemented to logically perform the tasks of a real CPU. The CPU is designed based on x86 architecture

Features:
1. 32-bit word size
2. 1024 Bytes addressable memory
3. 32-bit ultra-fast registers
4. Register-register CPU

Control Unit – Handles all the communication logic between modules based on the fetched instruction in the instruction register. This will act as the brain of the CPU. Also responsible for reading the status register once there is a flag set. 

Memory Controller – This module is responsible for reading and writing data from/to the memory. Since the CPU is byte addressable, the memory controller handles the proper reading/writing based on the endianness defined. This module also contains the memory data register and memory address register.

MDR – Memory data register. Contains the data to be written to the memory or data that has been fetched from the memory.

MAR – Memory address register. Contains the address of the data to be written/fetched to/from the memory. 

ALU – Handles all arithmetic logic. Since this CPU is a register-register type, ALU only handles data from/to the registers in the register file. 

PC – Program Counter. A register that always contain the next memory address of the next instruction. 
Instruction Register – A register that contains the instruction to be executed. 

Status Register – A register that contains flag information. 

Register File – Contains 32 special purpose registers. 

Steps to execute the code:

1. Copy all the header files to includes folder and use 'make' file to run the program.
2. <./cpu > to execute the code
3. A prompt with few options appears.Choose an option
4. If you want to give your own assembly instruction, input it at the command line. 
5. After successful execution of every instruction, the memory and register values will be printed.



Instruction format for the R-type, I-type, J-type instructions is considered while designing the CPU. Based on the instruction, parsing takes place. Based on the opcode, the fuction to execute the instruction is called from ALU.c

The program is tested by implementing Binary Search.


