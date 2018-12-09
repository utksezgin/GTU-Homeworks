        ; 8080 assembler code
        .hexfile sum.hex
        .binfile sum.com
        ; try "hex" for downloading in hex format
        .download bin  
        .objcopy gobjcopy
        .postbuild echo "OK!"
        ;.nodump

		; OS call list
PRINT_B		equ 1
PRINT_MEM	equ 2
READ_B		equ 3
READ_MEM	equ 4
PRINT_STR	equ 5
READ_STR	equ 6

	; Position for stack pointer
stack   equ 0F000h

	org 000H
	jmp begin

	; Start of our Operating System
GTU_OS:	PUSH D
	push D
	push H
	push psw
	nop	; This is where we run our OS in C++, see the CPU8080::isSystemCall()
		; function for the detail.
	pop psw
	pop h
	pop d
	pop D
	ret
	; ---------------------------------------------------------------
	; YOU SHOULD NOT CHANGE ANYTHING ABOVE THIS LINE        

	;This program prints even numbers from 0 to 50.


begin:
	LXI SP,stack  ; always initialize the stack pointer
    mvi c, 52	  ; init c with 52
	mvi d, 0 	  ; init d with 0
loop:
	mov b, d      ; Copy content of d to B
	mvi A, PRINT_B; 
	call GTU_OS	  ; SYS_CALL PRINT_B
	inr d         ;++d incrementing the number
	inr d         ;++d twice since we want even numbers
	dcr c		  ; --c
	dcr c         ; --c
	jnz loop	  ; goto loop if c!=0
	;C reached to 52 but won't print 52.
	hlt			  ; Halt the program
