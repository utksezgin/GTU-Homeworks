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
GET_RND		equ 7
TExit		equ 8
TJoin		equ 9
TYield		equ 10
TCreate		equ 11


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

	;This program tests all the system calls in our simulated OS.
	



begin:
	LXI SP,stack  ; always initialize the stack pointer

	mvi A, TCreate	;
	lxi B, F1		;
	call GTU_OS		;
	mvi A, TJoin	;
	call GTU_OS		;
	mvi A, TCreate	;
	lxi B, F2		;
	call GTU_OS		;
	mvi A, TJoin	;
	call GTU_OS		;


	; End of program.
	hlt			  ; Halt the program
	

F3:
    mvi b, 51	  ; init b with 51
	mvi c, 50	  ; init c with 50
loop3:
	mvi A, PRINT_B; 
	call GTU_OS	  ; SYS_CALL PRINT_B
	inr b         ; ++b
	dcr c 		  ; --c
	jnz loop3	  ; goto loop if c!=0
	mvi A, PRINT_B; 
	call GTU_OS	  ; SYS_CALL PRINT_B

	mvi A, TExit  ;
	call GTU_OS