; ****************************************************************************

;  Assignment: 6
;  Description:	Simple assembly language program to convert
;		integers to tridecimal/ASCII charatcers and output
;		the tridecimal/ASCII strings to the screen (using the
;		provided routine).


; ****************************************************************************
;  STEP #2
;  Macro, "tri2int", to convert a tridecimal/ASCII string
;  into an integer.  The macro reads the ASCII string (byte-size,
;  NULL terminated) and converts to a doubleword sized integer.
;	- Accepts both 'A' and 'a' (which are treated as the same thing).
;	- Accepts both 'B' and 'b' (which are treated as the same thing).
;	- Accepts both 'C' and 'c' (which are treated as the same thing).
;	- Assumes valid/correct data, no error checking is performed.
;  Skips any leading blanks.

;  Example:  given the ASCII string: " 01aB", NULL
;  The is,  " " (blank) followed by "0" followeed by "1" followed
;  by "a" followed by "B" and NULL would be converted to integer 310.

; -----
;  Arguments
;	%1 -> string address (reg)
;	%2 -> integer number (destination address)

; -----
; Algorithm:
;	YOUR ALGORITHM GOES HERE

%macro	tri2int	2
;	YOUR CODE GOES HERE
// clear the rax will resolve the problem that rax/eax holding trash values
	mov rax, 0 // * important to have this
	%%checkSpace:
		cmp byte[%1], ' '; check space
		jne %%findCharacter ; if not space -> it's char to convert ; jump to findChar
		inc %1 ;increment to go to next char 
		jmp %%checkSpace ; if there still space -> keep check ; jump to checkEmptySpace
		
	%%findCharacter: ; if not space -> it's char to convert
		cmp byte[%1], NULL ; NULL used to detrmine end str
		je %%done

		;if not end -> convert
		%%convertLoop: ; convert loop 
			cmp byte[%1], NULL ;check again to see if NULL
			je %%done
			cmp byte[%1], ' '; recheck for empty space again
			je %%done

			;check to see whether the char is number or letter
			cmp byte[%1], '9'
			jg %%haveCharacter
			;if not charatcer -> convert it to decimal

            mov r11b, byte[%1]
			sub r11b,'0' ; convert to decimal
			mov r8, 13
			imul r8
			movsx r11d, r11b ; extend byte to 32
			;66-67 most likely to cause issue
			;so this seem like it does not add the convert value together
			;convert -> correct but just not correct when it get put into
			add eax, r11d ; add that digit into the register
			mov dword[%2], eax ; store the result into the register
			inc %1 ; go to next char
			jmp %%convertLoop ; jump to convertLoopString 

    %%haveCharacter:
        mov r11b, byte[%1]
        ;convert to lower case  
        ; hard code that value to 10
        cmp r11b, 'a'
        jge %%lowCase
        jl %%upCase
        

    %%lowCase:
        sub r11b, 'a'
        add r11b , 10
        jmp %%goAgain

    %%upCase:
        sub r11b, 'A'
        add r11b , 10
        jmp %%goAgain

    %%goAgain:
        mov r8, 13
		imul r8
        movsx r11d, r11b  
		;95-96 most likely to cause issue
		;so this seem like it does not add the convert value together
        add eax, r11d
        mov dword[%2], eax ; store the result into the register
        inc %1
        jmp %%convertLoop

	%%done: 

%endmacro

; --------------------------------------------------------------

section	.data

; -----
;  Define standard constants.

TRUE		equ	1
FALSE		equ	0

SUCCESS		equ	0			; successful operation
NOSUCCESS	equ	1			; unsuccessful operation

STDIN		equ	0			; standard input
STDOUT		equ	1			; standard output
STDERR		equ	2			; standard error

SYS_read	equ	0			; system call code for read
SYS_write	equ	1			; system call code for write
SYS_open	equ	2			; system call code for file open
SYS_close	equ	3			; system call code for file close
SYS_fork	equ	57			; system call code for fork
SYS_exit	equ	60			; system call code for terminate
SYS_creat	equ	85			; system call code for file open/create
SYS_time	equ	201			; system call code for get time

