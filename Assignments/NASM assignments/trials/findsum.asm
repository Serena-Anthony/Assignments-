section .data
m1: db 'enter no of elements : '
l1: equ $-m1
m2: db 'enter each element : '
l2: equ $-m2
m3: db 'sum of given values is :'
l3: equ $-m3
newline: db 10
tab : db 9
zero : db '0'
lz: equ $-zero

section .bss
array : resw 200
num : resw 1
n : resw 1
temp : resw 1
count : resw 1
sum : resw 1

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

       
        call read_array

        mov eax, 4
        mov ebx, 1
        mov ecx, m3
        mov edx, l3
        int 80h

        
        call find_sum

        exit:
        mov eax, 1
        mov ebx, 0
        int 80h

find_sum:
    pusha
    mov ebx, array
        mov eax, 0
    mov word[sum], 0
    mov eax, 0
    loop_sum:
        cmp ax, word[n]
        je end_find
        mov cx, word[ebx+2*eax]
        add cx, word[sum]
        mov word[sum], cx
        inc eax
        jmp loop_sum
    end_find:
        mov cx, word[sum]
        mov word[num], cx
        call print_num
        popa
        ret

read_array:
    pusha
     mov ebx, array
        mov eax, 0
    loopa:
        cmp ax, word[n]
        je end_loopa
        call print_msg
        call read_num
        mov cx, word[num]
        mov word[ebx+2*eax], cx
        inc eax
        jmp loopa
    end_loopa:
        popa
        ret

print_msg:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m2
    mov edx, l2
    int 80h
    popa
    ret

print_newline:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    popa
    ret

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

print_num:
    pusha
    mov word[count], 0
    cmp word[num], 0
    jne extracting
    call print_zero

    extracting:
        mov ax, word[num]
        cmp ax, 0
        je printing
        mov bx, 10
        mov dx, 0
        div bx
        push dx
        mov word[num], ax
        inc word[count]
        jmp extracting
    printing:
        cmp word[count], 0
        je end_print
        pop dx
        mov word[temp], dx
        dec word[count]
        add word[temp], 30h

        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h
        jmp printing

    end_print:
        popa
        ret

print_zero:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, zero
    mov edx, lz
    int 80h
    popa
    ret