section .data
	msg1:db 'Enter number of elements:'
	l1:equ $-msg1
	msg2:db 'Enter each element:'
	l2:equ $-msg2
	msg3: db 'Sorted array',10
	l3: equ $-msg3
	tab:db 9

	
section .bss
num: resw 1
temp: resw 1
count: resw 1
array: resw 100
array1: resw 100
n: resw 1
	
section .text
global _start:
	_start:
	mov eax,4
     	mov ebx,1
	mov ecx,msg1
	mov edx,l1
	int 80h
	call read_num
	mov cx,word[num]
	mov word[n],cx
	
	mov esi,array1
	mov eax,0 
	call read_array
	
	mov esi,array1
	call sort_array
	
	mov eax,4
	mov ebx,1
	mov ecx,msg3
	mov edx,l3
	int 80h
	
	mov ebx,array1
	mov eax,0
	call print_array
end:
mov eax,1
mov ebx,0
int 80h

sort_array:
	pusha
	mov ecx,1
	loop1:
		mov ax,word[esi+2*ecx]
		mov edx,ecx
		dec edx
		while:
			cmp ax,word[esi+2*edx]
			ja end_while
			copy:
				mov bx,word[esi+2*edx]
				inc edx
				mov word[esi+2*edx],bx
				dec edx
				dec edx
				cmp dx,0
				jae while
		end_while:
			inc edx
			mov word[esi+2*edx],ax
			inc ecx
			cmp cx,word[n]
			jb loop1
	
	end_loop1:
		popa
		ret				
	
read_array:
	pusha
	mov eax,0
	read_loop:
		cmp ax,word[n]
		je end_aread
		call print_msg
		call read_num
		mov cx,word[num]
		mov word[esi+2*eax],cx
		inc eax
		jmp read_loop
	end_aread:
		popa
		ret

print_msg:
	pusha
	mov eax,4
	mov ebx,1
	mov ecx,msg2
	mov edx,l2
	int 80h	
	popa
	ret

print_array:
	pusha
	print_loop:
		cmp ax,word[n]
		je end_print1
		mov cx,word[ebx+2*eax]
		mov word[num],cx
		call print_num
		call print_tab
		inc eax
		jmp print_loop
	end_print1:
	popa
	ret	
	
	
print_tab:
	pusha
	mov eax,4
	mov ebx,1
	mov ecx,tab
	mov edx,1
	int 80h
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
