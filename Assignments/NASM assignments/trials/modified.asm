section .data
m1: db 'Enter value of row/column of sq matrix: ', 10
l1 : equ $-m1
m2 : db 'Enter value of each element of matrix: '
l2 : equ $-m2
m3: db 'the given matrix is :', 10
l3: equ $-m3
m4: db ' the array formed is :', 10
l4: equ $-m4
m5: db 'sum of elements in array is : '
l5: equ $-m5
newline : db 10
tab : db 9

section .bss
temp : resw 1
count: resw 1
sum: resw 1
num: resw 1
n: resw 1
m: resw 1
i: resw 1
j: resw 1
co: resw 1
coa: resw 1
array : resw 100
matrix : resw 100

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

    mov ebx, matrix
    mov eax, 0
    call read_matrix

    mov eax, 4
    mov ebx, 1
    mov ecx, m3
    mov edx, l3
    int 80h

    mov ebx, matrix
    mov eax, 0
    call print_matrix

    mov esi, matrix
    mov eax, 0
    mov edi, array
    mov edx, 0
    call put_in_array

    mov ebx, array
    mov eax, 0
    call print_m4
    call print_array
    call print_newline
    call find_sum

    exit_final:
        mov eax, 1
        mov ebx, 0
        int 80h


find_sum:
    pusha
    mov ebx, array
    mov eax, 0
    mov word[sum], 0
    loop_sum:
        mov cx, word[ebx+2*eax]
        add cx, word[sum]
        mov word[sum], cx
        inc eax
        cmp ax, word[m]
        jb loop_sum
    end_loop_sum:
        mov cx, word[sum]
        mov word[num], cx
        call print_m5
        call print_num
        call print_newline
        popa
        ret

print_array:
    pusha
    mov word[i], 0
    loop:
        mov cx, word[i]
        cmp cx, word[m]
        ja end_loop
        mov cx, word[ebx+2*eax]
        mov word[num], cx
        call print_num
        call print_tab
        inc word[i]
        jmp loop

    end_loop:
        popa
        ret

put_in_array:
    pusha
    mov word[co], 0   ; counter to check back/fwd movement => co =0 means we are moving to the left (back)
    ; co =1 -> we r moving to right int eh row...fwd movement
    mov word[coa], 0
    ; coa decides whether we hav to take tht element or not... coa= 0 --> we take n put tht element in an array

    mov word[i], 0; i to keep track of no of rows... outer count
    mov word[j], 0 ; j keeps track of innner count
    mov word[m], 0 ; to keep count of no of elements in array

    loop1:
        mov word[j], 0  ;start of new loop set j back to 0
        add ax , word[n]
        cmp word[co], 0
        jne loop_fwd
        jmp loop1
    
        loop_back:
            inc word[co]
            dec eax
            mov cx, word[esi+ 2*eax]
            cmp word[coa], 0
            jne not_add_back
            inc word[coa] ; cuz it didt go to jne
            mov word[edi +2*edx], cx
            inc edx
            inc word[m]
            jmp next_back

            not_add_back:
                dec word[coa]
            next_back:
                inc word[j]
                mov cx, word[j]
                cmp cx, word[n]
                jb loop_back
                jmp outer

        loop_fwd:
            dec word[co]
            mov cx, word[esi +2*eax]
            inc eax
            cmp word[coa], 0
            jne not_add_fwd
            inc word[coa]
            mov word[edi+ 2*edx], cx
            inc edx
            inc word[m]
            jmp next_fwd

            not_add_fwd:
                dec word[coa]

            next_fwd:
                inc word[j] 
                mov cx, word[j]
                cmp cx, word[n]
                jb loop_fwd 
                jmp outer        

        outer:
            inc word[i]
            mov cx, word[i]
            cmp cx, word[n]
            jb loop1
    exit:
        popa
        ret


print_matrix:
    pusha
    mov word[i], 0
    mov word[j], 0
    i_ploop:
        mov word[j], 0
        j_ploop:
            mov dx, word[ebx+ 2*eax]
            mov word[num], dx
            call print_num
            call print_tab
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[n]
            jb j_ploop
        
        inc word[i]
        mov cx, word[i]
        cmp cx, word[n]
        jb i_ploop
    
    end_mprint:
        popa
        ret


read_matrix:
    pusha
    mov word[i], 0
    mov word[j], 0

    i_loop:
        mov word[j], 0
        j_loop:
            call print_m2
            call read_num
            mov dx, word[num]
            mov word[ebx+ 2*eax], dx
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[n]
            jb j_loop

        inc word[i]
        mov cx, word[i]
        cmp cx, word[n]
        jb i_loop

    end_mread:
        popa
        ret

print_tab:
    pusha
    mov eax,4
    mov ebx, 1
    mov ecx, tab
    mov edx, 1
    int 80h
    popa
    ret
print_newline:
    pusha
    mov eax,4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    popa
    ret
print_m5:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m5
    mov edx, l5
    int 80h
    popa
    ret

print_m4:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, m4
    mov edx, l4
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