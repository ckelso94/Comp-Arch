#include "stages.h"
#include <stdint.h>
#include <stdio.h>

void ID_stage(IF_ID_Buffer *in_buf, uint16_t *reg_file, ID_EXE_Buffer *out_buf)
{
	printf("ID\n");
	out_buf->rs = reg_file[(in_buf->instr & 0b0000111000000000) >> 9];
	out_buf->rt = reg_file[(in_buf->instr & 0b0000000111000000) >> 6];
	out_buf->instr = in_buf->instr;
	out_buf->PC = in_buf->PC;

	uint16_t opcode = (in_buf->instr & 0b1111000000000000) >> 12;
}
