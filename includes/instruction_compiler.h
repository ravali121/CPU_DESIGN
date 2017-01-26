/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef INCLUDES_INSTRUCTION_COMPILER_H_
#define INCLUDES_INSTRUCTION_COMPILER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#include "constants.h"
#include "label_handler.h"

extern uint32_t IR;
extern uint32_t PC;

bool compileInstr(char *instr);

#endif /* INCLUDES_INSTRUCTION_COMPILER_H_ */
