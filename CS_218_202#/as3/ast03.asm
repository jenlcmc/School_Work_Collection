; *****************************************************************
;  Assignment: 3
;  Description: Simple assembly example


; -----
;  Write a simple assembly language program to compute the
;  the provided formulas.

;  Focus on learning basic arithmetic operations
;  (add, subtract, multiply, and divide).
;  Ensure understanding of sign and unsigned operations.

; *****************************************************************
;  Data Declarations (provided).

section	.data
; -----
;  Define constants.

NULL		equ	0			; end of string

TRUE		equ	1
FALSE		equ	0

EXIT_SUCCESS	equ	0			; Successful operation
SYS_exit	equ	60			; call code for terminate

; -----
;  Assignment #3 data declarations

; byte data
bNum1		db	11
bNum2		db	15
bNum3		db	26
bNum4		db	37
bNum5		db	33
bNum6		db	-17
bNum7		db	-29
bNum8		db	-40
bAns1		db	0
bAns2		db	0
bAns3		db	0
bAns4		db	0
bAns5		db	0
bAns6		db	0
bAns7		db	0
bAns8		db	0
bAns9		db	0
bAns10		db	0
wAns11		dw	0
wAns12		dw	0
wAns13		dw	0
wAns14		dw	0
wAns15		dw	0
bAns16		db	0
bAns17		db	0
bAns18		db	0
bRem18		db	0
bAns19		db	0
bAns20		db	0
bAns21		db	0
bRem21		db	0

; word data
wNum1		dw	229
wNum2		dw	467
wNum3		dw	1738
wNum4		dw	2210
wNum5		dw	375
wNum6		dw	-234
wNum7		dw	-361
wNum8		dw	-418
wAns1		dw	0
wAns2		dw	0
wAns3		dw	0
wAns4		dw	0
wAns5		dw	0
wAns6		dw	0
wAns7		dw	0
wAns8		dw	0
wAns9		dw	0
wAns10		dw	0
dAns11		dd	0
dAns12		dd	0
dAns13		dd	0
dAns14		dd	0
dAns15		dd	0
wAns16		dw	0
wAns17		dw	0
wAns18		dw	0
wRem18		dw	0
wAns19		dw	0
wAns20		dw	0
wAns21		dw	0
wRem21		dw	0

; double-word data
dNum1		dd	13456789
dNum2		dd	31342
dNum3		dd	219815
dNum4		dd	61569
dNum5		dd	2617
dNum6		dd	-1345
dNum7		dd	-2733
dNum8		dd	-4256
dAns1		dd	0
dAns2		dd	0
dAns3		dd	0
dAns4		dd	0
dAns5		dd	0
dAns6		dd	0
dAns7		dd	0
dAns8		dd	0
dAns9		dd	0
dAns10		dd	0
qAns11		dq	0
qAns12		dq	0
qAns13		dq	0
qAns14		dq	0
qAns15		dq	0
dAns16		dd	0
dAns17		dd	0
dAns18		dd	0
dRem18		dd	0
dAns19		dd	0
dAns20		dd	0
dAns21		dd	0
dRem21		dd	0

; quadword data
qNum1		dq	24656793
qNum2		dq	115732
qNum3		dq	1526241
qNum4		dq	254879
qNum5		dq	317517
qNum6		dq	-222147
qNum7		dq	-216517
qNum8		dq	-445758
qAns1		dq	0
qAns2		dq	0
qAns3		dq	0
qAns4		dq	0
qAns5		dq	0
qAns6		dq	0
qAns7		dq	0
qAns8		dq	0
qAns9		dq	0
qAns10		dq	0
dqAns11		ddq	0
dqAns12		ddq	0
dqAns13		ddq	0
dqAns14		ddq	0
dqAns15		ddq	0
qAns16		dq	0
qAns17		dq	0
qAns18		dq	0
qRem18		dq	0
qAns19		dq	0
qAns20		dq	0
qAns21		dq	0
qRem21		dq	0

