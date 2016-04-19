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
		default:
			return 0;
	}
}

void forwarding_unit(ID_EXE_Buffer *in_buf, EXE_MEM_Buffer *mem_read_buf, MEM_WB_Buffer *wb_read_buf, uint8_t *forward_a, uint8_t *forward_b, uint8_t rsaddr, uint8_t rtaddr)
{
	//Dependency exists, the register file will be written to, and destination is not $zero register
	if((rsaddr == mem_read_buf->rd && mem_read_buf->reg_write == 1 && mem_read_buf->rd != 0 && mem_read_buf->reg_dst == 1) || 
	   (rsaddr == mem_read_buf->rt && mem_read_buf->reg_write == 1 && mem_read_buf->rt != 0 && mem_read_buf->reg_dst == 0))
	{
		*forward_a = 0x1;
	}
	else if((rsaddr == wb_read_buf->rd && wb_read_buf->reg_write == 1 && wb_read_buf->rd != 0 && wb_read_buf->reg_dst == 1) ||
		(rsaddr == wb_read_buf->rt && wb_read_buf->reg_write == 1 && wb_read_buf->rt != 0 && wb_read_buf->reg_dst == 0))
	{
		*forward_a = 0x2;
	}

	if((rtaddr == mem_read_buf->rd && mem_read_buf->reg_write == 1 && mem_read_buf->rd != 0 && in_buf->ALU_src == 0 && mem_read_buf->reg_dst == 1) ||
	   (rtaddr == mem_read_buf->rt && mem_read_buf->reg_write == 1 && mem_read_buf->rt != 0 && (in_buf->ALU_src == 0 || in_buf->mem_write == 1) && mem_read_buf->reg_dst == 0))
	{
		*forward_b = 0x1;
	}
	else if((rtaddr == wb_read_buf->rd && wb_read_buf->reg_write == 1 && wb_read_buf->rd != 0 && in_buf->ALU_src == 0 && wb_read_buf->reg_dst == 1) ||
		    (rtaddr == wb_read_buf->rt && wb_read_buf->reg_write == 1 && wb_read_buf->rt != 0 && (in_buf->ALU_src == 0 || in_buf->mem_write == 1) && wb_read_buf->reg_dst == 0))
	{
		*forward_b = 0x2;
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


void EXE_stage(ID_EXE_Buffer *in_buf, uint16_t *PC, uint8_t *skip_next, EXE_MEM_Buffer *out_buf, EXE_MEM_Buffer *mem_read_buf, MEM_WB_Buffer *wb_read_buf)
{
	uint8_t forward_a = 0;
	uint8_t forward_b = 0;

	if(*skip_next)
	{
		//clearing control values to skip
		out_buf->mem_write = 0;
		out_buf->mem_to_reg = 0;
		out_buf->reg_dst = 0;
		out_buf->reg_write = 0;
		out_buf->mem_read = 0;
		out_buf->next_PC = in_buf->PC;
		*skip_next -= 1;
		return;
	}

	//passing the register addresses using in WB forward
	out_buf->rt = (in_buf->instr & 0x01C0) >> 6;//just the rt part
	out_buf->rd = (in_buf->instr & 0x0038) >> 3;//just the rd part

	uint8_t rsaddr = (in_buf->instr & 0x0E00) >> 9;

	uint16_t ALU_b;
	uint16_t ALU_a;
	//determine whether we need to forward a value to ALU
	forwarding_unit(in_buf, mem_read_buf, wb_read_buf, &forward_a, &forward_b, rsaddr, out_buf->rt);

	//choose forwarded value or instruction value
	if(forward_a == 0x0)
	{
		ALU_a = in_buf->rs;
	}
	else if(forward_a == 0x1)
	{
		ALU_a = mem_read_buf->ALU_out;
	}
	else
	{
		if(wb_read_buf->mem_to_reg == 1)
		{
			ALU_a = wb_read_buf->mem_data;
		}
		else
		{
			ALU_a = wb_read_buf->ALU_data;
		}
	}

	uint8_t dontusert = 0;

	if(forward_b == 0x0 || in_buf->mem_write == 1)
	{
		if(in_buf->ALU_src == 0)
		{
			ALU_b = in_buf->rt;
		}
		else
		{
			ALU_b = sign_extend_const(in_buf->instr);
			if(!in_buf->mem_read && !in_buf->mem_write)
			{
				ALU_b = sign_extend_const(in_buf->instr);
			}
			else
			{
				ALU_b = in_buf->instr & 0x3F;
			}
		}
	}
	else if(forward_b == 0x1)
	{
		ALU_b = mem_read_buf->ALU_out;
	}
	else
	{
		if(wb_read_buf->mem_to_reg == 1)
		{
			ALU_b = wb_read_buf->mem_data;
		}
		else
		{
			ALU_b = wb_read_buf->ALU_data;
		}
	}

	if(forward_b == 1 && in_buf->mem_write)
	{
		out_buf->rt_val = mem_read_buf->ALU_out;
		dontusert = 1;
	}
	else if(forward_b == 2 && in_buf->mem_write)
	{
		dontusert = 1;
		if(wb_read_buf->mem_to_reg == 1)
		{
			out_buf->rt_val = wb_read_buf->mem_data;
		}
		else
		{
			out_buf->rt_val = wb_read_buf->ALU_data;
		}
	}

	//what the ALU should do
	//uint8_t func = ALU_ctrl(in_buf->ALU_op, in_buf->instr & 0x3);//last three bits of instr are func
	uint8_t func = in_buf->ALU_op;
	
	//actually do th math
	out_buf->ALU_out = ALU(ALU_a, ALU_b, func);
	
	//skipping (branching)
	if(in_buf->skip && ((!in_buf->skip_value && out_buf->ALU_out == 0) ||//seq
						(in_buf->skip_value && out_buf->ALU_out != 0)))//sne
	{
		//out_buf->next_PC = in_buf->PC + 2;
		*skip_next = 1;
	}

	//slt logic
	if(in_buf->slt_ctrl == 1)
	{
		out_buf->ALU_out >>= 15;//shift all the way down
	}

	//jumping
	if(in_buf->jump)
	{
		//out_buf->next_PC = in_buf->instr & 0x0FFF;//just get bottom 12 bits
		*PC = in_buf->instr & 0x0FFF;//just get bottom 12 bits
		*skip_next = 2;//flush 2 instructions
	}
	else
	{
		//out_buf->next_PC = in_buf->PC;
	}


	//passing rt forward
	if(dontusert == 0)
	{
		out_buf->rt_val = in_buf->rt;
	}

	//setting future control values
	out_buf->mem_write = in_buf->mem_write;
	out_buf->mem_to_reg = in_buf->mem_to_reg;
	out_buf->reg_dst = in_buf->reg_dst;
	out_buf->reg_write = in_buf->reg_write;
	out_buf->mem_read = in_buf->mem_read;

}


