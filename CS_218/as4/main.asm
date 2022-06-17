

section .data
;	System Service Constants
	SYSTEM_EXIT equ 60
	SUCCESS equ 0
	SYSTEM_READ equ 0 
	STANDARD_IN equ 0
	SYSTEM_WRITE equ 1
	STANDARD_OUT equ 1

;	Labels
	stringMacro db "getStringLength: ", NULL
	testString db "Testing Length", LINEFEED, NULL
	pass db "PASS", LINEFEED, NULL
	fail db "FAIL", LINEFEED, NULL
	newline db LINEFEED, NULL
	daysLabel db "getDays: ", NULL

	integerTest1 db "String to Integer 1 (-41632): ", NULL
	integerTest2 db "String to Integer 2 (9055): ", NULL
	integerTest3 db "String to Integer 3 (+3): ", NULL

	integerTest4 db "Integer to String (-88,216): ", NULL
	integerTest5 db "Integer to String (372,441): ", NULL

;	Character Constants
	NULL equ 0
	LINEFEED equ 10

;	Time constants
	SECONDS_PER_MINUTE equ 60
	MINUTES_PER_HOUR equ 60
	HOURS_PER_DAY equ 24

;	Time Variables
	secondsInput dd 321265
	secondsOutput dd -1
	minutesOutput dd -1
	hoursOutput dd -1
	daysOutput dd -1

;	Conversion Tests
	stringLength dq -1
	integerString1 db "-41632", NULL
	integerString2 db "9055", NULL
	integerString3 db "+3", NULL
	integerOutput1 dd -1
	integerOutput2 dd -1
	integerOutput3 dd -1
	integerInput1 dd -88216
	integerInput2 dd 372441

section .bss
	stringBuffer resb 1000
	stringOutput1 resb 12
	stringOutput2 resb 12

section .text

;	Calculates the length of a null terminated string (not including null)
;	Argument 1: String Address
;	Argument 2: 64 bit register/memory segment to store the length
%macro getStringLength 2
	mov rcx, 0 ;loop index
	%%getStringLengthLoop:
		mov bl, byte[%1 + rcx] ;take one char
		cmp bl, NULL  ;check to see if end of string or not
		je %%getStringLengthDone ;if yes then jump to done   
		inc rcx ;index incr
	jmp %%getStringLengthLoop
	%%getStringLengthDone:
	mov %2, rcx ;store into argument
%endmacro

;	Calculates the number of days, hours, and seconds equal
;	to a given amount of time (in seconds).
;	
;	Argument 1: Total time in seconds (32 bit signed integer)
;	Argument 2: Days (32 bit signed integer)
;	Argument 3: Hours (32 bit signed integer)
;	Argument 4: Minutes (32 bit signed integer)
;	Argument 5: Seconds (32 bit signed integer)
%macro getDays 5
	mov eax, %1 ;take data
	mov r8d, SECONDS_PER_MINUTE
	cdq ;eax -> edx:eax
	idiv r8d
	mov %5, edx ;store seconds
	mov r9d, MINUTES_PER_HOUR
	cdq
	idiv r9d
	mov %4, edx ;store minutesOutput
	mov r10d, HOURS_PER_DAY
	cdq
	idiv r10d
	mov %3, edx ;store hoursOutput
	mov %2, eax ;store daysOutput
%endmacro

;	Converts a string representing an integer decimal value to an
;	unsigned dword integer
;	Argument 1: An address to a null terminated string
;	Argument 2: A 32 bit register/memory segment to store the value
%macro stringToInt32 2
	mov rcx, 0
	mov r9d, 0 ;store flag
	mov eax, 0 ; sum
	%%convertLoopString:
		mov bl, byte[%1 + rcx] ;each char
		cmp bl, NULL ;end of string
		je %%doneLoop ;if char == NULL then done loop

		cmp bl, '+' ;check sign
		je %%nextCharacter
		cmp bl, '-' ;check sign
		je %%negative
		cmp bl, '' 
		je %%nextCharacter

		sub bl, 48 ;convert to digit
		mov r10d, 10
		imul r10d
		movsx ebx, bl  ;extend byte to 32
		add eax,ebx ;add num in that digit
		jmp %%nextCharacter 

	%%nextCharacter:
		inc rcx
		jmp %%convertLoopString

	%%negative:
		inc rcx
		mov r9d, -1 ;stor sign for negative
		jmp %%convertLoopString

	%%doneLoop:
		cmp r9d, 0 ;check sign
		je %%convertDone  
		mov r11d, -1 
		imul r11d ;sign
		mov %2, eax  ;store output
	%%convertDone:
		mov %2, eax ;store output