; *****************************************************************

section	.text
global _start
_start:

; ----------------------------------------------
; Byte Operations

; unsigned byte additions
;	bAns1  = bNum1 + bNum4 (11 +37)
;	bAns2  = bNum2 + bNum4 (15 + 37)
;	bAns3  = bNum3 + bNum3 (26 + 26)

	mov al, byte [bNum1]
	add al, byte[bNum4]
	mov byte [bAns1], al
	mov al, 0 ; clear al

	mov al, byte [bNum2]
	add al, byte [bNum4]
	mov byte [bAns2], al
	mov al, 0 ; clear al

	mov al, byte [bNum3]
	add al, byte [bNum3]
	mov byte [bAns3], al
	mov al, 0 ; clear al

; -----
; signed byte additions
;	bAns4  = bNum5 + bNum6
;	bAns5  = bNum7 + bNum8
	mov al, byte [bNum5]
	add al, byte [bNum6]
	mov byte [bAns4], al
	mov al, 0		;clear
 
	; check
	mov al, byte [bNum7]
	add al, byte [bNum8]
	mov byte [bAns5], al
	mov al, 0		;clear
; -----
; unsigned byte subtractions
;	bAns6  = bNum4 - bNum3
;	bAns7  = bNum3 - bNum1
;	bAns8  = bNum2 - bNum1

	mov al, byte [bNum4]
	sub al, byte [bNum3]
	mov byte [bAns6], al
	mov al, 0		;clear

	mov al, byte [bNum3]
	sub al, byte [bNum1]
	mov byte [bAns7], al
	mov al, 0		;clear

	mov al, byte [bNum2]
	sub al, byte [bNum1]
	mov byte [bAns8], al
	mov al, 0		;clear
; -----
; signed byte subtraction
;	bAns9  = bNum6 - bNum6
;	bAns10 = bNum8 - bNum7
; signed byte subtractio
	mov al, byte [bNum6]
	sub al, byte [bNum6]
	mov byte [bAns9], al
	mov al, 0		;clear

	mov al, byte [bNum8]
	sub al, byte [bNum7]
	mov byte [bAns10], al
	mov al, 0		;clear

; -----
; unsigned byte multiplication
;	wAns11  = bNum1 * bNum2
;	wAns12  = bNum3 * bNum4
;	wAns13  = bNum3 * bNum3
	mov al, byte [bNum1]
	mul byte [bNum2]
	mov word[wAns11], ax
	mov al, 0		;clear

	mov al, byte [bNum3]
	mul byte [bNum4]
	mov word [wAns12], ax
	mov al, 0		;clear

	mov al, byte [bNum3]
	mul byte [bNum3]
	mov word [wAns13], ax
	mov al, 0
; -----
; signed byte multiplication
;	wAns14  = bNum5 * bNum8
;	wAns15  = bNum6 * bNum7
; signed byte multiplication

	mov al, byte [bNum5] 
	imul byte [bNum8]
	mov word [wAns14], ax
	mov al, 0		;clear

	;signed byte multiplication
	mov al, byte [bNum6]
	imul byte [bNum7]
	mov word [wAns15], ax
	mov al, 0		;clear

; above this line is all correct
; prob need to check for divison as it all f up
; the other one seem correct as if correct 
; for byte then other one should be too
; -----
; unsigned byte division
;	bAns16 = bNum4 / bNum2
;	bAns17 = bNum3 / bNum1
;	bAns18 = wNum4 / bNum1
;	bRem18 = wNum4 % bNum1
; unsigned byte division

	; need to chekc this again
	mov rax, 0
	mov al, byte [bNum4] ; this hold correct
	div byte [bNum2] ; not getting correct result
	mov byte [bAns16], al
	mov al, 0		;clear

	mov al, byte [bNum3] ; f up too
	div byte [bNum1]
	mov byte [bAns17], al
	mov ax, 0		;clear

	; ** 
	mov ax, word[wNum4]
	div byte[bNum1]
	mov byte[bAns18], al
	mov byte[bRem18], ah


