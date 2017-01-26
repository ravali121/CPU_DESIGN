/*
 * register_dictionary.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Marvin
 */

#include <string.h>
#include "includes/register_dictionary.h"
#include "includes/constants.h"

// for reference, currently not used
enum Registers {
	zeroR = 0,
	at,
	v0, v1,
	a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9,
	k0, k1,
	gp, sp, fp, ra,
	hi, lo
};

uint16_t getRegisterAddr(char *s) {
	if (0 == strcmp(s, "zeroR")) {
		return 0;
	} else if (0 == strcmp(s, "at")) {
		return 1;
	} else if (0 == strcmp(s, "v0")) {
		return 2;
	} else if (0 == strcmp(s, "v1")) {
		return 3;
	} else if (0 == strcmp(s, "a0")) {
		return 4;
	} else if (0 == strcmp(s, "a1")) {
		return 5;
	} else if (0 == strcmp(s, "a2")) {
		return 6;
	} else if (0 == strcmp(s, "a3")) {
		return 7;
	} else if (0 == strcmp(s, "t0")) {
		return 8;
	} else if (0 == strcmp(s, "t1")) {
		return 9;
	} else if (0 == strcmp(s, "t2")) {
		return 10;
	} else if (0 == strcmp(s, "t3")) {
		return 11;
	} else if (0 == strcmp(s, "t4")) {
		return 12;
	} else if (0 == strcmp(s, "t5")) {
		return 13;
	} else if (0 == strcmp(s, "t6")) {
		return 14;
	} else if (0 == strcmp(s, "t7")) {
		return 15;
	} else if (0 == strcmp(s, "s0")) {
		return 16;
	} else if (0 == strcmp(s, "s1")) {
		return 17;
	} else if (0 == strcmp(s, "s2")) {
		return 18;
	} else if (0 == strcmp(s, "s3")) {
		return 19;
	} else if (0 == strcmp(s, "s4")) {
		return 20;
	} else if (0 == strcmp(s, "s5")) {
		return 21;
	} else if (0 == strcmp(s, "s6")) {
		return 22;
	} else if (0 == strcmp(s, "s7")) {
		return 23;
	} else if (0 == strcmp(s, "t8")) {
		return 24;
	} else if (0 == strcmp(s, "t9")) {
		return 25;
	} else if (0 == strcmp(s, "k0")) {
		return 26;
	} else if (0 == strcmp(s, "k1")) {
		return 27;
	} else if (0 == strcmp(s, "gp")) {
		return 28;
	} else if (0 == strcmp(s, "sp")) {
		return 29;
	} else if (0 == strcmp(s, "fp")) {
		return 30;
	} else if (0 == strcmp(s, "ra")) {
		return 31;
	}
	return 32; // return invalid address to fail
}
