section .data
    string_len: db 0
	;cnt: 		db 0
	newline:	db 10
	msg1: db "Enter a string : "
	size1: equ $-msg1
   ; msg2: db "Enter the starting index n1 : "
	;size2: equ $-msg2
	;msg3: db  "Enter the starting index n2 : "
	;size3: equ $-msg3
	msg4: db  "The required substring is : "
	size4: equ $-msg4
	;msg5: db  "Invalid Substring Indices.",10
	;size5: equ $-msg5
	;zero: db '0'
	;zerol: equ $-zero

section .bss
    string: resw 50
	temp: 	resw 1
    ;string_len: 	resw 1

section .text
    global _start:
    _start:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg1
        mov edx, size1
        int 80h
        mov ebx, string
        call read_string

        mov eax, 4
        mov ebx, 1
        mov ecx, msg4
        mov edx, size4
        int 80h

        call print_newline
        mov ebx, string
        call print_string
        call print_newline

        exit:
        mov eax, 1
        mov ebx, 0
        int 80h

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
        cmp word[temp], 10 ;null char
        je endreadstring
        inc word[string_len]
        mov ax, word[temp]
        mov word[ebx], ax
        inc ebx
        inc ebx
        jmp reading
    endreadstring:
        mov word[ebx], 0
        ;lmov ebx, string
        popa
        ret

print_newline:
	pusha	
	mov eax,4
	mov ebx,1
	mov ecx,newline
	mov edx,1
	int 80h
	popa
	ret

print_string:
    pusha
    mov ebx, string
    printing:
        mov ax, word[ebx]
        mov word[temp], ax
        cmp word[temp], 0
        je endprintstring
        push ebx
        mov eax, 4
        mov ebx, 1
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        inc ebx
        inc ebx
        jmp printing
    endprintstring:
        popa
        ret