; -----
; signed byte division
;	bAns19 = bNum5 / bNum7
;	bAns20 = bNum8 / bNum6
;	bAns21 = wNum7 / bNum6
;	bRem21 = wNum7 % bNum6
; signed byte division
	mov al, byte [bNum5]
	cbw
	idiv byte [bNum7]
	mov byte [bAns19], al
	mov al, 0		;clear

	mov al, byte [bNum8]
	cbw
	idiv byte [bNum6]
	mov byte [bAns20], al
	mov ax, 0		;clear

	mov ax, word[wNum7]
	idiv byte[bNum6]
	mov byte[bAns21], al
	mov byte[bRem21], ah

	;correct

; *****************************************
; Word Operations

; -----
; unsigned word additions
;	wAns1  = wNum2 + wNum3
;	wAns2  = wNum1 + wNum4
;	wAns3  = wNum2 + wNum1
; unsigned word additions
	mov ax, word [wNum2]
	add ax, word [wNum3]
	mov word [wAns1], ax
	mov ax, 0		;clear

	mov ax, word [wNum1]
	add ax, word [wNum4]
	mov word [wAns2], ax
	mov ax, 0		;clear

	mov ax, word [wNum2]
	add ax, word [wNum1]
	mov word [wAns3], ax
	mov ax, 0		;clear


; -----
; signed word additions
;	wAns4  = wNum5 + wNum8
;	wAns5  = wNum6 + wNum7
; signed word additions
	mov ax, word [wNum5]
	add ax, word [wNum8] 
	mov word [wAns4], ax
	mov ax, 0		;clear

	mov ax, word [wNum6]
	add ax, word [wNum7]
	mov word [wAns5], ax
	mov ax, 0		;clear


; -----
; unsigned word subtractions
;	wAns6  = wNum4 - wNum1
;	wAns7  = wNum3 - wNum2
;	wAns8  = wNum2 - wNum1
; unsigned word subtractions
	mov ax, word [wNum4]
	sub ax, word [wNum1]
	mov word [wAns6], ax
	mov ax, 0		;clear

	mov ax, word [wNum3]
	sub ax, word [wNum2]
	mov word [wAns7], ax
	mov ax, 0		;clear

	mov ax, word [wNum2]
	sub ax, word [wNum1]
	mov word [wAns8], ax
	mov ax, 0		;clear


; -----
; signed word subtraction
;	wAns9  = wNum5 - wNum7
;	wAns10  = wNum8 - wNum6
; signed word subtraction
	mov ax, word [wNum5]
	sub ax, word [wNum7]
	mov word [wAns9], ax
	mov ax, 0		;clear

	mov ax, word [wNum8]
	sub ax, word [wNum6]
	mov word [wAns10], ax
	mov ax, 0		;clear

; -----
; unsigned word multiplication
;	dAns11 = wNum1 * wNum3
;	dAns12  = wNum4 * wNum1
;	dAns13  = wNum2 * wNum2
; unsigned word multiplication
; when multi, it can cause overflow -> have to extend it little bit
	mov ax, word [wNum1]
	mul word [wNum3]
	mov word [dAns11], ax ; this will hold lower bit of result
	mov word [dAns11 + 2], dx ; hold upper bit of result
	mov ax, 0		;clear

	; same with above
	mov ax, word [wNum4]
	mul word [wNum1]
	mov word [dAns12], ax ; 8 bits
	mov word [dAns12 + 2], dx ;dx still 8 bits
	mov ax, 0		;clear

	; same with above
	mov ax, word [wNum2]
	mul word [wNum2]
	mov word [dAns13], ax
	mov word [dAns13 + 2], dx
	mov ax, 0

