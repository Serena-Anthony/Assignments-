; find the mode n print the value
section .data
m1 : db 'enter the no of elements: '
l1 : equ $-m1
m2: db 'enter each element: '
l2 : equ $-m2
m3: db 'the req array is : ', 10
l3 : equ $-m3
m4: db 'the array of freq is : ', 10
l4 : equ $-m4
newline: db 10
tab : db 9
zero:db '0'
lz: equ $-zero

section .bss
array: resw 200
array_b: resw 200
num: resw 1
i: resw 1
n: resw 1
max:  resw 1
ele: resw 1
count: resw 1
temp: resw 1
freq: resw 1

section .text
global_start:
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
        
        mov eax, 4
        mov ebx, 1
        mov ecx, m3
        mov edx, l3
        int 80h
        mov ebx, array
        mov eax, 0
        call print_array

        mov ebx, array
        mov eax, 0
        call find_max
        ; print the max after find_max
        mov ecx, 0
        mov cx, word[max]
        mov word[num], cx
        call print_num
        call print_newline
        ; create an array of maxno of elements 
        mov esi, array_b
        mov edx, 0
        call create_freq_array

        mov esi,array_b
        mov edx, 0
        mov ebx, array
        mov eax, 0
        call find_freq

        mov esi, array_b
        mov edx, 0
        mov cx, 0
        mov cx, word[max]
        mov word[n], cx
        call print_newline
        call print_array



find_freq:
    pusha
    mov word[i], 0
    loop_freq:
        mov cx, word[ebx+2*eax]
        mov word[ele], cx
        mov word[freq], 0
        for_iloop:
            mov cx, 0
            mov cx, word[ele]
            cmp cx, word[ebx+2*eax]
            je inc_count
            mov cx, 0
            mov cx, word [i]
            cmp cx, word[n]
            jae end
            inc word[i]
            inc eax

        inc_count:
        inc word[freq]
        mov cx, 0
        mov cx, word[freq]
        mov word[esi+2*eax], cx
        inc word[i]
        inc eax
        jmp loop_freq
       
        end:
            popa
            ret


create_freq_array:
    pusha
    mov word[i], 0
    mov cx, 0
    loop_b:
        mov cx, word[i]
        cmp cx, word[max]
        je end_array2
        mov word[esi+2*edx], 0
        inc edx
        inc word[i]
        jmp loop_b
    end_array2:
        popa
        ret

find_max:
    pusha
    mov eax, 0
    mov cx, word[ebx+ 2*eax]
    mov word[max], cx
    mov word[i], 0
    loop_max:
        mov dx, word[ebx+2*eax]
        mov cx, word[i]
        cmp cx, word[n]
        je end_loop
        cmp word[max], dx
        jb max_replace
        inc word[i]
        inc eax
        jmp loop_max

    max_replace:
        mov dx, 0
        mov dx, word[ebx+ 2*eax]
        mov word[max], dx
        inc eax
        inc word[i]
        jmp loop_max

    end_loop:
        popa
        ret

read_array:
    mov ebx, array
    mov eax, 0
    pusha
    read_loop:  
        cmp ax, word[n]
        je end_reada
        call print_msg
        call read_num
        mov cx, word[num]
        mov word[ebx+2*eax], cx
        inc eax
        jmp read_loop
    end_reada:
        popa
        ret

print_msg :
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m2
    mov edx, l2
    int 80h
    popa
    ret 

print_newline :
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    popa
    ret 

 print_zero :
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, zero
    mov edx, lz
    int 80h
    popa
    ret    

print_array:
    pusha
    print_loop:
        cmp ax, word[n]
        je end_printa
        mov cx, word[ebx+2*eax]
        mov word[num], cx
        call print_num
        call print_space
        inc eax
        jmp print_loop
    end_printa:
        popa
        ret

print_space:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, tab
    mov edx, 1
    int 80h
    popa
    ret 

read_num :
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
        dec word[count]
        mov word[temp], dx
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