section .data
m1: db 'enter no of digits to be averaged : '
l1 : equ $-m1
m2: db 'enter each digit : '
l2: equ $-m2
m3 : db 'average of given numbers is : '
l3: equ $-m3
newline: db 10
tab : db 9
space : db 32

section .bss
num : resw 1
n: resw 1
i: resw 1
temp: resw 1
count: resw 1
sum: resw 1
array : resw 100

section .data
    global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, m1
    mov edx, l1
    int 80h
    call read_num
    mov ax, word[num]
    mov word[n], ax

    call read_array
    call find_avg

    exit:
    mov eax, 1
    mov ebx, 0
    int 80h

find_avg:
    mov ebx , array
    mov ecx , 0
    
    mov word[i], 0
    mov word[sum], 0
    loop_avg:
        mov ax,word[i]
        cmp ax, word[n]
        jae end_loop_avg
        mov dx, word[ebx+2*ecx]
       ; mov word[sum], dx
        add word[sum], dx
        inc ecx
        inc word[i]
        jmp loop_avg
    end_loop_avg:
        mov ax, word[sum]
        mov bx, word[n]
        div bx
        mov word[num], ax
        call print_num
        call print_newline
        popa
        ret


read_array:
    mov ebx, array
    mov ecx, 0
    mov word[i], 0
    looping:
        mov ax,word[i]
        cmp ax, word[n]
        jae end_reada
        call print_m2
        call read_num
        ;call print_newline
        mov dx, word[num]
        mov word[ebx+ 2*ecx], dx
        inc ecx
        inc word[i]
        jmp looping
    end_reada:
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

print_m2:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m2
    mov edx, l2
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
        je end_readnum
        mov ax, word[num]
        mov bx, 10
        mul bx
        sub word[temp], 30h
        add ax, word[temp]
        mov word[num], ax
        jmp reading

    end_readnum:
        popa 
        ret

print_num:
    pusha
    mov word[count], 0
    extracting:
        mov ax, word[num]
        cmp ax, 0
        je printing
        mov bx, 10
        mov dx, 0
        div bx
        push dx
        mov word[num], ax
       ; add word[temp], 30h
        inc word[count]
        jmp extracting
    
    printing:
        cmp word[count],0
        je end_printnum
        pop dx
        dec word[count]
        mov word[temp], dx
        add word[temp], 30h
        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h
        jmp printing

    end_printnum:
        popa
        ret
        