; -----
; signed word multiplication
;	dAns14  = wNum6 * wNum7
;	dAns15  = wNum5 * wNum8
; signed word multiplication
	mov ax, word [wNum6]
	imul word [wNum7]
	mov word [dAns14], ax
	mov word[dAns14 + 2], dx
	mov ax, 0		;clear

	mov ax, word [wNum5]
	imul word [wNum8]
	mov word [dAns15], ax
	mov word [dAns15  + 2], dx
	
	mov ax, 0		;clear
; -----
; unsigned word division
;	wAns16 = wNum4 / wNum2
;	wAns17 = wNum3 / wNum1
;	wAns18 = dNum4 / wNum3
;	wRem18 = dNum4 % wNum3
; unsigned word division
	mov ax, word [wNum4]
	div word [wNum2]
	mov word [wAns16], ax
	mov ax, 0		;clear

	mov ax, word [wNum3] 
	div word [wNum1]
	mov word [wAns17], ax
	mov ax, 0		;clear

	mov ax, word [dNum4]
	mov dx, word [dNum4 + 2] ; extend the size because dword
	div word [wNum3]
	mov word [wAns18], ax
	mov word [wRem18], dx
	mov ax, 0		;clear

; -----
; signed word division
;	wAns19 = wNum5 / wNum7
;	wAns20 = wNum7 / wNum6
;	wAns21 = dNum8 / wNum6
;	wRem21 = dNum8 % wNum6

	mov ax, word [wNum5]
	cwd
	idiv word [wNum7]
	mov word [wAns19], ax
	mov ax, 0

	mov ax, word [wNum7]
	cwd
	idiv word [wNum6]
	mov word [wAns20], ax
	mov ax, 0		;clear

	mov ax, word [dNum8]
	mov dx, word [dNum8 + 2] ; extend the size because dword
	idiv word [wNum6]
	mov word [wAns21], ax
	mov word [wRem21], dx
	mov ax, 0		;clear


; *****************************************
; Double-Word Operations

; -----
; unsigned double-word additions
;	dAns1  = dNum1 + dNum3
;	dAns2  = dNum4 + dNum3
;	dAns3  = dNum2 + dNum4

	mov eax, dword [dNum1]
	add eax, dword [dNum3]
	mov dword [dAns1], eax
	mov eax, 0		;clear

	mov eax, dword [dNum4]
	add eax, dword [dNum3]
	mov dword [dAns2], eax
	mov eax, 0		;clear

	mov eax, dword [dNum2]
	add eax, dword [dNum4]
	mov dword [dAns3], eax
	mov eax, 0		;clear

; -----
; signed double-word additions
;	dAns4  = dNum7 + dNum5 
;	dAns5  = dNum8 + dNum6

	mov eax, dword[dNum7]
	add eax, dword[dNum5]
	mov dword[dAns4], eax
	
	mov eax, dword[dNum8]
	add eax, dword[dNum6]
	mov dword[dAns5], eax

; -----
; unsigned double-word subtractions
;	dAns6  = dNum1 - dNum2
;	dAns7  = dNum4 - dNum2
;	dAns8  = dNum3 - dNum1

	mov eax, dword [dNum1]
	sub eax, dword [dNum2]
	mov dword [dAns6], eax
	mov eax, 0		;clear

	mov eax, dword [dNum4]
	sub eax, dword [dNum2]
	mov dword [dAns7], eax
	mov eax, 0		;clear

	mov eax, dword [dNum3]
	sub eax, dword [dNum1]
	mov dword [dAns8], eax
	mov eax, 0		;clear

; -----
; signed double-word subtraction
;	dAns9  = dNum5 - dNum8
;	dAns10 = dNum7 – dNum6

	mov eax, dword [dNum5]
	sub eax, dword [dNum8]
	mov dword [dAns9], eax
	mov eax, 0		;clear

	mov eax, dword [dNum7]
	sub eax, dword [dNum6]
	mov dword [dAns10], eax
	mov eax, 0		;clear



