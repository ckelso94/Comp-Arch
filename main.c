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

void IF_test()
{
	IF_ID_Buffer out;
	uint16_t instr_mem[] = {0x0, 0x5, 0x3};
	uint16_t PC = 4;
	IF_stage(PC, instr_mem, &out);
	printf("instr: %d\n", out.instr);
	printf("PC: %d\n", out.PC);
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

	long prog_size = 0;
	FILE **files = (FILE **) malloc((argc-1) * sizeof(FILE *));
	int *sizes = (int *) malloc((argc-1) * sizeof(int));

	//getting the instructions from a binary file from args
	for(int i = 1; i < argc; i++)
	{
		files[i-1] = fopen(argv[i], "r");
		if(files[i-1] == NULL)
		{
			fprintf(stderr, "a.out not found\n");
			return EXIT_FAILURE;
		}
		fseek(files[i-1], 0, SEEK_END);
		//size is the number of instructions
		sizes[i-1] = ftell(files[i-1]) / sizeof(uint16_t);
		prog_size += sizes[i-1];
		rewind(files[i-1]);
	}

	uint16_t *instr_mem = malloc(prog_size * sizeof(uint16_t));

	long current = 0;//offset of where to insert each file into instr_mem
	for(int i = 0; i < argc - 1; i++)
	{
		int size = sizes[i];
		fread(instr_mem + current, sizeof(uint16_t), size, files[i]);
		current += size;
		fclose(files[i]);
	}
	free(sizes);
	free(files);

	//TODO see if endianness matters
	for(int i = 0; i < prog_size; i++)
	{
		//printf("%d\n",instr_mem[i]);
	}

	//to actually pipeline, change the rightmost buffers from _read to _write
	IF_stage(PC, instr_mem, &if_id_read);
	ID_stage(&if_id_read, reg_file, &id_exe_read);
	EXE_stage(&id_exe_read, &exe_mem_read);
	MEM_stage(&exe_mem_read, &PC, data_mem, &mem_wb_read);
	WB_stage(&mem_wb_read, reg_file);

	/* also uncomment this for pipelining
	if_id_read = if_id_write;
	id_exe_read = id_exe_write;
	exe_mem_read = exe_mem_write;
	mem_wb_read = mem_wb_write;
	*/

	IF_test();
}
