section .data
array1 : dw 12,67,34,5,30,45,22
length : dd 7
space : db " "

section .bss
num :resw 1
temp:resb 1
nod :resw 1
key:resw 2
i: resw 1
j: resw 1

section .text
global _start
_start:
    mov ebx,array1
    mov word[i],0

    i_loop:
        inc word[i]
        mov ebx,array1
        mov cx,word[length]
        cmp cx,word[i]
        je endloop
        mov ecx,0
        mov cx,word[i]
        mov eax,0
        add ax,cx
        mov cx,word[ebx+2*eax]
        mov word[key],cx
        mov cx,word[i]
        mov word[j],cx;
        dec word[j]
        movzx eax,word[j]
    j_loop:
        mov cx,word[key]
        cmp word[ebx+2*eax],cx
        jl new
        mov cx,word[ebx+2*eax]
        mov word[ebx+2*eax+2],cx
        dec eax
        dec word[j]
        cmp word[j],0xff
        jne j_loop
        cmp word[j],0
        jge j_loop
    
    new:
        mov cx,word[key]
        mov [ebx+2*eax+2],cx
        jmp i_loop
    endloop:
        call print_array
        mov eax,1
        mov ebx,1
        int 0x80

print_array:
    pusha
    mov ebx,array1
    mov eax,0
    printloop:
        cmp ax,word[length]
        je end_print1
        mov cx,word[ebx+2*eax]
        mov word[num],cx
        ;;The number to be printed is copied to ’num’
        ;;before calling print num function
        call print_num
        pusha
        mov eax,4
        mov ebx,1
        mov ecx,space
        mov edx,1
        int 0x80
        popa
        inc eax
        jmp printloop
    end_print1:
        popa
        ret

print_num:
    pusha
    mov word[nod],0
    cmp word[num],0
    je print_zero
extract_num:
    cmp word[num],0
    je print_loop
    mov bx,10
    mov ax,word[num]
    mov dx,0
    div bx
    push dx
    mov word[num],ax
    inc word[nod]
    jmp extract_num
print_loop:
    pop dx
    mov byte[temp],dl
    add byte[temp],30h
    mov eax,4
    mov ebx,1
    mov ecx,temp
    mov edx,1
    int 0x80
    dec word[nod]
    mov cx,word[nod]
    cmp cx,0
    je exit_print
    jmp print_loop
exit_print:
    popa
    ret

print_zero:
    mov eax,4
    mov ebx,1
    mov ecx,'0'
    mov edx,1
    int 0x80
    jmp exit_print