; -----
; unsigned double-word multiplication
;	qAns11  = dNum4 * dNum1
;	qAns12  = dNum3 * dNum3
;	qAns13  = dNum2 * dNum1

	mov eax, dword [dNum4]
	mul dword [dNum1]
	mov dword [qAns11], eax ; hold upper bits
	mov dword [qAns11 + 4], edx ; hold lower and +4 because dword size

	mov eax, dword [dNum3]
	mul dword [dNum3]
	mov dword [qAns12], eax ; hold upper bits
	mov dword [qAns12 + 4], edx ; hold lower and +4 because dword size

	mov eax, dword [dNum2]
	mul dword [dNum1]
	mov dword [qAns13], eax ; hold upper bits
	mov dword [qAns13 + 4], edx ; hold lower and +4 because dword size

; -----
; signed double-word multiplication
;	qAns14  = dNum7 * dNum5
;	qAns15  = dNum8 * dNum6

	mov eax, dword [dNum7]
	imul dword [dNum5]
	mov dword [qAns14], eax ; hold upper bits
	mov dword [qAns14 + 4], edx ; hold lower and +4 because dword size

	mov eax, dword [dNum8]
	imul dword [dNum6]
	mov dword [qAns15], eax ; hold upper bits
	mov dword [qAns15 + 4], edx ; hold lower and +4 because dword size

; -----
; unsigned double-word division
;	dAns16 = dNum1 / dNum3
;	dAns17 = dNum4 / dNum2
;	dAns18 = qAns12 / dNum3
;	dRem18 = qAns12 % dNum3

	mov eax, dword [dNum1]
	div dword [dNum3]
	mov dword [dAns16], eax
	mov eax, 0		;clear

	mov eax, dword [dNum4]
	div dword [dNum2]
	mov dword [dAns17], eax
	mov eax, 0		;clear

	mov eax, dword [qAns12]
	mov edx, dword [qAns12 + 4] ; extend the size because dword
	div dword [dNum3]
	mov dword [dAns18], eax
	mov dword [dRem18], edx
	mov eax, 0		;clear

; -----
; signed double-word division
;	dAns19 = dNum5 / dNum7
;	dAns20 = dNum8 / dNum6
;	dAns21 = qAns11 / dNum7
;	dRem21 = qAns11 % dNum7

	mov eax, dword [dNum5]
	cdq ; convert word in ax into dword dx:ax
	idiv dword [dNum7]
	mov dword [dAns19], eax
	mov eax, 0		;clear

	mov eax, dword [dNum8]
	cdq ; convert word in ax into dword dx:ax
	idiv dword [dNum6]
	mov dword [dAns20], eax
	mov eax, 0		;clear

	mov eax, dword[qAns11]
	mov edx, dword[qAns11+4]
	idiv dword[dNum7]
	mov dword[dAns21], eax
	mov dword[dRem21], edx	;clear

; *****************************************
; QuadWord Operations

; -----
; unsigned quadword additions
;	qAns1  = qNum1 + qNum2
;	qAns2  = qNum3 + qNum4
;	qAns3  = qNum3 + qNum4

	mov rax, qword [qNum1]
	add rax, qword [qNum2]
	mov qword [qAns1], rax
	mov rax, 0		;clear

	mov rax, qword [qNum3]
	add rax, qword [qNum4]
	mov qword [qAns2], rax
	mov rax, 0		;clear

	mov rax, qword [qNum3]
	add rax, qword [qNum4]
	mov qword [qAns3], rax
	mov rax, 0		;clear

; -----
; signed quadword additions
;	qAns4  = qNum5 + qNum7
;	qAns5  = qNum6 + qNum8

	mov rax, qword [qNum5]
	add rax, qword [qNum7]
	mov qword [qAns4], rax
	mov rax, 0		;clear

	mov rax, qword [qNum6]
	add rax, qword [qNum8]
	mov qword [qAns5], rax
	mov rax, 0		;clear

