section .data
m1: db 'Enter a sentence: '
l1: equ $-m1
m2: db 'Enter a word to search : '
l2: equ $-m2
m3: db 'The Word is present and the frequency of it is : '
l3 : equ $-m3
m4 : db 'the word is not present in sentence ', 10
l4 : equ $-m4
zero : db '0'
lz : equ $-zerol
newline: db 10
tab : db 9
space : db 32

section .bss

section .text
    global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, m1
    mov edx, l1
    int 80h
    mov ebx, string

    read_string:
        push ebx
        mov eax, 3
        mov ebx, 0
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        cmp word[temp], 10
        je end_readstring
        inc word[string_len]
        mov ax, word[temp]
        mov word[bx], ax
        inc ebx
        jmp read_string
    
    end_readstring:
        mov word[bx], 32
        push ebx

        mov eax, 4
        mov ebx, 1
        mov ecx, m2
        mov edx, l2
        int 80h
        mov ebx, string2

    read_word:
        push ebx
        mov eax, 3
        mov ebx, 0
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        cmp byte[temp], 10
        je end_readword
        inc word[word_len]
        mov ax, word[temp]
        mov word[bx], ax
        inc ebx
        jmp read_word
    end_readword:
        push ebx
        mov 

read_num:
    pusha
    mov word[num], 0
    reading :
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
        add ax, word [temp]
        mov word[num], ax
        jmp reading
    end_read:
        popa
        ret

print_num:
    pusha
    mov word[count], 0
    extracting:
        mov eax, word[num]
        cmp eax, 0
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
        pop edx
        dec word[count]
        mov word[temp], edx
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