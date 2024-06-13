section .data
m1: db 'enter no of elements: '
l1 : equ $-m1
m2: db 'enter each element: '
l2 : equ $-m2
m3 : db ' sorted array : ', 10
l3 : equ $-m3
tab : db 9
newline : db 10
zero : db '0'
lz : equ $-zero

section .bss


section .text
global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, m1
    mov edx, l1
    int 80h
    call read_num
    mov cx, word[num]
    mov word[n], cx

    mov ebx, array
    mov eax, 0
    call read_array

    mov ebx, array
    mov eax, 0
    call sort_array

    read_array:
        


read_num:
    pusha
    mov word[num], 0
    reading:
        mov eax, 3
        mov ebx, 0
        mov ecx, temp
        mov edx, 1
        int 80h
        cmp word[temp], 10
        je end_read
        mov ax, word[num]
        mov bx, 10
        mul bx
        sub word[temp], 30h
        add ax, word[temp]
        mov word[num], ax
        jmp reading

    end_read:
        popa
        ret

