#include "stages.h"
#include <stdint.h>
#include <stdio.h>

void ID_stage(IF_ID_Buffer *in_buf, uint16_t *reg_file, ID_EXE_Buffer *out_buf)
{
	printf("ID\n");
	out_buf->rs = reg_file[(in_buf->instr & 0b000111000000) >> 9];
	out_buf->rt = reg_file[(in_buf->instr & 0b000000111000) >> 6];
	out_buf->instr = in_buf->instr;
	out_buf->PC = in_buf->PC;
}
