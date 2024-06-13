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
        mul
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

read_string:
    pusha
    mov ebx, string
    reading:
        push ebx
        mov eax, 3
        mov ebx, 0
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        cmp word[temp], 10
        je end_reads
        inc word[string_len]
        mov ax, word[temp]
        mov word[ebx], ax
        inc ebx
        jmp reading
    end_reads:
        mov word[ebx], 0
        mov ebx, string
        popa
        ret

print_String:
    pusha
    mov ebx, string
    print:
        mov ax, word[ebx]
        mov word[temp], ax
        cmp word[temp], 0
        jne prinstring
        call print_zero

        printstring:
            push ebx
            mov eax, 4
            mov ebx, 1
            mov ecx, temp
            mov edx, 1
            int 80h
            pop ebx
            inc ebx
            jmp print_String

    end_printing:
        popa
        ret

read_matrix:
    pusha
    mov word[i], 0
    mov word[j], 0
    i_loop:
        mov word[j], 0
        j_loop:
            call print_msg
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
    end_readm:
        popa
        ret

print_matrix:
    pusha
    mov word[i], 0
    mov word[j], 0
    i_loopp:
        mov word[j], 0
        j_loopp:
            mov dx, word[ebx+2*eax]
            mov word[num], dx
            call print_num
            call print_tab
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[m]
            jb j_loopp
        call print_newline
        inc word[i]
        mov cx, word[i]
        cmp cx, word[n]
        jb i_loopp

    end_printm:
        popa
        ret
