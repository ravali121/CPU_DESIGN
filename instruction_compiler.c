/*
 * instruction_compiler.c
 *
 *  Created on: Oct 17, 2016
 *      Author: 212554696
 */
#include "includes/instruction_compiler.h"
#include "includes/register_dictionary.h"

#if defined(_WIN32) || defined(_WIN64)
#define strcasecmp stricmp
#endif

bool compileInstr(char *instr)
{
    bool valid_inst = false;
    char *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL, *p5 = NULL, *p6 = NULL;
    char *endPtr; // needed for strtol
    uint32_t inst_parser=0;
    
    printf("\n\n>>>>PARSING INSTRUCTION: %s\n", instr);
    printf("CURRENT PC: %i\n", PC);
    p1 = strtok(instr, " ");
    printf("p1 = %s\t", p1);
    
    
    /**
     * syntax: 	j <label>
     * e.g.		j loop
     *
     * token will parse the label including the '\n'
     * make sure to use removeInvalidChars() function to remove '\n'
     */
    if(!strcasecmp(p1, "j")) {
		inst_parser |= J << 26;
		p2 = strtok(NULL, "");
		char *labelName = removeInvalidChars(p2); // <<< remember to do this!
		printf("parsing label: [%s]\n", labelName);
		Label label = getLabelByName(labelName);
		uint32_t labelOffset = label.offset;
		labelOffset &= ~(0xFC << 24); // flush most significant six bits for opcode;
		inst_parser |= labelOffset;
		valid_inst = true;
        }
   else if(!strcasecmp(p1, "jal")) {
  		inst_parser |= JAL << 26;
  		p2 = strtok(NULL, "");
  		char *labelName = removeInvalidChars(p2); // <<< remember to do this!
  		printf("parsing label: [%s]\n", labelName);
  		Label label = getLabelByName(labelName);
  		uint32_t labelOffset = label.offset;
  		labelOffset &= ~(0xFC << 24); // flush most significant six bits for opcode;
  		inst_parser |= labelOffset;
  		valid_inst = true;
        }
   else if(!strcasecmp(p1, "jr")) {
	    inst_parser |= RTYPE << 26;
	    p2 = strtok(NULL, " ");
		char *parseRegister = removeInvalidChars(p2);
	    printf("parsing: [%s]\t", parseRegister);
		uint8_t rs = getRegisterAddr(parseRegister);
		printf("rs: %x\t\n", rs);
		inst_parser |= rs << 21;
		inst_parser |= JR_FUNC;
		valid_inst = true;
   }
   else if(!strcasecmp(p1,"push")) {
  		inst_parser |= PUSH << 26;

  		p2 = strtok(NULL, " ");
  		char *parseRegister = removeInvalidChars(p2);
        printf("parsing: [%s]\t", parseRegister);
  		uint8_t rs = getRegisterAddr(parseRegister);
  		printf("rs: %x\t\n", rs);

  		inst_parser |= rs << 21;
  		valid_inst = true;
  	}
      else if(!strcasecmp(p1,"pop")) {
  		inst_parser |= POP << 26;
  		p2 = strtok(NULL, " ");
  		char *parseRegister = removeInvalidChars(p2);
        printf("parsing: [%s]\t", parseRegister);
  		uint8_t rt = getRegisterAddr(parseRegister);
  		printf("rt: %x\t\n", rt);

  		inst_parser |= rt << 21;
  		valid_inst = true;
  	}
    else if(!strcasecmp(p1, "bne"))
    {
        inst_parser |= BNE << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
        
    }
    else if(!strcasecmp(p1, "beq"))
    {
        inst_parser |= BEQ << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "bl"))
    {
        inst_parser |= BL << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "ble"))
    {
        inst_parser |= BLE << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "bge"))
    {
        inst_parser |= BGE << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "bg"))
    {
        inst_parser |= BG << 26;
        p2 = strtok(NULL, ",");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, " ,");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %d\t\n", rs);
        
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        
        p4 = strtok(NULL, "");
        char *labelName = removeInvalidChars(p4); // <<< remember to do this!
        printf("parsing label: [%s]\n", labelName);
        Label label = getLabelByName(labelName);
        uint32_t labelOffset = label.offset;
        labelOffset &= ~(0xFFFF << 16); // flush most significant sixteen bits for opcode;
        inst_parser |= labelOffset;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "ld"))
    {
        // converts assembly code to binary
        inst_parser |= LD << 26;
        
        // get destination register
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        // get offset
        p3 = strtok(NULL, ", (");
        printf("parsing: %s\t", p3);
        long offsetInLong = strtol(p3, &endPtr, 0);
        offsetInLong &= ~(0xFFFF << 16);
        // need to be in unsigned to extract
        // the 16 bits from long
        uint16_t offset = 0;
        offset |= offsetInLong;
        printf("offset: %x\t\n", offset);
        
        // get source register
        p4 = strtok(NULL, ")");
        printf("parsing: %s\t", p4);
        uint8_t rs = getRegisterAddr(p4);
        printf("rs: %x\t\n", rs);
        inst_parser |= rs << 21; // rs comes first before rt in IR
        inst_parser |= rt << 16;
        inst_parser |= offset;
        valid_inst = true;
    } else if (!strcasecmp(p1, "lds")) {
        // e.g.
        // lds t0, 0(t2, t4)3
        // converts assembly code to binary
        inst_parser |= LDS << 26;
        
        // get destination register
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rd = getRegisterAddr(p2);
        printf("rd: %x\t\n", rd);
        
        // get offset
        // offset is 6 bits
        p3 = strtok(NULL, ", (");
        printf("parsing: %s\t", p3);
        long offsetInLong = strtol(p3, &endPtr, 0);
        offsetInLong &= ~(0xFFFF8 << 11);
        // need to be in unsigned to extract
        // the 6 bits from long
        uint8_t offset = 0;
        offset |= offsetInLong;
        printf("offset: %x\t\n", offset);
        
        // get source register
        // source register will contain the address
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        uint8_t rs = getRegisterAddr(p4);
        printf("rs: %x\t\n", rs);
        
        p5 = strtok(NULL, " )");
        printf("parsing: %s\t", p5);
        uint8_t rt = getRegisterAddr(p5);
        printf("rt: %x\t\n", rt);
        
        // scale is 5 bits long
        p6 = strtok(NULL, "\0");
        printf("parsing: %s\t", p6);
        long scaleInLong = strtol(p6, &endPtr, 0);
        scaleInLong &= ~(0xFFFFFE << 5);
        // need to be in unsigned to extract
        // the 16 bits from long
        uint8_t scale = 0;
        scale |= scaleInLong;
        printf("scale: %x\t\n", scale);
        
        //r-type command
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        inst_parser |= rd << 11;
        inst_parser |= offset << 6;
        inst_parser |= scale;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "lea"))
    {
        // load address
        inst_parser |= LEA << 26;
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        inst_parser |= rt << 21;
        // rs is not used for la instruction
        uint8_t rs = 0;
        inst_parser |= rs << 16;
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        long addressInLong = strtol(p3, &endPtr, 0);
        addressInLong &= ~(0xFFFF << 16);
        uint16_t address = 0;
        address |= addressInLong;
        printf("address: %x\t\n", address);
        
        inst_parser |= address;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "st"))
    {
        inst_parser |= ST << 26;
        // get source register, $rt
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        // get offset
        p3 = strtok(NULL, ", (");
        printf("parsing: %s\t", p3);
        long offsetInLong = strtol(p3, &endPtr, 0);
        
        uint16_t offset = 0;
        offsetInLong &= ~(0xFFFF << 16);
        offset |= offsetInLong;
        printf("offset: %x\t\n", offset);
        
        // get $rs
        p4 = strtok(NULL, ")");
        printf("parsing: %s\t", p4);
        uint8_t rs = getRegisterAddr(p4);
        printf("rs: %x\t\n", rs);
        
        inst_parser |= rs << 21; // rs comes first before rt in IR
        inst_parser |= rt << 16;
        inst_parser |= offset;
        valid_inst = true;
    } else if (!strcasecmp(p1, "sts")) {
        // e.g.
        // sts t0, 0(t2, t4)3
        // converts assembly code to binary
        inst_parser |= STS << 26;
        
        // get source register
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rs = getRegisterAddr(p2);
        printf("rs: %x\t\n", rs);
        
        // get offset
        // offset is 6 bits
        p3 = strtok(NULL, ", (");
        printf("parsing: %s\t", p3);
        long offsetInLong = strtol(p3, &endPtr, 0);
        offsetInLong &= ~(0xFFFF8 << 11);
        // need to be in unsigned to extract
        // the 6 bits from long
        uint8_t offset = 0;
        offset |= offsetInLong;
        printf("offset: %x\t\n", offset);
        
        // get destination register
        // destination register will contain the address
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        uint8_t rd = getRegisterAddr(p4);
        printf("rd: %x\t\n", rd);
        
        p5 = strtok(NULL, " )");
        printf("parsing: %s\t", p5);
        uint8_t rt = getRegisterAddr(p5);
        printf("rt: %x\t\n", rt);
        
        // scale is 5 bits long
        p6 = strtok(NULL, "\0");
        printf("parsing: %s\t", p6);
        long scaleInLong = strtol(p6, &endPtr, 0);
        scaleInLong &= ~(0xFFFFFE << 5);
        // need to be in unsigned to extract
        // the 16 bits from long
        uint8_t scale = 0;
        scale |= scaleInLong;
        printf("scale: %x\t\n", scale);
        
        //r-type command
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        inst_parser |= rd << 11;
        inst_parser |= offset << 6;
        inst_parser |= scale;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "addi"))
    {
        // converts assembly code to binary
        inst_parser |= ADDI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        // use IR to call addi funtion
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "add"))
    {
        // converts assembly code to binary
        inst_parser |= ADD << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "subi"))
    {
        inst_parser |= SUBI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        // use IR to call addi funtion
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "sub"))
    {
        // converts assembly code to binary
        inst_parser |= SUB << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "muli"))
    {
        inst_parser |= MULI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        // use IR to call addi funtion
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "mul"))
    {
        // converts assembly code to binary
        inst_parser |= MUL << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "divi"))
    {
        inst_parser |= DIVI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        // use IR to call addi funtion
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "div"))
    {
        // converts assembly code to binary
        inst_parser |= DIV << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "cmp"))
    {
        // converts assembly code to binary
        inst_parser |= CMP << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rs1 = getRegisterAddr(p2);
        printf("rs1: %x\t\n", rs1);
        
        p3 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p3);
        uint8_t rs2 = getRegisterAddr(p3);
        printf("rs2: %x\t\n", rs2);
        
        /*        p4 = strtok(NULL, ", \n");
         printf("parsing: %s\t", p4);
         uint8_t rs2 = getRegisterAddr(p4);
         printf("rs2: %x\t\n", rs2);*/
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        //inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "mov"))
    {
        // converts assembly code to binary
        inst_parser |= MOV << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        /*        p4 = strtok(NULL, ", \n");
         printf("parsing: %s\t", p4);
         uint8_t rs2 = getRegisterAddr(p4);
         printf("rs2: %x\t\n", rs2);*/
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        //inst_parser |= rs2 << 16;
        inst_parser |= rt  << 16;
        
        valid_inst = true;
    }else if (!strcasecmp(p1, "and"))
    {
        // converts assembly code to binary
        inst_parser |= AND << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }else if (!strcasecmp(p1, "or"))
    {
        // converts assembly code to binary
        inst_parser |= OR << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "andi"))
    {
        inst_parser |= ANDI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "ori"))
    {
        inst_parser |= ORI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "xor"))
	{
		// converts assembly code to binary
		inst_parser |= XOR << 26;

		p2 = strtok(NULL, ", ");
		printf("parsing: %s\t", p2);
		uint8_t rt = getRegisterAddr(p2);
		printf("rt: %x\t\n", rt);

		p3 = strtok(NULL, ", ");
		printf("parsing: %s\t", p3);
		uint8_t rs1 = getRegisterAddr(p3);
		printf("rs1: %x\t\n", rs1);

		p4 = strtok(NULL, ", \n");
		printf("parsing: %s\t", p4);
		uint8_t rs2 = getRegisterAddr(p4);
		printf("rs2: %x\t\n", rs2);

		// rs comes first before rt
		inst_parser |= rs1 << 21;
		inst_parser |= rs2 << 16;
		inst_parser |= rt  << 11;

		valid_inst = true;
	}
    else if(!strcasecmp(p1, "xori"))
    {
        inst_parser |= XORI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "sll"))
    {
        // converts assembly code to binary
        inst_parser |= SLL << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "slli"))
    {
        inst_parser |= SLLI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "srl"))
    {
        // converts assembly code to binary
        inst_parser |= SRL << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "srli"))
    {
        inst_parser |= SRLI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    else if (!strcasecmp(p1, "sra"))
    {
        // converts assembly code to binary
        inst_parser |= SRA << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs1 = getRegisterAddr(p3);
        printf("rs1: %x\t\n", rs1);
        
        p4 = strtok(NULL, ", \n");
        printf("parsing: %s\t", p4);
        uint8_t rs2 = getRegisterAddr(p4);
        printf("rs2: %x\t\n", rs2);
        
        // rs comes first before rt
        inst_parser |= rs1 << 21;
        inst_parser |= rs2 << 16;
        inst_parser |= rt  << 11;
        
        valid_inst = true;
    }
    else if(!strcasecmp(p1, "srai"))
    {
        inst_parser |= SRAI << 26;
        
        p2 = strtok(NULL, ", ");
        printf("parsing: %s\t", p2);
        uint8_t rt = getRegisterAddr(p2);
        printf("rt: %x\t\n", rt);
        
        p3 = strtok(NULL, ", ");
        printf("parsing: %s\t", p3);
        uint8_t rs = getRegisterAddr(p3);
        printf("rs: %x\t\n", rs);
        
        // rs comes first before rt
        inst_parser |= rs << 21;
        inst_parser |= rt << 16;
        p4 = strtok(NULL, ", ");
        printf("parsing: %s\t", p4);
        long immInLong = strtol(p4, &endPtr, 0);
        
        uint16_t imm = 0;
        immInLong &= ~(0xFFFF << 16);
        imm |= immInLong;
        printf("imm: %x\t\n", imm);
        
        inst_parser |= imm;
        valid_inst = true;
    }
    
    
    if(valid_inst)
    {
        IR = inst_parser;
        printf("IR: \t%08x\n", IR);
    }
    
    return valid_inst;
}
