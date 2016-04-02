#include "stages.h"
#include <stdint.h>
#include <stdio.h>

uint16_t ALU(uint16_t a, uint16_t b, uint8_t func)
{
	switch(func)
	{
		case 0x0:
			return a + b;
		case 0x1:
			return a - b;
		case 0x2:
			return a << b;
		case 0x3:
			return a >> b;
		case 0x4:
			return a & b;
		case 0x5:
			return a | b;
		case 0x6:
			return a ^ b;
		case 0x7:
			return ~(a | b);
	}
}

/*
uint8_t ALU_ctrl(uint8_t ALU_op, uint8_t func)
{
	switch(ALU_op)//TODO use the actual values
	{
		case 0x0:
			return 0x0;//add, for lw-type instructions
		case 0x1:
			return 0x1;//sub, for slt-type instructions
		case 0x02:
			return func;//standard ALU
	}
}
*/

uint16_t sign_extend_const(uint16_t instr)
{
	uint16_t c = instr & 0x3F;//get last 6 bits
	if(c & 0x20)//if sign bit is set
		{
			c |= ~0x003F;//fill upper bits with 1s
		}
	return c;
}


void EXE_stage(ID_EXE_Buffer *in_buf, EXE_MEM_Buffer *out_buf)
{
	printf("EXE\n");
	//see what value we need to feed into the ALU
	uint16_t ALU_b;
	if(in_buf->ALU_src == 0)//TODO use actual values
	{
		ALU_b = in_buf->rt;
	}
	else
	{
		ALU_b = sign_extend_const(in_buf->instr);
	}

	//what the ALU should do
	//uint8_t func = ALU_ctrl(in_buf->ALU_op, in_buf->instr & 0x3);//last three bits of instr are func
	uint8_t func = in_buf->ALU_op;
	
	//actually do th math
	out_buf->ALU_out = ALU(in_buf->rs, ALU_b, func);
	
	//skipping (branching)
	//TODO fix skip_value to use the actual value
	if(in_buf->skip && ((!in_buf->skip_value && out_buf->ALU_out == 0) ||//seq
						(in_buf->skip_value && out_buf->ALU_out != 0)))//sne
	{
		out_buf->next_PC = in_buf->PC + 2;
	}
	else
	{
		out_buf->next_PC = in_buf->PC;
	}

	//slt logic
	if(in_buf->slt_ctrl == 1)
	{
		out_buf->ALU_out &= 0x8000;//get sign bit
		out_buf->ALU_out >>= 15;//shift all the way down
	}

	//jumping
	if(in_buf->jump)
	{
		out_buf->next_PC = in_buf->instr & 0x0FFF;//just get bottom 12 bits
	}

	//passing rt forward
	out_buf->rt_val = in_buf->rt;

	//passing the register addresses using in WB forward
	out_buf->rt = (in_buf->instr & 0x01C0) >> 6;//just the rt part
	out_buf->rd = (in_buf->instr & 0x0038) >> 3;//just the rd part
	
	//setting future control values
	out_buf->mem_write = in_buf->mem_write;
	out_buf->mem_to_reg = in_buf->mem_to_reg;
	out_buf->reg_dst = in_buf->reg_dst;
	out_buf->reg_write = in_buf->reg_write;
	out_buf->mem_read = in_buf->mem_read;
}


