/*
 * memory_controller.c
 *
 *  Created on: Sep 16, 2016
 *      Author: Marvin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "includes/memory_controller.h"
#include "includes/constants.h"

int MAR = 0;
int MDR = 0;


/* Memory block of 64K bytes */
extern unsigned char memory[65536];

void printMAR() {
	printf("MEMORY ADDRESS REGISTER:\t%04x\n", MAR);
}

void printMDR() {
	printf("MEMORY DATA REGISTER:   \t%04x\n", MDR);
}

int getMAR() {
	return MAR;
}

static void setMAR(int value) {
	MAR = value;
}

int getMDR(){
	return MDR;
}

static void setMDR(int value) {
	MDR = value;
}

void storeToMem(uint16_t addr, int value) {
	if( addr > (uint32_t) MAX_MEMORY_ADDR) {
		printf("Address value out of bounds.\n");
		return;
	}
	// little endian notation
	memory[addr] = value & 0xFF;
	memory[addr + 1] = (value >> 8)  & 0xFF;
	memory[addr + 2] = (value >> 16) & 0xFF;
	memory[addr + 3] = (value >> 24) & 0xFF;

	setMAR(addr);
	setMDR(value);

	printMAR();
	printMDR();
	printf("*******************************************************\n");
}

int loadFromMem(uint16_t addr) {
	int data =  (memory[addr + 3] << 24) |
			    (memory[addr + 2] << 16) |
				(memory[addr + 1] << 8)  |
				 memory[addr];
	setMAR(addr);
	setMDR(data);

	printMAR();
	printMDR();
	printf("*******************************************************\n");
	return data;
}


void printMemory() {
	{
		int i;

		printf("\n*******************************************************\n");
		printf("\tBootstrap Memory\n");
		printf("*******************************************************\n");

		printf("Address    \t\tMemory\n");

		for (i = 0; i < INSTR_MEMORY_BASE; i = i + 16)
		{
		    printf("%06d   %02X %02X %02X %02X  ", i, memory[i], memory[i+1], memory[i+2], memory[i+3]);
		    printf("%02X %02X %02X %02X  ", memory[i+4], memory[i+5], memory[i+6], memory[i+7]);
		    printf("%02X %02X %02X %02X  ", memory[i+8], memory[i+9], memory[i+10], memory[i+11]);
		    printf("%02X %02X %02X %02X  \n", memory[i+12], memory[i+13], memory[i+14], memory[i+15]);
		}

		printf("\n*******************************************************\n");
		printf("\tInstruction Memory\n");
		printf("*******************************************************\n");
		printf("Address    \t\tMemory\n");
		for (i = INSTR_MEMORY_BASE; i < DATA_MEMORY_BASE; i = i+16)
		{
		    printf("%06d   %02X %02X %02X %02X  ", i, memory[i], memory[i+1], memory[i+2], memory[i+3]);
		    printf("%02X %02X %02X %02X  ", memory[i+4], memory[i+5], memory[i+6], memory[i+7]);
		    printf("%02X %02X %02X %02X  ", memory[i+8], memory[i+9], memory[i+10], memory[i+11]);
		    printf("%02X %02X %02X %02X  \n", memory[i+12], memory[i+13], memory[i+14], memory[i+15]);
		}

		printf("\n*******************************************************\n");
		printf("\tData Memory\n");
		printf("*******************************************************\n");
		printf("Address    \t\tMemory\n");
		for (i = DATA_MEMORY_BASE; i < 4096; i = i+16)
		{
		    printf("%06d   %02X %02X %02X %02X  ", i, memory[i], memory[i+1], memory[i+2], memory[i+3]);
		   printf("%02X %02X %02X %02X  ", memory[i+4], memory[i+5], memory[i+6], memory[i+7]);
		    printf("%02X %02X %02X %02X  ", memory[i+8], memory[i+9], memory[i+10], memory[i+11]);
		    printf("%02X %02X %02X %02X  \n", memory[i+12], memory[i+13], memory[i+14], memory[i+15]);
		}
		printf("*******************************************************\n");
		    printf("\n\n");
	}

}


