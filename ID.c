#include "stages.h"
#include <stdint.h>
#include <stdio.h>

/*return value:
[RegDst(0),ALUSrc(1),MemToReg(2),RegWrite(3),MemRead(4),MemWrite(5),
 Slt(6),Skip(7),SkipValue(8),Jump(9),ALUOp(10-11),Func(12-14),0(15)]
*/
uint16_t control_unit(uint16_t instr)
{	
	uint8_t opcode;
	uint8_t func;
	opcode = (instr & 0b1111000000000000) >> 12;
	func = instr & 0b0000000000000111;
	switch(opcode)
	{
		case 0b0000:
			//R-Type
			switch(func)
			{
				case 0b000: //add
					return 0b1001000000100000;
				case 0b001: //sub
					return 0b1001000000100010;
				case 0b010: //sll
					return 0b1001000000100100;
				case 0b011: //srl
					return 0b1001000000100110;
				case 0b100: //and
					return 0b1001000000101000;
				case 0b101: //or
					return 0b1001000000101010;
				case 0b110: //xor
					return 0b1001000000101100;
				case 0b111: //nor
					return 0b1001000000101110;
			}
		case 0b0001: //lw
			return 0b0111100000000000;
		case 0b0010: //sw
			return 0b0100010000000000;
		case 0b0011: //seq
			return 0b0000000100010000;
		case 0b0100: //jmp
			return 0b0000000001110000;
		case 0b0101: //slt
			return 0b1001001000100010;
		case 0b0110: //slti
			return 0b0101001000010000;
		case 0b0111: //sne
			return 0b0000000110010000;
		case 0b1000: //addi
			return 0b0101000000100000;
		case 0b1001: //subi
			return 0b0101000000100010;
		case 0b1010: //slli
			return 0b0101000000100100;
		case 0b1011: //srli
			return 0b0101000000100110;
		case 0b1100: //andi
			return 0b0101000000101000;
		case 0b1101: //ori
			return 0b0101000000101010;
		case 0b1110: //xori
			return 0b0101000000101100;
		case 0b1111: //nori
			return 0b0101000000101110;
	}				
}

uint8_t bin_val(uint16_t val)
{
	if(val>0){ return 1;}
	else{ return 0;}
}


void ID_stage(IF_ID_Buffer *in_buf, ID_EXE_Buffer *old_out, uint16_t *reg_file, uint8_t *load_hazard, ID_EXE_Buffer *out_buf)
{
	out_buf->rs = reg_file[(in_buf->instr & 0b0000111000000000) >> 9];
	out_buf->rt = reg_file[(in_buf->instr & 0b0000000111000000) >> 6];
	out_buf->instr = in_buf->instr;
	out_buf->PC = in_buf->PC;

	uint16_t ctrl_signals;
	ctrl_signals = control_unit(in_buf->instr);
	out_buf->ALU_src = bin_val(ctrl_signals & 0b0100000000000000);
	out_buf->slt_ctrl = bin_val(ctrl_signals & 0b0000001000000000);
	out_buf->skip = bin_val(ctrl_signals & 0b0000000100000000);
	out_buf->skip_value = bin_val(ctrl_signals & 0b0000000010000000);
	out_buf->jump = bin_val(ctrl_signals & 0b0000000001000000);
	out_buf->mem_write = bin_val(ctrl_signals & 0b0000010000000000);
	out_buf->mem_read = bin_val(ctrl_signals & 0b0000100000000000);
	out_buf->mem_to_reg = bin_val(ctrl_signals & 0b0010000000000000);
	out_buf->reg_dst = bin_val(ctrl_signals & 0b1000000000000000);
	out_buf->reg_write = bin_val(ctrl_signals & 0b0001000000000000);
	//ALU op is basically func now
	out_buf->ALU_op = (ctrl_signals & 0b0000000000001110) >> 1;

	if(old_out->mem_read == 1 && out_buf->jump == 0 && 
			(old_out->rt == out_buf->rs ||
			 old_out->rt == out_buf->rt && (out_buf->ALU_src == 0 || out_buf->mem_write == 1)))
	{
		*load_hazard = 1;
		out_buf->skip = 0;
		out_buf->jump = 0;
		out_buf->mem_write = 0;
		out_buf->reg_write = 0;
	}
}

