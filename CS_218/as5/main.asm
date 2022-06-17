
;description = repeatedly prompt a user to input
;integer numbers until they enter “Quit”. You must use the
;functions below to prompt the user, check their response,
;and convert to an integer. Output “Valid Numeric Value” if
;their number is accepted.
section .data 
    ;const var
    STD_IN equ 0
    STD_OUT equ 1; standard output
    SYSTEM_WRITE equ 1; write   
    SYS_READ equ 0 ;read
    LF   equ 10 ;line feed
    NULL equ 0  ;end of string
    SYS_EXIT equ 60; termination
    EXIT_SUCESS equ 0 ; successful code

    MAX equ 2147483647 ;
    MIN equ -2147483648
    BUFFER_SIZE equ 100 

    ;prompt and error messages
    prompt db "Enter number: ", NULL
    quit db "Quit", NULL
    overflowError db "Error: Buffer overflow. Need to be under 100", LF, NULL
    QuitMessage db "End program", LF, NULL

    belowError db "Number Below Minimum Limit", LF, NULL
    aboveError db "Number Above Maximum Limit", LF, NULL
    noDigitError db "No Digits", LF, NULL
    unexpectedError db "Unexpected character ",LF, NULL
    spaceAfter db "Unexpected Character Space after sign", LF, NULL
    validMess db "Valid Numeric Value", LF, NULL
    invalidMess db "Invalid Numeric Value", LF, NULL
section .bss
    ;uninitialized var for program
    stringBuffer resb 100
    valueConvert resd 1
section .text

;Returns the length of the string (not including the null)
;as a 32 bit unsigned integer.
;rdi - address to NUll terminated string
global getStringLength
getStringLength:
    mov r10, 0  ;index
	getStringLengthLoop:
		mov bl, byte[rdi + r10] ;take one char
		cmp bl, NULL  ;check to see if end of string or not
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
        mov rax, SYSTEM_WRITE ;system code for write() 
        mov rsi, rdi ;address of chars to write
        mov rdi, STD_OUT ;standard out
                        ; RDX = count to write, set above
        mov rdx, r11
        syscall
        pop rbx
        ret

;use the print system service (above) to
;output a request to the user and read in the user’s
;response using a read system service. Check that the data
;returned from the user fits within the specified buffer.
;Replace the linefeed with a null character. If it does not
;fit within the buffer, clear any remaining input and return -1
; if fit, return size of input include null
;1st - rdi - string prompt
;2nd - rsi  - string buffer
;3rd - rdx  - max
global promptUser
promptUser:
    push rbx    ;prologue
    mov rbx, 0
    ;display prompt
    call printString

    ;read
    mov rax, SYS_READ
    mov rdi, STD_IN
    mov rsi, stringBuffer
    mov rdx, BUFFER_SIZE
    syscall

    checkOverflowLoop:
        cmp byte[stringBuffer + rbx], LF 
        je inputDone ;if ==
        inc rbx  
        cmp rbx, rdx ; rdx -buffer size
        jb checkOverflowLoop ;if rbx <= rdx
        ;error case
        ;mov rbx, 0
        clearBufferLoop:
            mov rax, SYS_READ
            mov rdi, STD_IN
            mov rsi, stringBuffer
            mov rdx, 1
            syscall
            cmp byte[stringBuffer], LF
            jne clearBufferLoop ;if not linefeed, then continue clear
            jmp errCase
    errCase:
        mov rax, -1
        jmp promptDone
    inputDone:
        mov byte[stringBuffer + rbx], NULL ;add NULL terminator
        mov rax, rbx
        jmp promptDone
    promptDone: 
        pop rbx
        ret

;Compare the strings character by character. If the first
;string is greater, return 1. If the second string is
;greater, return -1. Otherwise, return 0 if they are equal.
;1st = address to null terminated string -rdi
;2nd = address to null terminated string -rsi
global compareString
compareString:
    compareStringLoop:
		mov al, byte[rdi] ;take one char
        mov bl, byte[rsi] ;take one char
		cmp al, bl  ;check ascii value
		jne notEqual  

        cmp byte[rdi], NULL ;check to see end of string
        je checkAgain

        inc rdi    
        inc rsi   

        jmp compareStringLoop

    checkAgain:
        cmp byte[rsi], NULL ;same with above
        je equal    
    notEqual:
        cmp al, bl  
        jg string1 ; str1 > str2
        mov rax, -1   ;string2
        jmp done
    string1:
        mov rax, 1  
        jmp done
    equal:
        mov rax, 0
        jmp done
	done:
        ret ;return rax

