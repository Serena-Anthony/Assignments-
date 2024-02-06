;Read a number and find whether it is prime.

section .data
newline: db 10
msg3 : db 'Yes'
l3 : equ $-msg3
msg4 : db 'No'
l4 : equ $-msg4

section .bss
digit1 : resb 1
digit2 : resb 1
num1:resb 1
temp:resw 1

section .text
global _start
_start:

;Reading first digit
mov eax, 3
mov ebx, 0
mov ecx, digit1
mov edx, 1
int 80h

;Reading second digit
mov eax, 3
mov ebx, 0
mov ecx, digit2
mov edx, 2 ;Here we put 2 because we need to read and
int 80h    ;omit enter key press as well

sub byte[digit1], 30h
sub byte[digit2], 30h
;Getting the number from ASCII
; num1 = (10* digit1) + digit2

mov al, byte[digit1] ; Copying first digit to al
mov bl, 10
mul bl ; Multiplying al with 10
movzx bx, byte[digit2] ; Copying digit2 to bx
add ax, bx
mov byte[num1], al ; We are sure that no less than 256, so we can
                   ;omit higher 8 bits of the result.

; we finally have read the 2 digit num now check through loop

mov eax, '1'
mov ah,0

l1:
	mov [temp], eax
	mov eax,4
	mov ebx,1
	push ecx
	
	mov ecx, [temp]
	mov edx, 1
	int 80h
	
	mov eax, [temp]
	sub eax, 30h
	mov bl, byte[num1]
        sub bl, 30h
        div bl

   cmp ah, 0	 
   je if
	   else:
	   	mov eax, 4
	   	mov ebx, 1
	   	mov ecx, msg4
	   	mov edx, l4
	   	int 80h
	   	jmp exit
	   	
	  if:
	  	mov eax, 4
	  	mov ebx, 1
	  	mov ecx, msg3
	  	mov edx, l3
	  	int 80h
	  	
	  	
inc eax
add eax, '0'
pop ecx
loop l1

exit:
mov eax,1
mov ebx,0
int 80h



