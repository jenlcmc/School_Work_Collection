
#; Description = utilize arrays and functions to sort a list of numbers
#; Using cocktail sort and find median

.data

#; constant variables
SIZE = 100
SYSTEM_EXIT = 10
SYSTEM_PRINT_INTEGER = 1
SYSTEM_PRINT_CHARACTER = 11
SYSTEM_PRINT_FLOAT = 2
SYSTEM_PRINT_STRING = 4

#; variables for program
array:  .word  57  ,307 ,757 ,64  ,335 ,832 ,885 ,475 ,25  , 309
        .word  258 ,439 ,285 ,685 ,934 ,881 ,345 ,64  ,742 , 776
        .word  316 ,778 ,818 ,356 ,482 ,628 ,283 ,444 ,537 , 921
        .word  676 ,428 ,288 ,587 ,569 ,420 ,706 ,395 ,25  , 852
        .word 402 ,930 ,196 ,68  ,745 ,70  ,698 ,87  ,384 , 144
        .word 353 ,345 ,782 ,45  ,510 ,296 ,315 ,2   ,309 , 676
        .word 556 ,794 ,45  ,289 ,423 ,79  ,899 ,337 ,71  , 525
        .word 16  ,313 ,291 ,763 ,437 ,855 ,125 ,419 ,582 ,  70
        .word 948 ,112 ,220 ,131 ,369 ,332 ,282 ,196 ,470 , 152
        .word 935 ,753 ,197 ,964 ,362 ,998 ,371 ,838 ,338 , 644

median: .word 0

#; all prompt string

beforeHeader: .asciiz "Unsorted List: \n"
afterHeader: .asciiz "\nSorted List: \n"

medianPrompt: .asciiz "\nMedian: "
spaces: .asciiz " "
newline: .asciiz "\n"

.text


.globl main
.ent main
main:
    li $v0, 4 #; print header string
    la $a0, beforeHeader
    syscall

    la $a0, array #; pass array as address
	li $a1, SIZE #; pass size 
	jal printArray

	#; declare var for the loop
	# stack local for flag
	add $sp, -4
	sw $s0, 4($sp) #;flag for swap
	li $s0, 1 # act like bool var for sorted or not
	mainLoop:
		li $s0, 0 #; flag for swapping set false to restore
		
		#; call shakeRight function
		la $a0, array
		li $a1, SIZE
		jal shakeRight

		# either return 1 or 0 
		move $s0, $v0 #;move value from funct to flag

		# if nothing move (return 0) -> arr is sorted
		beq $s0, 0, doneMainLoop

		#; otherwise, reset flag so that it can be used for next one
		li $s0, 0

		#; call shakeLeft function
		la $a0, array
		li $a1, SIZE
		jal shakeLeft

		move $s0, $v0 #;move value from funct to flag
		
		beq $s0, 1, mainLoop # if not sorted -> jump back to loop
		beq $s0, 0, doneMainLoop # if sorted -> done

	doneMainLoop:
		li $v0, 4 #; print header string
		la $a0, afterHeader
		syscall

		# print array
		la $a0, array
		li $a1, SIZE
		jal printArray

		li $v0, 4 #; print header string
		la $a0, medianPrompt
		syscall


		li $t6, SIZE
		rem $t6, $t6, 2 #; rem result
		beq $t6, 0, evenSize

		la $t3, array
		li $t5, SIZE
		sub $t5, $t5, 1 #; -1 as its start from 0
		div $t5, $t5, 2 #;hold index for arr element

		mul $t5, $t5, 4 #; multiple data size
		add $t3, $t3, $t5 #; update array index
		lw $t1, 0($t3) #; load data 
		
		# print value
		li $v0, SYSTEM_PRINT_INTEGER
		move $a0, $t2
		syscall

		evenSize:
			li $t7, SIZE
			div $t7, $t7, 2 #; n/2 -index
			move $t4, $t7 #;n/2 for both
			sub $t4, $t4, 1 #; t4 = n/2 -1 - index

			la $t3, array
			mul $t7, $t7, 4 #; multiple data size
			add $t3, $t3, $t7  #; update array index
			lw $t1, 0($t3) #; load data 

			la $t3, array
			mul $t4, $t4, 4
			add $t3, $t3, $t4 #; go to next element
			lw $t2, 0($t3) #; 

			# add both elements and div by 2
			add $t1, $t1, $t2  
			div $t1, $t1, 2

			# print result
			li $v0, SYSTEM_PRINT_INTEGER
			move $a0, $t1
			syscall


		#; resotre stack
		lw $s0, 4($sp) 
		add $sp, 4

		li $v0, 10
		syscall

