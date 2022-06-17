; Program Description: This program will demonstrate mastery over arithmetic operations in x86 assembly.

section .data
; System service call values
SERVICE_EXIT equ 60
SERVICE_WRITE equ 1
EXIT_SUCCESS equ 0
STANDARD_OUT equ 1
NEWLINE equ 10

programDone db "Program Done.", NEWLINE 
stringLength dq 14

;	Example variables
byteExample1 db 0x10
byteExample2 db 0x32
byteExample3 db 0x00
byteExample4 db 100
wordExample1 dw 0x0002
wordExample2 dw 0x00F0
doubleExample1 dd 0x10101010
doubleExample2 dd 0
 
;	Data variables
doubleVariable2 dd 0x89ABCDEF
byteVariable3 db 250
doubleVariable4 dd 0x12345678
doubleVariable5 dd 0xC1240000
wordVariable6a dw -42
wordVariable6b dw 40
quadVariable8a dq 0xFFFFFFFFFFFFFFFF
quadVariable8b dq 0xF0F0F0F0F0F0F0F0
doubleVariable9 dd 0xC2860000
wordVariable9 dw 0x1234
byteVariable10a db 0x02
byteVariable10b db 0xF0
doubleVariable11a dd 40008
doubleVariable11b dd 12
quadVariable12a dq 0xFFFFFFFFFFFFFFFF
quadVariable12b dq 0x00000000000000F1
byteVariable13 db 0x0A
byteVariable14a db 0xF0
byteVariable14b db 0x02
doubleVariable15 dd 80009
wordVariable15 dw 3050
wordVariable16a dw 0x0497
wordVariable16b dw 0x0002
byteVariable17 db 0xB8
wordVariable18a dw 0x00FF
wordVariable18b dw 0xFFFA
wordVariable18c dw 0x0005
doubleVariable19a dd 0xB0040030
doubleVariable19b dd 0xC0000000
quadVariable20 dq 0x000000039ABCDEF0
doubleVariable20 dd 0xFEDCBA98
   
;	Answer variables
doubleAnswer1 dd 0xFFFFFFFF
doubleAnswer2 dd 0x00000000
quadAnswer3 dq 0xFFFFFFFFFFFFFFFF
quadAnswer4 dq 0xFFFFFFFFFFFFFFFF
quadAnswer5 dq 0
wordAnswer6 dw 0x00000000
doubleAnswer7 dd 0x0FFFFFFD
quadAnswer8 dq 0xFFFFFFFFFFFFFFFF
doubleAnswer9 dd 0x00000000
wordAnswer10 dw 0
quadAnswer11 dq 0
doubleQuadAnswer12 ddq 0
wordAnswer13 dw 0xFFFF
byteAnswer14 db 0x00
byteRemainder14 db 0x00
wordAnswer15 dw 0x0000
wordRemainder16 dw 0xFFFF   
byteAnswer17 db 0x00
wordAnswer18 dw 0x0000
doubleAnswer19 dd -1
doubleRemainder19 dd -1
doubleRemainder20 dd 0x00000000

section .text
global _start
_start:

;=====MOV=====
;  	Moving an immediate value into a register
	mov ax, 0
;  	Copying a value from one register to another
	mov ecx, ebx
;	Copying a value from a variable to a register
	mov edx, dword[doubleExample1]
	
;	1. doubleAnswer1 = 400000
;	copy number into double word type name doubleAnswer1
	mov dword[doubleAnswer1], 400000
;	2. doubleAnswer2 = doubleVariable2
;	move dword var into 32 bits register 
;	then move that register into answer var
	mov eax, dword[doubleVariable2]
	mov dword[doubleAnswer2], eax 

;=====MOVZX=====
;	3. quadAnswer3 = byteVariable3
;	extend 8 to 32 bits using movzx and copy use mov
	movzx rax, byte[byteVariable3]
	mov qword[quadAnswer3], rax
;	4. quadAnswer4 = doubleVariable4
;	copy 32 bits 2x word into 32 bits register
;	then copy 64 bits reg into answer var
	mov eax, dword[doubleVariable4]
	mov qword[quadAnswer4], rax
;=====MOVSX=====
;	5. quadAnswer5 = doubleVariable5
;	extend signed 32 bits into 64 using movsxd
;	then move that reg into answer var
	movsxd rax, dword[doubleVariable5]
	mov qword[quadAnswer5], rax
;=====ADD=====
;  Adding two byte values together
	mov al, byte[byteExample1]
	add al, byte[byteExample2]
	mov byte[byteExample3], al

;	6. wordAnswer6 = wordVariable6a + wordVariable6b
;	copy word type - 16bits into 16 bits register
;	then add and sopy into answer var
	mov ax, word[wordVariable6a]
	add ax, word[wordVariable6b]
	mov word[wordAnswer6], ax
;	7. doubleAnswer7 = doubleAnswer7 + 2
	add dword[doubleAnswer7], 2  

;=====SUB=====
;	8. quadAnswer8 = quadVariable8a - quadVariable8b
;	copy 64 bits into 64 bits register
;	subtarct it and copy into answer var
	mov rax, qword[quadVariable8a]
	sub rax, qword[quadVariable8b]
	mov qword[quadAnswer8], rax
;	9. doubleAnswer9 = doubleVariable9 - wordVariable9
;	extend the size of word- 16 into double- 32
;	then copy double- 32 into another register
;	add tehm and copy to answer var
	movzx ebx, word[wordVariable9]
	mov eax, dword[doubleVariable9]
	sub eax, ebx
	mov dword[doubleAnswer9], eax

