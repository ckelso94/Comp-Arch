#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "stages.h"

void EXE_test()
{
	ID_EXE_Buffer in;
	in.rs = 0x0005;
	in.rt = 0x0004;
	in.instr = 0x0002;
	in.PC = 0x0006;
	in.ALU_src = 1;
	in.slt_ctrl = 0;
	in.skip = 0;
	in.skip_value = 0;
	in.jump = 0;
	in.ALU_op = 0x00;
	//other control bits don't matter
	
	EXE_MEM_Buffer out;
	EXE_stage(&in, &out);
	printf("out:%d\n",out.ALU_out);
	printf("new PC:%d\n",out.next_PC);
}

int main(int argc, char** argv)
{
	printf("hello world\n");

	IF_ID_Buffer if_id_read;
	IF_ID_Buffer if_id_write;
	ID_EXE_Buffer id_exe_read;
	ID_EXE_Buffer id_exe_write;
	EXE_MEM_Buffer exe_mem_read;
	EXE_MEM_Buffer exe_mem_write;
	MEM_WB_Buffer mem_wb_read;
	MEM_WB_Buffer mem_wb_write;

	uint16_t PC;
	uint16_t reg_file[8];
	uint16_t data_mem[1024];

	//getting the instructions from a binary file
	//TODO filename should be from argv
	FILE *in = fopen("a.out", "r");
	if(in == NULL)
	{
		fprintf(stderr, "a.out not found\n");
		return EXIT_FAILURE;
	}
	fseek(in, 0, SEEK_END);
	//size is the number of instructions
	int size = ftell(in) / sizeof(uint16_t);
	rewind(in);
	uint16_t *instr_mem = malloc(size * sizeof(uint16_t));
	fread(instr_mem, sizeof(uint16_t), size, in);
	fclose(in);

	//TODO see if endianness matters
	for(int i = 0; i < size; i++)
	{
		//printf("%d\n",instr_mem[i]);
	}

	IF_stage(&PC, instr_mem, &if_id_write);
	ID_stage(&if_id_read, reg_file, &id_exe_write);
	EXE_stage(&id_exe_read, &exe_mem_write);
	MEM_stage(&exe_mem_read, &PC, data_mem, &mem_wb_write);
	WB_stage(&mem_wb_read, reg_file);

	if_id_read = if_id_write;
	id_exe_read = id_exe_write;
	exe_mem_read = exe_mem_write;
	mem_wb_read = mem_wb_write;

	EXE_test();
}
