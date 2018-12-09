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


	
	;READ_B call. Gets an integer from user into B register.
	mvi A, READ_B; 
	call GTU_OS	  ; SYS_CALL READ_B
	mvi A, PRINT_B; Prints input.
	call GTU_OS	  ; 

	;READ_MEM call. Gets an integer from user into BC address
	mvi A, READ_MEM; 
	call GTU_OS	  ; SYS_CALL READ_MEM
	;PRINT_MEM call. Prints the input.
	mvi A, PRINT_MEM; 
	call GTU_OS	  ; SYS_CALL PRINT_MEM

	;READ_STR call. Gets an string from user into BC Address.
	mvi A, READ_STR; 
	call GTU_OS	  ; SYS_CALL READ_STR
	;PRINT_STR call. Prints the input.
	mvi A, PRINT_STR; 
	call GTU_OS	  ; SYS_CALL PRINT_STR

	;GET_RND CALL
	mvi A, GET_RND; Gets an random integer from OS.
	call GTU_OS	  ; SYS_CALL GET_RND
	mvi A, PRINT_B; Prints the input.
	call GTU_OS	  

	; End of program.
	hlt			  ; Halt the program
	