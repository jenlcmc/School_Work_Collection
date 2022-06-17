
#; Description = MIPS program that will create a variation of a magic square.

.data
#;	System service constants
	SYSTEM_PRINT_INTEGER = 1
	SYSTEM_PRINT_STRING = 4
	SYSTEM_PRINT_CHARACTER = 11
	SYSTEM_EXIT = 10
	SYSTEM_READ_INTEGER = 5

#;	Random Number Generator Values
	M = 0x00010001
	A = 75
	C = 74
	previousRandomNumber: .word  1

#;	Magic Square
	MINIMUM_SIZE = 2
	MAXIMUM_SIZE = 10
	MAXIMUM_TOTAL = 1000
	magicSquare: .space MAXIMUM_SIZE*MAXIMUM_SIZE*4 

	promtpSize: .asciiz "Magic Square Size (2-10): "
	sizeError: .asciiz "\nSize must be between 2 and 10. \n\n"

	magicPromtp: .asciiz "\nMagic Number: "
	magicError: .asciiz "\nMagic number must be between the square size and 1000.\n\n"
	spaces: .asciiz " "
	newline: .asciiz "\n"

.text
.globl main
.ent main
main:
	# prologue
	subu $sp, $sp, 12
	sw $s0, ($sp)
	sw $s1, 4($sp)
	sw $ra, 8($sp)
	
	#; Ask user for size of magic square to generate
	li $v0, 4 #; print header string
    la $a0, promtpSize
    syscall

	#;	Check that the size is between 2 and 10
	li $v0, 5 # call code for read int 
	syscall # result will be in v0
	move $s0, $v0 # store size

	blt $v0, MINIMUM_SIZE, wrongSize # if less than 2 -> error
	bgt $v0, MAXIMUM_SIZE, wrongSize # if more than 10 -> error
	
	j checkTotal

	checkTotal:
		#; Ask user for column/row total
		li $v0, 4 #; print header string
		la $a0, magicPromtp
		syscall

		#;	Check that the total is between the square size and 1000
		li $v0, 5 # call code for read int 
		syscall # result will be in v0
		move $s1, $v0 # store magic number

		bgt $v0, MAXIMUM_TOTAL, wrongBounds# if more than 10 -> error
		move $a0, $v0
		jal checkSquare

		beq $v0, 1, wrongBounds

		j makeMagic

	#;	Output an error and ask again if not within bounds
	wrongSize:
		li $v0, 4 #; print error message
		la $a0, sizeError
		syscall

		j main

	wrongBounds:
		#;	Output an error and ask again if not within bounds
		li $v0, 4 #; print header string
		la $a0, magicError
		syscall

		j checkTotal

	#; Create a magic square
	makeMagic:
		la $a0, magicSquare
		move $a1, $s0
		move $a2, $s1
		jal createMagicSquare
	
	#; Print the magic square
		la $a0, magicSquare
		move $a1, $s0
		move $a2, $s0
		jal printMatrix

		j endProgram
	endProgram:
	# epislogue
		lw $s0, ($sp) 
		lw $s1, 4($sp)
		lw $s2, 8($sp)
		lw $ra, 12($sp)
		addu $sp, $sp, 12

		li $v0, SYSTEM_EXIT
		syscall
.end main

#; Prints a 2D matrix to the console
#; Arguments:
#;	$a0 - &matrix
#;	$a1 - rows
#;	$a2 - columns
.globl printMatrix
.ent printMatrix
printMatrix:
	subu $sp, $sp, 12
	sw $s0, ($sp) # i
	sw $s1, 4($sp) # j
	sw $s2, 8($sp) # hold array value
	move $t4, $a0 # hold array

	li $s0, 0
	li $s1, 0
	li $s2, 0
	# outerLoopPrint:
		innerLoopPrint:
			mul $t2, $a2, $s0 # num of col * i
			add $t2, $t2, $s1 # num of col * i + j
			mul $t2, $t2, 4 # * dataSize = 4
			add $s2, $t2, $t4 # + base address

			lw $t3, 0($s2) # get array[i][j]

			li $v0, SYSTEM_PRINT_INTEGER
			move $a0, $t3
			syscall
			
			li $v0, SYSTEM_PRINT_STRING
			la $a0, spaces
			syscall

			add $s1, $s1, 1
			blt $s1, $a2, innerLoopPrint # if j < colums then go back loop
			
			li $v0, SYSTEM_PRINT_CHARACTER
			la $a0, '\n'
			syscall

			add $s0, $s0, 1
			li $s1, 0
			blt $s0, $a1, innerLoopPrint # if i < rows then go back loop

			lw $s0, 0($sp) 
			lw $s1, 4($sp)
			lw $s2, 8($sp)
			addu $sp, $sp, 12
			jr $ra
	
