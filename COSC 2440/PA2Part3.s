;	PA2 Part 3
;	I store the value of s (2) in R0 and the array into R1. Then I compared R0 to 0, 1, and 2 with a branch to
;	their respective functions if s is equal to 0, 1, or 2. For the default, I placed the function under the 
;	comparison and branch statements since it would only arrive at the default function if s did not equal
; 	0, 1, or 2.
;	This is the assembly language version of:
;	int a[10] = {7,6,4,5,5,1,3,2,9,8};
;	int r = 0, s = 2;
;	
;	switch (s) {
;		case 0:
;			r = a[0] + a[1]; break;
;		case 1:
;			r = a[1] - a[2]; break;
;		case 2:
;			r = a[2] * a[3]; break;
;		default:
;			r = a[9]
;	}

	TTL	PA2Part3
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
	MOV32	R0, #2				; Stores the value of 2 (s) in R0
	ADR	R1, a					; Loads R1 with address of a[0]
Switch
	CMP	R0, #0					; Compares to see if s == 0
	BEQ	case0					; Goes to case0 label if true
	CMP	R0,	#1					; Compares to see if s == 1
	BEQ	case1					; Goes to case1 label if true
	CMP R0, #2					; Compares to see if s == 2
	BEQ	case2					; Goes to case2 label if true
default	
	LDR	R4, [R1, #36]			; Loads a[9] into R4 (r)
	B	Exit					; Unconditional branch to exit
case0
	LDR	R2, [R1]				; Loads a[0] into R2
	LDR	R3, [R1, #4]			; Loads a[1] into R3
	ADD	R4,	R2, R3				; Adds R2 and R3 and sets in R4 (r)
	B	Exit					; Unconditional branch to exit
case1
	LDR	R2, [R1, #4]			; Loads a[1] into R2
	LDR	R3, [R1, #8]			; Loads a[2] into R3
	SUB	R4, R2, R3				; Subtracts R3 from R2 and sets in R4 (r)
	B	Exit					; Unconditional branch to exit
case2
	LDR	R2, [R1, #8]			; Loads a[2] into R2
	LDR	R3, [R1, #12]			; Loads a[3] into R3
	MUL	R4, R2, R3				; Multiplies R2 and R3, then sets value in R4 (r)
	B	Exit					; Unconditional branch to exit

a	DCD	7, 6, 4, 5, 5, 1, 3, 2, 9, 8	; Stores the array as a
	
Exit
	MOV32	R0, #0				; dummy instruction
	
	END							; END directive ends program