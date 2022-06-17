
;  Assignment: 5
;  Description:

; use to declare intialized var

section	.data
; -----;
;  Define constants.

NULL         equ 	0 ; null pointer
TRUE         equ 	1 ; boolean true
FALSE        equ 	0 ; boolean false
EXIT_SUCCESS equ 	0 ; successful termination
SYS_exit    equ 	60 ; exit syscall

; ----- PROGRAM VARIABLES
aSides db 10, 14, 13, 37, 54 ; array of sides
    db 31, 13, 20, 61, 36 ;byte
    db 14, 53, 44, 19, 42
    db 27, 41, 53, 62, 10
    db 19, 28, 14, 10, 15
    db 15, 11, 22, 33, 70
    db 15, 23, 15, 63, 26
    db 24, 33, 10, 61, 15
    db 14, 34, 13, 71, 81
    db 38, 73, 29, 17
cSides dd 1145, 1135, 1123, 1123, 1123 ; counter for sides
    dd 1254, 1454, 1152, 1164, 1542 ;double word
    dd 1353, 1457, 1182, 1142, 1354
    dd 1364, 1134, 1154, 1344, 1142
    dd 1173, 1543, 1151, 1352, 1434
    dd 1355, 1037, 1123, 1024, 1453
    dd 1134, 2134, 1156, 1134, 1142
    dd 1267, 1104, 1134, 1246, 1123
    dd 1134, 1161, 1176, 1157, 1142
    dd 1153, 1193, 1184, 1142
pSides dw 133, 114, 173, 131, 115 ; pointer for sides
    dw 164, 173, 174, 123, 156 ;word size
    dw 144, 152, 131, 142, 156
    dw 115, 124, 136, 175, 146
    dw 113, 123, 153, 167, 135
    dw 114, 129, 164, 167, 134
    dw 116, 113, 164, 153, 165
    dw 126, 112, 157, 167, 134
    dw 117, 114, 117, 125, 153
    dw 123, 173, 115, 106
qSides dd 2183, 2372, 3231, 3121, 2153 ; quadratic sides
    dd 3254, 1342, 5341, 4158, 1523 ;double word
    dd 2125, 3133, 7384, 2274, 2114
    dd 5645, 1371, 3123, 3317, 1923
    dd 1634, 2334, 1156, 4164, 2742
    dd 3453, 4153, 2284, 2142, 3144
    dd 5345, 5130, 1423, 2113, 4123
    dd 2434, 1334, 3056, 3184, 1242
    dd 2353, 2153, 2284, 1142, 2334
    dd 3145, 1934, 2123, 4113
length dd 49 ; length of array
aMin dd 0 ;min of array for areas
aeMed dd 0 ;median for areas array
aMax dd 0 ; maximum value of array
aSum dd 0 ; sum of array
aAve dd 0 ; average value of array
pMin dd 0 ; minimum value of pointer
peMed dd 0 ; median value of pointer
pMax dd 0 ; maximum value of pointer
pSum dd 0 ; sum of pointer
pAve dd 0 ; 

;extra varibles for median  
firstArea dd 0   
lastArea dd 0
middleArea1 dd 0
middleArea2 dd 0

firstPeri dd 0
lastPeri dd 0
middlePeri1 dd 0
middlePeri2 dd 0

; Uninitialized data
section .bss
; 32 bit
kiteAreas resd 49 ;use this one to store array for areas
kitePerims resd 49 ;use this one to store array for perimeters

    ; db 8b, dw 16b, dd 32b, dq 64b
    ; unsorted list, estimate median value
    ; list length is odd, computed by summing first, last, and middle values and then
    ; dividing by 3

    ; DO NOT CHANGE the size types of the provided data sets. 
    ; All Unsigned data
    ; DIV/MUL will be used also,
    ; CDW/CWD/CDQ would NOT be used -> for signed data
    ; JA/JB/JAE/JBE must be used -> unsigned data
    ; 1/area = (pSides[n] * qSides[n]) / 2 -> done
    ; 2/perimeter = 2 * (aSides[n] * cSides[n]) -> done
    ; 3/min, max, middle, sum, and  average of areas and perimeter
    ; pSides[] is word
    ; qSides[] is doubleWord
    ; aSides[] is byte
    ; cSides[] is doubleWord
section .text
global _start
_start:

; step 1 = -> calculate area first 
; area = (pSides[n] * qSides[n]) / 2
; pSides[] is word - dw
; qSides[] is doubleWord - dd
; db = 8, dw = 16, dd = 32, dq = 64