.end printMatrix

#; Gets a random non-negative number between a specified range
#; Uses a linear congruential generator
#;	m = 2^16+1
#;	a = 75
#;	c = 74
#;	newRandom = (previous*a+c)%m
#; Arguments:
#;	$a0 - Minimum Value
#;	$a1 - Maximum Value
#; Global Variables/Constants Used
#;	previousRandom - Used to generate the next value, must be updated each time
#;	m, a, c
#; Returns a random signed integer number
.globl getRandomNumber
.ent getRandomNumber
getRandomNumber:
	lw $t0, previousRandomNumber
	li $t1, A
	li $t2, C
	li $t3, M

	#; Multiply the previous random number by A
	mul $t4, $t0, $t1
	#; Add C
	add $t4, $t4, $t2  
	#; Get the remainder by M
	rem $t6, $t4, $t3 # hold value (previous*a+c)%m == newRandom
	#; Set the previousRandomNumber to this new random value
	sw $t6, previousRandomNumber
	
	#; Use the new random value to generate a random number within the specified range
	#;	return randomNumber = newRandom%(maximum-minimum+1)+minimum
	sub $t5, $a1, $a0   
	add $t5, $t5, 1 
	rem $v0, $t6, $t5
	add $v0, $v0, $a0 # random number
	
	jr $ra
.end getRandomNumber

#; Creates a magic square 2D matrix
#;
#; Example 3x3 Magic Square with 11 as totals:
#;	4 1 6	4+1+6 = 11
#;  5 3 3	5+3+3 = 11
#;  2 7 2	2+7+2 = 11
#;	
#;	4+5+2 = 11
#;	1+3+7 = 11
#;	6+3+2 = 11
#;	
#; Arguments:
#;	$a0 - &matrix
#;	$a1 - size of matrix
#;	$a2 - row/column desired total
.globl createMagicSquare
.ent createMagicSquare
createMagicSquare: 
	subu $sp, $sp, 36
	sw $s0, ($sp) 
	sw $s1, 4($sp) 
	sw $s2, 8($sp) 
	sw $s3, 12($sp) 
	sw $ra, 16($sp)
	sw $s4, 20($sp) 
	sw $s5, 24($sp) 
	sw $s6, 28($sp)

	move $s0, $a1 # hold size temp
	move $s1, $a2 # hold magic number
	mul $s2, $a1, $a2 # total of pos loop

	li $t3, 0 # counter
	mul $a1, $a1, $a1  # size * size - > size of 1d arr
	initLoop:
		sw $zero, 0($a0)
		add $a0, $a0, 4 #; go to next element
		addi $t3, $t3, 1 # increment counter
		blt $t3, $s0, initLoop # if i < size - > loop
		li $s3, 0 # counter

	#; loop:
	createLoop:
		bge $s3, $s2, exitCreate # if i >= max pos loop -> stop
	#; 	Choose a random row # using getRandomNumber

		li $a0, 1
		move $a1, $s0
		jal getRandomNumber

		move $t7, $v0 # hold random row # 
	#; 	Choose a random column # using getRandomNumber
		li $a0, 1
		move $a1, $s0
		jal getRandomNumber

		move $t6, $v0 # hold random column #

		#; 	Check if the column and row totals are < desired total
		#; 	If both are < than the desired total:
		#; 		Add 1 to matrix[row][column]
		#; Repeat until all rows/columns have a total value equal to the desired value

		subu $t7, $t7, 1 # -1 as start from 0/ i /row
		subu $t6, $t6, 1 # j/column

		la $a0, magicSquare
		move $a1, $s0
		move $a2, $s0
		move $a3, $t7
		jal getRowTotal

		move $s4, $v0 # update -> hold get row total 

		la $a0, magicSquare
		move $a1, $s0
		move $a2, $s0
		move $a3, $t6
		jal getColumnTotal

		move $s5, $v0 # update -> hold get column total 

		# if row >= magic 
		bge $s4, $s1, updateArr
		# if colum > = magic 
		bge $s5, $s1, updateArr
		# otherwise, add 1 
		la $t0, magicSquare # base address
		
		mul $t5, $s0, $t7 # num of col * i
		add $t5, $t5, $t6 # num of col * i + j
		mul $t5, $t5, 4 # * dataSize = 4
		add $t5, $t5, $t0 # + base address

		lw $t4, 0($t5) # get array[i][j]
		j haveAdd

		haveAdd:
			add $t4, $t4, 1 # add 1 
			sw $t4, 0($t5)# load val into array
			addu $s3, $s3, 1 # increment counter	
			j createLoop
		updateArr:
			# skip that row and colum
			j createLoop
			# then go back to createLoop for another row and colum

	exitCreate:
		
		lw $s0, 0($sp) 
		lw $s1, 4($sp)
		lw $s2, 8($sp)
		lw $s3, 12($sp)
		lw $ra, 16($sp)
		lw $s4, 20($sp)
		lw $s5, 24($sp)
		lw $s6, 28($sp)
		addu $sp, $sp, 32
		jr $ra
