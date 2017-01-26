/*
 * register_file.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Marvin
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "includes/register_file.h"
#include "includes/constants.h"

/* CPU regiseters */
unsigned int R[32];

// for testing
void initRegisters() {
	R[0] = 0; // always zero
	for (int i = 1; i < 32; i++) {
		R[i]= i;
	}
}

void printReg(char reg) {
	if(isValidReg(reg)) {
		printf("\t%04x\n", R[reg]);
	}
}

void printAllReg() {
    printf("\n*******************************************************\n");
    printf("\tREGISTER FILE\n");
    printf("*******************************************************\n");
    printf("        HEX  | DEC\n");
    printf("zeroR = %08x | %04i\n",R[0],R[0]);
    printf("   at = %08x | %04i\n",R[1],R[1]);
    printf("   v0 = %08x | %04i, v1 = %08x | %04i\n",R[2],R[2],R[3],R[3]);
    printf("   a0 = %08x | %04i, a1 = %08x | %04i, a2 = %08x | %04i, a3 = %08x | %04i\n",R[4],R[4],R[5],R[5],R[6],R[6],R[7],R[7]);
    printf("   t0 = %08x | %04i, t1 = %08x | %04i, t2 = %08x | %04i, t3 = %08x | %04i\n",R[8],R[8],R[9],R[9],R[10],R[10],R[11],R[11]);
    printf("   t4 = %08x | %04i, t5 = %08x | %04i, t6 = %08x | %04i, t7 = %08x | %04i\n",R[12],R[12],R[13],R[13],R[14],R[14],R[15],R[15]);
    printf("   s0 = %08x | %04i, s1 = %08x | %04i, s2 = %08x | %04i, s3 = %08x | %04i\n",R[16],R[16],R[17],R[17],R[18],R[18],R[19],R[19]);
    printf("   s4 = %08x | %04i, s5 = %08x | %04i, s6 = %08x | %04i, s7 = %08x | %04i\n",R[20],R[20],R[21],R[21],R[22],R[22],R[23],R[23]);
    printf("   t8 = %08x | %04i, t9 = %08x | %04i\n" ,R[24],R[24],R[25],R[25]);
    printf("   k0 = %08x | %04i, k1 = %08x | %04i\n",R[26],R[26],R[27],R[27]);
    printf("   gp = %08x | %04i, sp = %08x | %04i, fp = %08x | %04i, ra = %08x | %04i\n",R[28],R[28],R[29],R[29],R[30],R[30],R[31],R[31]);
}

static bool isValidReg(char reg) {
	if(reg > 31 || reg < 0) {
		printf("Invalid Register Address!\n");
		return false;
	}
	return true;
}

int getRegisterValue(char reg) {
	if(isValidReg(reg)) {
		return R[reg];
	}
	return R[0];
}

void setRegister(char reg, int value) {
	if (0 == reg) {
		printf("R[0] cannot be set!\n");
	} else if(isValidReg(reg)) {
		R[reg] = value;
	}
}
