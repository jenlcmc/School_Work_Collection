;	Counts the instances of abundant numbers between 2 and 200,000.
;	Uses pthreads to divide the work.

section .data
;	System Service Codes
	SYSTEM_EXIT equ 60
	SYSTEM_WRITE equ 1
	SYSTEM_READ equ 0
	
;	Systerm Service Options
	SUCCESS equ 0
	FAILURE equ 1

;	Special Characters
	LINEFEED equ 10
	NULL equ 0
	
;	Shared Resources
	abundantCount dq 0
	nextValue dq 2
	mutexLock dq LOCK_AVAILABLE	
	
;	Lock States
	LOCK_AVAILABLE equ 0
	LOCK_BUSY equ 1

;	Formatted Messages
	messagePrintAbundantCount db "Abundant Numbers between 2 and 200,000: %d", LINEFEED, NULL
	messageThreadWorking db "Thread %d: Created.", LINEFEED, NULL
	messageThreadDone db "Thread %d: Joined.", LINEFEED, NULL
	messageNumbersProcessed db "Thread examined %d numbers.", LINEFEED, NULL
	
;	Program Constraints
	MAXIMUM_VALUE equ 200000
	THREAD_COUNT equ 6
	
section .bss
;	Thread ID's	
	threadIDs resq THREAD_COUNT*5
	
extern pthread_create, pthread_join, printf
section .text

global main
main:
	push rbp
	mov rbp, rsp
	
	; Need to initialize thread id values, will be set by pthread_create
	mov rcx, THREAD_COUNT*5
	mov rax, 0
	initializeIDsLoop:
		mov qword[threadIDs+rax], 0
		inc rax
	loop initializeIDsLoop

	; Start Threads
	mov r13, 1
	mov r12, threadIDs
	startThreadsLoop:
		mov rdi,  r12
		mov rsi, NULL
		mov rdx, findAbundantNumbers
		mov rcx, NULL
		call pthread_create
		
		mov rdi, messageThreadWorking
		mov rsi, r13
		mov rax, 0
		call printf
		
		add r12, 40
	inc r13
	cmp r13, THREAD_COUNT
	jbe startThreadsLoop

	; Join Threads
	mov r13, 1
	mov r12, threadIDs
	joinThreadsLoop:
		mov rdi,  qword[r12]
		mov rsi, NULL
		call pthread_join
		
		mov rdi, messageThreadDone
		mov rsi, r13
		mov rax, 0
		call printf
		
		add r12, 40
	inc r13
	cmp r13, THREAD_COUNT
	jbe joinThreadsLoop
	
	mov rdi, messagePrintAbundantCount
	mov rsi, qword[abundantCount]
	mov rax, 0
	call printf
	
	pop rbp

	endProgram:
		mov rax, SYSTEM_EXIT
		mov rdi, SUCCESS
		syscall
;	End of main	

global findAbundantNumbers
findAbundantNumbers:
	push rbx
	push r12
	
	mov r12, 0	; Numbers processed
	
;	Thread must work until it receives a number to check greater than the maximum
	findAbundantNumbersLoop:
;		Obtain lock
		call obtainLock
;		Get next value to check and update it
		mov rbx, qword[nextValue]
		inc qword[nextValue]
;		Release lock
		call releaseLock
	
; 		Check if thread is done
		cmp rbx, MAXIMUM_VALUE
		ja findAbundantNumbersDone
	
		inc r12
	
; 		Check if value is abundant
;		Must check all numbers between 1 and Value/2
		mov rcx, rbx
		shr rcx, 1	;	Value/2
		mov r8, 1	;	Number being checked as divisor
		mov r9, 0	;	Divisor sum
		divisorLoop:
			mov rax, rbx
			mov rdx, 0
			div r8
			cmp rdx, 0
			jne notADivisor
				add r9, r8
			notADivisor:
			inc r8
		cmp r8, rcx
		jbe divisorLoop
		
		; If the sum of the proper divisors are greater than the number, it is abundant
		cmp r9, rbx
		jbe notAnAbundantNumber
			lock inc qword[abundantCount]
;			inc qword[abundantCount]
		notAnAbundantNumber:
	
	jmp findAbundantNumbersLoop
	findAbundantNumbersDone:

	mov rdi, messageNumbersProcessed
	mov rsi, r12
	mov rax, 0
	call printf

	pop r12
	pop rbx
ret

;	This is an example of a spinlock.  The thread will continuously try to obtain the free lock value (0).
;	Once a thread obtains the lock, it replaces the value with 1 meaning it is being used.
global obtainLock
obtainLock:
	mov rax, LOCK_BUSY
;	swap rax and mutex values
	lock xchg rax, qword[mutexLock]	; The lock keyword ensures that only this thread can access the memory location during the instruction
	cmp rax, LOCK_BUSY
	je obtainLock
ret

;	Frees the lock to be used by another thread.
global releaseLock
releaseLock:
	mov qword[mutexLock], LOCK_AVAILABLE
ret