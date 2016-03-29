#include <stdio.h>
#include <stdint.h>
#include "stages.h"

int main(int argc, char** argv)
{
	printf("hello world\n");
	IF_ID_Buffer if_id;
	ID_EXE_Buffer id_exe;
	EXE_MEM_Buffer exe_mem;
	MEM_WB_Buffer mem_wb;

	uint16_t PC;
	uint16_t instr_mem[1024];
	uint16_t reg_file[8];
	uint16_t data_mem[1024];

	IF_stage(&PC, instr_mem, &if_id);
	ID_stage(&if_id, reg_file, &id_exe);
	EXE_stage(&id_exe, &PC, &exe_mem);
	MEM_stage(&exe_mem, data_mem, &mem_wb);
	WB_stage(&mem_wb, reg_file);
}
