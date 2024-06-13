;;prog to find avg of num in array

section .data
m1 : db 'enter no of elements:'
l1: equ $-m1
m2 : db 'enter each element:'
l2: equ $-m2
m3 : db 'avg of numbers :'
l3 : equ $-m3
tab : db 9
;newline : db 10
zero : db '0'
lz : equ $-zero

section .bss
n : resw 1
num : resw 1
temp: resw 1
array : resw 100
count : resw 1

section .text
global_start:
_start:

mov eax, 4
mov ebx, 1
mov ecx, m1
mov edx, l1
int 80h
call read_num
mov eax, dword[num]
mov dword[n], eax

;; initialisation
mov ebx, array 
mov eax, 0
call read_array

mov ebx, array
mov eax, 0
mov edx, 0

loop1:
mov ecx, dword[ebx+2*eax]
add edx, ecx 
inc eax
cmp eax, dword[n]
jb loop1
mov ax, dx
mov bx, word[n]
mov dx, 0
div bx
mov dword[num], ax

mov eax, 4
mov ebx, 1
mov ecx, m3
mov edx, l3
int 80h
call newline
call print_num

exit:
mov eax, 1
mov ebx, 0
int 80h

print_num:
	pusha
	mov dword[count],0
	
	extracting:
		mov ax,dword[num]
		cmp ax,0
		je printing
		mov bx,10
		mov dx,0
		div bx
		push dx
		mov word[num],ax
		inc dword[count]
		jmp extracting
	printing:
		cmp dword[count],0
		je end_printing
		pop dx
		dec dword[count]
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

read_num:
	pusha
	mov word[num], 0
loop_read:
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
	mov bl, word[temp]
	sub bl, 30h
	mov bh, 0
	add ax, bx
	mov word[num], ax
	jmp loop_read
end_read:
	popa
	ret

newline:
pusha
mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, 1
int 80h
popa ret

print_array:
pusha
print_loop:
    cmp ax, word[n]
    je end_print
    mov cx, word[ebx+ 2*eax]
    mov word[num], cx
    call print_num
    call print_tab
    inc eax
    jmp print_loop
end_print
popa
ret

read_array:
pusha
read_loop:
    cmp eax, word[n]
    je end_aread
    call read_num
    mov cx, word[num]
    mov word[ebx+ 2*eax], cx
    inc eax

end_aread:
popa 
ret

