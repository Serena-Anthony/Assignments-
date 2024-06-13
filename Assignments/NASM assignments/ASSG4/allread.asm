read_matrix:
    mov ebx, matrix
    mov eax, 0
    pusha
    mov word[i], 0
    mov word[j], 0
    i_loop:
        mov word[j], 0
        j_loop:
            call read_num
            mov cx, word[num]
            mov word[ebx+2*eax], cx
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[m]
            jb j_loop
        inc word[i]
        mov dx, word[i]
        cmp dx, word[n]
        jb i_loop
    endmatrix:
        popa
        ret

print_matrix:
    mov ebx, matrix
    mov eax, 0
    pusha
    mov word[i], 0
    mov word[j], 0
    i_looppm:
        mov word[j], 0
        j_looppm:
            mov dx, word[ebx+2*eax]
            mov word[num], dx
            call print_num
            call print_tab
            inc eax
            inc word[j]
            mov cx, word[j]
            cmp cx, word[m]
            jb j_looppm
        call print_newline
        inc word[i]
        mov dx, word[i]
        cmp dx, word[n]
        jb i_looppm
    endprintmatrix:
        popa
        ret

read_string:
    pusha
    mov ebx, string
    reading:
        push ebx
        mov eax, 3
        mov ebx ,0
        mov ecx, temp
        mov edx, 1
        int 80h
        pop ebx
        cmp word[temp], 10
        je endreadstring
        inc word[string_len]
        mov ax, word[temp]
        mov word[ebx], ax
        inc ebx
        inc ebx
        jmp reading
    endreadstring:
        mov word[ebx],0
        popa
        ret

print_string:
    pusha
    mov ebx, string
    printing:
        mov ax, word[ebx]
        mov word[temp], ax
        cmp word[temp], 0  ;check if null char
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


read_array:
    mov ebx, array
    mov eax, 0
    pusha
    loopa: 
        cmp ax, word[n]
        je endloopa
        call print_msg
        call read_num
        mov cx, word[num]
        mov word[ebx+2*eax], cx
        inc eax
        jmp loopa
    endloopa:
        popa
        ret

print_array:
    pusha
    printloop:
        cmp ac, word[n]
        je endprintloop
        mov cx, word[ebx+2*eax]
        mov word[num], cx
        call print_num
        inc eax
        jmp printloop
    endprintloop:
        popa
        ret

read_num:
	pusha 
	mov word[num],0
	reading:
		mov eax,3
		mov ebx,0
		mov ecx,temp
		mov edx,1
		int 80h
		cmp word[temp],10
		je end_read
		mov ax,word[num]
		mov bx,10
		mul bx
		mov bx,word[temp]
		sub bx,30h
		add ax,bx
		mov word[num],ax
		jmp reading
	end_read:
		popa
		ret

print_num:
	pusha
	mov word[count],0
	cmp word[num], 0
	jne extracting
	call print_zero

	extracting:
		mov ax,word[num]
		cmp ax,0
		je printing
		mov bx,10
		mov dx,0
		div bx
		push dx
		mov word[num],ax
		inc word[count]
		jmp extracting
	printing:
		cmp word[count],0
		je end_printing
		pop dx
		dec word[count]
		mov word[temp],dx
		add word[temp],30h
		mov eax,4
		mov ebx,1
		mov ecx,temp
		mov edx,1
		int 80h
		jmp printing
	end_printing:
		popa
		ret
