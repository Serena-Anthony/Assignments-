.text

.globl main
main:
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg1
	syscall
	
	li $v0,5
	syscall
	move $t0,$v0
	
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg2
	syscall
	
	li $v0,5
	syscall
	move $t1,$v0
	
	li	$v0,4		# print_string syscall code = 4
	la	$a0, msg3
	syscall
	
	li $v0,5
	syscall
	move $t2,$v0
	
	
	move $t4,$zero
	#move $t5,$0
	# t0 ->a t1->b t2->c
	slt $t3, $t0, $t1
	
	beq $t3, $zero, print
	bne $t2, $zero, print
	addi, $t4, $t5, 1
	
	
	print:
	
	li $v0,1
	move $a0,$t4
	syscall
	
	li $v0,10
	syscall
	
.data
msg1: .asciiz "Enter A:"
msg2: .asciiz "Enter B:"
msg3: .asciiz  "Enter c:"
