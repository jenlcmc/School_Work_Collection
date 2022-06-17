; *****************************************************************

;  Assignment: 7
;  Description:	Simple assembly language program to sort
;		a list of integers using the provided gnome
;		sort algorithm.


;  Write a simple assembly language program to sort
;  a list of integers using the provided gnome sort algorithm.

; -----
;  GNOME Sort Algorithm:
;	function gnomeSort(a[0..size-1]) {
;		i := 1
;		j := 2
;		while (i < size)
;			if (a[i-1] <= a[i])
;				i := j
;				j := j + 1 
;		else
;			swap a[i-1] and a[i]
;			i := i - 1
;			if (i = 0) i := 1
;		}

; *****************************************************************************
;  Macros to find the statistical information.
;	findSumAve - calculate sum and average
;	findMinMax - calculate minimum and maximum
;	findMid - calculate middle value

; -----
;  findSumAve	%1-sepIntArr, %2-len,  %3-sum, %4-ave

%macro	findSumAve	4
	; mov the len into ecx
	; %2 == parameter 2 == len
	; set up counter
	mov ecx, dword[%2] 
	mov rsi, 0 

	;set up sum and average
	mov dword[%3], 0   
	mov dword[%4], 0

	%%sumAveLoop:
		;get next var into eax
		mov eax, dword[%1 + rsi * 4] ; %1 == araay
		add dword[%3], eax ; calcualte sum  
		
		; loop back 
		inc rsi 
		loop %%sumAveLoop

		;when done loop -> average
		mov eax, dword[%3] ;take sum 
		mov edx, 0 ; clear upper bits before div
		div dword[%2]
		mov dword[%4], eax ; move res to ave var	

%endmacro


; -----
;  findMinMax	sepIntArr, len, min, max

%macro	findMinMax	4

	; mov the len into ecx
	; %2 == parameter 2 == len
	; set up counter
	mov ecx, dword[%2] 
	mov rsi, 0 

	;set up min and max  
	mov eax, dword[%1]
	mov dword[%3], eax
	mov dword[%4], eax


	%%minMaxLoop: 
		;get next var into eax
		mov eax, dword[%1 + rsi * 4] ; %1 == araay

		; check to see if it is min or not
		cmp eax, dword[%3]
		jae %%notNewMin  
		mov dword[%3], eax ; store min

		; check if max or not
		%%notNewMin:
			cmp eax, dword[%4]
			jbe %%notMax  
			mov dword[%4], eax ; store max

		%%notMax:
			; loop back
			inc rsi 
			loop %%minMaxLoop
		
%endmacro


; -----
;  findSumAve	%1-sepIntArr, %2-len, %3-mid

%macro	findMid		3

	; the program is even lnegth
	mov eax, dword[%2] ;put length into eax
	; clear edx to div
	mov edx, 0   
	mov r12d, 2
	div r12d ; rax= length /2

	cmp edx, 0 ; even or odd  
	je %%evenLength

	mov r12d, dword[%1 + eax * 4] ; get arr[len/2]
	mov dword[%3], r12d ;put the element into var
	jmp %%medDone  

	%%evenLength:
		mov r11d, dword[%1 + eax * 4] ;get 1st mid
		mov r12d, dword[(%1 + eax * 4) + 4] ;get 2nd mid
		add r12d, r11d ; add togetehr
		mov eax, r12d ; put add value back to do div
		;clear reg rdx so no seg
		mov edx, 0  
		mov r8d, 2
		div r8d ; average of 2 number -> med 
		mov dword[%3], eax

	%%medDone:
		; clear vars 
		mov r12, 0
		mov r11, 0  
		mov rax, 0
	

%endmacro


; *****************************************************************************

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

