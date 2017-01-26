/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef MEMORY_CONTROLLER_H_
#define MEMORY_CONTROLLER_H_

#include "constants.h"

#define DATA_MEMORY_BASE 2048
#define INSTR_MEMORY_BASE 1024
#define BOOT_MEMORY_BASE 0
#define STACK_BOTTOM 61436
#define STACK_TOP 65532

#define MAX_MEMORY_ADDR 65532

void printMemory();
void printMAR();
void printMDR();

int getMAR();
int getMDR();

void storeToMem(uint16_t addr, int value);
int loadFromMem(uint16_t addr);


#endif /* MEMORY_CONTROLLER_H_ */
