 # print string : li $v0, 4
 # read int : li $v0,5
 # print int : li $v0, 1
 # exit : li $v0, 10   
 #slt (t0,t1,t2)-> if(s2<s3)->s1= 1

    .data
msg1: .asciiz "enter a"
msg2: .asciiz "enter b"
msg3: .asciiz "enter c"
msg4: .asciiz "the value of d is : "
msg5: .asciiz "condition not satisfied"
    .text
    .globl main
main:
#print msg
li $v0, 4
la $a0, msg1
syscall

#get value of a n save
li $v0, 5
syscall
move $t1,$v0

li $v0, 4
la $a0, msg2
syscall

li $v0, 5
syscall
move $t2, $v0

li $v0, 4
la $a0, msg3
syscall

li $v0, 5
syscall
move $t3, $v0

# t1->a, t2->b, t3->code

slt $t0, $t1, $t0
beq $t0, $0, not    #if(a>=b) go to not
bne $t3, $t0, not   # if(a<b) but (c!=0) go to not
addi $t4, $0, 1

li $v0, 4
la $a0, msg4
syscall

li $v0, 4
move $a0, $t4
syscall

not:
    li $v0, 4
    la $a0, msg5
    syscall

    li $v0, 10
    syscall

