/*
 * instruction_parser.c
 *
 *  Created on: Oct. 17, 2016
 *      Author: Marvin
 */

// INSTRUCTIONS

#include "includes/instruction_parser.h"

// 0010 00ss ssst tttt iiii iiii iiii iiii
void addi(uint8_t rs, uint8_t rt, int16_t imm) {
    setRegister(rt, aluAdd(getRegisterValue(rs), imm));
}

void mipsAdd(uint8_t rs1, uint8_t rt, uint8_t rs2) {
    setRegister(rt, aluAdd(getRegisterValue(rs1), getRegisterValue(rs2)));
}
// 0010 01ss ssst tttt iiii iiii iiii iiii
void subi(uint8_t rs, uint8_t rt, int16_t imm){
    setRegister(rt, aluSub(getRegisterValue(rs), imm));
}

void mipsSub(uint8_t rs1, uint8_t rt, uint8_t rs2){
    setRegister(rt, aluSub(getRegisterValue(rs1), getRegisterValue(rs2)));
}

void muli(uint8_t rs, uint8_t rt, int16_t imm){
    setRegister(rt, aluMul(getRegisterValue(rs), imm));
}

void mipsMul(uint8_t rs1, uint8_t rt, uint8_t rs2){
    setRegister(rt, aluMul(getRegisterValue(rs1), getRegisterValue(rs2)));
}

void divi(uint8_t rs, uint8_t rt, int16_t imm){
    setRegister(rt, aluDiv(getRegisterValue(rs), imm));
}

void mipsDiv(uint8_t rs1, uint8_t rt, uint8_t rs2){
    setRegister(rt, aluDiv(getRegisterValue(rs1), getRegisterValue(rs2)));
}

//1000 11ss ssst tttt iiii iiii iiii iiii
void ld(uint8_t rs, uint8_t rt, int16_t imm){
    setRegister(rt, loadFromMem(aluAdd(getRegisterValue(rs), imm)));
}

void lds(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t offset, uint8_t scale) {
    int memAddr = aluMul(getRegisterValue(rt), scale); //implement scale
    memAddr = aluAdd(memAddr, offset);
    memAddr = aluAdd(getRegisterValue(rs), memAddr);
    setRegister(rd, loadFromMem(memAddr));
}

void sts(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t offset, uint8_t scale) {
    int memAddr = aluMul(getRegisterValue(rt), scale); //implement scale
    memAddr = aluAdd(memAddr, offset);
    memAddr = aluAdd(getRegisterValue(rd), memAddr);
    storeToMem(memAddr, getRegisterValue(rs));
}

//1010 11ss sssx xxxx aaaa aaaa aaaa aaaa
void st(uint8_t rs, uint8_t rt, int16_t imm){
    storeToMem(aluAdd(getRegisterValue(rs), imm), getRegisterValue(rt));
}

void la(uint8_t rt, int16_t addr) {
    setRegister(rt, addr);
}

void compare(uint8_t rs1, uint8_t rs2){
    aluSub(getRegisterValue(rs1), getRegisterValue(rs2));
}

void moveR(uint8_t rt, uint8_t rs){
    setRegister(rt, getRegisterValue(rs));
}

void mipsAnd(uint8_t rs1, uint8_t rt, uint8_t rs2) {
    setRegister(rt, aluAnd(getRegisterValue(rs1), getRegisterValue(rs2)));
}

void mipsOr(uint8_t rs1, uint8_t rt, uint8_t rs2) {
    setRegister(rt, aluOr(getRegisterValue(rs1), getRegisterValue(rs2)));
}

void mipsXor(uint8_t rs1, uint8_t rt, uint8_t rs2) {
    setRegister(rt, aluXor(getRegisterValue(rs1), getRegisterValue(rs2)));
}

void mipsAndI(uint8_t rs, uint8_t rt, uint16_t imm) {
    setRegister(rt, aluAnd(getRegisterValue(rs), (uint32_t)imm));
}

void mipsOrI(uint8_t rs, uint8_t rt, uint16_t imm) {
    setRegister(rt, aluOr(getRegisterValue(rs), (uint32_t)imm));
}

void mipsXorI(uint8_t rs, uint8_t rt, uint16_t imm) {
    setRegister(rt, aluXor(getRegisterValue(rs), (uint32_t)imm));
}

void shiftLeft(uint8_t rs1, uint8_t rt, uint8_t rs2){
    unsigned int shift = getRegisterValue(rs2);
        setRegister(rt, aluShiftLeft(getRegisterValue(rs1), shift));
}

void shiftLeftI(uint8_t rs, uint8_t rt, uint16_t imm){
        setRegister(rt, aluShiftLeft(getRegisterValue(rs), (uint32_t)imm));
}

void shiftRightL(uint8_t rs1, uint8_t rt, uint8_t rs2){
    uint32_t shift = (uint32_t)getRegisterValue(rs2);
        setRegister(rt, aluShiftRightL(getRegisterValue(rs1), shift));
}

