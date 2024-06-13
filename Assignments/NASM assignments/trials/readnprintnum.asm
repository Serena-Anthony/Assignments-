section .data
m1 : db 'Enter no of integers :'
l1 : equ $-m1
m2 : db 'enter value of each int :'
l2 : equ $-m2
m3 : db 'product is :'
l3: equ $-m3
newline : db 10
tab : db 9

;size of ax = 16
; 1 byte = 8 bit
; 1 word = 2 byte = 16 bits


section .bss
i : resd 1
n : resd 1
prod : resd 1
num : resd 1
temp : resd 1
count : resd 1
read : resd 10
print : resd 10

section .text
global_start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, m1
mov edx, l1
int 80h

call read_num
mov eax, dword[read]
mov dword[n], eax

mov dword[i], 0
mov dword[prod], 1

loop1:
    call print_newline
    mov eax, 4
    mov ebx, 1
    mov ecx, m2
    mov edx, l2
    int 80h

    call read_num 
    mov eax, dword[read]
    mov ebx, dword[prod]
    mul ebx
    mov dword[prod], eax
    inc dword[i]
    mov eax, dword[n]
    cmp eax, dword[i]
    ja loop1
    jmp exit1

exit1:
call print_newline
mov eax, 4
mov ebx, 1
mov ecx, m3
mov edx, l3
int 80h
call print_newline
mov eax, dword[prod]
mov dword[temp], eax
call print_num


read_num:
pusha
mov dword[num], 0
loop_read:
    mov eax, 3
    mov ebx, 0
    mov ecx, temp
    mov edx, 1

    cmp dword[temp], 10
    je end_loop

    mov eax, dword[num]
    mov ebx, 10
    mul ebx

    sub dword[temp],30h
    add eax, dword[temp]
    mov dword[num], eax
    jmp loop_read

end_loop:
popa
ret

print_num:
mov dword[count], 0
pusha
    extract_num:
    cmp dword[num], 0
    je print_num

    inc dword[count]
    mov edx, 0
    mov eax, dword[num]
    mov ebx, 10
    div ebx

    push edx
    mov dword[num], eax
    jmp extract_num

    print_no:
    cmp dword[count], 0
    je end_print

    dec dword[count]
    pop edx
    mov dword[temp], edx
    add dword[temp], 30h

    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 1
    int 80h
    jmp print_no
    
    end_print:
    popa
    ret

print_newline:
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    popa
    ret