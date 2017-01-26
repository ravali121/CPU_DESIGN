/*
 * register_dictionary.h
 *
 *  Created on: Sep 17, 2016
 *      Author: Ravali
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdint.h>

#define sint16_t    int16_t

/* Opcodes */
#define MOV     1        // MOVE VALUE OF ONE REGISTER TO ANOHER
#define J		2		 // JUMP
#define JAL     3        // JUMP AND LINK

#define CMP     5        // COMPARE TWO REGISTERS
#define SUBI    6        // SUB IMMEDIATE
#define MULI    7        // MUL IMMEDIATE
#define ADDI    8        // ADD IMMEDIATE
#define DIVI    9        // DIV IMMEDIATE
#define SUB     10       // SUB R-Type
#define MUL     11       // MUL R-Type
#define ADD     12       // ADD R-Type
#define DIV     13       // DIV R-Type
#define AND     14       // Bitwise AND
#define ANDI    15       // Bitwise AND with Immediate
#define OR      16       // Bitwise OR
#define ORI     17       // Bitwise OR with Immediate
#define XOR     18       // Bitwise XOR
#define XORI    19       // Bitwise XOR with Immediate
#define SLL     20       // SHIFT LEFT R-Type
#define SLLI    21       // SHIFT LEFT Immediate
#define SRL     22       // SHIFT RIGHT LOGICAL R-Type
#define SRLI    23       // SHIFT RIGHT LOGICAL Immediate
#define SRA     24       // SHIFT RIGHT Arithmetic R-Type
#define SRAI    25       // SHIFT RIGHT Arithmetic Immediate
#define ST      26       // STORE WORD
#define LEA     27       // LOAD EFFECTIVE ADDRESS // not in basic MIPS ref, chose 36 because it's next to 35?
#define LD      28       // LOAD WORD
#define LDS     29       // LOAD SCALED
#define STS     30       // STORE SCALED
#define PUSH	31	 	 // PUSH TO STACK
#define POP		32	 	 // POP FROM STACK
#define BNE     33       // BRANCH if not equal.
#define BEQ     34       // BRANCH if equal.
#define BL      35       // BRANCH if less than.
#define BLE     36       // BRANCH if less than equal.
#define BGE     37       // BRANCH if greater than equal.
#define BG      38       // BRANCH if greater than.
#define RTYPE   63        // RTYPE INSTRUCTIONS e,g, ADD, AND, JR

#define JR_FUNC		8		 // JUMP REGISTER FUNCTION, JR is RTYPE so we parse it using function (lease significant 6 bits)
#endif /* CONSTANTS_H_ */
