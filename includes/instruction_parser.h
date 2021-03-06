/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef INSTRUCTION_PARSER_H_
#define INSTRUCTION_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "register_dictionary.h"
#include "memory_controller.h"
#include "register_file.h"
#include "alu.h"
#include "constants.h"

extern uint32_t PC;

void addi(uint8_t rs, uint8_t rt, int16_t imm);
void mipsAdd(uint8_t rs1, uint8_t rt, uint8_t rs2);
void subi(uint8_t rs, uint8_t rt, int16_t imm);
void mipsSub(uint8_t rs1, uint8_t rt, uint8_t rs2);
void muli(uint8_t rs, uint8_t rt, int16_t imm);
void mipsMul(uint8_t rs1, uint8_t rt, uint8_t rs2);
void divi(uint8_t rs, uint8_t rt, int16_t imm);
void mipsDiv(uint8_t rs1, uint8_t rt, uint8_t rs2);
void ld(uint8_t rs, uint8_t rt, int16_t imm);
void lds(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t offset, uint8_t scale);
void sts(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t offset, uint8_t scale);
void st(uint8_t rs, uint8_t rt, int16_t imm);
void la(uint8_t rt, int16_t addr);
void compare(uint8_t rs1, uint8_t rs2);
void moveR(uint8_t rt, uint8_t rs);
void mipsAnd(uint8_t rs1, uint8_t rt, uint8_t rs2);
void mipsOr(uint8_t rs1, uint8_t rt, uint8_t rs2);
void mipsXor(uint8_t rs1, uint8_t rt, uint8_t rs2);
void mipsAndI(uint8_t rs, uint8_t rt, uint16_t imm);
void mipsOrI(uint8_t rs, uint8_t rt, uint16_t imm);
void mipsXorI(uint8_t rs, uint8_t rt, uint16_t imm);
void shiftLeft(uint8_t rs1, uint8_t rt, uint8_t rs2);
void shiftLeftI(uint8_t rs, uint8_t rt, uint16_t imm);
void jump(uint32_t offset);
void jumpAndLink(uint32_t offset);
void push(uint8_t rs);
void pop(uint8_t rt);

void parseInstructionReg(uint32_t instruction);

#endif /* INSTRUCTION_PARSER_H_ */
