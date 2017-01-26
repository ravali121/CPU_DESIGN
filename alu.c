/*
 * alu.c
 *
 *  Created on: Sep 17, 2016
 *      Author: Marvin
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "includes/alu.h"
#include "includes/constants.h"
#include "includes/register_file.h"

enum flags_index{
    CF = 0, /* Carry Flag */
    PF = 2, /* Parity Flag */
    AF = 4, /* Adjust Flag */
    ZF = 6, /* Zero Flag */
    SF = 7, /* Sign Flag */
    TF = 8, /* Trap Flag */
    IF = 9, /* Interrupt Enable Flag */
    DF = 10, /* Direction Flag */
    OF = 11, /* Overflow Flag */
    IN   /*  Invalid */
};

int checkFlag(unsigned int flag_index)
{
    return (SR & (1 << flag_index));
}

void set_flag(unsigned int flag_index)
{
    if (flag_index < IN)
        SR |= 1 << flag_index;
    return;
}

void clear_flag(unsigned int flag_index)
{
    if (flag_index < IN)
        SR &= ~(1 << flag_index);
    return;
}



int binary(int num) // To get MSB bit of an integer
{
    return ((num >> 31) & 1); //Assuming 32 bit integer
}

void zero(int c)
{
    if(c==0)
    {
        set_flag(ZF);
    }
    else
    {
        clear_flag(ZF);
    }
}

void sign(int c)
{
    if(c==1)
    {
        set_flag(SF);
    }
    else
    {
        clear_flag(SF);
    }
}


// carry flag check
void carry(int x, int y, unsigned int addition)
{
    if (addition > 2147483647) // range of int -2147483648 to +2147483647 (32 bit)
    {
        set_flag(CF);
    }
    else
    {
        clear_flag(CF);
    }
}

// Overflow flag check
void overflow(int x, int y, int z)
{
    if(x == 0 && y == 0)
    {
        if(z == 1)
        {
            set_flag(OF);
        }
        else
        {
            clear_flag(OF);
        }
    }

    else if(x == 1 && y == 1)
    {
        if(z == 0)
        {
            set_flag(OF);
        }
        else
        {
            clear_flag(OF);
        }
    }
    else
    {
        clear_flag(OF);
    }
}


//Bitwise ADD
int aluAdd(int a, int b)
{

    int x,y, c=0;
    x = binary(a);
    y = binary(b);

    while(b!=0)
    {
        c = a & b;
        a = a^b;
        b = c << 1;

    }

    unsigned int addition = (unsigned) a;
    carry(x, y, addition);

    int z = binary(a); // check MSB bit of sum
    overflow(x, y, z);
    sign(z);
    zero(a);
    return a;

}


int complement(int c)
{
    return aluAdd(~c,1);// 2's complement
}

//Bitwise SUB
int aluSub(int a, int b)

{
    int difference;
    difference = aluAdd(a, complement(b));
    int x = binary(a);
    int y = binary(b);
    int z = binary(difference);

    sign(z);
    overflow(x, y, z);

    if( x == 0 && y ==0) // carry checked in unsigned integers only
    {
        if(z == 1)
        {
            set_flag(CF);
        }
        else
        {
            clear_flag(CF);
        }
    }
    else
    {
        clear_flag(CF);
    }

    zero(difference);
    return difference ;
}

//Bitwise MUL
int aluMul(int x, int y)
{
    int a = 0, b = 0, c = 0, product = 0;
    bool isNegativeSign = false;
    int64_t product64bit = 0;
    a=x;
    b=y;
    // check if negative numbers
    if((binary(a)^binary(b)) == 1) {
        isNegativeSign = true;
    }
    // convert to unsigned if applicable
    if(binary(a) == 1) {
        a = complement(a);
    }

    if(binary(b) == 1) {
        b = complement(b);
    }

    while(a >= 1)		/*To check if 'a' is even or odd*/
    {
        if (a & 0x1)
        {
            product64bit = product = aluAdd(product,b);
        }
        a = a>>1;		/*left shift Operation*/
        b<<=1;			/*Right shift Operation*/
    }

    if (isNegativeSign) {
        product= complement(product);
        product64bit = complement(product64bit);
    }

    hi = (0xFFFFFFFF00000000 & product64bit)>>32;
    lo = 0x00000000FFFFFFFF & product64bit;

    a = binary(x);
    b = binary(y);
    carry(a, b, product);
    c = binary(product);
    overflow(a, b, c);
    sign(c);
    zero(product);

    return product;
}


int aluDiv(int dividend, int divisor)
{
    int a = 0, b = 0, c = 0, quotient = 0, localRemainder = dividend;
    bool isNegativeDividend = false;
    bool isNegativeDivisor = false;

    if (dividend < 0)
    {
        isNegativeDividend = true;
        if (divisor > 0)
            isNegativeDivisor = false;
    }
    else
    { /* positive dividend */
        isNegativeDividend = false;
        if (divisor < 0)
            isNegativeDivisor = true;
    }

    // convert to unsigned if applicable
    if(binary(dividend) == 1) {
        dividend = complement(dividend);
    }

    if(binary(divisor) == 1) {
        divisor = complement(divisor);
    }

    while(dividend > divisor)
    {
        localRemainder = aluSub(localRemainder,divisor);
        if((localRemainder & 0x80000000))
        {
            localRemainder = aluAdd(localRemainder,divisor);
        }
        else
        {
            quotient = aluAdd(quotient,1);
        }
        if (localRemainder < divisor )
            break;
    }

    if (isNegativeDividend)
    {
        localRemainder = complement(localRemainder);
    }

    if ((isNegativeDividend && !isNegativeDivisor)
            || (!isNegativeDividend && isNegativeDivisor))
    {
        quotient = complement(quotient);
    }

    hi = localRemainder;
    lo = quotient;

    a = binary(dividend);
    b = binary(divisor);
    carry(a, b, quotient);
    c = binary(quotient);
    overflow(a, b, c);
    sign(c);
    zero(quotient);

    return quotient;
}

int aluAnd(int a, int b)
{
    int c = (a & b);
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));
    zero(c);
    return (c);
}
int aluOr(int a, int b)
{
    int c = (a | b );
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));
    zero(c);
    return (c);
}
int aluXor(int a, int b)
{
    int c = (a ^ b);
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));
    zero(c);
    return (c);
}

int aluShiftLeft(int a, int b)
{
    int c = (a << b);
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));;
    zero(c);
    return (c);
}

int aluShiftRightL(int a, int b)
{
    int c = ((a >> b)&~(((1<<31)>>b)<<1));
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));
    zero(c);
    return (c);
}

int aluShiftRightA(int a, int b)
{
    int c = ((a >> b));
    carry(binary(a), binary(b), c);
    overflow(binary(a), binary(b), binary(c));
    sign(binary(c));
    zero(c);
    return (c);
}
