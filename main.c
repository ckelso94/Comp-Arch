#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "stages.h"

int main(int argc, char** argv)
{
	printf("hello world\n");

	IF_ID_Buffer if_id;
	ID_EXE_Buffer id_exe;
	EXE_MEM_Buffer exe_mem;
	MEM_WB_Buffer mem_wb;

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
		printf("%d\n",instr_mem[i]);
	}

	IF_stage(&PC, instr_mem, &if_id);
	ID_stage(&if_id, reg_file, &id_exe);
	EXE_stage(&id_exe, &exe_mem);
	MEM_stage(&exe_mem, &PC, data_mem, &mem_wb);
	WB_stage(&mem_wb, reg_file);
}
