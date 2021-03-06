# 1 "loader.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "loader.s"
# 11 "loader.s"
;where we can save registers if we need a temporary register


;some needed addresses for constants




;loading some constants into memory
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0

sw $v0, 0x2($zero)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0

sw $v0, 0x4($zero)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF

sw $v0, 0x6($zero)

;loading default values in registers
andi $v1, $v1, 0x0000
 ori $v1, $v1, 0x1
 slli $v1, $v1, 4
 ori $v1, $v1, 0x0
 slli $v1, $v1, 4
 ori $v1, $v1, 0x1
 slli $v1, $v1, 4
 ori $v1, $v1, 0x0

andi $v2, $v2, 0x0000
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4
 ori $v2, $v2, 0x0
 slli $v2, $v2, 4
 ori $v2, $v2, 0xF

andi $v3, $v3, 0x0000
 ori $v3, $v3, 0x0
 slli $v3, $v3, 4
 ori $v3, $v3, 0x0
 slli $v3, $v3, 4
 ori $v3, $v3, 0xF
 slli $v3, $v3, 4
 ori $v3, $v3, 0x0

andi $t0, $t0, 0x0000
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4
 ori $t0, $t0, 0x0
 slli $t0, $t0, 4
 ori $t0, $t0, 0x0

andi $a0, $a0, 0x0000
 ori $a0, $a0, 0x0
 slli $a0, $a0, 4
 ori $a0, $a0, 0x0
 slli $a0, $a0, 4
 ori $a0, $a0, 0x1
 slli $a0, $a0, 4
 ori $a0, $a0, 0x0

andi $a1, $a1, 0x0000
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4
 ori $a1, $a1, 0x0
 slli $a1, $a1, 4
 ori $a1, $a1, 0x5


;loading values in memory from the project instructions pdf
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1

sw $v0, 0($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0

sw $v0, 2($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1
 slli $v0, $v0, 4
 ori $v0, $v0, 0x1

sw $v0, 4($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0

sw $v0, 6($a0)
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF
 slli $v0, $v0, 4
 ori $v0, $v0, 0xF

sw $v0, 8($a0)

;still need to load v0 with its default value
andi $v0, $v0, 0x0000
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0
 slli $v0, $v0, 4
 ori $v0, $v0, 0x4
 slli $v0, $v0, 4
 ori $v0, $v0, 0x0

# 1 "test.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "test.s"

;0x0100

;0xFF00

;0x00FF


;while($a1 > 0) do {
while_top:
slti $t0, $a1, 1;test <= 0 (or < 1) (we don't need t0 until later)
seq $t0, $zero;if <= 0, jump to end
jmp while_end

 ;$a1 = $a1 - 1
 addi $a1, $a1, -1
 ;$t0 = Mem[$a0]
 lw $t0, 0($a0)

 ;if($t0 > 0x0100) then {
 sw $v0, 0x0($zero);save $v0
 lw $v0, 0x2($zero);load const 1 from address (put in memory by simulator)
 slt $v0, $v0, $t0;$v0 = 1 if 0x0100 < $t0
 sne $v0, $zero;if $v0 = 1 (i.e. $t0 > 0x0100), then skip the jump
 jmp else_body
 lw $v0, 0x0($zero);restore $v0

  ;$v0 = $v0 / 8
  srli $v0, $v0, 3
  ;$v1 = $v1 | $ v0
  or $v1, $v1, $v0

  ;Mem[$a0] = 0xFF00
  sw $v0, 0x0($zero);save $v0
  lw $v0, 0x4($zero);load const 1 from address (put in memory by simulator)
  sw $v0, 0($a0);save 0xFF00 to memory
  lw $v0, 0x0($zero);restore $v0

  jmp if_end;skip the else body

 else_body:
 lw $v0, 0x0($zero);restore $vo from if statement
  ;$v2 = $v2 * 4
  slli $v2, $v2, 2
  ;$v3 = $v3 ^ $v2
  xor $v3, $v3, $v2

  ;Mem[$a0] = 0x00FF
  sw $v0, 0x0($zero);save $v0
  lw $v0, 0x6($zero);load const 1 from address (put in memory by simulator)
  sw $v0, 0($a0);save 0x00FF to memory
  lw $v0, 0x0($zero);restore $v0

 if_end:

 ;$a0 = $a0 + 2
 addi $a0, $a0, 2

 ;go to top of loop
 jmp while_top

 ;end of loop
 while_end:
;do nothing
