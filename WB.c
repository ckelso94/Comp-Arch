#include "stages.h"
#include <stdint.h>
#include <stdio.h>

uint16_t Mux_Mem_to_Reg(uint8_t mem_to_reg, uint16_t mem_data, uint16_t alu_data)
{
	//Choose which data output to write back to register based on control signal
	uint16_t write_data;
	if(mem_to_reg == 1)
	{
		//commented out so the program builds
		write_data = mem_data;
	}
	else
	{
		//commented out so the program builds
		write_data = alu_data;
	}

	return write_data;
}

uint8_t Mux_Reg_Dst(uint8_t reg_dst, uint8_t rt, uint8_t rd)
{
	//Choose which register to write output to based on control signal
	uint8_t write_addr;
	if(reg_dst == 0)
	{
		//commented out so the program builds
		write_addr = rt;
	}
	else
	{
		//commented out so the program builds
		write_addr = rd;
	}

	return write_addr;
}

void WB_stage(MEM_WB_Buffer *in_buf, uint16_t *reg_file)
{
	uint16_t write_data = Mux_Mem_to_Reg(in_buf->mem_to_reg, in_buf->mem_data, in_buf->ALU_data);

	uint8_t write_addr = Mux_Reg_Dst(in_buf->reg_dst, in_buf->rt, in_buf->rd);

	//Write data to register at specified address in register file
	if(in_buf->reg_write == 1)
	{
		reg_file[write_addr] = write_data;
	}
}