;=====INC=====
;	Using inc to increment a register
	inc ax

;=====DEC=====
;	Using dec to decrement a variable
	dec byte[byteExample4]
	
;=====MUL=====
;	Multiplying two words and storing the parts into a dword sized variable
	mov ax, word[wordExample1]
	mul word[wordExample2]
	mov word[doubleExample2], ax ; Stores the lower bits
	mov word[doubleExample2+2], dx	; Stores the upper bits

;	10. wordAnswer10 = byteVariable10a x byteVariable10b
;	copy 8 bits into 8 bts register
;	multiple it and then copy it into word- 16 bits answer
	mov al, byte[byteVariable10a]
	mul byte[byteVariable10b]  
	mov word[wordAnswer10], ax
;	11. quadAnswer11 = doubleVariable11a x doubleVariable11b
;	copy dword-32 var into register
;	mul it with another var and copy that 32 bits register into ans
;	after that, becasue 2x and 2x so have to extend the size for quad-64 bits
	mov eax, dword[doubleVariable11a]
	mul dword[doubleVariable11b]
	mov dword[quadAnswer11], eax   
	mov dword[quadAnswer11 + 4], edx
;	12. doubleQuadAnswer12 = quadVariable12a x quadVariable12b
;	copy quad-64 into 64 register
;	mul it with another var
;	then move the reslt into 64 bit var but have to put it into upper bits
	mov rax, qword[quadVariable12a]
	mul qword[quadVariable12b]
	mov qword[doubleQuadAnswer12], rax ;lower bits
	mov qword[doubleQuadAnswer12 + 8], rdx ;upper bits

;=====IMUL=====
;	13. wordAnswer13 = byteVariable13 x -3
;	extend from 8 to 16 bits
;	mul signed by -3   
;	then copy into answer var
	movzx ax, byte[byteVariable13]
	imul ax, -3
	mov word[wordAnswer13], ax

;=====DIV=====

;	14. byteAnswer14 = byteVariable14a / byteVariable14b
;	      byteRemainder14 =  byteVariable14a % byteVariable14b
;	initialize ax with 0 and then move byte- 8 bits var into 8 bits register
;	then div with another variable
;	put lower register contain answer into ans var 8 bits
;	move reminder from upper bits
	mov ax, 0
	mov al, byte[byteVariable14a]
	div byte[byteVariable14b]
	mov byte[byteAnswer14], al   
	mov byte[byteRemainder14], ah
;	15. wordAnswer15 = doubleVariable15 / wordVariable15
;	copy word-8 bits into 8 bits register 
;	copy the upper bits into dx   
;	div the values
;	then move ax into 8 bits answer
	mov ax, word[doubleVariable15]
	mov dx, word[doubleVariable15 + 2] 
	div word[wordVariable15]
	mov word[wordAnswer15], ax ;upper bits
;	16. wordRemainder16 = wordVariable16a % wordVariable16b
;	copy 0 into upper bits of 8 bits
;	then move 8 bits var into 8 bits registers
;	div it with another variable
;	move the upper bits into ans variable
;	init dx-upper bits with 0   
;	then copy 16 bits word to ax- lower bits 8 bits
;	div it with another variable
;	copy upper bits into ans variable
	mov dx, 0  
	mov ax, word[wordVariable16a]
	div word[wordVariable16b]
	mov word[wordRemainder16], dx
;=====IDIV=====

;	17. byteAnswer17 = byteVariable17 / 5
;	copy 8 bits reg into lower bits 
;	extend byte to word 
;	copy 5 into temp register then divide then move it into var ans
	mov al, byte[byteVariable17]
	cbw 
	mov bl, 5
	idiv bl
	mov byte[byteAnswer17], al
;	18. wordAnswer18 = (wordVariable18a x wordVariable18b) / wordVariable18c
;	copy 16 bits reg into lower bits 
;	mul and div it
;	copy lower bits reg into ans var
	mov ax, word[wordVariable18a]
	imul word[wordVariable18b]
	idiv word[wordVariable18c]
	mov word[wordAnswer18], ax

;	19. doubleAnswer19 = doubleVariable19a / doubleVariable19b
;	      doubleRemainder19 = doubleVariable19a % doubleVariable19b
;	copy 32 bits into lower bits register
;	extend 32 to 64
;	div and move lower bits reg into ans var and upper bits into remainder var
	mov eax, dword[doubleVariable19a]
	cdq
	idiv dword[doubleVariable19b]
	mov dword[doubleAnswer19], eax  
	mov dword[doubleRemainder19], edx
	;fix
;	20. doubleRemainder20 = quadVariable20 % doubleVariable20
;	copy 32 bits into lower bits register
;	copy the upper bits into upper register
;	div and move upper bits into remainder var
	mov eax, dword[quadVariable20]
	mov edx, dword[quadVariable20 + 4]
	idiv dword[doubleVariable20]
	mov dword[doubleRemainder20], edx

endProgram:
; 	Outputs "Program Done." to the console
	mov rax, SERVICE_WRITE
	mov rdi, STANDARD_OUT
	mov rsi, programDone
	mov rdx, qword[stringLength]
	syscall

; 	Ends program with success return value
	mov rax, SERVICE_EXIT
	mov rdi, EXIT_SUCCESS
	syscall