#include "stages.h"
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

void MEM_stage(EXE_MEM_Buffer *in_buf, uint16_t *PC, uint16_t *data_mem, MEM_WB_Buffer *out_buf)
{
	printf("aluout:%d\nrt_val:%d\n",in_buf->ALU_out, in_buf->rt_val);
	//writing to memory
	if(in_buf->mem_write)
	{
		if(in_buf->ALU_out / 2 > MEM_SIZE - 1)
		{
			fprintf(stderr, "out of bounds write\n");
			assert(0);
		}
		data_mem[in_buf->ALU_out / 2] = in_buf->rt_val;
	}

	//reading from memory
	if(in_buf->mem_read)
	{
		fprintf(stderr, "out of bounds read\n");
		if(in_buf->ALU_out / 2 > MEM_SIZE - 1)
		{
			assert(0);
		}
		out_buf->mem_data = data_mem[in_buf->ALU_out / 2];
	}
	else
	{
		out_buf->mem_data = 0xBEEF;
	}
	
	//writing to PC
	*PC = in_buf->next_PC;

	//passing stuff forward
	out_buf->ALU_data = in_buf->ALU_out;
	out_buf->rt = in_buf->rt;
	out_buf->rd = in_buf->rd;
	out_buf->mem_to_reg = in_buf->mem_to_reg;
	out_buf->reg_dst = in_buf->reg_dst;
	out_buf->reg_write = in_buf->reg_write;
}
