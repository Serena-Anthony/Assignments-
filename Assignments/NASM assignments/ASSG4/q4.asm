;;QUESTION 4
section .data
	string_len: dw 0
	lost_len:   dw 0
	cnt: 		db 0
	newline:	db 10
	msg1: db "Enter the sentence : "
	size1: equ $-msg1	
	msg2: db "Enter the word to search: "
	size2: equ $-msg2
	msg3: db "The Word is present and the frequency of it is : "
	size3: equ $-msg3
	msg4: db "The Word is not present in the sentence.",10
	size4: equ $-msg4
	zero: db '0'
	zerol: equ $-zero
	wordcounter:	dw 0
	
section .bss
	string: resb 200
	lost: 	resb 50
	temp: 	resb 1
	sym:	resb 1
	extra:	resb 1
	num: 	resw 1
	count: 		 resb 10
	i:		resw 1
	j:		resw 1
	
	
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
	mov byte[ebx], 32
	push ebx
	
	
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, size2
	int 80h
	
	mov ebx, lost
readingL:
	push ebx
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h
	pop ebx
	cmp byte[temp], 10
	je end_readingL
	inc byte[lost_len]
	mov al,byte[temp]
	mov byte[ebx], al
	inc ebx
	jmp readingL

end_readingL:
	push ebx
	mov 	word[i],0
	mov 	word[j],0
	mov		ebx,string
	
outer_loop:
	mov		ax,word[string_len]
	cmp		ax,word[i]
	je		end_outer
	
	mov 	word[j],0
inner_loop:
	mov		ax,word[lost_len]
	cmp		ax,word[j]
	je 		found
		
okcontinuing:
	mov		ebx,string
	add		bx,word[i]
	add		bx,word[j]
	mov		ecx,lost
	add		cx,word[j]
	
	inc		word[j]
	
	mov		al,byte[ebx]
	cmp		byte[ecx],al
	

	
	je		inner_loop
	jne 	end_inner

end_inner:
	inc		word[i]
	jmp		outer_loop
	
	
end_outer:
	jmp done
	
found:
	
	mov		ebx,string
	add		bx,word[i]
	add		bx,word[j]

	cmp		byte[ebx],32
	je 		foundfinally
	
	jmp		okcontinuing
	
foundfinally:
	inc	word[wordcounter]
	jmp	okcontinuing

	
	
done:
	cmp	word[wordcounter],0
	je	notfoundprint
	
	
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h
	
foundprint:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, size3
	int 80h
	
	mov	ax,word[wordcounter]
	mov	word[num],ax
	call print_num
	
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h
	
	jmp exit
	
notfoundprint:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg4
	mov edx, size4
	int 80h
	jmp exit
	
exit:
	mov eax, 1
	mov ebx, 0
	int 80h
	
	
	
	
	
print_num:						;;Function to print number
	
	mov byte[count],0
	pusha
	;cmp word[num],0
	;je print_zero_or_not
extract_no:
	cmp word[num], 0
	je print_no
	inc byte[count]
	mov dx, 0
	mov ax, word[num]
	mov bx, 10
	div bx
	push dx
	mov word[num], ax
	jmp extract_no
print_no:
	cmp byte[count], 0
	je end_print
	dec byte[count]
	pop dx
	mov byte[temp], dl
	add byte[temp], 30h
	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h
	jmp print_no
end_print:
	popa
	ret
