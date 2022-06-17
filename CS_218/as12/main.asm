
#; Description = MIPS program that will implement a mergeSort.

.data
#;	System service constants
	SYSTEM_PRINT_INTEGER = 1
	SYSTEM_PRINT_STRING = 4
	SYSTEM_PRINT_CHARACTER = 11
	SYSTEM_READ_INTEGER = 5
	SYSTEM_EXIT = 10
	
#;	Random Number Generator Values
	M = 0x00010001
	A = 75
	C = 74
	previousRandomNumber: .word  1
	
	MINIMUM_VALUE = 1
	MAXIMUM_VALUE = 100
	ARRAY_SIZE = 100
	numbers: .space ARRAY_SIZE*4

	totalMerge: .word 0
	

#;	Labels
	unsortedArrayLabel: .asciiz "Unsorted:\n"
	sortedArrayLabeL: .asciiz "\nSorted:\n"
	mergesLabel: .asciiz "\nMerges: "
	
.text
.globl main
.ent main
main:
	#;  Uses the random number function to initialize the array to random values
	li $t7, 0 # counter
	initLoop:
		beq $t7, ARRAY_SIZE, doneInit
		li $a0, MINIMUM_VALUE
		li $a1, MAXIMUM_VALUE
		jal getRandomNumber

		la $t6, numbers
		mul $t0, $t7, 4
		add $t1, $t6, $t0
		sw $v0, ($t1)
		addi $t7, $t7, 1 # increment counter 
		j initLoop

	#;	Prints the unsorted array of random values
	doneInit:
		li $v0, SYSTEM_PRINT_STRING
		la $a0, unsortedArrayLabel
		syscall

		la $a0, numbers
		li $a1, ARRAY_SIZE
		jal printArray

		li $v0, SYSTEM_PRINT_CHARACTER
		la $a0, '\n'
		syscall

	#;	Sort using mergeSort
		li $v0, SYSTEM_PRINT_STRING
		la $a0, sortedArrayLabeL
		syscall

		la $a0, numbers
		li $a1, ARRAY_SIZE
		jal mergeSort

		sw $v0, totalMerge

	#;	Print the sorted array
		la $a0, numbers
		li $a1, ARRAY_SIZE
		jal printArray
	#;	Print the number of merges used
		li $v0, SYSTEM_PRINT_STRING
		la $a0, mergesLabel
		syscall

		li $v0, SYSTEM_PRINT_INTEGER
		lw $a0, totalMerge
		syscall
	
	li $v0, SYSTEM_EXIT
	syscall
	
.end main

