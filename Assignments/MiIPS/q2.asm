.text
.globl main
main:

li $v0,4
la $a0,msg1
syscall

li $v0,5
syscall 
move $t2,$v0

move $t0,$0  #counter
move $t1,$0  #sum
move $s0,$0

loop: 
	li $v0,4
	la $a0,msg3
	syscall
	
	li $v0,5
	syscall
	move $t3,$v0
	
	slt $t5,$s0,$t3
	beq $t5,$0, continue
	move $s0,$t3
	
	continue:
	add $t1,$t1,$t3
	addi $t0,$t0,1
	beq $t0,$t2,exit
	j loop
	
exit: 
li $v0,4
la $a0,msg2
syscall

li $v0,1
move $a0,$t1
syscall

li $v0,4
la $a0,msg4
syscall

li $v0,1
move $a0,$s0
syscall

li $v0,10
syscall


.data
msg1: .asciiz "Enter n:"
msg2: .asciiz "The sum of 10 numbers:"
msg3: .asciiz "Enter each number:"
msg4: .asciiz "Max number:"
