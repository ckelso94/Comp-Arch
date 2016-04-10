#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "stages.h"


//prints contents of a register file
void print_reg(uint16_t *reg_file)
{
	static char *reg_names[] = {"$ze","$v0","$v1","$v2","$v3","$t0","$a0","$a1"};
	for(int i = 0; i < 8; i++)
	{
		printf("%s:%d\n",reg_names[i],reg_file[i]);
	}
}

void print_mem(uint16_t *data_mem)
{
	uint16_t num_zero = 0;
	for(int i = 0; i < MEM_SIZE; i++)
	{
		if(data_mem[i] != 0)
		{
			if(num_zero > 0)
			{
				printf("%d zero values omitted\n", num_zero);
			}
			printf("mem[%d]:%d\n",i,data_mem[i]);
			num_zero = 0;
		}
		else
		{
			num_zero++;
		}
	}
	if(num_zero > 0)
	{
		printf("%d zero values omitted\n", num_zero);
	}
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
	uint16_t reg_file[8] = {0,1,2,3,4,5,6,7};
	uint16_t data_mem[MEM_SIZE];
	for(int i = 0; i < MEM_SIZE; i ++)
	{
		data_mem[i] = 0;
	}
	uint8_t skip_next = 0;

	long prog_size = 0;
	FILE **files = (FILE **) malloc((argc-1) * sizeof(FILE *));
	int *sizes = (int *) malloc((argc-1) * sizeof(int));

	//getting the instructions from a binary file from args
	for(int i = 1; i < argc; i++)
	{
		files[i-1] = fopen(argv[i], "r");
		if(files[i-1] == NULL)
		{
			fprintf(stderr, "binary not found\n");
			return EXIT_FAILURE;
		}
		fseek(files[i-1], 0, SEEK_END);
		//size is the number of instructions
		sizes[i-1] = ftell(files[i-1]) / sizeof(uint16_t);
		prog_size += sizes[i-1];
		rewind(files[i-1]);
	}

	uint8_t num_nops = 5;//extra padding at end

	uint16_t *instr_mem = malloc((prog_size + num_nops) * sizeof(uint16_t));

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

	//inserting padding at end
	for(int i = prog_size; i < prog_size + num_nops; i++)
	{
		instr_mem[i] = 0;
	}

	for(int i = 0; i < prog_size; i++)
	{
		printf("%d\n",instr_mem[i]);
	}

	while(PC / 2 < (prog_size + num_nops))
	{
		printf("\nPC: %d\n",PC);
		IF_stage(PC, instr_mem, &if_id_write);
		PC += 2;
		ID_stage(&if_id_read, reg_file, &id_exe_write);
		EXE_stage(&id_exe_read, &PC, &skip_next, &exe_mem_write, &exe_mem_read, &mem_wb_read);
		MEM_stage(&exe_mem_read, data_mem, &mem_wb_write);
		WB_stage(&mem_wb_read, reg_file);

		reg_file[0] = 0;//hard code $zero

		print_reg(reg_file);
		print_mem(data_mem);

		printf("skip_next:%d\n",skip_next);

		if_id_read = if_id_write;
		id_exe_read = id_exe_write;
		exe_mem_read = exe_mem_write;
		mem_wb_read = mem_wb_write;
	}

}
