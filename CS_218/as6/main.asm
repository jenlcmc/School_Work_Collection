
;Description = This program will involve writing functions to perform a variety of tasks related to floating points, 
;the command line, and integrating with C/C++ code.
section .data 
    ;const var
    STD_IN equ 0
    STD_OUT equ 1; standard output
    SYS_WRITE equ 1; write   
    SYS_READ equ 0 ;read
    LF   equ 10 ;line feed
    NULL equ 0  ;end of string
    SYS_EXIT equ 60; termination
    EXIT_SUCESS equ 0 ; successful code

    ;var for calculation
    helium dq 0.06689
    pi dq 3.14159
    valueError dq 0.00
    valueCal1 dq 4.00
    valueCal2 dq 3.00
    valueCal3 dq 2.00

    ;var to store  
    weight dq 0.00
    diameter dq 0.00
    volume dq 0.00
    balloonNeed dq 0
    balloonCal dq 0.00

    ;string to check  
    checkW db "-W", NULL
    checkD db "-D", NULL

    ;error string messages
    singleCommandErr db "Please include the following: -W weight -D diameter", LF, NULL
    not5 db "Expected 4 arguments: -W weight -D diameter", LF, NULL
    notW db "Expected -W argument", LF, NULL
    notD db "Expected -D argument", LF, NULL
    convertFail db "Invalid number entered", LF, NULL
section .bss
;use C library and C code file
extern atof, ceil, printBalloonsRequired 
section .text
;Returns the length of the string (not including the null)
;as a 32 bit unsigned integer.
;rdi - address to NUll terminated string
global getStringLength
getStringLength:
    mov r10, 0  ;index
    mov rcx, 0 ;char
	getStringLengthLoop:
		mov cl, byte[rdi + r10] ;take one char
		cmp cl, NULL  ;check to see if end of string or not
		je getStringLengthDone ;if yes then jump to done   
		inc r10 ;index incr
	    jmp getStringLengthLoop
	getStringLengthDone:
        mov eax, r10d
        ret ;return eax

;determine the length of the string and use the write system service to
;print the string to the screen. 
;This function has no return value.
;rdi - address to ull terminated string
global printString
printString:
    push rbx ;prologue
    mov rbx, rdi ;mov rdi (string) to rbx
    call getStringLength ;get string
    mov r11, rax ;rax is value of length

        ;Call OS to output string
        mov rax, SYS_WRITE ;system code for write() 
        mov rsi, rdi ;address of chars to write
        mov rdi, STD_OUT ;standard out
                        ; RDX = count to write, set above
        mov rdx, r11
        syscall
        pop rbx
        ret

