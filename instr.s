andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
sw $v0, 0x2($zero)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0xF
slli $v0, $v0, 4
ori $v0, $v0, 0xF
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
sw $v0, 0x4($zero)
andi $v1, $v1, 0x0000
ori $v1, $v1, 0x1
slli $v1, $v1, 4
ori $v1, $v1, 0x0
slli $v1, $v1, 4
ori $v1, $v1, 0x1
slli $v1, $v1, 4
ori $v1, $v1, 0x0
slli $v1, $v1, 4
andi $v2, $v2, 0x0000
ori $v2, $v2, 0x0
slli $v2, $v2, 4
ori $v2, $v2, 0x0
slli $v2, $v2, 4
ori $v2, $v2, 0x0
slli $v2, $v2, 4
ori $v2, $v2, 0xF
slli $v2, $v2, 4
andi $v3, $v3, 0x0000
ori $v3, $v3, 0x0
slli $v3, $v3, 4
ori $v3, $v3, 0x0
slli $v3, $v3, 4
ori $v3, $v3, 0xF
slli $v3, $v3, 4
ori $v3, $v3, 0x0
slli $v3, $v3, 4
andi $t0, $t0, 0x0000
ori $t0, $t0, 0x0
slli $t0, $t0, 4
ori $t0, $t0, 0x0
slli $t0, $t0, 4
ori $t0, $t0, 0x0
slli $t0, $t0, 4
ori $t0, $t0, 0x0
slli $t0, $t0, 4
andi $a0, $a0, 0x0000
ori $a0, $a0, 0x0
slli $a0, $a0, 4
ori $a0, $a0, 0x0
slli $a0, $a0, 4
ori $a0, $a0, 0x1
slli $a0, $a0, 4
ori $a0, $a0, 0x0
slli $a0, $a0, 4
andi $a1, $a1, 0x0000
ori $a1, $a1, 0x0
slli $a1, $a1, 4
ori $a1, $a1, 0x0
slli $a1, $a1, 4
ori $a1, $a1, 0x0
slli $a1, $a1, 4
ori $a1, $a1, 0x5
slli $a1, $a1, 4
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
sw $v0, 0($a0)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
sw $v0, 2($a0)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
ori $v0, $v0, 0x1
slli $v0, $v0, 4
sw $v0, 4($a0)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0xF
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
sw $v0, 6($a0)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0xF
slli $v0, $v0, 4
ori $v0, $v0, 0xF
slli $v0, $v0, 4
sw $v0, 8($a0)
andi $v0, $v0, 0x0000
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
ori $v0, $v0, 0x4
slli $v0, $v0, 4
ori $v0, $v0, 0x0
slli $v0, $v0, 4
slti $t0, $a1, 1
seq $t0, $zero
jmp while_end
addi $a1, $a1, -1
lw $t0, 0($a0)
sw $v0, 0x0($zero)
lw $v0, 0x2($zero)
slt $v0, $v0, $t0
sne $v0, $zero
jmp else_body
lw $v0, 0x0($zero)
srli $v0, $v0, 3
or $v1, $v1, $v0
sw $v0, 0x0($zero)
lw $v0, 0x4($zero)
sw $v0, 0($a0)
lw $v0, 0x0($zero)
jmp if_end
lw $v0, 0x0($zero)
slli $v1, $v2, 2
xor $v3, $v3, $v2
sw $v0, 0x0($zero)
lw $v0, 0x4($zero)
sw $v0, 0($a0)
lw $v0, 0x0($zero)
addi $a0, $a0, 2
jmp while_top