#; Sorts an array using the merge sort algorithm:
#;	Split array into two halves
#;	Call mergeSort on each half
#;	Merge each half of the array
#;    Compare the front of each array
#;		Push the lower valued element and increment its pointer
#;		Continue until both sub-arrays are empty
#;		Pop the values back into the array (in reverse)
#;	Base Case: Array Size = 1 just return (do not count as a merge)
#;	Arguments:
#;		$a0 - &array (signed word integers)
#;		$a1 - array size (signed word integer)
#;	Return a count of the number of merges
.globl mergeSort
.ent mergeSort
mergeSort:
	# prologue for arr1, arr1_size, arr2, arr2_size
	subu $sp, $sp, 32
	sw $s0, ($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $s3, 12($sp)
	sw $s4, 16($sp)
	sw $s5, 20($sp)
	sw $s6, 24($sp)
	sw $ra, 28($sp)

	# store original size
	move $s5, $a1
	# store original ar
	move $s6, $a0
	# store total merge into preserved regs
	li $s4, 0
	# base case: size = 1
	beq $a1, 1, baseCase 

	div $s0, $a1, 2 # hold size for array 1 (size /2)
	sub $s1, $a1, $s0 # hold size for array 2 (size - arr1_size)
	move $s2, $a0  # adress for array 1 (&array)
	mul $s3, $s0, 4 
	add $s3, $s3, $s2 # adress for array 2 (&array + (size_arr1 * 4))

	# call merge sort and add return value tot toal merge for array 1
	move $a0,$s2 # s2 = address
	move $a1, $s0 # s0 = size
	jal mergeSort
	# calculate total merge
	# add $s4, $s4, $v0

	# call merge sort and add return value tot toal merge for array 2
	move $a0,$s3
	move $a1, $s1
	jal mergeSort
	# calculate total merge
	# add $s4, $s4, $v0

	recursiveLoop:
		# the s2, s3 will hold array1 and 2
		lw $t1, 0($s2) # take 1st value of arr 1
		lw $t2, 0($s3) # take 1st value of arr 2

		# if arr1 < arr2 -> push arr1 val
		blt $t1, $t2, pushArr1

		# push 2nd if 1st > 2nd
		subu $sp, $sp, 4
		sw $t2, 0($sp)

		# update ptr for arr2
		addu $s3, $s3, 4
		subu $s1, $s1, 1 # decrement size for arr2
		# check if arr2 has any left -> not push rest of array 1
		beq $s1, 0, pushRestArr1
		j recursiveLoop

	pushArr1:
		# push 1st if 1st < 2nd
		subu $sp, $sp, 4
		sw $t1, 0($sp)

		# update ptr for arr1
		addu $s2, $s2, 4
		subu $s0, $s0, 1 # decrement size for arr1
		# check if arr1 has any left -> not push rest of array 2
		beq $s0, 0, pushRestArr2
		j recursiveLoop

	pushRestArr1:
		# s0 hold size for arr1
		pushArr1Loop:
			beq $s0, 0, popArr
			lw $t1, 0($s2) # take 1st value of arr 1
			addi $sp, $sp, -4
			sw $t1, ($sp) # t1 -> first value 

			# update address for arr1
			addu $s2, $s2, 4 # not work -> not update/ go to next value at all 
			subu $s0, $s0, 1 # decrement counter for arr1
			j pushArr1Loop

	pushRestArr2:
		# s1 hold size for arr2
		pushArr2Loop:
			beq $s1, 0, popArr
			lw $t2, 0($s3) # take 1st value of arr 2
			subu $sp, $sp, 4
			sw $t2, 0($sp)

			# update address for arr2
			addu $s3, $s3, 4
			subu $s1, $s1, 1 # decrement counter for arr1
			j pushArr2Loop

	popArr:
	#; acess last elem of array
		# s6 = addrs of arr
		move $t3, $s5 #; size
		sub $t3, $t3, 1
		mulo $t3, $t3, 4
		add $s6, $s6, $t3

		popLoop:
			beq $s5, 0, hasRecursive
			# pop stack 
			lw $t6, ($sp)
			sw $t6, ($s6)
			
			move $v0, $s4
			add $s4, $s4, 1

			addu $sp, $sp, 4 # update stack ptr
			subu $s5, $s5, 1 # decrement size
			subu $s6, $s6, 4 # go to prev one
			j popLoop

	baseCase:
		# li $v0, 0
		j endFunction

	hasRecursive:
		j endFunction
	endFunction:
		# sw $s4, totalMerge
		# epilogue
		
		lw $s0, ($sp) 
		lw $s1, 4($sp)
		lw $s2, 8($sp)
		lw $s3, 12($sp)
		lw $s4, 16($sp)
		lw $s5, 20($sp)
		lw $s6, 24($sp)
		lw $ra, 28($sp)
		addu $sp, $sp, 32

		jr $ra
.end mergeSort

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

#; Prints an array to the console with a new line every 10 elements
#; Arguments:
#;	$a0 - &array
#;	$a1 - elements
.globl printArray
.ent printArray
printArray:
	
	move $t0, $a0

	li $t1, 1
	printLoop:
		li $v0, SYSTEM_PRINT_INTEGER
		lw $a0, ($t0)
		syscall
		
		li $v0, SYSTEM_PRINT_CHARACTER
		li $a0, ' '
		syscall
		
		remu $t2, $t1, 10 # new line after 10 elements
		bnez $t2, skipNewLine
			li $v0, SYSTEM_PRINT_CHARACTER
			li $a0, '\n'
			syscall
		skipNewLine:
		
		addu $t1, $t1, 1 # Newline Counter
		addu $t0, $t0, 4
		subu $a1, $a1, 1
	bnez $a1, printLoop

	jr $ra
.end printArray


