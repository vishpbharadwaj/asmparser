/*
 * functions.c
 *
 *  Created on: 24-May-2017
 *      Author: vishnu
 */

#include "main.h"

#define MNEMONIC_SIZE 79

char  *asm_mnemonic_LUT[] = {
		/*
		 * rules: operation or rather computation has to take place and not movement of data.
		 * Not even altering registers and flags not including jump even though it includes
		 * operation but it also checks flags. the below mnemonics involve predominantly ALU
		 */
		"ADC", // add with carry
		"ADD", // just add
		"AND", // logical AND
		"CBW", // convert
		"CWDE", // convert
		"CMP", // compare
		"COM", // compare scalar ordered...
		"CVT", // convert
		"CWD", // convert word to double
		"CDQ", // convert to double to quad
		"DA", // DAA and DAS decimal adjust
		"DIV", // floating div
		"F2XM1", // computes (2^x - 1) value
		"FADD", // floating values
		"FBSTP", // Converts the value to an 18-digit packed BCD, stores result in dst opnd, & pops the reg stack
		"FCOM", // compare floating values
		"FCOS", // cosine value
		"FDECSTP", // Subtracts one from the TOP field of the FPU status word
		"FDIV", // floating div
		"FICOM", // FICOM-/p compares value in ST(0) with an integer src opnd and sets the condition code flags
		"FINCSTP", // Adds one to the TOP field of the FPU status word (increments the top-of-stack pointer)
		"FMUL", // floating mul
		"FNOP", // floating nop
		"FPATAN", // floating partial arc tangent
		"FPREM", // flaoting partial remainder
		"FPTAN", // floating partial tangent
		"FSCALE", // flaoting scaling
		"FSIN", // FSIN and FSINCOS operation
		"FSQRT", // floating sqrt
		"FSUB", // floating sub
		"FTST", // Compares the value in the ST(0) register with 0.0 and sets the condition code flags
		"FUCOM", // FUCOM-/p/pp Performs an unordered comparison of register ST(0) and ST(i) and sets condition code flags
		"FXAM", // Examines the contents of the ST(0) register and sets the condition code flags
		"FYL2X", // Compute y * log_2(x) & "FYL2XP1" Compute y * log_2(x + 1)
		"HADD", // HADDPD/PS packed precision floating point add
		"HSUB", // HSUBPD/PS packed precision floating point sub
		"IDIV", //Signed Divide
		"IMUL", // Signed Multiply
		"INC", //Increment by 1
		"MAX", // MAXPD/PS/SD/SS returns max of src & dst opnd
		"MIN", // MINPD/PS/SD/SS returns min of src & dst opnd
		"MUL", // MULPD/PS/SD/SS unsigned multiply
		"NEG", // 2's complement negation
		"NOP", // no op
		"NOT", // 1's complement negation
		"OR", // OR/PD/PS OR
		"PADD", // PADD/B/W/D/Q/SB/SW/USB/USW packed SIMD add
		"PAND", // PAND and PANDN AND and AND & not
		"PAVG", // PAVGB/W packed average cal
		"PCMP", // PCMPEQB/PCMPEQD/PCMPEQW/PCMPESTRI/PCMPESTRM/PCMPGTB/PCMPGTD/PCMPGTW/PCMPISTRI packed compare
		"PMADD", // PMADDWD multiply and add packed
		"PMAX", // PMAXSW/UB packed max val
		"PMIN", // PMINSW/UB packed min val
		"PMUL", // PMULHUW/PMULHW/PMULLW/PMULUDQ packed mul
		"POR", // packed bitwise or
		"PSAD", // PSADBW sum of absolute differences
		"PSLL", // PSLLD/PSLLDQ/PSLLQ/PSLLW shift left logical
		"PSR", // PSRAD/PSRAW/PSRLD/PSRLDQ/PSRLQ/PSRLW shift right arith and logical
		"PSUB", // PSUBB/PSUBD/PSUBQ/PSUBSB/PSUBSW/PSUBUSB/PSUBUSW/PSUBW packed subtract
		"PXOR", // logical xor
		"RCL", // rotate
		"RCR", // rotate
		"ROL", // rotate
		"ROR", // rotate
		"RCP", // RCPSS/RCPPS performs approx reciprocals
		"SAL", // shift
		"SAR", // shift
		"SHL", // shift
		"SHR", // shift
		"SBB", // integer subtraction with borrow
		"SCA", // SCAS/SCASB/SCASW/SCASD/SCASQ scan string - performs compare
		"SHLD", // double precision shift left
		"SHRD", // double precision shift right
		"SQRT", // SQRTPD/SQRTPS/SQRTSD/SQRTSS sqrt calculation
		"SUB", // SUB/SUBPD/SUBPS/SUBSD/SUBSS subtraction
		"TEST", // logical compare
		"UCOM", // UCOMISD/UCOMISS unordered compare
		"XADD", // exchange and add
		"XOR" // XOR/XORPD/PS logical xor
};

char *curr_line = NULL;
char *prev_mnemonic = NULL;
size_t len = 0;
ssize_t read;
char *curr_mnemonic = NULL;
FILE *prsr_out_file;
char prsrname[] = "asmprsr_";


extern FILE *asm_file;
extern char *ip_file_name;

/* process initialization */
unsigned char proc_init(){
	return TRUE;
}

/* mnemonic_parser */
unsigned char mnemonic_parser(){
	short int mnmc_count = 0;
	char y = '1'; /* for writing 1 */
	char x = '0'; /* for writing 0 */

	strcat(prsrname,ip_file_name); /* writing to file with appropriate name */
	prsr_out_file = fopen(prsrname, "w");

    while ((read = getline(&curr_line, &len, asm_file)) != -1) {
        /* perform sub string search */
        for(mnmc_count = 0; mnmc_count < MNEMONIC_SIZE; mnmc_count++) {
        	if(strcasestr(curr_line, asm_mnemonic_LUT[mnmc_count]) != NULL){
        		curr_mnemonic = asm_mnemonic_LUT[mnmc_count];
        		if(curr_mnemonic == asm_mnemonic_LUT[45]){ /* mnemonic for "OR" */
        			/* search again as OR comes in DWORD, QWORD etc*/
        			if((strstr(curr_line, "DWORD")) || (strstr(curr_line, "QWORD")) || (strstr(curr_line, "format"))){
        				continue; /* but opcodes with either of the above with OR or XOR will be missed*/
        			}
        			break;
        		}
        		else
        			break; /* mnemonic found */
        	}
        }

        /* perform prev_line and curr_line processing*/
        if(prev_mnemonic == curr_mnemonic){
        	/* writing 0 to file as ALU cannot perform more than one operation */
        	fprintf(prsr_out_file,"%c\n",x);
        }
        else{
        	/* writing 1 to file as ALU can perform multiple operations as there is a mismatch */
        	fprintf(prsr_out_file,"%c\n",y);
        }

        /* final assignment just before the loop */
        prev_mnemonic = curr_mnemonic;
    }

    fclose(prsr_out_file);

	return TRUE;
}
