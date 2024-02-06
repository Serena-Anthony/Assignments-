; 2. Read a 2-digit number and find the sum of even numbers from0 
;to that number.

section .data
add1: db 'enter number',10
l1: equ $-add1
newline:db 10
newl:equ $-newline

section .bss
bleh: resb 1
num: resw 1
count: resw 1
sum: resw 1
temp: resw 1

section .text
global _start
_start:

read_var:
mov word[num], 0

mov eax, 4
mov ebx, 1
mov ecx, add1
mov edx, l1
int 80h

read_loop:
mov eax, 3
mov ebx, 0
mov ecx, bleh
mov edx, 1
int 80h

cmp byte[bleh], 10
je end_read
mov ax, word[num]
mov bx, 10
mul bx
mov bl, byte[bleh]
sub bl, 30h
mov bh, 0
add ax, bx
mov word[num], ax 
jmp read_loop 
end_read: 

mov word[count],0
mov word[sum],0
mov ax,word[sum]
mov bx,word[count]
for:
add bx,2
cmp bx,word[num]
ja printnum
add ax,bx
jmp for

printnum:
mov word[sum],ax
mov word[count],0
pusha

extract_no:
cmp word[sum], 0
je print_no
inc word[count]
mov dx, 0
mov ax, word[sum]
mov bx, 10
div bx
push dx
mov word[sum], ax
jmp extract_no

print_no:
cmp word[count], 0
je end_print
dec word[count]
pop dx
mov byte[temp], dl
add byte[temp], 30h
mov eax, 4
mov ebx, 1
mov ecx, temp
mov edx, 1
int 80h
jmp print_no
end_print:

mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, newl
int 80h

mov eax, 1
mov ebx, 0
int 80h
