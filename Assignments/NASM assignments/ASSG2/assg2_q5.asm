;  Read n numbers and find the mean of them.

section .data
	zero: db '0'
	l1: equ $-zero
	space: db ' '
	l2: equ $-space
	m: db 'Enter n: '
	l: equ $-m
	m1: db 'Enter a number: '
	l3: equ $-m1
	m2: db 'Mean of entered numbers: '
	l4: equ $-m2

section .bss
	read: resd 1
	print: resd 1
	temp: resd 1
	counter: resd 1
	i: resd 1
	n: resd 1
	sum: resd 1
	
section .data
global _start:
_start:
mov eax,4
mov ebx,1
mov ecx,m
mov edx,l
int 80h

call read_num
mov eax,dword[read]
mov dword[n],eax

mov dword[i],0
mov dword[sum],0

for:
    mov eax,4
    mov ebx,1
    mov ecx,m1
    mov edx,l3
    int 80h
    
    call read_num
    mov eax,dword[read]
    add eax,dword[sum]
    mov dword[sum],eax
    inc dword[i]
    mov eax,dword[n]
    cmp eax,dword[i]
    ja for
    jmp exit


exit:

mov eax,dword[sum]
mov edx,0
div dword[n]
mov dword[print],eax

mov eax,4
mov ebx,1
mov ecx,m2
mov edx,l4
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
	
	
	
	
	
	
