/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef ALU_H_
#define ALU_H_

#include "constants.h"

extern uint32_t SR;
extern int32_t hi;
extern int32_t lo;

int checkFlag(unsigned int );
int aluAdd(int a, int b);
int aluSub(int a, int b);
int aluMul(int x, int y);
int aluDiv(int x, int y);
int aluAnd(int a, int b);
int aluOr(int a, int b);
int aluXor(int a, int b);
int aluShiftLeft(int a, int b);
int aluShiftRightL(int a, int b);
int aluShiftRightA(int a, int b);

#endif /* ALU_H_ */
