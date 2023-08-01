; Accept three 2-digit numbers and find the greatest among them.

section .data
	zero: db '0'
	l1: equ $-zero
	space: db ' '
	l2: equ $-space
	m1: db 'Enter number1: '
	l3: equ $-m1
	m2: db 'Enter number2: '
	l4: equ $-m2
	m3: db 'Enter number3: '
	l5: equ $-m3
	m4: db 'The greatest of three numbers is: '
	l6: equ $-m4

section .bss
	read: resd 1
	print: resd 1
	temp: resd 1
	counter: resd 1
	num1: resw 1
	num2: resw 1
	num3: resw 1
	max: resw 1
	
section .data
global _start:
_start:

mov eax,4
mov ebx,1
mov ecx,m1
mov edx,l3
int 80h

call read_num
mov ax,word[read]
mov word[num1],ax

mov eax,4
mov ebx,1
mov ecx,m2
mov edx,l4
int 80h

call read_num
mov ax,word[read]
mov word[num2],ax

mov eax,4
mov ebx,1
mov ecx,m3
mov edx,l5
int 80h

call read_num
mov ax,word[read]
mov word[num3],ax

mov ax,word[num1]
cmp ax,word[num2]
ja copy_num1
mov ax,word[num2]

;WILL JUMP TO COPY NUM1 IF NUM1 > NUM2
copy_num1:
mov word[max],ax

mov ax,word[num3]
cmp word[max],ax
jb copy_num3
jmp exit

copy_num3:
mov ax,word[num3]
mov word[max],ax

exit:

mov ax,word[max]
mov word[print],ax
mov eax,4
mov ebx,1
mov ecx,m4
mov edx, l6
int 80h

call print_num

mov eax,1
mov ebx,0
int 80h

read_num:
	pusha
	mov dword[read],0
	
	reading:
		mov eax,3
		mov ebx,0
		mov ecx,temp
		mov edx,1
		int 80h

		cmp dword[temp],10
		je end_read

		sub dword[temp],30h
		mov eax,dword[read]
		mov edx,0
		mov ebx,10
		mul ebx

		add eax,dword[temp]
		mov dword[read],eax
		jmp reading

	end_read:
		popa
		ret

print_num:
	pusha
	mov dword[counter],0
	cmp dword[print],0

	jne extracting

	mov eax,4
	mov ebx,1
	mov ecx,zero
	mov edx,l1
	int 80h

	jmp end_print

	extracting:
		cmp dword[print],0
		je printing
		mov eax,dword[print]
		mov edx,0
		mov ebx,10
		div ebx
		push edx
		mov dword[print],eax
		inc dword[counter]
		jmp extracting

	printing:
		cmp dword[counter],0
		je end_print

		pop edx
		mov dword[temp],edx
		add dword[temp],30h
		mov eax,4
		mov ebx,1
		mov ecx,temp
		mov edx,1
		int 80h
		dec dword[counter]
		jmp printing
        
end_print:
	popa
	ret
	
	
	
	
	
	
