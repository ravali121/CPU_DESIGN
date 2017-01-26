/*
 * registerFile.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Marvin
 */

#ifndef REGISTER_FILE_H_
#define REGISTER_FILE_H_

#include <stdbool.h>

void initRegisters();
static bool isValidReg(char reg);

void setRegister(char reg, int value);
int getRegisterValue(char reg);

void printReg(char reg);
void printAllReg();

#endif /* REGISTER_FILE_H_ */
