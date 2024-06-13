; void insert(int a[], int n) /* function to sort an aay with insertion sort */
; { 
; int i, j, temp; 
; for (i = 1; i < n; i++) { 
; temp = a[i]; 
; j = i - 1; 
; while(j>=0 && temp <= a[j]) /* Move the elements greater than temp to
; one position ahead from their current position*/ 
; { 
; a[j+1] = a[j]; 
; j = j-1; 
; } 
; a[j+1] = temp; 
; } 
;}

section .data
newline : db 10
tab : db 9
m1 : db "Enter no of elements of array: ", 10
l1 : equ $-m1
m2 : db "Enter each element :"
l2 : equ $-m2
m3 : db "Insertion sorted array : "
l3 : equ $-m3
zero : db "0"
lz : equ $-zero

section .bss
num :resw 1
temp :resw 1
n :resw 1
count :resw 1
array :resw 200

section .text
global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, m1
    mov edx, l1
    int 80h
    call read_num
    mov ax, word[num]
    mov word[n], ax

    mov ebx, array 
    mov eax, 0
    call read_array 

    mov esi, array 
    call sort_array

    mov eax, 4
    mov ebx, 1
    mov ecx, m3
    mov edx, l3
    int 80h

    mov ebx, array
    mov eax, 0
    call print_array

    sort_array:
        pusha
        mov ecx, 1 ;starts with i=1
        loop1:
            mov ax, word[esi +2*ecx]  ; temp = a[i]
            mov edx, edx
            dec edx   ; so tht we get j = i-1
            while:
                cmp ax, word[esi +2*edx] ; temp <=a[j]
                ja end_while
                copy:
                    mov bx, word[esi +2*edx]
                    inc edx
                    mov word[esi+2*edx], bx  ; a[j+1] = a[j]
                    dec edx
                    dec edx ; j = i-1
                    cmp edx, 0
                    jae while ; continue while if j >=0
                    end_while:
                        inc edx
                        mov word[esi+2*edx], ax ; a[j+1] = temp
                        inc ecx
                        cmp cx, word[n]
                        jb loop1
            end_loop1:
                popa
                ret


    read_array:
        pusha
        mov eax, 0
        read_loop:
            cmp ax, word[n]
            je end_aread
            call print_m2
            call read_num
            mov cx, word[num]
            mov [ebx+ 2*eax], cx
            inc eax
            jmp read_loop
        end_aread:
        popa
        ret
    
    print_m2:
        pusha
        mov eax, 4
        mov ebx, 1
        mov ecx, m2
        mov edx, l2
        int 80h
        popa
        ret


    print_array:
        pusha
        print_loop:
            cmp ax, word[n]
            je end_aprint
            mov cx, word[ebx+2*eax]
            mov word[num], cx
            call print_num
            call print_tab
            inc eax
            jmp print_loop
        end_aprint:
        popa
        ret

    read_num:
        pusha
        mov word[num], 0
        reading:
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
            sub word[temp], 30h
            mov bx, word[temp]
            add ax, bx
            mov word[num], ax
            jmp reading
        end_read:
            popa 
            ret


    print_num:
        pusha
        mov word[count], 0
        cmp word[num], 0
        call print_zero
        extracting:
            mov ax, word[num]
            cmp eax, 0
            je printing
            mov bx, 10
            mov dx, 0
            div bx
            push dx
            mov word[num], ax
            inc word[count]
            jmp extracting
        printing:
            cmp word[count], 0
            je end_print
            pop dx
            dec word[count]
            mov word[temp], dx
            add word[temp], 30h
            mov eax, 4
            mov ebx, 1
            mov ecx, temp
            mov edx, 1
            int 80h
            jmp printing
        end_print:
            popa 
            ret

    print_tab:
        pusha
        mov eax, 4
        mov ebx, 1
        mov ecx, tab
        mov edx, 1
        int 80h
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