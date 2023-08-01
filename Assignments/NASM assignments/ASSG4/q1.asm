section .data
	msg1:db 'Enter number of elements in array:'
	l1:equ $-msg1
	msg2:db 'Enter each element of array:'
	l2:equ $-msg2
	msg3: db 'Sum of entered array elements:'
	l3: equ $-msg3
	tab:db 9
	zero : db "0"
	lz : equ $-zero
	
section .bss
num: resw 1
temp: resw 1
count: resw 1
index1: resw 1
index2: resw 1
array: resw 100
array1: resw 100
array2: resw 100
n: resw 1
m: resw 1
sum: resw 1
	
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
	mov word[m],cx
	
	mov esi,array1
	mov eax,0 
	call read_array
	
	mov eax,4
    mov ebx,1
	mov ecx,msg1
	mov edx,l1
	int 80h
	call read_num
	mov cx,word[num]
	
	mov word[n],cx
	mov esi,array2
	mov eax,0
	call read_array
	
	mov eax,0
	mov ecx,0
	mov ebx,array
	mov esi,array1
	mov edi,array2
	mov edx,0
	call merge_arrays
	mov ax,word[m]
	add ax,word[n]
	mov word[n],ax
	mov ebx,array
	mov eax,0
	call print_array
	
	end: 	
	mov eax,1
	mov ebx,0
	int 80h

;array: ebx,eax
;array1: esi,ecx,length m
;array2: edi,edx,length n
merge_arrays:
	pusha
	mov word[index1],0
	mov word[index2],0
	looping:
		mov cx,word[index2]
		mov ax,word[esi+2*ecx] ;array1 element
		cmp ax,word[edi+2*edx]
		jb array1_add

		array2_add:
			mov cx,word[edi+2*edx] ;array2 element
			inc edx
			mov ax,word[index1]
			mov word[ebx+2*eax],cx
			inc word[index1]
			jmp next
		array1_add:
			mov cx,ax
			mov ax,word[index1]
			mov word[ebx+2*eax],cx
			inc word[index1]
			inc word[index2]
		next:
			cmp dx,word[n]
			je end_array2
			mov cx,word[index2]
			cmp cx,word[m]
			jb looping
	end_array1:
		mov ax,word[index1]
		mov cx,word[edi+2*edx]
		mov word[ebx+2*eax],cx
		inc word[index1]
		inc edx
		cmp dx,word[n]
		je end_looping
		jmp end_array1
	end_array2:
		mov ax,word[index1]
		mov cx,word[index2]
		mov dx,word[esi+2*ecx]
		mov word[ebx+2*eax],dx
		inc word[index1]
		inc word[index2]
		mov cx,word[index2]
		cmp cx,word[m]
		jb end_array2
	end_looping:
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

 print_zero:
        pusha
        mov eax, 4
        mov ebx, 1
        mov ecx, zero
        mov edx, lz
        int 80h
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
