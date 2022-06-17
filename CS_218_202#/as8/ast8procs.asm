; *****************************************************************

;  Assignment: 8
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
;  Due to the data sizes, the summation for the dividend (top)
;  must be performed as a quad-word.


; ********************************************************************************

section	.data

; -----
;  Define constants.

TRUE		equ	1
FALSE		equ	0
NULL         equ 	0 ; null pointer
EXIT_SUCCESS equ 	0 ; successful termination
SYS_exit    equ 	60 ; exit syscall

; -----
;  Variables for gnomeSort() function (if any).

; -----
;  Variables for basicStats() function (if any).

; -----
;  Variables for corrCoefficient() function (in any).

sumX dd 0
sumY dd 0
sumXY dd 0


; ********************************************************************************

section	.text

; ********************************************************************
;  gnome sort function.
global gnomeSort
gnomeSort:
; -----
;  Call:
;	call gnomeSort(list, len)

;  Arguments Passed:
;	1) list, addr - rdi
;	2) length, value - rsi

;  Returns:
;	sorted list (list passed by reference)
    ;prologue 
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
;	YOUR CODE GOES HERE



; ********************************************************************
;  Find basic statistical information for a list of integers:
;	minimum, median, maximum, sum, and average

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  Note, the list is already sorted.

global basicStats
basicStats:
; -----
;  Call:
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
    pop rbx
    mov rsp, rbp ; clear locals 
    pop rbp 
ret

; ********************************************************************
;  Function to calculate the median of an sorted list.

; -----
;  Call:
;	ans = listMedian(lst, len)
global listMedian
listMedian:
;  Arguments Passed:
;	- list, address /rdi
;	- length, value /rsi

;  Returns:
;	median (in eax)
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

;	YOUR CODE GOES HERE
    medDone:
    pop r10
    pop r12
    pop rbx
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret

; ********************************************************************
;  Function to calculate the correlation coefficient
;  between two lists (of equal size).

; -----
;  HLL Call:
;	r = corrCoefficient(xList, yList, len)
global corrCoefficient
corrCoefficient:

;  Arguments Passed:
;	1) xList, addr - rdi
;	2) yList, addr - rsi
;	3) length, value - rdx

;  Returns:
;	r value (in xmm0)
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
    pop rbx
    mov rsp, rbp ; clear locals 
    pop rbp 
    ret

; ********************************************************************************