.end createMagicSquare

#; Gets the total of the specified column
#; Arguments
#;	$a0 - &matrix
#;	$a1 - rows
#;	$a2 - columns
#;	$a3 - column # to total.
#; Returns the total of the column values in the matrix
.globl getColumnTotal
.ent getColumnTotal
getColumnTotal:
	li $v0, 0 # sum = 0 
	li $t0, 0 # i
	li $t1, 0 # j

	loopFindCol:
		mul $t2, $a2, $t0 # num of col * i
		add $t2, $t2, $a3 # num of col * i + j/need to find
		mul $t2, $t2, 4 # * dataSize = 4
		add $t3, $t2, $a0 # + base address

		lw $t4, ($t3) # get array[i][j]
		add $v0, $v0, $t4 # sum 

		addi $t0, $t0, 1
		blt $t0, $a1, loopFindCol # if j < rows then go back loop

		jr $ra
.end getColumnTotal

#; Gets the total of the specified row
#; Arguments
#;	$a0 - &matrix
#;	$a1 - rows
#;	$a2 - columns
#;	$a3 - row # to total
#; Returns the total of the row values in the matrix
.globl getRowTotal
.ent getRowTotal
getRowTotal:
	li $v0, 0 # sum = 0 
	li $t1, 0 # j

	loopFind:
		mul $t2, $a2, $a3 # num of col * i/row need to calculate
		add $t2, $t2, $t1 # num of col * i + j
		mul $t2, $t2, 4 # * dataSize = 4
		add $t3, $t2, $a0 # + base address

		lw $t4, ($t3) # get array[i][j]
		add $v0, $v0, $t4 # sum 

		addi $t1, $t1, 1
		blt $t1, $a2, loopFind # if j < columns then go back loop
		jr $ra
.end getRowTotal

.globl checkSquare
.ent checkSquare
checkSquare:
	# a0 number 
	li $t0, 1 # i = 1
	squareLoop:
	add $t0, $t0, 1 # increment counter 

	rem $t1, $a0, $t0 # number % i 
	div $t2, $a0, $t0 # number / i

	beq $t1, 0, isPerfect
	
	li $v0, 0
	
	mul $t0, $t0, $t0 # i * i
	ble $t0, $a0, squareLoop

	isPerfect:
		bne $t2, $t0, notPerfect
		li $v0, 1
		j endCheck

	notPerfect:
		li $v0, 0
		j endCheck

	endCheck:
		jr $ra
.end checkSquare