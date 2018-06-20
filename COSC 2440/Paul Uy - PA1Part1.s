;	Name: Paul Uy
;	PA1 Part 1
;	I set the counter for the loop in R0, the value to store in R1, and the address to store the value in in R2.
; 	Then the process is looped until the counter is equal or greater than 100. This is the assembly language version of
;
;	int a[100];
;	for (i = 0; i<100;i++)	{
;	a[i] = 100 - i;
;	}

	TTL	PA1Part1
	; Inserts title at the start of each page
	AREA	RESET, DATA, READONLY
	; AREA directive instructs assembler to assemble a new code or data section
	; RESET is name of this section
	; DATA tells assembler that this section contains data
	; READONLY ensures no write overs when saving things in the program
	EXPORT __Vectors	
	; EXPORT directive declares a symbol that can used by the linker to resolve symbol
	; references in separate object and library files
	
__Vectors	DCD	0x20002000		; Stack point value when stack is empty, starting point
				DCD	Reset_Handler	; Reset Vector
	
	AREA	MYCODE, CODE, READONLY
	; MYCODE is name of this section
	; CODE tells the assembler that this section contains machine instructions

	ENTRY
	; ENTRY directive declares an entry point to the program
	EXPORT	Reset_Handler
		
Reset_Handler
	MOV	R0, #0						; Sets R0 to 0
	LDR	R2, =A						; Loads R2 with address of A
Loop
	CMP	R0,	#100					; Compares R0 to 100
	BGE	Exit						; Goes to the Exit label if R0 >= 100
	MOV	R1, #100					; Sets R1 to 100
	SUB	R1, R1, R0					; Subtracts R0 from R1 and stores in R1
	STR	R1, [R2, R0, LSL #2]		; Stores R1 in the memory address of R2 + R0*4
 	ADD	R0, R0, #1					; Adds 1 to R0 and stores it in R0
	B	Loop						; Unconditional branch back to Loop label
Exit	B	Exit					; Unconditional branch to Exit label (Stops program)
A	SPACE	400						; Allocates 400 bytes of zeroed store

	END								; END directive ends program