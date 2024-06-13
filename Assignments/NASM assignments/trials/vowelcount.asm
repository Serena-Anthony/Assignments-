section .data
m1: db "Enter a string:"
l1: equ $-m1
m2: db "No. of A :"
l2: equ $-m2
m3: db "No. of E :"
l3: equ $-m2
m4: db "No. of I :"
l4: equ $-m2
m5: db "No. of O :"
l5: equ $-m2
m6: db "No. of U :"
l6: equ $-m2
acount : db 0
ecount : db 0
icount : db 0
ocount : db 0
ucount : db 0
string_len : db 0

section .bss
string :resw 200
temp : resw 1

section .text
global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, m1
    mov edx, l1
    int 80h
    mov ebx, string
    mov eax, 0
    call read_string

    count:
            mov eax, ebx
            cmp eax, 0
            je end_counting
            cmp eax, 'a'
            je inc_a
            cmp eax, 'e'
            je inc_e
            cmp eax, 'i'
            je inc_i
            cmp eax, 'o'
            je inc_o
            cmp eax, 'u'
            je inc_u
            cmp eax, 'A'
            je inc_a
            cmp eax, 'E'
            je inc_e
            cmp eax, 'I'
            je inc_i
            cmp eax, 'O'
            je inc_o
            cmp eax, 'U'
            je inc_u
            next:
                inc ebx
                jmp count
                call end_counting 

            end_counting:
                ; print no of a
                mov eax, 4
                mov ebx, 1
                mov ecx, m2
                mov edx, l2
                int 80h
                add word[acount], 30h
                mov eax, 4
                mov ebx, 1
                mov ecx, acount
                mov edx, 1
                int 80h

                ;print no of e
                mov eax, 4
                mov ebx, 1
                mov ecx, m3
                mov edx, l3
                int 80h
                add word[ecount], 30h
                mov eax, 4
                mov ebx, 1
                mov ecx, ecount
                mov edx, 1
                int 80h

                ;print no of i
                mov eax, 4
                mov ebx, 1
                mov ecx, m4
                mov edx, l4
                int 80h
                add word[icount], 30h
                mov eax, 4
                mov ebx, 1
                mov ecx, icount
                mov edx, 1
                int 80h

                ;print no of o
                mov eax, 4
                mov ebx, 1
                mov ecx, m5
                mov edx, l5
                int 80h
                add word[ocount], 30h
                mov eax, 4
                mov ebx, 1
                mov ecx, ocount
                mov edx, 1
                int 80h

                ;print no of u
                mov eax, 4
                mov ebx, 1
                mov ecx, m6
                mov edx, l6
                int 80h
                add word[ucount], 30h
                mov eax, 4
                mov ebx, 1
                mov ecx, ucount
                mov edx, 1
                int 80h

        exit:
            mov eax, 1
            mov ebx, 0
            int 80h

    inc_a:
        inc word[acount]
        jmp next

    inc_e:
        inc word[ecount]
        jmp next

    inc_i:
        inc word[icount]
        jmp next

    inc_o:
        inc word[ocount]
        jmp next

    inc_u:
        inc word[ucount]
        jmp next
        
    print_string:
        pusha
        mov ebx, string

    printing:
        mov eax, ebx
        mov word[temp], ax
        cmp word[temp], 10
        je end_prints

        push ebx
        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        inc ebx
        jmp printing

    end_prints:
        popa 
        ret

    read_string:
        pusha
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
        mov ebx, eax
        inc ebx
        jmp read_string

        end_reads:
            mov ebx, 0
            mov ebx, string
            popa
            ret
