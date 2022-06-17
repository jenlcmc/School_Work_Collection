
#; Description = add together dollar and cent totals and calculate the total amount.

.data
dollarAmounts: .word 243, 123, 113, 203, 231, 147, 113, 207, 198, 160
			  .word 177, 227, 121, 197, 208, 119, 135, 134, 230, 171
			  .word 201, 101, 200, 196, 189, 240, 201, 134, 182, 201

centAmounts: .word 27, 46, 19, 81, 20, 36, 48, 61, 86, 89
			.word 89, 47, 45, 62, 64, 34, 18, 78, 84, 10
			.word 29, 11, 22, 97, 70, 61, 2, 71, 44, 92

COUNT = 30

#;	Calculate these values
totalDollars: .space 4
totalCents: .space 4
	
#;	Labels
amountLabel: .asciiz "Total: $"
period: .asciiz "."

#;	System Services
SYSTEM_EXIT = 10
SYSTEM_PRINT_INTEGER = 1
SYSTEM_PRINT_STRING = 4	

.text
.globl main
.ent main
main:
	#; Add together dollar and cent values from the provided arrays
	la $t0, dollarAmounts #; dollar starting addr
	li $t1, 0 #; loop index, i =0
	li $t2, COUNT #; length  
	li $t3, 0 #; initialize for dollar sum = 0

	la $t5, centAmounts #; cent starting addr
	li $t6, 0 #; init sum for cent = 0 

	sumLoop:
		lw $t4, ($t0) #; get arr[i] dollar
		add $t3, $t3, $t4 #; sum = sum + arr[i]

		lw $t7, ($t5) #; ger arr[i] cent
		add $t6, $t6, $t7

		add $t1, $t1, 1 #; i++  
		add $t0, $t0, 4 #; update arr address dollar
		add $t5, $t5, 4 #; update arr address cent

		blt $t1, $t2, sumLoop #; if i < length -> cont

		#; sw $t3, totalDollars #; store val in var / t3 = dollar
		#; sw $t6, totalCents #; store val in var / t6 = cent

	#; Convert dollars to cents and add to cent total

	li $t0, 100 #; to mul 100
	mul $t3, $t3, $t0 #; * 100
	add $t6, $t3, $t6 #; dollar in cent + cents 
	#; sw $t4, totalCents #; store val in var / t6 = cent

	#; Calculate dollars and cents using division on the cent total
	#; la $t0, totalCents 
	li $t0, 100 #; to divide and mod 100
	div $t4, $t6, $t0 #; div result
	rem $t5, $t6, $t0 #; rem result

	#; Store results in totalDollars and totalCents
	sw $t4, totalDollars #; store val in var
	sw $t5, totalCents #; store val in var

	#; Print Total Amount
	li $v0, SYSTEM_PRINT_STRING
	la $a0, amountLabel
	syscall
	
	li $v0, SYSTEM_PRINT_INTEGER
	lw $a0, totalDollars
	syscall
	
	li $v0, SYSTEM_PRINT_STRING
	la $a0, period
	syscall
	
	li $v0, SYSTEM_PRINT_INTEGER
	lw $a0, totalCents
	syscall

	li $v0, SYSTEM_EXIT
	syscall
.end main
