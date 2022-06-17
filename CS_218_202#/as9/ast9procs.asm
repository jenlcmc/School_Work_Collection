; *****************************************************************

;  Assignment: 9
;  Description: <description here>

;  Functions Template.

; --------------------------------------------------------------------
;  Write four assembly language functions.

;  The void function, gnomeSort(), sorts the numbers into ascending
;  order (small to large).  Uses the gnome sort algorithm from
;  assignment #7 (modified to sort in descending order).

;  The void function, basicStats(), finds the minimum, median, and
;  maximum, sum, and average for a list of numbers.
;  The median is determined after the list is sorted by the 
;  using the listMedian function.

;  The value returning function, listMedian(), computes the 
;  median of the list.

;  The  value returning function, corrCoefficient(), computes the
;  correlation coefficient for the two data sets.
;  Note, summation and division performed as integer values.
;  Final result is real in xmm0.

;  NO static variables allowed.
;  Must create stack dynamic locals as neeed.

; ********************************************************************************

section	.data

; -----
;  Define standard constants.

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation

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
;  Define program specific constants.

SUCCESS 	equ	0
BADNUMBER	equ	1
INPUTOVERFLOW	equ	2
OUTOFRANGE	equ	3
ENDOFINPUT	equ	4

MIN		equ	1
MAX		equ	1000000
BUFFSIZE	equ	50			; 50 chars including NULL

; -----
;  NO static local variables allowed...

; ********************************************************************************

section	.text

; extra macros for convert
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
;	%1 -> string value
;	%2 -> integer number 

; -----
; Algorithm:
;	YOUR ALGORITHM GOES HERE

%macro	tri2int	2
;	YOUR CODE GOES HERE
	; clear the rax will resolve the problem that rax/eax holding trash values
	mov rax, 0 ; * important to have this
	%%checkSpace:
        mov r15b, byte[%1]
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
			ja %%haveCharacter
			;if not charatcer -> convert it to decimal

            mov r11b, byte[%1]
			sub r11b,'0' ; convert to decimal
			mov r8, 13
			mul r8
			movsx r11d, r11b ; extend byte to 32
			;66-67 most likely to cause issue
			;so this seem like it does not add the convert value together
			;convert -> correct but just not correct when it get put into
			add eax, r11d ; add that digit into the register
			mov %2, eax ; store the result into the register
			inc %1 ; go to next char
			jmp %%convertLoop ; jump to convertLoopString 

    %%haveCharacter:
        mov r11b, byte[%1]
        ;convert to lower case  
        ; hard code that value to 10
        cmp r11b, 'a'
        jae %%lowCase
        jb %%upCase
        

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
		mul r8
        movsx r11d, r11b  
		;95-96 most likely to cause issue
		;so this seem like it does not add the convert value together
        add eax, r11d
        mov %2, eax ; store the result into the register
        inc %1
        jmp %%convertLoop

	%%done: 

%endmacro

; --------------------------------------------------------
;  Read an ASCII base-13 number from the user

;  Return codes:
;	SUCCESS		Successful conversion
;	BADNUMBER	Invalid input entered
;	INPUTOVERFLOW	User entry character count exceeds maximum length
;	OUTOFRANGE	Valid, but out of required range
;	ENDOFINPUT	End of the input

; -----
;  HLL Call:
;	status = readB13Num(&numberRead);

;  Arguments Passed:
;	1) numberRead, addr - rdi

;  Returns:
;	number read (via reference)
;	status code (as above)
global readB13Num
readB13Num:

    ;prologue
    push rbp ;stack reg
    mov rbp, rsp  ;init stack
    sub rsp, 8
    push rbx
    push r15
    push r14
    mov r15, rdi
    
    mov dword[rbp - 4], 0 ;string buffer
    lea r12, [rbp - 4]
    mov dword[rbp - 8], 0 ; int convert
    lea r13, [rbp - 8]
    mov rax, 0

    ;read
    mov rax, SYS_read
    mov rdi, STDIN
    mov rsi, r12
    mov rdx, BUFFSIZE
    syscall

    checkOverflowLoop:
        cmp byte[r12 + rbx], ' ' ;check for empty space
        jne findAChar
        
    continueChecking:
        inc rbx  
        cmp rbx, rdx ; rdx -buffer size
        jb checkOverflowLoop ;if rbx <= rdx
        
        ;overflow case
        clearBufferLoop:
            mov rax, SYS_read
            mov rdi, STDIN
            mov rsi, r12
            mov rdx, 1
            syscall
            cmp byte[r12], LF
            jne clearBufferLoop ;if not linefeed, then continue clear
            jmp overflow

    findAChar:
        ;check until user enter 
        cmp byte[r12 + rbx], LF 
        je inputDone ;if ==
        jmp continueChecking

    overflow:
        mov rax, INPUTOVERFLOW
        jmp doneCheck

    inputDone:
        cmp rbx, 0 
        je eof ; size of str is 0
        mov byte[r12 + rbx], NULL ;add NULL terminator
        jmp doneGetChar

    eof:
        mov eax, ENDOFINPUT
        jmp doneCheck
    
    doneGetChar:
        mov rsi, 0 ; counter  
        mov rcx, rbx ; length of string 

        check13Loop:
            mov byte[r12 + rbx + 1], NULL ;add NULL terminator make sure
            
            mov al, byte[r12 + rsi] ;get char of string
            
            cmp al, '0'
            jb notBase13
            cmp al, '9'
            ja checkChar

            jmp goodChar

        checkChar:
            cmp al, 'A'
            jb notBase13
            cmp al, 'C'
            ja checkLower

            jmp goodChar

        checkLower:

            cmp al, 'a'
            jb notBase13
            cmp al, 'c'
            ja notBase13

            jmp goodChar

        goodChar:
            inc rsi 
            loop check13Loop

            ;all char are good
            ;r12 hold string   
            ;r13 will hold int value

            tri2int r12, dword[r13]
            mov r14d, dword[r13]
            
            cmp r14, MIN
            jb outOfRange

            
            cmp r14, MAX
            ja outOfRange

            mov rax, SUCCESS
            mov rdi, r15  
            mov rdi, r14
            jmp doneCheck

    outOfRange:
        mov rax, OUTOFRANGE
        jmp doneCheck
            


    notBase13:
        mov rax, BADNUMBER
        jmp doneCheck

    
    doneCheck:
        pop r14
        pop r15
        pop rbx
        add rsp, 8 ; clear locals 
        pop rbp
        ret

;	YOUR CODE GOES HERE

; ********************************************************************
;  Gnome sort function.

; -----
;  HLL Call:
;	call gnomeSort(list, len)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi

;  Returns:
;	sorted list (list passed by reference)
;	YOUR CODE GOES HERE
global gnomeSort
gnomeSort:
    ;prologue
    push rbp ;stack reg
    mov rbp, rsp  ;init stack
    sub rsp, 8
    mov dword[rbp - 4], 0; will hold a[i-1]
    mov dword[rbp - 8], 0 ; hold a[i]
    push r11 ; i 
    push r12 ; j

    mov r11, 1 ; i = 1 
    mov r12, 2 ; j = 2
    
    whileLoop:
		cmp r11, rsi ;check to see if it is end of array 
		jae doneLoop  
		
		mov r8d, dword[(rdi + r11 * 4) - 4] ;a[i-1]
		mov r9d, dword[rdi + r11 * 4] ;a[i]

        mov dword[rbp - 4], r8d
        mov dword[rbp - 8], r9d

		cmp r8d, r9d ;if (a[i-1] < a[i])
		ja swapVal

		;otherwise do if statement
		mov r11d, r12d ; i = j
		add r12d, 1 ; j++
		jmp whileLoop

		swapVal: ;if (a[i-1] <= a[i])

			mov r10d, dword[rbp - 4] ;temp = a[i-1]
			mov r8d, dword[rbp - 8] ;a[i-1] = a[i]
			mov r9d, r10d ;a[i] = temp

			; put the val back to that pos
            
			mov dword[(rdi + r11 * 4) - 4], r8d ; a[i-1]
			mov dword[rdi + r11 * 4], r9d ;a[i]

			sub r11d, 1 ;i--
			cmp r11d, 0  ; if(i == 0)
			jne loopAgain ;if (i != 0)
			mov r11d, 1  ; i = 1
			jmp whileLoop

		loopAgain:
			jmp whileLoop;

	doneLoop:
    ; clear local
    pop r12  
    pop r11
    pop rbx
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret

global printString 
printString:
push rbx
; -----
;  Count characters in string.
mov rbx, rdi
mov rdx, 0 
strCountLoop:
cmp byte [rbx], NULL 
je strCountDone 
inc rdx
inc rbx
jmp strCountLoop 
strCountDone:
cmp rdx, 0 
je prtDone
; -----
;  Call OS to output string.
mov rax, SYS_write 
mov rsi, rdi
mov rdi, STDOUT
syscall
; system code for write()
; address of chars to write
; standard out
; RDX=count to write, set above
; system call
; -----
;  String printed, return to calling routine.
prtDone:
pop rbx
ret
; ********************************************************************
;  Find basic statistical information for a list of integers:
;	minimum, median, maximum, sum, and average

;  Note, must call the lesitMedian function.

; -----
;  HLL Call:
;	call basicStats(list, len, min, med, max, sum, ave)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi
;	3) minimum, addr - rdx
;	4) median, addr - rcx
;	5) maximum, addr - r8
;	6) sum, addr - r9
;	7) ave, addr - stack, rbp+16

