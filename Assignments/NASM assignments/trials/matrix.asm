section .data
m1: db 'enter no of rows (n) :'
l1: equ $-m1
m2: db 'enter no of columns (m):'
l2: equ $-m2
m3: db 'enter each element:'
l3: equ $-m3
m5: db 'given matrix is :'
l5: equ $-m5
m4: db 'transpose of given matrix is :', 10
l4: equ $-m4
zero : db '0'
lz : equ $-zero
tab : db 9
newline: db 10

section .bss
matrix : resw 100
matrixT : resw 100
num: resw 1
n: resw 1
m: resw 1
i: resw 1
j: resw 1
temp : resw 1
count : resw 1

section .text
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

    mov eax, 4
    mov ebx, 1
    mov ecx, m2
    mov edx, l2
    int 80h
    mov ax, word[num]
    mov word[m], ax

    call read_matrix

    mov eax,4
    mov ebx,1
    mov ecx, m5
    mov edx, l5
    int 80h

    call print_matrix

    mov esi, matrix
    mov edi, matrixT
    mov ecx, 0
    mov edx, 0
    call transpose
    call print_msg4

    mov ax, word[n]
    mov bx, word[m]
    mov word[m], ax
    mov word[n], bx
    ; exchange m & n for transpose

    mov ebx, matrixT
    mov eax, 0
    call print_matrix

end_t:
    mov eax, 1
    mov ebx, 0
    int 80h

transpose:
    pusha
    mov word[i], 0
    mov word[j], 0
    ;change array elements positions
    ; eg : 123456 as 135246
    
    loop1:
        mov word[j], 0
        loop2:
            mov ax, word[esi + 2*ecx]
            mov word[edi +2*edx], ax
            inc word[j]
            inc edx ; to go to next empty slot
            add cx, word[m] ; mov fwd by "column" no of steps
            mov ax, word[j]
            cmp ax, word[n]
            jb loop2
    
        inc word[i]
        inc esi
        inc esi
        ; this inc esi amt by 1 word so ht we cn go to first element of next row
        ; eg the next row beginning is "2" 
        mov ax, word[i]
        cmp ax, word[m]
        jb loop1

    end_loop1:
    popa
    ret

print_msg4:
    pusha
    mov eax,4
    mov ebx, 1
    mov ecx, m4
    mov edx, l4
    int 80h
    popa
    ret

read_matrix:
    pusha
    mov ebx, matrix
    mov eax, 0
    mov word[i], 0
    mov word[j], 0

    i_loop:
        mov word[j], 0
        j_loop:
            call print_m3
            call read_num

            mov dx, word[num]
            mov word[ebx+2*eax], dx
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[m]
            jb j_loop

        inc word[i]
        mov cx, word[i]
        cmp cx, word[n]
        jb i_loop

    end_mread:
    popa
    ret

print_m3:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m3
    mov edx, l3
    popa
    ret

print_matrix:
    pusha
    mov ebx, matrix
    mov eax, 0
    mov word[i], 0
    mov word[j], 0

    i_forloop:
        mov word[j], 0
        j_forloop:
            mov dx, word[ebx+2*eax]
            mov word[num], dx
            call print_num
            call print_tab
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[m]
            jb j_forloop

        call print_newline
        inc word[i]
        mov cx, word[i]
        cmp cx, word[n]
        jb i_forloop

    end_mprint:
    popa
    ret

print_tab:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, tab
    mov edx, 1
    int 80h
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
        je end_readnum

        mov ax, word[num]
        mov ebx, 10
        mul ebx
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
    cmp word[num], 0
    jne extracting
    call print_zero

    extracting:
        cmp word[num], 0
        je printing
        mov ax, word[num]
        mov ebx, 10
        div ebx
        push edx
        mov word[num], ax
        inc word[count]
        jmp extracting

    printing:
        cmp word[count], 0
        je end_printing

        pop edx
        dec word[count]
        mov word[temp], dx
        add word[temp], 30h

        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h
        jmp printing

    end_printing:
    popa
    ret
