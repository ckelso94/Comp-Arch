while_top: slti $t0, $a1, 1;test <= 0 (or < 1) (we don't need t0 until later)
seq $t0, $zero;if <= 0, jump to end
jmp while_end
 addi $a1, $a1, -1
 lw $t0, 0($a0)
 sw $v0, 0x20($zero);save $v0
 lw $v0, 0x22($zero);load const 1 from address (put in memory by simulator)
 slt $v0, $v0, $t0;$v0 = 1 if 0x0100 < $t0
 sne $v0, $zero;if $v0 = 1 (i.e. $t0 > 0x0100), then skip the jump
 jmp else_body
 lw $v0, 0x20($zero);restore $v0
  srli $v0, $v0, 3
  or $v1, $v1, $v0
  sw $v0, 0x20($zero);save $v0
  lw $v0, 0x24($zero);load const 1 from address (put in memory by simulator)
  sw $v0, 0($a0);save 0xFF00 to memory
  lw $v0, 0x20($zero);restore $v0
  jmp if_end;skip the else body
 else_body: lw $v0, 0x20($zero);restore $vo from if statement
  slli $v1, $v2, 2
  xor $v3, $v3, $v2
  sw $v0, 0x20($zero);save $v0
  lw $v0, 0x24($zero);load const 1 from address (put in memory by simulator)
  sw $v0, 0($a0);save 0xFF00 to memory
  lw $v0, 0x20($zero);restore $v0
 if_end: addi $a0, $a0, 2
 jmp while_top
 while_end: jmp while_end;do nothing