;convert an integer format string to its signed 32 bit
;integer equivalent. In addition, the function must do some
;error checking to ensure that the string is correctly formatted.
;In addition, spaces should be allowed before the sign or
;after the final digit in the string.
;Output an appropriate message if an error occurs. These
;error messages should be stored as global variables.
;Return a 1 if the number is converted successfully, or -1 otherwise.
;1st -address to null terminated string - rdi
;2ns ; address to 32 bit location to store convert - rsi
global stringTo32Int
stringTo32Int:
    push rbx   ;flag for sign
    push r12 ;flag for digits
    push r13 
    mov r9, 0 ;blank 
    mov r13, 0 ;blank
    mov rcx, 0 ;flag for nodigit
    mov rax, 0 ;use for converse
    mov r10, 0 ;used to hold char   
    mov rbx, 0 ;reset rbx    
    mov qword[rsi], 0; reset value  

    checkSpace: ;ignore space
        cmp byte[rdi], ' ' ;check space
        jne findChar  ;if not space -> char
        inc rdi 
        inc rcx
        jmp checkSpace

    findChar:
        cmp byte[rdi], NULL
        je doneLoop
    convertLoopString:
        mov r11b, byte[rdi] ;each char
        cmp r11b, NULL ;end of string
        je doneLoop ;if char == NULL then done loop
        cmp r11b, ' '
        je doneLoop ;if char == ' ' then done

        cmp r11b, '0' ; if < '0'
        jb checkSign
        cmp r11b, '9' ;check sign
        ja character ;unexpected char

        sub r11b, '0' ;convert to digit
        mov r12, 1
        mov r8, 10
        imul r8
        movsx r11, r11b  ;extend byte to 32
        add rax,r11 ;add num in that digit
        mov qword[rsi], rax
        inc rdi
        inc rcx
        jmp convertLoopString

    ;unexpected error
    character:
        cmp r12, 1 ;check flag to see if there is digits
        jne noDigit
        mov rdi, 0

        ;add char to error  string
        ;mov rdi, unexpectedError
        ;call getStringLength 
        ;mov r13, rax ;lenbth 1st string
        ;add byte[unexpectedError + r13], r11b
        mov rdi, unexpectedError
        call printString
        jmp failCase

    ;no digit error
    noDigit:
        mov rdi, noDigitError
        call printString
        jmp failCase

    ;check for sign
    checkSign:
        cmp rbx, -1 ;check to see if negative sign 
        je errorString
        cmp rbx, 1  ;check to see if positive sign 
        je errorString
        cmp r11b, '-'
        je negative
        cmp r11b, '+'
        je positive
        jmp errorString

    ;negative sign
    negative:
        mov rbx, -1    ;flag for sign
        inc rdi ;go to next one
        inc rcx
        cmp byte[rdi], NULL ;check to see if end of not
        je errorString
        cmp byte[rdi], ' ' ;check for space error
        je spaceError
        jmp convertLoopString
    positive:
        mov rbx, 1 ;flag for sign
        inc rdi  ;go to next one
        inc rcx
        cmp byte[rdi], NULL ;check to see if end of not
        je doneLoop
        cmp byte[rdi], ' ' ;check for space error
        je spaceError
        jmp convertLoopString
    ;check for space error
    spaceError:
        mov rdi, spaceAfter
        call printString
        jmp failCase

    ;extra check
    errorString:
        jmp noDigit

    ;done convertLoopString
    doneLoop:
        cmp rcx, 1  
        je noDigit
        cmp rbx, 0 ;check to see if negative or not
        jge checkValue
        mov r8, -1 
        imul r8
        jmp checkValue
    ;check for max and min
    checkValue:
        cmp rax, -2147483648
        jl underMin
        cmp rax, 2147483647
        jg aboveMax

        jmp validCase

    ;min case
    underMin:
        mov rdi, belowError
        call printString
        jmp failCase
    ;max case
    aboveMax:
        mov rdi, aboveError
        call printString
        jmp failCase

    ;fail case return -1
    failCase:
        mov qword[rsi], rax
        mov rax, -1   
        jmp convertDone
    ;valid case return 1
    validCase:
        mov qword[rsi], rax
        mov rax, 1
        jmp convertDone
    convertDone:
        pop rbx
        pop r12
        pop r13
        ret
global _start
_start:

    ;main loop
    inputLoop:
        ;put variables into registers
        mov rdi, prompt
        mov rsi, stringBuffer
        mov rdx, BUFFER_SIZE
        call promptUser

        ;check to see if overflow or not
        cmp rax, -1   
        je overflow   

        ;put var into regs
        mov rdi, stringBuffer
        mov rsi, quit
        call compareString

        ;check to see if quit ot not
        cmp rax, 0
        je Quit

        ;put var into regs
        mov rdi, stringBuffer
        mov rsi, valueConvert
        call stringTo32Int
        
        ;check if can convert or not
        cmp rax, -1   
        je invalid   

        mov rdi, validMess
        call printString
        jmp inputLoop
    ;error
    invalid:
        mov rdi, invalidMess
        call printString
        jmp inputLoop
    ;error
    overflow:
        mov rdi, overflowError
        call printString
        jmp Quit

    Quit:
        mov rdi, QuitMessage
        call printString
        jmp endProgram
endProgram:
	mov rax, SYS_EXIT
	mov rdi, EXIT_SUCESS
	syscall