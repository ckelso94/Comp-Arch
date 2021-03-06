#define mov(r,A,B,C,D)\
	andi r, r, 0x0000@\
	ori r, r, 0x~A@\
	slli r, r, 4@\
	ori r, r, 0x~B@\
	slli r, r, 4@\
	ori r, r, 0x~C@\
	slli r, r, 4@\
	ori r, r, 0x~D@\

;where we can save registers if we need a temporary register
#define TEMP_ADDR 0x0

;some needed addresses for constants
#define CONST_1_ADDR 0x2
#define CONST_2_ADDR 0x4
#define CONST_3_ADDR 0x6

;loading some constants into memory
mov($v0,0,1,0,0)
sw $v0, CONST_1_ADDR($zero)
mov($v0,F,F,0,0)
sw $v0, CONST_2_ADDR($zero)
mov($v0,0,0,F,F)
sw $v0, CONST_3_ADDR($zero)

;loading default values in registers
mov($v1,1,0,1,0)
mov($v2,0,0,0,F)
mov($v3,0,0,F,0)
mov($t0,0,0,0,0)
mov($a0,0,0,1,0)
mov($a1,0,0,0,5)

;loading values in memory from the project instructions pdf
mov($v0,0,1,0,1)
sw $v0, 0($a0)
mov($v0,0,1,1,0)
sw $v0, 2($a0)
mov($v0,0,0,1,1)
sw $v0, 4($a0)
mov($v0,0,0,F,0)
sw $v0, 6($a0)
mov($v0,0,0,F,F)
sw $v0, 8($a0)

;still need to load v0 with its default value
mov($v0,0,0,4,0)
