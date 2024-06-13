.data
arr: .space 400
m1: .asciiz "enter n: "
m2: .asciiz "enter each number: "
m3: .asciiz "sum of n integers: "
newl: .asciiz"\n"
tab : .asciiz "\t"

.text
.globl main
main:
    li $v0, 4
    la $a0, m1
    syscall

    li $v0, 5
    syscall
    move $s0, $v0

li $t0, 0
loop:
slt $t1, $t0, $s0
beq $t1, $0, endl

li $v0, 4
la $a0, m2
syscall

li $v0, 5
syscall
move $t2, $v0

add $t3, $t0, $0
sll $t3, $t3, 2
sw $t2, arr($t3)

addi $t0, 1
j loop

endl:
li $t0, 0
li $s1, 0
    loopp:
    slt $t1, $t0, $s0
    beq $t1, $0, exit
    add $t3, $t0, $0
    sll $t3, $t3, 2
    lw $t1, arr($t3)

    add $s1, $s1, $t1

    li $v0, 1
    move $a0, $t1
    syscall

    addi $t0, 1
    j loopp

exit:
    div $s2,$s1,$s0
    li $v0, 1
    move $a0, $s2
    syscall

    li $v0, 10
    syscall