LF		equ	10
SPACE		equ	" "
NULL		equ	0
ESC		equ	27

; -----
;  Variables and constants.

MAX_STR_SIZE	equ	10

; -----
;  Misc. data definitions (if any).


; -----
;  Assignment #6 Provided Data:

dStr1		db	"    12a4B", NULL
iNum1		dd	0

dStrLst1	db	"     1a9C", NULL, "      3Ab", NULL, "    1cA92", NULL
		db	"    82bAc", NULL, "      bac", NULL
len1		dd	5
sum1		dd	0

dStrLst2	db	"      3A8", NULL, "    A6791", NULL, "    193b0", NULL
		db	"    250b0", NULL, "   a13081", NULL, "    14b21", NULL
		db	"    224A2", NULL, "    11010", NULL, "    11201", NULL
		db	"     10C0", NULL, "        B", NULL, "       c6", NULL
		db	"      7b1", NULL, "     C009", NULL, "    19a45", NULL
		db	"    15557", NULL, "     23a9", NULL, "    189c0", NULL
		db	"    A12a4", NULL, "    11c11", NULL, "    12a2c", NULL
		db	"    11B92", NULL, "    15a10", NULL, "    1b667", NULL
		db	"     B726", NULL, "     B312", NULL, "      420", NULL
		db	"     55C2", NULL, "    26516", NULL, "     5182", NULL
		db	"      192", NULL, "    21a44", NULL, "     18c4", NULL
		db	"     79a6", NULL, "    24c12", NULL, "     a231", NULL
		db	"     97B5", NULL, "    17312", NULL, "      812", NULL
		db	"      7c4", NULL, "    123A4", NULL, "    278b1", NULL
		db	"        7", NULL, "        c", NULL, "    B1512", NULL
		db	"     7c52", NULL, "    11b44", NULL, "    10134", NULL
		db	"     7a64", NULL, "     4b71", NULL, "     2c44", NULL
		db	"      2b4", NULL, "    112c2", NULL, "    11aa5", NULL
		db	"     2012", NULL, "    22a30", NULL, "     7164", NULL
		db	"     1067", NULL, "    117b1", NULL, "    21000", NULL
		db	"     2b74", NULL, "     2127", NULL, "    23212", NULL
		db	"      117", NULL, "    20c63", NULL, "    b2112", NULL
		db	"    11C45", NULL, "    11064", NULL, "    11B21", NULL
		db	"    260a0", NULL, "    23A75", NULL, "    c3725", NULL
		db	"     3A10", NULL, "      120", NULL, "    13332", NULL
		db	"    10C22", NULL, "     7B60", NULL, "    a2313", NULL
		db	"    11c60", NULL, "     4312", NULL, "    17b65", NULL
		db	"    23241", NULL, "    27C31", NULL, "      730", NULL
		db	"     4313", NULL, "    30233", NULL, "    13657", NULL
		db	"    31113", NULL, "     1661", NULL, "    11312", NULL
		db	"    17A55", NULL, "    12241", NULL, "    13C31", NULL
		db	"     3270", NULL, "     7a53", NULL, "    15127", NULL
		db	"       A5", NULL, "    7a3b1", NULL, "   AbCaBc", NULL
		db	"     1b9c", NULL
len2		dd	100
sum2		dd	0

; ****************************************************************************

section	.bss

iLst1		resd	5
iLst2		resd	100

tempNum		resd	1

; ****************************************************************************

section	.text
global	_start
_start:

; ==================================================
;  Main program
;	perform conversion (non-macro)
;	calls the macro on various data items

; -----
;  STEP #1
;	Convert tridecimal/ASCII NULL terminated string at 'dStr1'
;	into an integer which should be placed into 'iNum1'
;	Note, 12A4B (base-13) = 34,708 (base-10)
;	DO NOT USE MACRO HERE!!