lst	dd	123,  42, 146,  76, 120,  56, 164,  65, 155,  57
	dd	111, 188,  33,  05,  27, 101, 115, 108,  13, 115
	dd	 17,  26, 129, 117, 107, 105, 109,  30, 150,  14
	dd	147, 123,  45,  40,  65,  11,  54,  28,  13,  22
	dd	 69,  26,  71, 147,  28,  27,  90, 177,  75,  14
	dd	181,  25,  15,  22,  17,   1,  10, 129,  12, 134
	dd	 61,  34, 151,  32,  12,  29, 114,  22,  13, 131
	dd	127,  64,  40, 172,  24, 125,  16,  62,   8,  92
	dd	111, 183, 133,  50,   2,  19,  15,  18, 113,  15
	dd	 29, 126,  62,  17, 127,  77,  89,  79,  75,  14
	dd	114,  25,  84,  43,  76, 134,  26, 100,  56,  63
	dd	 24,  16,  17, 183,  12,  81, 320,  67,  59, 190
	dd	193, 132, 146, 186, 191, 186, 134, 125,  15,  76
	dd	 67, 183,   7, 114,  15,  11,  24, 128, 113, 112
	dd	 24,  16,  17, 183,  12, 121, 320,  40,  19,  90
	dd	135, 126, 122, 117, 127,  27,  19, 127, 125, 184
	dd	 97,  74, 190,   3,  24, 125, 116, 126,   4,  29
	dd	104, 124, 112, 143, 176,  34, 126, 112, 156, 103
	dd	 69,  26,  71, 147,  28,  27,  39, 177,  75,  14
	dd	153, 172, 146, 176, 170, 156, 164, 165, 155, 156
	dd	 94,  25,  84,  43,  76,  34,  26,  13,  56,  63
	dd	147, 153, 143, 140, 165, 191, 154, 168, 143, 162
	dd	 11,  83, 133,  50,  25,  21,  15,  88,  13,  15
	dd	169, 146, 162, 147, 157, 167, 169, 177, 175, 144
	dd	 27,  64,  30, 172,  24,  25,  16,  62,  28,  92
	dd	181, 155, 145, 132, 167, 185, 150, 149, 182,  34
	dd	 81,  25,  15,   9,  17,  25,  37, 129,  12, 134
	dd	177, 164, 160, 172, 184, 175, 166,  62, 158,  72
	dd	 61,  83, 133, 150, 135,  31, 185, 178, 197, 185
	dd	147, 123,  45,  40,  66,  11,  54,  28,  13,  22
	dd	 49,   6, 162, 167, 167, 177, 169, 177, 175, 164
	dd	161, 122, 151,  32,  70,  29,  14,  22,  13, 131
	dd	 84, 179, 117, 183, 190, 100, 112, 123, 122, 131
	dd	123,  42, 146,  76,  20,  56,  64,  66, 155,  57
	dd	 39, 126,  62,  41, 127,  77, 199,  79, 175,  14

len	dd	350

min	dd	0
med	dd	0
max	dd	0
sum	dd	0
avg	dd	0


; --------------------------------------------------------------

section	.text
global	_start
_start:

; -----
;  Sort numbers via gnome sort.
	mov r11d, 1 ; i = 1  
	mov r12d, 2 ; j = 2

	whileLoop:
		cmp r11d, dword[len] ;check to see if it is end of array 
		jae doneLoop  
		
		mov r8d, dword[(lst + r11d * 4) - 4] ;a[i-1]
		mov r9d, dword[lst + r11d * 4] ;a[i]

		cmp r8d, r9d ;if (a[i-1] > a[i])
		ja swapVal

		;otherwise do if statement
		mov r11d, r12d ; i = j
		add r12d, 1 ; j++
		jmp whileLoop

		swapVal: ;if (a[i-1] <= a[i])

			mov r10d, r8d ;temp = a[i-1]
			mov r8d, r9d ;a[i-1] = a[i]
			mov r9d, r10d ;a[i] = temp

			; put the val back to that pos
			mov dword[(lst + r11d * 4) - 4], r8d ; a[i-1]
			mov dword[lst + r11d * 4], r9d ;a[i]

			sub r11d, 1 ;i--
			cmp r11d, 0  ; if(i == 0)
			jne loopAgain ;if (i != 0)
			mov r11d, 1  ; i = 1
			jmp whileLoop

		loopAgain:
			jmp whileLoop;

	doneLoop:
; -----
;  Use macros to find stats

	findSumAve	lst, len, sum, avg
	findMinMax	lst, len, min, max
	findMid		lst, len, med


; ******************************
; Done, terminate program.

last:
	mov	rax, SYS_exit
	mov	rdi, SUCCESS
	syscall

