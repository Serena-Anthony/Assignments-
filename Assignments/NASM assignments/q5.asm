section .data
    user: db "enter the number of iterations", 10
    nlen: equ $ - user

section .bss
out :resb 4
n :resb 2
    
section .text
global _start
_start:
;; Prompt the user to enter a number 
    mov eax, 4
    mov ebx, 1
    mov ecx, user
    mov edx, nlen
    int 80h
    
;; Read user input and stores that ot 'iterations'
    mov eax, 3
    mov ebx, 2
    mov ecx, n
    mov edx, 5
    int 80h

;setting edi to zero
xor edi, edi
loop:
    mov ecx, edi
    add ecx, 0x30
    mov [out], ecx
    mov ecx, out
    ;;writing the nos
    mov eax,4
    mov ebx,1
    mov edx,1
    int 80h
    inc edi
    ;;compare current edi with input n value
    cmp edi, [n]
    je loop
    
.exit:
;exit
    mov eax, 1
    mov ebx, 0
    int 0x80
