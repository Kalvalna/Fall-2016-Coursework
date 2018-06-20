;	PA2 Part 2
;	I set R0 as i (0), the address of the array in R1, R2 as s (0), and the value of a[i] in R3.
; 	Then the process is looped until the counter is equal or greater than 10 or if s == a[i]. 
;	This is the assembly language version of:
;	int main(int argc, char ** argv)
;	{
;		int a[10] = {7,6,4,5,5,1,3,2,9,8};
;		int i = 0;
;		int s = 0;
;		
;		while (i < 10) {
;			s = s + a[i];
;			i = i + 1;
;		}
;
;		return 0;
;	}

	TTL	PA2Part2
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
	MOV32	R0, #0					; Sets R0 as i (0)
	ADR	R1, a					; Loads R1 with address of a[0]
	MOV32	R2, #0					; Sets R0 as s (0)
Loop
	CMP	R0,	#10					; Compares R0 to 10
	BGE	Exit					; Goes to the Exit label if R0 >= 10
	LDR	R3, [R1], #4			; Loads the value at the address of a[i] into R3
	ADD R2, R3					; Adds a[i] to s and stores as s
	ADD	R0, #1					; Adds 1 to i
	B	Loop					; Unconditional branch to the Loop label


a	DCD	7, 6, 4, 5, 5, 1, 3, 2, 9, 8	; Stores the array as a
	
Exit
	MOV32	R0, #0				; Dummy instruction
	
	END							; END directive ends program