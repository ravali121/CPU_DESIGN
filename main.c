#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "includes/constants.h"
#include "includes/memory_controller.h"
#include "includes/register_file.h"
#include "includes/register_dictionary.h"
#include "includes/alu.h"
#include "includes/instruction_compiler.h"
#include "includes/instruction_parser.h"
#include "includes/label_handler.h"

/* Program Counter */
uint32_t PC = BOOT_MEMORY_BASE;

/* Status Register */
uint32_t SR;

/* Instruction Register */
uint32_t IR = 0;

/* hi register */
int32_t hi = 0;

/* lo register */
int32_t lo = 0;

uint8_t show_memory = 1;
unsigned char memory[65536];
char *flag_name[12+1] = {"CF","","PF","","AF","","ZF","SF","TF","IF","DF","OF",""};

void print_cpu_state(void)
{
	printf("*******************************************************\n");
	printf("*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
    printf("*******************************************************\n");
    printf("\tProgram Counter\n");
    printf("*******************************************************\n");
    printf("\tPC = %u\n", PC);
    printf("\n*******************************************************\n");
    printf("\tFlags\n");
    printf("*******************************************************\n");
    printf("\tFlags = %u\n", SR);
    for (int i = 0; i < 12 ; i++)
    {
        if (i != 1 &&  i != 3 && i != 5 )
        {
            if(checkFlag(i))
                printf("\t%s = 1\n", flag_name[i]);
            else
                printf("\t%s = 0\n", flag_name[i]);
        }
        if (i == 6)
            printf("\n");
    }
    printAllReg();
    printf("   hi = %08x | %04i, lo = %08x | %04i\n", hi, hi, lo, lo);
    printf("**********************____*****************************\n");
    printf("*******************************************************\n");
}

int returnIndex(char *ptr)
{
    char i = 0;
    i = atoi(++ptr);

    return i;
}

int main(int argc, char *argv[])
{
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);

    bool bufferCleared 	= false;
    int operation       = 0;
    int lineNo          = 0;
    int i		= 0;
    int key =0;
    FILE *fd 		= 0;
    FILE *myNumFile     = 0;     
    char *instr;
    instr 		= malloc(40);
    char *filename = malloc(40); // instruction filename

    start:
    /*DO NOT remove these clear buffer instructions
     * These are required to run the terminal properly*/
    fflush(stdin);
#if !(defined(_WIN32) || defined(_WIN64))
    if(!bufferCleared)
    {
        while ( getchar() != '\n' );
        bufferCleared = true;
    }
#endif
    if(argc > 1) {
    	for(int i = 0; i < argc; i++) {
    		if(0 == strcmp("-filename", argv[i])) {
    			strcpy(filename, argv[i+1]);
    			printf("Instructions filename: %s\n", filename);
    		} else if(0 == strcmp("-help", argv[i])) {
    			printf("To run:\n \t\t./CPU <argument_tag> <argument_value>\n\n");
    			printf("\t\targument_tag\t\t\targument_value\n");
    			printf("\t\t-filename\t\t\t<filename.txt>\n");
    			printf("\n\n");
    			printf("example execution command:\n");
    			printf("\t\t./CPU -filename instructions2.txt\n");
    			return 0;
    		}
    	}
    }
    else {
    	strcpy(filename, "instructions.txt");
    	printf("Instructions filename: %s\n", filename);
    }
    printf("Select the execution source:\n"
            "1. Compile and Load to memory\n"
            "2. Execute loaded program\n"
            "3. Execute on terminal\n>> ");
    scanf("%d",&operation);

    // initialization
    setRegister(getRegisterAddr("sp"), STACK_TOP);

    switch(operation)
    {
        case 1:
        	// compile labels
        	PC = INSTR_MEMORY_BASE; // reset base instruction memory
        	fd = fopen(filename,"r");

        	while(fgets(instr, 40, fd)) {

        		bool isLabel = false;
        			char* label = (char*) malloc(40);
        			parseLabel(instr, label);
        			if(0 < strlen(label)) {
        				// save label
        				Label currentLabel;
						currentLabel.offset = lineNo;
						strcpy(currentLabel.name, label);
						addLabel(currentLabel);
						printf("Label successfully parsed.\n");
						printLabel(currentLabel.name);

						storeToMem((uint16_t)PC, currentLabel.offset);
        			}
        		lineNo++;
				PC += 4;
        	}
        	// don't forget to close
        	fclose(fd);

        	printLabels();

        	// compile instructions
        	lineNo = 0;
        	PC = INSTR_MEMORY_BASE; // reset base instruction memory
            fd = fopen(filename,"r");
            while(fgets(instr, 40, fd))
            {
                if(isLabelPresent(lineNo)) { // skip current line if present
                	Label currentlabel = getLabelByOffset(lineNo);
                	printf("Label [%s] found; parsing next line.", currentlabel.name);
                } else {
                	printf("Instruction Read Successfully!\n");
					if(!compileInstr(instr))  // Parse the instruction to instruction memory.
					{
						printf("Compilation failed at line %d\n", lineNo);
						goto end;
					}
					storeToMem((uint16_t)PC, IR);
                }
                lineNo++;
                PC += 4;
                IR = 0; // don't forget to reset after every instruction
            }
            // don't forget to close
            fclose(fd);

            printMemory();
            goto start;
            break;
        case 2:
            PC  = INSTR_MEMORY_BASE;
            lineNo = 0;
            while(1)
            {
            	if(isLabelPresent(lineNo)) { // skip current line if present
					Label currentlabel = getLabelByOffset(lineNo);
					printf("Label [%s] found; parsing next line.\n", currentlabel.name);
					PC += 4;
				} else {
					IR  = loadFromMem(PC);
					if(!IR)
						break;
					parseInstructionReg(IR);
					PC += 4;
					printf("\n\n\n\n\n");
					print_cpu_state();
					IR = 0; // don't forget to reset after every instruction
				}

            }
            printMemory();
            printf("Program Execution Finished\n");
            break;
        case 3:
            while(1)
            {
                printf(">> ");
                /*DO NOT remove these clear buffer instructions
                * These are required to run the terminal properly*/
                fflush(stdin);
#if !(defined(_WIN32) || defined(_WIN64))
                if(!bufferCleared)
                {
                    while ( getchar() != '\n' );
                    bufferCleared = true;
                }
#endif
                fgets(instr,20,stdin);
                if(!strncmp(instr, "exit", 4))
                    break;

                printf("Instr = %s", instr);
                if(!compileInstr(instr))
                {
                    printf("Instruction does not exists\n");
                    //goto end;
                }
                PC+=4;
                parseInstructionReg(IR);
                print_cpu_state();
                IR = 0; // don't forget to reset after every instruction
            }
            break;
        default:
            printf("Please select correct option\n");
            goto start;
            break;
    }
    end:
    return 0;
}
