;6.Write a program to read a string of size n and two numbers n1 and n2 (1<=n1<=n2<=n), compute the substring between the indices n1 and n2 and print the result.

section .data
	sym_cnt: db 0
	string_len: db 0
	cnt: 		db 0
	newline:	db 10
	msg1: db "Enter a string : "
	size1: equ $-msg1
	msg2: db "Enter the starting index n1 : "
	size2: equ $-msg2
	msg3: db  "Enter the starting index n2 : "
	size3: equ $-msg3
	msg4: db  "The required substring is : "
	size4: equ $-msg4
	msg5: db  "Invalid Substring Indices.",10
	size5: equ $-msg5
	zero: db '0'
	zerol: equ $-zero

section .bss
	string: resb 50
	temp: 	resb 1
	sym:	resb 1
	extra:	resb 1
	num: 	resw 1
	n1: 	resw 2
	n2:		resw 2
	count: 	resb 10

section .data
global _start
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, size1
	int 80h
	mov ebx, string
reading:
	push ebx
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h
	pop ebx
	cmp byte[temp], 10
	je end_reading
	inc byte[string_len]
	mov al,byte[temp]
	mov byte[ebx], al
	inc ebx
	jmp reading

end_reading:
	push ebx
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, size2
	int 80h
	call	read_num
	mov		ax,word[num]
	mov		word[n1],0
	mov		word[n1],ax
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, size3
	int 80h
	call	read_num
	mov		ax,word[num]
	mov		word[n2],ax
	
	
	call check
	
	dec		word[n1]
	mov		bx,word[n1]
	sub		word[n2],bx
	;sub		word[n2],2
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg4
	mov edx, size4
	int 80h
	
	call print_array

exit:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h
	
	mov eax, 1
	mov ebx, 0
	int 80h
	
invalid:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg5
	mov edx, size5
	int 80h
	
	mov eax, 1
	mov ebx, 0
	int 80h
	
check:
	pusha
	mov	ax,word[n1]
	cmp	ax,word[n2]
	ja 	invalid	
	
	mov	ax,word[string_len]
	cmp	ax,word[n2]
	jb  invalid
	popa 
	ret

	
print_array:
	pusha
	mov ebx, string
	add	ebx, dword[n1]
	mov	eax,0
	mov	word[cnt],0

printing:
	mov al, byte[ebx]
	mov byte[temp], al
	mov al,byte[cnt]
	cmp al,byte[n2]
	je end_printing
	push ebx
	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h
	pop ebx
	inc ebx
	inc byte[cnt]
	jmp printing
end_printing:
	popa
	ret

read_num:
	pusha
	mov word[num], 0
loop_read:
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h
	cmp byte[temp], 10
	je end_read
	mov ax, word[num]
	mov bx, 10
	mul bx
	mov bl, byte[temp]
	sub bl, 30h
	mov bh, 0
	add ax, bx
	mov word[num], ax
	jmp loop_read
end_read:
	popa
	ret

