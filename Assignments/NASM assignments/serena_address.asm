  global    _start:

          section   .text
_start:   mov       rax, 1                  ; system call for write
          mov       rdi, 1                  ; file handle 1 is stdout
          mov       rsi, message            ; address of string to output
          mov       rdx, 80                 ; number of bytes
          syscall                           ; invoke operating system to do the write
          mov       rax, 60                 ; system call for exit
          xor       rdi, rdi                ; exit code 0
          syscall                           ; invoke operating system to exit

          section   .data
message:  db        "Serena Anthony", 10, "Room 734, MLH", 10, "NIT Calicut", 10, "Kozhikode", 10, "P.O: 673674",10   ; note the newline at the , 10 is ascii for new line or 0ah is hexadecimal for it 
