section .data
tab: db 9
newline: db 10
msg1: db 'Enter number of elements:'
l1: equ $-msg1
msg2: db 'Enter each element of array:'
l2: equ $-msg2
msg3: db 'inputed array is : ',10
l3: equ $-msg3
zero : db "0"
lz : equ $-zero

section .bss

section .text
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, l1
    int 80h
    call read_num
    mov cx, word[num]
    mov word[n], cx

    mov ebx, array
    mov eax, 0
    call read_array


print_msg:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    popa
    ret

read_array:
    pusha
    read_loop:
        cmp ax, word[n]
        je end_read
        call print_msg
        call read_num
        mov cx, word[num]
        mov word[ebx+2*eax], cx
        inc eax
        jmp read_loop
    end_read:
        popa
        ret

print_array:
    pusha
    printloop:
        cmp ax, word[n]
        je endprinta
        mov cx, word[ebx+2*eax]
        mov word[num], cx
        call print_num
        call print_tab
        inc eax
        jmp printloop
    endprinta:
        popa
        ret