; -----
; unsigned quadword subtractions
;	qAns6  = qNum4 - qNum1
;	qAns7  = qNum3 - qNum2
;	qAns8  = qNum2 - qNum1

	mov rax, qword [qNum4]
	sub rax, qword [qNum1]
	mov qword [qAns6], rax
	mov rax, 0		;clear

	mov rax, qword [qNum3]
	sub rax, qword [qNum2]
	mov qword [qAns7], rax
	mov rax, 0		;clear

	mov rax, qword [qNum2]
	sub rax, qword [qNum1]
	mov qword [qAns8], rax
	mov rax, 0		;clear

; -----
; signed quadword subtraction
;	qAns9  = qNum8 - qNum6
;	qAns10 = qNum5 - qNum7

	mov rax, qword [qNum8]
	sub rax, qword [qNum6]
	mov qword [qAns9], rax
	mov rax, 0		;clear

	mov rax, qword [qNum5]
	sub rax, qword [qNum7]
	mov qword [qAns10], rax
	mov rax, 0		;clear

; -----
; unsigned quadword multiplication
;	dqAns11  = qNum1 * qNum3
;	dqAns12  = qNum2 * qNum4
;	dqAns13  = qNum1 * qNum2

	mov rax, qword[qNum1]
	mul qword[qNum3]
	mov qword[dqAns11], rax
	mov qword[dqAns11 + 8], rdx

	mov rax, qword[qNum2]
	mul qword[qNum4]
	mov qword[dqAns12], rax
	mov qword[dqAns12 + 8], rdx

	mov rax, qword[qNum1]
	mul qword[qNum2]
	mov qword[dqAns13], rax
	mov qword[dqAns13 + 8], rdx

; -----
; signed quadword multiplication
;	dqAns14  = qNum5 * qNum7
;	dqAns15  = qNum6 * qNum8

	mov rax, qword[qNum5]
	imul qword[qNum7]
	mov qword[dqAns14], rax
	mov qword[dqAns14 + 8], rdx

	mov rax, qword[qNum6]
	imul qword[qNum8]
	mov qword[dqAns15], rax
	mov qword[dqAns15 + 8], rdx

; -----
; unsigned quadword division
;	qAns16 = qNum4 / qNum1
;	qAns17 = qNum3 / qNum2
;	qAns18 = dqAns12 / qNum3
;	qRem18 = dqAns12 % qNum3

	mov rax, qword[qNum4]
	div qword[qNum1]
	mov qword[qAns16], rax

	mov rax, qword[qNum3]
	div qword[qNum2]
	mov qword[qAns17], rax

	mov rax, qword[dqAns12]
	mov rdx, qword[dqAns12 + 8]
	div qword[qNum3]
	mov qword[qAns18], rax
	mov qword[qRem18], rdx

; -----
; signed quadword division
;	qAns19 = qNum5 / qNum7
;	qAns20 = qNum8 / qNum6
;	qAns21 = dqAns11 / qNum7
;	qRem21 = dqAns11 % qNum7

	mov rax, qword[qNum5]
	cqo
	idiv qword[qNum7]
	mov qword[qAns19], rax

	mov rax, qword[qNum8]
	cqo
	idiv qword[qNum6]
	mov qword[qAns20], rax

	mov rax, qword[dqAns11]
	mov rdx, qword[dqAns11 + 8]
	idiv qword[qNum7]
	mov qword[qAns21], rax
	mov qword[qRem21], rdx

; *****************************************************************
;	Done, terminate program.

last:
	mov	rax, SYS_exit		; call call for exit (SYS_exit)
	mov	rdi, EXIT_SUCCESS	; return code of 0 (no error)
	syscall

