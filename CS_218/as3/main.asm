
; Program Description: Display the total pizzas needed by each department, 
; the total pizzas required overall, and the average pizzas required per department 
; by work with arrays of data, loops, and conditionals.

section .data

; ===System service call values===
SERVICE_EXIT equ 60
SERVICE_WRITE equ 1
EXIT_SUCCESS equ 0
STANDARD_OUT equ 1
NEWLINE equ 10
programDone dw "Program Done:", NEWLINE 
stringLength dw 13

; ===Const Data variables===
DEP_SIZE equ 10
SLICES_PERSON equ 3
SLICES_PIZZA equ 8

; ===Array variable===
people dw 43, 217, 19, 1036, 407, 8 ,806, 560, 1, 96

section .bss

; ===Answer variable array + vars===
    total resw 10
    sum resw 1 
    average resw 1  

section .text
global _start
_start:

; ===Calculate total pizzas for each department===

mov cx, DEP_SIZE 	; DEP_SIZE counter 
mov rbx, 0 			; index = 0

; ===Loop for calculate pizzas for each department and sum===

calculationLoop:

; total pizza = number of people * 3 / 8

mov r8w, SLICES_PERSON		; copy 3 into reg
mov r9w, SLICES_PIZZA 		; copy 8 into reg
mov ax, word[people + (rbx * 2)] 	; get people[rbx]
mul r8w
div r9w 		; dx:ax = dx- remainder

cmp dx, 0 		; compare reminder with 0
jne Add1 		; if not 0 then go to Add1
dec ax			; extra check in case something gone wrong

Add1: 			; Add 1 when remainder != 0
    inc ax 		; increase 1 cause pizza can not be half or something

mov word[total + (rbx * 2)], ax		; copy into new arr
; ===Calculate Sum===

add word[sum], ax

inc rbx 		; increase index
loop calculationLoop 		; loop again

; Calculate average pizzas

mov ax, 0 		; clear the reg
mov ax, word[sum] 		; then copy val into reg
mov r8w, DEP_SIZE 		; copy 10 into reg
div r8w
mov word[average], ax

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