;  Returns:
;	minimum, median, maximum, sum, and average
;	via pass-by-reference (addresses on stack)
;	YOUR CODE GOES HERE
global basicStats
basicStats: 
    ;prologue
    push rbp ;stack reg
    mov rbp, rsp  ;init stack
    sub rsp, 4
    push r12 ;counter
    push r11  
    push r10

    mov r11, rdi ; get array address
    mov r10, rsi ; get length

    ;get min and max values
    ; get min
    mov r13, r10  
    dec r13
    mov eax, dword[rdi + r13 * 4] ; rdi hold address of array
    mov dword[r8], eax ; return min

    mov eax, dword[rdi] ;get max
    mov dword[rdx], eax ;return max   

    ; get median 
    ;list, address /rdi
    ;length, value /rsi  
    mov rdi, r11  
    mov rsi, r10
    call listMedian ; call get median 
    mov dword[rcx], eax  ; put median back to var

    ;find sum
    mov r12, 0 ;counter/indexpop rbp
    mov dword[rbp - 4], 0 ;running sum 
    mov eax, 0

    sumLoop:
        add eax, dword[rdi + r12 * 4] ;sum += arr[i]
        mov dword[rbp - 4], eax
        inc r12   
        cmp r12, rsi ; comapre to size
        jb sumLoop

        mov dword[r9], eax; return sum ;

    ;calculate average
    mov rdx, 0  ;clear upper bits  
    div rsi ; rax/rsi 
    mov r12, qword[rbp + 16] ;acess stack/ get ave adress
    mov dword[r12], eax ;return ave

    ;epilogue
    pop r10  
    pop r11
    pop r12 
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret


; ********************************************************************
;  Function to calculate the estimated median of an unsorted list.

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

; -----
;  HLL Call:
;	ans = listMedian(lst, len)

;  Arguments Passed:
;	- list, address
;	- length, value

;  Returns:
;	median (in eax)
;	YOUR CODE GOES HERE
global listMedian
listMedian:
    ;prologue
    push rbp ;stack reg
    mov rbp, rsp  ;init stack
    sub rsp, 4
    push r10  
    push r12

    mov rax, rsi ;get length
    mov rdx, 0 
    mov r12, 2 
    div r12    ;length/2 in rax 
    mov dword[rbp - 4], eax
    mov rax, 0
    mov r10d, dword[rbp - 4]

    cmp edx, 0  
    je evenSize  

    mov eax, dword[rdi + r10 * 4]
    jmp medDone

    evenSize:
        mov r11d, dword[rdi + r10 * 4]  
        mov r13d, dword[rdi + r10 * 4 - 4]
        add r11d, r13d   
        mov rax, r11
        mov rdx, 0  
        mov r12, 2 
        div r12d

;	epilogue
    medDone:
    pop r10
    pop r12
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret


; ********************************************************************
;  Function to calculate the correlation coefficient
;  between two lists (of equal size).

; -----
;  HLL Call:
;	r = corrCoefficient(xList, yList, len)

;  Arguments Passed:
;	1) xList, addr - rdi
;	2) yList, addr - rsi
;	3) length, value - rdx

;  Returns:
;	r value (in xmm0)
;	YOUR CODE GOES HERE
global corrCoefficient
corrCoefficient:
    ;prologue
    push rbp ;stack reg
    mov rbp, rsp  ;init stack
    sub rsp, 12
    push r10
    push r13 ; hold length

    mov dword[rbp - 4], 0 ; sumXY
    mov dword[rbp - 8], 0 ; sumX
    mov dword[rbp - 12], 0 ; sumY

    mov r10, 0 ;counter/index  
    mov rax, 0 ; sum for x  
    mov r12, 0 ; sum for y  
    mov r13, rdx ; hold length because mul and div make it reset

    loopTop:
        mov eax, dword[rdi + r10 * 4] ; x
        mov r12d, dword[rsi + r10 * 4] ; y

        mul r12d  
        add dword[rbp - 4], eax ; sum XY  

        inc r10    
        cmp r10, r13  
        jb loopTop

        mov r10, 0 ;counter/index  

    loopBot:
        mov eax, dword[rdi + r10 * 4] ;  x
        mov r12d, dword[rsi + r10 * 4] ;  y

        mul eax ; x * x 
        add dword[rbp - 8], eax   

        mov rax, 0
        mov eax, r12d  ; put y back to rax
        mul eax ; y * y 
        add dword[rbp - 12], eax

        inc r10    
        cmp r10, r13  
        jb loopBot

        ; done the loop -> convert
        mov r12d, dword[rbp - 4]
        cvtsi2sd xmm0, r12    
        
        mov rax, 0 
        mov eax, dword[rbp - 8]
        mov rbx, 0
        mov ebx, dword[rbp - 12]
        mul rbx  
        cvtsi2sd xmm1, rax  
        sqrtsd xmm1, xmm1 

        divsd xmm0, xmm1

;	YOUR CODE GOES HERE
    pop r13  
    pop r10
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret


; ********************************************************************************