; set up counter for the loop
    mov ecx, dword[length] ;length counter
    mov rsi, 0 ; loop counter/index

    calculateLoop:
        ;use this to calculate
        mov r10d, 2 ; mov 2 into register to div 
        ;calculate areas
        ; the array for the areas is 32 bits - dd
        ; will need to adjust size (extend)
        ; word so * 2 (2 is offset)
        ; dword so * 4
        movzx r9d, word[pSides + rsi * 2] ;psides[i]
        mov r8d, dword[qSides + rsi * 4] ; qSides[i]
        mov eax, r9d ; mov the pSide into 32 register/eax
        mul r8d ; pSides[n] * qSides[n]
        div r10d ;(pSides[n] * qSides[n]) / 2
        ;* 4 because it is 32 bits
        mov dword[kiteAreas + rsi * 4], eax ; mov result into var

        ;clear registers
        mov r9d, 0
        mov r8d, 0
        mov eax, 0

        ;step 2: calculate perimeters
        ;2 * (aSides[n] * cSides[n])
        ;extend the size for aSides because aSides is byte
        ;by using movzx
        movzx r9d, byte[aSides + rsi] ;because byte -> no * 
        mov r8d, dword[cSides + rsi * 4] ; for cSides -> no need to use movzx because same size
        mov eax, r9d ;mov aSides into eax to * and /
        mul r8d ;aSides[n] * cSides[n]
        mul r10d ;2 * (aSides[n] * cSides[n])
        mov dword[kitePerims + rsi * 4], eax

        inc rsi ;increment the counter/index
        loop calculateLoop ;end of the loop

    ; step 3: min, max, middle/median, sum, and  average of areas and perimeter
    ;to do this -> need another loop 
    
    ;clear registers
    mov rsi, 0
    mov r9d, 0
    mov r8d, 0
    mov eax, 0
    mov r10d, 0

    ;set up 2nd loop for step 3
    mov rsi, 0
    mov ecx, dword[length] ;length counter

    ;set up for min, max, sum, average
    mov eax, dword[kiteAreas]
    mov dword[aMin], eax
    mov dword[aMax], eax

    ;get 1st value of areas and put it in variable
    mov dword[firstArea], eax

    mov eax, dword[kitePerims]   
    mov dword[pMin], eax
    mov dword[pMax], eax

    ;get 1st value of perimeter and put it in variable
    mov dword[firstPeri], eax

    ;make sure that the variable is 0
    mov dword[aSum], 0
    mov dword[pSum], 0

    secondLoop: 
        ;calculate sum of areas array
        mov eax, dword[kiteAreas + rsi * 4]
        add dword[aSum], eax   

        ;check for min (areas)
        cmp eax, dword[aMin] ;comape to see if eax < next one
        jae notNewAreaMin ; jae mean eax > next one
        mov dword[aMin], eax ;mov current value into var

        notNewAreaMin: 
            ;check for max (areas)
            cmp eax, dword[aMax]
            jbe notNewAreaMax
            mov dword[aMax], eax
        
        notNewAreaMax:
            ;this will do sum of perimeter 
            mov eax, dword[kitePerims + rsi * 4]
            add dword[pSum], eax  
            
            ;this will check for min of perimeter
            cmp eax, dword[pMin]
            jae notNewPeriMin
            mov dword[pMin], eax

        notNewPeriMin:
            ;this will check for max perimeter
            cmp eax, dword[pMax]
            jbe notNewPeriMax
            mov dword[pMax], eax

        notNewPeriMax:
            ;this will conclude the min/max/sum
            inc rsi 
            loop secondLoop

    ;calculate average
    ;this is for areas
    mov eax, dword[aSum] ;take value of areas sum into eax
    mov edx, 0 ;make sure that upper bits is clear
    div dword[length] ;sum /length 
    mov dword[aAve], eax ; move result to variable

    ;this is for perimeter
    mov eax, dword[pSum]
    mov edx, 0
    div dword[length]
    mov dword[pAve], eax

    ;calculate median value
    ;estimated median will be computed by summing the first, 
    ;last, and middle values and then dividing by 3

    ;get last values for both of the array 
    mov eax, dword[kiteAreas + 48 * 4]
    mov dword[lastArea], eax

    mov eax, dword[kitePerims + 48 * 4]
    mov dword[lastPeri], eax

    ;div length by 2 to find mid elems
    mov eax, dword[length]
    mov edx, 0
    mov r10d, 2 
    div r10d ;-> == length/2

    ;get middle elems for areas
    mov r9d, dword[kiteAreas + eax * 4]
    mov dword[middleArea1], r9d

    ;get middle eleme for perimeter
    mov r8d, dword[kitePerims + eax * 4]
    mov dword[middlePeri1], r8d

    ;set up 3 for dividing
    mov r10d, 3

    ;calculate median for areas 
    mov eax, dword[firstArea]
    add eax, dword[lastArea]
    add eax, dword[middleArea1]
    mov edx, 0
    div r10d
    mov dword[aeMed], eax

    ;calculate median for peri
    mov eax, dword[firstPeri]
    add eax, dword[lastPeri]
    add eax, dword[middlePeri1]
    mov edx, 0
    div r10d
    mov dword[peMed], eax

last:
    mov rax, SYS_exit
    mov rdi, EXIT_SUCCESS
