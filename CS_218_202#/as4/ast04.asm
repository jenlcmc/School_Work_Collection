; notes = negAve & sixCnt & sixSum & sixAve -> not work
; use to declare intialized var

section	.data
; -----
;  Define constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

; ----- vars for program

lst		dd	 4224, -1116,  1542,  1240,  1677
		dd	-1635,  2420,  1820,  1246,  -333 
		dd	 2315,  -215,  2726,  1140,  2565
		dd	 2871,  1614,  2418,  2513,  1422 
		dd	 -119,  1215, -1525,  -712,  1441
		dd	-3622,  -731, -1729,  1615,  2724 
		dd	 1217,  -224,  1580,  1147,  2324
		dd	 1425,  1816,  1262, -2718,  1192 
		dd	-1435,   235,  2764, -1615,  1310
		dd	 1765,  1954,  -967,  1515,  1556 
		dd	 1342,  7321,  1556,  2727,  1227
		dd	-1927,  1382,  1465,  3955,  1435 
		dd	 -225, -2419, -2534, -1345,  2467
		dd	 1615,  1959,  1335,  2856,  2553 
		dd	-1035,  1833,  1464,  1915, -1810
		dd	 1465,  1554,  -267,  1615,  1656 
		dd	 2192,  -825,  1925,  2312,  1725
		dd	-2517,  1498,  -677,  1475,  2034 
		dd	 1223,  1883, -1173,  1350,  2415
		dd	 -335,  1125,  1118,  1713,  3025

		
length		dd	100
lstMin		dd	0
estMed		dd	0
lstMax		dd	0
lstSum		dd	0
lstAve		dd	0

negCnt		dd	0
negSum		dd	0
negAve		dd	0

sixCnt		dd	0
sixSum		dd	0
sixAve		dd	0

first		dd  0
lastElem    dd  0
mid1        dd  0
mid2        dd  0      

; use to declare unintialized var
section .bss


; main 
section .text
global _start
_start:

    ; double word - 32 bits
    ; done- 1/ min/max = loop whole list find min & max 
    ; done -median 2/ find sum/ average/ median value
    ; median will be computed by summing the first, last, and two middle values and then dividing
    ; by 4.
    ; done- sum/count/average of (-)
    ; done- sum/count/average % 6 == 0

    ; use idiv/imul
    ; JG/JGE/JL/JLE 
    ; jg = if op1 > op2 / ja
    ; jge = op1 >= op2 /jae
    ; jl = op1 < 2 /jb
    ; jle = 1 <= 2 /jbe
    ; will have to use cmp 
    ; cmp rax, 5/ ecx, edx/ ax, word[wNum]

    ;get size /2
    mov eax, dword[length]
    cdq
    mov r9d, 2
    idiv r9d

    ;get mid2
    mov r8d, dword[lst + eax * 4]
    mov dword[mid2], r8d
    ;get mid1
    dec eax
    mov r8d, dword[lst + eax * 4]
    mov dword[mid1], r8d

    ; put 1st value into eax
    mov eax, dword [lst]
    ; min = max = eax = 1st val
    mov dword [lstMin], eax 
    mov dword [lstMax], eax

    ; 1st value
    mov dword [first], eax

    ; make sure sum is 0
    mov dword [lstSum], 0

    ; size of list
    mov ecx, dword [length]
    
    mov rsi, 0

calLoop:
    ; to acces next elem -> like i++
    ; then put it into eax
    mov eax, dword[lst + rsi * 4] 
    add dword [lstSum], eax

    ; this check for min
    cmp eax, dword [lstMin]
    jge notMin ;if not min
    mov dword [lstMin], eax ; if min -> put ot var

notMin:
    cmp eax, dword [lstMax] ; check for max
    jle notMax
    mov dword [lstMax], eax ; if max 

notMax:
    mov r8d, eax ;get last elem
    inc rsi  
    loop calLoop

    ;after done list loop

    ;calculate median 
    ;r8d hold last elem
    ;mov dword[lastElem], r8d ;put last elem to var
    add r8d, dword[first]
    add r8d, dword[mid1]
    add r8d, dword[mid2]
    cdq 
    mov r9d, 4   
    mov eax, r8d   
    idiv r9d  
    mov dword[estMed], eax
    ;clear regs 
    mov eax, 0  
    mov r8d, 0
    mov r9d, 0

; calculate average for lst
    
    ; put 1st value into eax
    mov eax, dword [lstSum]
    mov edx, 0 ; edx will hold rem so need to clear it
    idiv dword[length]
    mov dword[lstAve], eax
    mov eax, 0 ; clear regs

; use another loop to avoid confusion
; start to calcualte for (-) and %
    mov eax, dword [lst]
    ; set counter to size of list
    ;for(int i = size; i > 0; i--)
    ;mov rsi, dword[length2]

    ; make sure the var is 0
    mov dword[negSum], 0
    mov dword[sixSum], 0

    ;test counter
    mov rsi, 0

sideLoop:
    ; addition check as it this loop cause seg  
    cmp esi, dword[length]
    jae done
    ; to acces next elem -> like i++
    ; then put it into eax
    mov eax, dword[lst + rsi * 4] 

    ;check for % 6
    mov r8d, eax ; temp regs to hold value because eax val is changing
    mov ebx, 6 ;cant div immediate so have to put into reg
    cdq ; exntend
    idiv ebx  ; this change eax value
    mov eax, r8d ;set the value back to eax
    cmp edx, 0
    ; if eax % 6 == 0 -> divisible by 6
    je divisible6

    ;check for negative
    cmp eax, 0
    jl negative

    ; if none -> go to next elem
    jmp loopAgain

divisible6:
    ; cal sum for % 6
    add dword[sixSum], eax
    inc dword[sixCnt]

    ;check for negative
    cmp eax, 0 
    jl negative 
    ; if not -> go to next
    jmp loopAgain

negative:
    ; cal sum for negative
    add dword [negSum], eax
    inc dword[negCnt]
    jmp loopAgain

loopAgain:
    ; this is another way to do loop
    ;those 3 lines == loop synntax;
    ; due to using loop -> cause seg -> use this
    inc rsi
    loop sideLoop

done:
    ; after done loop -> calculate average 

    mov eax, dword[negSum]
    cdq
    idiv dword[negCnt]
    mov dword[negAve], eax

    mov eax, dword[sixSum]
    cdq
    idiv dword[sixCnt]
    mov dword[sixAve], eax

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall