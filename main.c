#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "stages.h"


//prints contents of a register file
void print_reg(uint16_t *reg_file)
{
	static char *reg_names[] = {"$zero","$v0","$v1","$v2","$v3","$t0","$a0","$a1"};
	for(int i = 0; i < 8; i++)
	{
		printf("%s:\t%d\n",reg_names[i],reg_file[i]);
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

void print_if_id(IF_ID_Buffer *buf)
{
	printf("IF ID Buffer\n");
	printf("instr:\t\t%d\n",buf->instr);
	printf("PC:\t\t%d\n", buf->PC);
}

void print_id_exe(ID_EXE_Buffer *buf)
{
	printf("ID EXE Buffer\n");
	printf("rs:\t\t%d\n", buf->rs);
	printf("rt:\t\t%d\n", buf->rt);
	printf("instr:\t\t%d\n", buf->instr);
	printf("PC:\t\t%d\n", buf->PC);
}

void print_exe_mem(EXE_MEM_Buffer *buf)
{
	printf("EXE MEM Buffer\n");
	printf("ALU_out:\t%d\n", buf->ALU_out);
	printf("rt_val:\t\t%d\n", buf->rt_val);
	printf("rt:\t\t%d\n", buf->rt);
	printf("rd:\t\t%d\n", buf->rd);
	printf("next_PC:\t%d\n", buf->next_PC);
}

void print_mem_wb(MEM_WB_Buffer *buf)
{
	printf("MEM WB Buffer\n");
	printf("mem_data:\t%d\n", buf->mem_data);
	printf("ALU_data:\t%d\n", buf->ALU_data);
	printf("rt:\t\t%d\n", buf->rt);
	printf("rd:\t\t%d\n", buf->rd);
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
		printf("\n---------------------\n");
		IF_stage(PC, instr_mem, &if_id_write);
		PC += 2;
		ID_stage(&if_id_read, reg_file, &id_exe_write);
		EXE_stage(&id_exe_read, &PC, &skip_next, &exe_mem_write, &exe_mem_read, &mem_wb_read);
		MEM_stage(&exe_mem_read, data_mem, &mem_wb_write);
		WB_stage(&mem_wb_read, reg_file);

		reg_file[0] = 0;//hard code $zero

		printf("Old buffers:\n");
		print_if_id(&if_id_read);
		print_id_exe(&id_exe_read);
		print_exe_mem(&exe_mem_read);
		print_mem_wb(&mem_wb_read);


		printf("\nNew buffers:\n");
		print_if_id(&if_id_write);
		print_id_exe(&id_exe_write);
		print_exe_mem(&exe_mem_write);
		print_mem_wb(&mem_wb_write);
		printf("\n");

		print_reg(reg_file);
		printf("\n");
		print_mem(data_mem);
		printf("\n");

		printf("skip_next:%d\n",skip_next);

		if_id_read = if_id_write;
		id_exe_read = id_exe_write;
		exe_mem_read = exe_mem_write;
		mem_wb_read = mem_wb_write;
	}

}
