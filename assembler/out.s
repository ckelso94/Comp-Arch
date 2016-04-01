# 1 "loader.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "loader.s"
# 12 "loader.s"
;where we can save registers if we need a temporary register


;some needed addresses for constants



;loading some constants into memory
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4 ori $v0, $v0, 0x0
 slli $v0, $v0, 4

sw $v0, 0x22($zero)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4 ori $v0, $v0, 0x0
 slli $v0, $v0, 4

sw $v0, 0x24($zero)

;loading default values in registers
andi $v1, $v1, 0x0000
 ori $v1, $v1, 0x1
 slli $v1, $v1, 4
 ori $v1, $v1, 0x0
 slli $v1, $v1, 4
 ori $v1, $v1, 0x1
 slli $v1, $v1, 4 ori $v1, $v1, 0x0
 slli $v1, $v1, 4

andi $v2, $v2, 0x0000
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4 ori $v2, $v2, 0xF
 slli $v2, $v2, 4

andi $v3, $v3, 0x0000
 ori $v3, $v3, 0x0
 slli $v3, $v3, 4
 ori $v3, $v3, 0x0
 slli $v3, $v3, 4
 ori $v3, $v3, 0xF
 slli $v3, $v3, 4 ori $v3, $v3, 0x0
 slli $v3, $v3, 4

andi $t0, $t0, 0x0000
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4 ori $t0, $t0, 0x0
 slli $t0, $t0, 4

andi $a0, $a0, 0x0000
 ori $a0, $a0, 0x0
 slli $a0, $a0, 4
 ori $a0, $a0, 0x0
 slli $a0, $a0, 4
 ori $a0, $a0, 0x1
 slli $a0, $a0, 4 ori $a0, $a0, 0x0
 slli $a0, $a0, 4

andi $a1, $a1, 0x0000
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4 ori $a1, $a1, 0x5
 slli $a1, $a1, 4


;loading values in memory from the project instructions pdf
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4 ori $v0, $v0, 0x1
 slli $v0, $v0, 4

sw $v0, 0($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4 ori $v0, $v0, 0x0
 slli $v0, $v0, 4

sw $v0, 2($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4 ori $v0, $v0, 0x1
 slli $v0, $v0, 4

sw $v0, 4($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4 ori $v0, $v0, 0x0
 slli $v0, $v0, 4

sw $v0, 6($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4 ori $v0, $v0, 0xF
 slli $v0, $v0, 4

sw $v0, 6($a0)

;still need to load v0 with its default value
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x4
 slli $v0, $v0, 4 ori $v0, $v0, 0x0
 slli $v0, $v0, 4