%endmacro

;	Converts a signed 32 bit integer to a null terminated string representation
;	Argument 1: 32 bit integer
;	Argument 2: Address to a string (12 characters maximum)
%macro int32ToString 2
	movsxd rax, %1 ;extand 32 to 64 bits
	cmp rax, 0  ;check to see if number negative or not
	mov rcx, 0 ;counter for digit
	jl %%negative ;if < 0 then negative
	jmp %%pushStack

	%%pushStack:
		mov rdx, 0
		mov r9d, 10   
		cqo ;rax -> rdx:rax
		idiv r9
		add rdx, '0' ;convert to char
		inc rcx ;inc counter to keep track of digits
		push rdx ;push to stack
		cmp rax, 0 ;check to see if result is 0 or not
		je %%popStack ;if yes then done with push stack
		jne %%pushStack ;loop again

	mov rbx, 0 ;counter for loop
	%%popStack:
		pop rdx
		mov byte[%2 + rbx + 1], dl ;add each char into result
		inc rbx ;increase loop counter
		dec rcx ;decrease digits counter
		cmp rcx, 0 ;check digits counter
		je %%done 
		jmp %%popStack ;loop again
		

	%%negative:
		mov byte[%2], '-' ;add '-' if it's negative
		mov r8, -1    
		imul r8 ;change sign
		jmp %%pushStack ;go ti push stack to start 
	%%done:
		mov byte[%2 + rbx + 1], NULL ;add null at the end
%endmacro

;	---------------------------------------------------------------
;	---------------------------------------------------------------
;	  DO NOT ALTER THE _START FUNCTION
;	---------------------------------------------------------------
;	---------------------------------------------------------------
global _start
_start:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, stringMacro
	mov rdx, 17
	syscall

	;	Test String Length
	getStringLength testString, qword[stringLength]
	cmp qword[stringLength], 15
	jne stringTestFail
		mov rsi, pass
	jmp stringTestEnd
	stringTestFail:
		mov rsi, fail
	stringTestEnd:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rdx, 5
	syscall
	
	;	Test getDays
	getDays dword[secondsInput], dword[daysOutput], dword[hoursOutput], dword[minutesOutput], dword[secondsOutput]
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, daysLabel
	mov rdx, 9
	syscall
	
	cmp dword[daysOutput], 3
	jne daysFail
	cmp dword[hoursOutput], 17
	jne daysFail
	cmp dword[minutesOutput], 14
	jne daysFail
	cmp dword[secondsOutput], 25
	jne daysFail
		mov rsi, pass
		jmp daysPass
	daysFail:
		mov rsi, fail
	daysPass:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rdx, 5
	syscall
	
	;	Test Integer Conversion
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, integerTest1
	mov rdx, 30
	syscall

	stringToInt32 integerString1, dword[integerOutput1]
	
	cmp dword[integerOutput1], -41632
	jne integerTest1Fail
		mov rsi, pass
	jmp integerTest1Pass
	integerTest1Fail:
		mov rsi, fail
	integerTest1Pass:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rdx, 5
	syscall
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, integerTest2
	mov rdx, 28
	syscall

	stringToInt32 integerString2, dword[integerOutput2]
	
	cmp dword[integerOutput2], 9055
	jne integerTest2Fail
		mov rsi, pass
	jmp integerTest2Pass
	integerTest2Fail:
		mov rsi, fail
	integerTest2Pass:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rdx, 5
	syscall
		
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, integerTest3
	mov rdx, 26
	syscall

	stringToInt32 integerString3, dword[integerOutput3]
	
	cmp dword[integerOutput3], 3
	jne integerTest3Fail
		mov rsi, pass
	jmp integerTest3Pass
	integerTest3Fail:
		mov rsi, fail
	integerTest3Pass:
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rdx, 5
	syscall
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, integerTest4
	mov rdx, 29
	syscall
	
	int32ToString dword[integerInput1], stringOutput1
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, stringOutput1
	mov rdx, 12
	syscall
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, newline
	mov rdx, 1
	syscall

	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, integerTest5
	mov rdx, 29
	syscall
	
	int32ToString dword[integerInput2], stringOutput2
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, stringOutput2
	mov rdx, 12
	syscall
	
	mov rax, SYSTEM_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, newline
	mov rdx, 1
	syscall
	
endProgram:
	mov rax, SYSTEM_EXIT
	mov rdi, SUCCESS
	syscall