void shiftRightLI(uint8_t rs, uint8_t rt, uint16_t imm){
        setRegister(rt, aluShiftRightL(getRegisterValue(rs), (uint32_t)imm));
}

void shiftRightA(uint8_t rs1, uint8_t rt, uint8_t rs2){
    uint32_t shift = (uint32_t)getRegisterValue(rs2);
        setRegister(rt, aluShiftRightA(getRegisterValue(rs1), shift));
}

void shiftRightAI(uint8_t rs, uint8_t rt, uint16_t imm){
        setRegister(rt, aluShiftRightA(getRegisterValue(rs), (uint32_t)imm));
}

void jump(uint32_t offset) {
	printf("Current PC: %i\n", PC);
	PC &= 0xF0000000; // as per MIPS instruction, retain the most significant 4 bits.
	printf("Adding %i and %i\n", INSTR_MEMORY_BASE, offset);
	PC |= aluAdd(INSTR_MEMORY_BASE, offset); // remember to add the memory base address.
	printf("Next PC: %i\n", PC);
}

void jumpAndLink(uint32_t offset) {
	printf("Current PC: %i\n", PC);
	// set return address register
	//since we're always adding 4 to PC, we don't need to explicitly add 4 here
	setRegister(getRegisterAddr("ra"), PC);

	PC &= 0xF0000000; // as per MIPS instruction, retain the most significant 4 bits.
	printf("Adding %i and %i\n", INSTR_MEMORY_BASE, offset);
	PC |= aluAdd(INSTR_MEMORY_BASE, offset); // remember to add the memory base address.
	printf("Next PC: %i\n", PC);
}

void jumpRegister(uint8_t rs) {
	PC = getRegisterValue(rs);
}

void push(uint8_t rs) {
	//check memory
	if(getRegisterValue(getRegisterAddr("sp")) <= STACK_BOTTOM) {
		printf("Bottom of the stack reached, unable to push data to the memory.\n");
	}
	else {
		setRegister(getRegisterAddr("sp"), aluAdd(getRegisterValue(getRegisterAddr("sp")), -4));
		storeToMem(getRegisterValue(getRegisterAddr("sp")), getRegisterValue(rs));
	}
}


void pop(uint8_t rt) {
	if(getRegisterValue(getRegisterAddr("sp")) >= STACK_TOP) {
		printf("Top of the stack reached, unable to pop data to the register.\n");
	} else {
		setRegister(rt, loadFromMem(getRegisterValue(getRegisterAddr("sp"))));
		setRegister(getRegisterAddr("sp"), aluAdd(getRegisterValue(getRegisterAddr("sp")), 4));
	}
}