.end main

#; $a0 - address of array
#; $a1 - size of array
#; function will print the array
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
		
		remu $t2, $t1, 5
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

#; $a0 - adress of array
#; $a1 - size of array
#; function will loop from right to left so that the smallest will be the 1st one
#; return 0 or 1 for the boolean flag to determine if it swapped or not
.globl shakeLeft
.ent shakeLeft
shakeLeft:
	move $t0, $a1 #; i
	sub $t0, $t0, 2 #; i -2 as last elem + largest is last
	add $t1, $zero, $zero #; start -0
	li $t2, 0 #; flag for swapping -false

	#; acess last elem
	move $t3, $a1 #; size
	sub $t3, $t3, 1
	mulo $t3, $t3, 4
	add $a0, $a0, $t3
	move $t6, $a0
	
	loopLeft:
		blt $t0, $t1, endLoopLeft #; if i < start ->stop
		sub $t0, $t0, 1 #; decrement counter 

		lw $t4, 0($a0) #; set $t4 to current/last elemt
		sub $t6, $t6, 4 #; go to prev element
		lw $t5, 0($t6) #; set $t5 to prev elemt
		ble $t5, $t4, noSwapVal #; if t5 prev < last-t4 -> loop without swap
		sw $t4, 0($t6) #; swap
		sw $t5, 0($a0)
		add $t2, $t2, 1 #; flag counter
		sub $a0, $a0, 4 #; go to prev element
		j loopLeft  #; jump back to loop
		
	noSwapVal:
		sub $a0, $a0, 4 #; go to prev element
		j loopLeft
	endLoopLeft:
		bge $t2, 1, haveSwapLeft # if counter flag >= 1 -> have swap
		li $v0, 0 #; flag false -return it
		j endShakeLeft

	haveSwapLeft:
		li $v0, 1 #; flag true -return it
		j endShakeLeft

	endShakeLeft:
		jr $ra
.end shakeLeft

#; $a0 - adress of array
#; $a1 - size of array
#; function will loop from left to right so that the largest will be the last one
#; return 0 or 1 for the boolean flag to determine if it swapped or not
.globl shakeRight
.ent shakeRight
shakeRight:
	add $t0, $zero, $zero #; start index initialized to 0
	move $t1, $a1 #; end index
	sub $t1, $t1, 1 #; -1 because start from 0
	li $t6, 0 #; flag for swapping -false
	loop:
		beq $t0, $t1, endLoop #; if counter == size -> done
		add $t0, $t0, 1 #; increment counter 

		lw $t2, 0($a0) #; set $t2 to current elemt
		lw $t3, 4($a0) #; set $t3 to next elemt
		ble $t2, $t3, noSwap #; if t2- curr < next-t3 -> loop without swap
		sw $t2, 4($a0) #; swap
		sw $t3, 0($a0)
		add $a0, $a0, 4 #; go to next element
		add $t6, $t6, 1 #; flag
		j loop  #; jump back to loop
		
	noSwap:
		add $a0, $a0, 4 #; go to next element
		j loop
	endLoop:
		bge $t6, 1, haveSwap # if counter flag >= 1 -> have swap
		li $v0, 0 #; flag false -return it
		j endShakeRight

	haveSwap:
		li $v0, 1 #; flag true -return it
		j endShakeRight

	endShakeRight:
		jr $ra
.end shakeRight