;	YOUR CODE GOES HERE
;	Convert tridecimal/ASCII NULL terminated string at 'dStr1'
	; put address into reg
    mov r10, 0
	mov r10, dStr1
	
	checkEmptySpace:
		cmp byte[r10], ' '; check space
		jne findChar ; if not space -> it's char to convert ; jump to findChar
		inc r10 ;increment to go to next char 
		jmp checkEmptySpace ; if there still space -> keep check ; jump to checkEmptySpace
		
	findChar: ; if not space -> it's char to convert
		cmp byte[r10], NULL ; NULL used to detrmine end str
		je doneLoop

		;if not end -> convert
		convertLoopString: ; convert loop 
			cmp byte[r10], NULL ;check again to see if NULL
			je doneLoop
			cmp byte[r10], ' '; recheck for empty space again
			je doneLoop

			;check to see whether the char is number or letter
			cmp byte[r10], '9'
			jg character
			;if not charatcer -> convert it to decimal

            mov r11b, byte[r10]
			sub r11b,'0' ; convert to decimal
			mov r8, 13
			imul r8
			movsx r11d, r11b ; extend byte to 32
			add eax, r11d ; add that digit into the register
			mov dword[iNum1], eax ; store the result into the register
			inc r10 ; go to next char
			jmp convertLoopString ; jump to convertLoopString 

    character:
        mov r11b, byte[r10]
        ;convert to lower case  
        ; hard code that value to 10
        cmp r11b, 'a'
        jge lowerCase
        jl upperCase
        

    lowerCase:
        sub r11b, 'a'
        add r11b , 10
        jmp goBackLoop

    upperCase:
        sub r11b, 'A'
        add r11b , 10
        jmp goBackLoop  

    goBackLoop:
        mov r8, 13
		imul r8
        movsx r11d, r11b  
        add eax, r11d
        mov dword[iNum1], eax ; store the result into the register
        inc r10
        jmp convertLoopString

	doneLoop: 
        mov r8, 0 
        mov r11, 0   
        mov rax, 0   
        mov r10, 0

; -----
;  Perform (iNum1 * 4) operation.
;	Note, 34,708 (base-10) * 4 (base-10) = 138,832 (base-10)

	mov	eax, dword [iNum1]
	mov	ebx, 4
	mul	ebx
	mov	dword [iNum1], eax

; ==================================================
;  Next, repeatedly call the macro on each value in an array.

;  Data Set #1 (short list)

	mov	ecx, dword [len1]		; length
	mov	rbx, iLst1			; starting index of integer list
	mov	rdi, dStrLst1			; address of string

cvtLoop1:
	push	rcx				; preserver registers
	push	rdi				; so macro can alter them
	push	rbx

	tri2int	rdi, tempNum

	mov	eax, dword [tempNum]
	add	dword [sum1], eax

	pop	rbx
	mov	dword [rbx], eax
	add	rbx, 4

	pop	rdi
	add	rdi, MAX_STR_SIZE

	pop	rcx
	dec	rcx				; check length
	cmp	rcx, 0
	ja	cvtLoop1

; ==================================================
;  Data Set #2 (long list)

	mov	rcx, [len2]			; length
	mov	rbx, iLst2			; starting index of integer list
	mov	rdi, dStrLst2			; address of string

cvtLoop2:
	push	rcx				; preserver registers
	push	rdi				; so macro can alter them
	push	rbx

	tri2int	rdi, tempNum

	mov	eax, dword [tempNum]
	add	dword [sum2], eax

	pop	rbx
	mov	dword [rbx], eax
	add	rbx, 4

	pop	rdi
	add	rdi, MAX_STR_SIZE

	pop	rcx
	dec	rcx				; check length
	cmp	rcx, 0
	ja	cvtLoop2

; ==================================================
; Done, terminate program.

last:
	mov	rax, SYS_exit
	mov	rdi, SUCCESS
	syscall

; ****************************************************************************

