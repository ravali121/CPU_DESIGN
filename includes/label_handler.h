/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef INCLUDES_LABEL_HANDLER_H_
#define INCLUDES_LABEL_HANDLER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "util.h"

typedef struct {
	char name[40];  // name of the label so we can refer to it later
	uint32_t offset;  // offset based on position in the code
} Label;

void addLabel(Label label);
uint32_t getLabelOffset(char *name);
Label getLabelByName(char *name);
Label getLabelByOffset(uint32_t address);
bool isLabelPresent(uint16_t position);
void parseLabel(char* instr, char* label);

void printLabels();
void printLabel(char *name);

#endif /* INCLUDES_LABEL_HANDLER_H_ */