void parseInstructionReg(uint32_t instruction)
{
    uint8_t opcode = instruction >> 26;
    switch(opcode) {
            
        case (uint8_t) ADDI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[ADDI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            addi(rs, rt, imm);
            break;
        }
        case (uint8_t) ADD: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[ADD] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsAdd(rs1, rt, rs2);
            break;
        }
        case (uint8_t) LD: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[LD] IR: %i: %i, (%i)%i", opcode, rt, imm, rs);
            ld(rs, rt, imm);
            break;
        }
        case (uint8_t) LDS: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            uint8_t rd = (instruction & 0x0000F800) >> 11;
            uint8_t offset = (instruction & 0x000007E0) >> 6;
            uint8_t scale = instruction & 0X1F;
            printf("[LDS] IR: %i: %i, %i(%i, %i)%i\n", opcode, rd, offset, rs, rt, scale);
            lds(rs, rt, rd, offset, scale);
            break;
        }
        case (uint8_t) SUBI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[SUBI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            subi(rs, rt, imm);
            break;
        }
        case (uint8_t) SUB: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[SUB] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsSub(rs1, rt, rs2);
            break;
        }
        case (uint8_t) MULI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[MULI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            muli(rs, rt, imm);
            break;
        }
        case (uint8_t) MUL: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[MUL] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsMul(rs1, rt, rs2);
            break;
        }
        case (uint8_t) DIVI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[DIVI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            divi(rs, rt, imm);
            break;
        }
        case (uint8_t) DIV: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[DIV] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsDiv(rs1, rt, rs2);
            break;
        }
        case (uint8_t) ST: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[ST] IR: %i: %i, (%i)%i\n", opcode, rt, imm, rs);
            st(rs, rt, imm);
            break;
        }
        case (uint8_t) STS: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            uint8_t rd = (instruction & 0x0000F800) >> 11;
            uint8_t offset = (instruction & 0x000007E0) >> 6;
            uint8_t scale = instruction & 0X1F;
            printf("[STS] IR: %i: %i, %i(%i, %i)%i\n", opcode, rd, offset, rs, rt, scale);
            sts(rs, rt, rd, offset, scale);
            break;
        }
        case (uint8_t) LEA: {
            uint8_t rt = (instruction & 0x03E00000) >> 21;
            uint8_t notUsed =(instruction & 0x001F0000 ) >> 16;
            uint16_t addr = instruction & 0xFFFF;
            printf("[LEA] IR: %i: %i, %i\n", opcode, rt, addr);
            la(rt, addr);
            break;
        }
        case (uint8_t) CMP: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            //uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[CMP] IR: %i: %i, %i\n", opcode, rs1, rs2);
            compare(rs1, rs2);
            break;
        }
        case (uint8_t) MOV: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt = (instruction & 0x001F0000) >> 16;
            //uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[MOV] IR: %i: %i, %i\n", opcode, rt, rs);
            moveR(rt, rs);
            break;
        }
        case (uint8_t) AND: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[AND] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsAnd(rs1, rt, rs2);
            break;
        }
        case (uint8_t) OR: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[OR] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsOr(rs1, rt, rs2);
            break;
        }
        case (uint8_t) XOR: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[XOR] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            mipsXor(rs1, rt, rs2);
            break;
        }
        case (uint8_t) ANDI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[ANDI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            mipsAndI(rs, rt, imm);
            break;
        }
        case (uint8_t) ORI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[ORI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            mipsOrI(rs, rt, imm);
            break;
        }
        case (uint8_t) XORI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[XORI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            mipsXorI(rs, rt, imm);
            break;
        }
        case (uint8_t) SLL: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[SLL] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            shiftLeft(rs1, rt, rs2);
            break;
        }
        case (uint8_t) SLLI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[SLLI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            shiftLeftI(rs, rt, imm);
            break;
        }
        case (uint8_t) SRL: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[SRL] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            shiftRightL(rs1, rt, rs2);
            break;
        }
        case (uint8_t) SRLI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[SRLI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            shiftRightLI(rs, rt, imm);
            break;
        }
        case (uint8_t) SRA: {
            uint8_t rs1 = (instruction & 0x03E00000) >> 21;
            uint8_t rs2 = (instruction & 0x001F0000) >> 16;
            uint8_t rt =(instruction & 0x0000F800 ) >> 11;
            printf("[SRA] IR: %i: %i, %i, %i\n", opcode, rt, rs1, rs2);
            shiftRightA(rs1, rt, rs2);
            break;
        }
        case (uint8_t) SRAI: {
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            int16_t imm = instruction & 0xFFFF;
            printf("[SRAI] IR: %i: %i, %i, %i\n", opcode, rt, rs, imm);
            shiftRightAI(rs, rt, imm);
            break;
        }
        case (uint8_t) J: {
            uint32_t offset = (instruction & 0x03FFFFFF);
            offset = offset << 2; // multiply by 4
            jump(offset);
            printf("[J] IR: %i %i\n", opcode, offset);
            break;
        }
        case (uint8_t) BNE: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BNE] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if(!(SR & (1<<6)))
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) BEQ: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BEQ] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if((SR & (1<<6)))
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) PUSH: {
        	uint8_t rs = (instruction & 0x03E00000) >> 21;
            printf("[PUSH] IR: %i: %i\n", opcode, rs);
            push(rs);
            break;
        }
        case (uint8_t) POP: {
        	uint8_t rt = (instruction & 0x03E00000) >> 21;
            printf("[POP] IR: %i: %i\n", opcode, rt);
            pop(rt);
            break;
        }
        case (uint8_t) BL: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BL] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if((SR & (1<<7)) ^ (SR & (1<<11)))
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) BLE: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BLE] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if( ((SR & (1<<7)) ^ (SR & (1<<11))) || ((SR & (1<<6))) )
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) BGE: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BGE] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if( !((SR & (1<<7)) ^ (SR & (1<<11))) )
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) BG: {
            uint32_t offset = (instruction & 0xFFFF);
            offset = offset << 2;
            uint8_t rs = (instruction & 0x03E00000) >> 21;
            uint8_t rt =(instruction & 0x001F0000 ) >> 16;
            printf("[BG] IR: %i: %i, %i, %i\n", opcode, rt, rs, offset);
            compare(rt,rs);
            if( !((SR & (1<<7)) ^ (SR & (1<<11))) && !((SR & (1<<6))) )
            {
                jump(offset);
            }
            break;
        }
        case (uint8_t) JAL: {
			uint32_t offset = (instruction & 0x03FFFFFF);
			offset = offset << 2; // multiply by 4
			jumpAndLink(offset);
			printf("[JAL] IR: %i %i\n", opcode, offset);
			break;
		}
        case (uint8_t) RTYPE: {
			printf("INSTRUCTION AT RTYPE: %x\n", instruction);
			uint8_t rs = (instruction & 0x03E00000) >> 21;
			uint8_t function = (instruction & 0x0000003F);
			switch (function) {
					// parse instructions here
				case (uint8_t) JR_FUNC: {
					printf("[JR] IR: %i %i\n", opcode, rs);
					jumpRegister(rs);
					break;
				}
				default: break;
			}
			break;
		}
        default: break;
    }
    printf("\n\n");
}




