#ifndef STAGES_H
#define STAGES_H
#include <stdint.h>

typedef struct
{
	//the instruction, not the address
	uint16_t instr;
	//the value of the next PC (actually PC+4)
	uint16_t PC;
} IF_ID_Buffer;

typedef struct
{
	//the two registers from reg_file
	uint16_t rs,rt;
	//the instruction, needed for const/jumps
	uint16_t instr;
	//PC+4 from IF_ID
	uint16_t PC;
	//control values
	uint8_t ALU_src,slt_ctrl,skip,skip_value,jump,ALU_op,func,
			mem_write,mem_to_reg,
			reg_dst,reg_write;
} ID_EXE_Buffer;

typedef struct
{
	//output from the ALU
	uint16_t ALU_out;
	//value of rt, used for writing
	uint16_t rt_val;
	//addresses of rt and rd, needed by WB
	uint8_t rt,rd;
	//next PC value
	uint16_t next_PC;
	//control values
	uint8_t mem_write,mem_to_reg,
			reg_dst,reg_write;

} EXE_MEM_Buffer;

typedef struct
{
	//data to possibly be written back
	uint16_t data;
	//possible registers to write to
	uint8_t rt,rd;
	//control values
	uint8_t reg_dst,reg_write;
} MEM_WB_Buffer;

void IF_stage(uint16_t *PC, uint16_t *instr_mem, IF_ID_Buffer *out_buf);
void ID_stage(IF_ID_Buffer *in_buf, uint16_t *reg_file, ID_EXE_Buffer *out_buf);
//PC is just a pointer, we need it to possible modify the PC value
//Don't use the pointer to read the PC, that's in in_buf
void EXE_stage(ID_EXE_Buffer *in_buf, uint16_t *PC, EXE_MEM_Buffer *out_buf);
void MEM_stage(EXE_MEM_Buffer *in_buf, uint16_t *data_mem, MEM_WB_Buffer *out_buf);
void WB_stage(MEM_WB_Buffer *in_buf, uint16_t *reg_file);

#endif