;rdi - argc (arg count)
;rsi = argv (starting address of arg vec)
global checkCommandLine
;rdi - argc (arg count)
;rsi - argv
;rdx - weight address
;rcx - diameter address
;check and convert the command line arguments.
checkCommandLine:
    ;check for argc
    cmp rdi, 1 
    je oneArgument ;error
    cmp rdi, 5
    jne notEnough ;error

    ;check for flags -W 
    mov rcx, qword[rsi + 8] ;2nd pos so +8
    cmp byte[rcx], '-'
    jne notFlagW
    cmp byte[rcx + 1], 'W'
    jne notFlagW
    cmp byte[rcx + 2], NULL
    jne notFlagW
    ;if not wrong then continue check other things
    ;clear rcx
    mov rcx, 0
    ;check for flags -D
    mov rcx, qword[rsi + 24]  ;4th pos so +24
    cmp byte[rcx], '-'
    jne notFlagD
    cmp byte[rcx + 1], 'D'
    jne notFlagD
    cmp byte[rcx + 2], NULL
    jne notFlagD

    ;Align stack to ultiple of 16
    mov rax, rsp 
    mov rcx, 16
    mov rdx, 0
    div rcx    
    sub rsp, rdx   
    mov rbx, rdx

    ;clear rcx
    mov rcx, 0
    ;to save the address of rsi as call function will mess up scratch regs
    push rsi 
    ;check for weight
    mov rdi, qword[rsi+ 16] ;5th argu
    ;call c function
    call atof
    ;check return value with 0.00
    ucomisd xmm0, qword[valueError]
    jbe valueErr
    ;pop to clear it and return it back to correct order
    pop rsi
    ;restore stack to prev alignment
    add rsp, rbx

    ;Align stack to ultiple of 16
    mov rax, rsp 
    mov rcx, 16
    mov rdx, 0
    div rcx    
    sub rsp, rdx   
    mov rbx, rdx

    ;mov the value into weight if it's correct
    movsd qword[weight], xmm0
    ;to save the address of rsi as call function will mess up scratch regs
    push rsi
    mov rdi, qword[rsi + 32] ;3rd argument ;new
    ;call c function
    call atof
    ;check return value with 0.00
    ucomisd xmm0, qword[valueError]
    jbe valueErr
    ;pop to clear it and return it back to correct order
    pop rsi 
    ;restore stack to prev alignment
    add rsp, rbx
    ;mov the value into diameter if it's correct
    movsd qword[diameter], xmm0
    jmp correct     
    
    ;if invalid value enter (ex: string instead of numbers)
    valueErr:
        ;pop to clear it and return it back to correct order
        pop rsi
        ;to save the address of rsi as call function will mess up scratch regs
        push rsi
        mov rdi, convertFail
        call printString
        ;pop to clear it and return it back to correct order
        pop rsi
        ;rax value for invalid number
        mov rax, -3   
        jmp done

    oneArgument: ;error for wrong argc
        mov rdi, singleCommandErr
        call printString
        mov rax, 0 ;value for error: 1 argument
        jmp done

    notEnough: ;error for wrong argc
        mov rdi, not5
        call printString
        mov rax, -1   ;value for error: #'s' argument != 5
        jmp done
    
    notFlagW: ;error for wrong flag 
        mov rdi, notW
        call printString
        mov rax, -2    ;value for error: not flag W
        jmp done

    notFlagD: ;error for wrong flag 
        mov rdi, notD
        call printString
        mov rax, -4 ;value for error: not flag D
        jmp done

    correct: ;correct case 
        mov rax, 1 ;value for correct case
        jmp done
    done:
        ret

;xmm0 - weight
;xmm1 - diameter
;calculate the number of balloonsrequired to lift the specified weight using the formulas above.  
;Return the number of balloons required.
global balloonCalculate   
balloonCalculate:
    movsd xmm2, qword[valueCal1] ;4
    divsd xmm2,  qword[valueCal2] ;4/3
    mulsd xmm2, qword[pi] ; 4/3 * pi
    divsd xmm1, qword[valueCal3] ;diameter/2
    movsd xmm3, xmm1
    mulsd xmm1, xmm3 ;(xmm1) ^3
    mulsd xmm1, xmm3
    mulsd xmm1, xmm2 ;xmm1 = volume

    ;calculate for balloonVolume
    mulsd xmm1, qword[helium] ;helium * volume == xmm1
    divsd xmm0, xmm1 ; weight/total == xmm0 == result
    
    ;Align stack to ultiple of 16
    mov rax, rsp 
    mov rcx, 16
    mov rdx, 0
    div rcx    
    sub rsp, rdx   
    mov rbx, rdx

    ;call ceil and return value
    call ceil   
    
    ;restore stack to prev alignment
    add rsp, rbx
    ; mov round up value into variable
    movsd qword[balloonNeed], xmm0
    ret
global main
main:
    ;store argc and argv for later use
    mov r9, rdi
    mov r10, rsi

    ;mov rdx and rcx for the function
    mov rdx, weight
    mov rcx, diameter
    call checkCommandLine

    ;if it is 1 then it's correct if not, then wrong and end program
    cmp rax, 1 
    jne errorCase  

    ;if correct then mov value of weight and diameter to call calculate balloonNeed
    movsd xmm0, qword[weight] ;weight
    movsd xmm1, qword[diameter]
    call balloonCalculate
    
    ;Align stack to ultiple of 16
    mov rax, rsp 
    mov rcx, 16
    mov rdx, 0
    div rcx    
    sub rsp, rdx   
    mov rbx, rdx

    ;mov variables into regs for call C++ fucntion from helper file
    movsd xmm0, qword[weight]
    movsd xmm1, qword[diameter]
    movsd xmm2, qword[balloonNeed]
    call printBalloonsRequired
    ;restore stack to prev alignment
    add rsp, rbx
    jmp endProgram
    ;error case just end the program
    errorCase:
        jmp endProgram
    
endProgram:
    mov rax, SYS_EXIT
    mov rdi, EXIT_SUCESS
    syscall