#include "stages.h"
#include <stdint.h>
#include <stdio.h>

void IF_stage(uint16_t PC, uint16_t *instr_mem, IF_ID_Buffer *out_buf)
{
	printf("IF\n");

	//Access instruction stored at address held in PC
	uint16_t offset_index = PC / 2;//byte index -> word index
	out_buf->instr = instr_mem[offset_index];

	//Add 2 to PC to get to next instruction
	PC += 2;

	//Store new value of PC for next stage
	out_buf->PC = PC;
}
