        ; 8080 assembler code
        .hexfile sum2.hex
        .binfile sum2.com
        ; try "hex" for downloading in hex format
        .download bin 
	.download hex
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
GET_RND 	equ 7

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

	;This program adds numbers from 0 to 10. The result is stored at variable
	; sum. The results is also printed on the screen.

sum	ds 2 ; will keep the sum

F1:
    mvi c, 50	  ; init c with 50
	mvi b, 0 	  ; init d with 0
loop1:
	mvi A, PRINT_B; 
	call GTU_OS	  ; SYS_CALL PRINT_B
	inr b         ; ++b
	dcr c		  ; --c
	jnz loop1	  ; goto loop if c!=0
	mvi A, PRINT_B; 
	call GTU_OS	  ; SYS_CALL PRINT_B

	mvi A, TExit  ;
	call GTU_OS