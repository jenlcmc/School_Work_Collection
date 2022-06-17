
;Description = This program will involve using the buffered I/O algorithm 
;to efficiently analyze a large text file.
section .data
;const variables
LF          equ     10  ;linefeed
NULL        equ     0   ;end of string
STD_IN      equ     0  
STD_OUT     equ     1 
STD_ERR     equ     2
EXIT_SUCESS equ     0
SYS_EXIT    equ     60
SYS_READ    equ     0   ;read
SYS_OPEN    equ     2 ;file open
SYS_WRITE   equ     1
SYS_CLOSE   equ     3
O_RDONLY    equ     000000q
BUFF_SIZE   equ     100000
;variables for the code
newline     db      LF, NULL
header      db      "File Text: ", LF, NULL
fileDesc    dq     0
echoOptions dd     0
;error string
errorOpen   db      "Could not open '", NULL
errorOpen2  db      "'", LF, NULL
readError   db      "Can't read the file", LF, NULL
endOfFile   db      "End of the file", LF, NULL
oneArgu1    db      "To use this program include the name of the file you wish to analyze.", LF, NULL
oneArgu2    db      "-echo may be added to print the file to the terminal.", LF, NULL
manyErr     db      "Incorrect number of arguments.", LF, NULL
invalid     db      "Invalid argument.", LF, NULL
;sucess and result string
valid       db      "File text:", LF, NULL
strWord     db      ""
strAverage  db      ""
strLetter   db      ""
tempWord    db      "Word Count: ", NULL
tempAverage db      "Average Word Length: "

section .bss
;uninitialized variables
    value               resq    1
    characterRead       resq    1
    characterBuffer     resq    1
    bufferIO            resb    BUFF_SIZE
    eof                 resq    1
    wordNumber          resq    1
    average             resq    1
    letter              resq    1
    special             resq    1 
    readBuffer          resb    BUFF_SIZE
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

;rdi -ascii value  
;retrieve a single character from the buffer as described in the buffer I/O algorithm. 
; Store thecharacter into a pass by reference argument.  
;The buffer variables and file descriptor may be accessed globally.  
;Return 1 if a character was retrieved succesfully, 
;0 if there are no more characters to retrieve, 
;and -1 if an error occurred during the read system service call.
global getCharacter
getCharacter:
    push rbx
    mainLoop:
        ;mov vars to regs
        mov r9, qword[characterRead]
        mov r10, qword[characterBuffer]
        ;check if read < Buff
        cmp r9, r10
        jae bufferBigger

        mov rcx, qword[characterRead]
        mov bl, byte[bufferIO +  rcx] ;check each char
        mov byte[value], bl ;then mov back to ascii val
        inc qword[characterRead] ;inc read
        mov rax, 1  
        jmp finish

        bufferBigger:
            cmp qword[eof], 1  ;check if eof or not
            jne notEOF
        
            mov rax, 0
            jmp finish
        notEOF: ;if not then continue read
            mov rax, SYS_READ
            mov rdi, qword[fileDesc] ;write to fileDesc
            mov rsi, bufferIO
            mov rdx, BUFF_SIZE
            syscall

            cmp rax, 0   ;check to see if can read or not
            jl cantRead
            jge keepGoing
            keepGoing: ;if can read then check if return < buff_size or not
                cmp rax, BUFF_SIZE
                jl endFile
                jge continueLoop

        cantRead: ;read err case
            mov rax, -1 
            mov rdi, readError
            call printString
            jmp finish

        endFile: ;end of file case
            inc qword[wordNumber]
            mov qword[eof], 1
            jmp continueLoop

        continueLoop: ;clear the var for read again
            mov qword[characterBuffer], rax
            mov qword[characterRead], 0
            jmp checkTwice

        checkTwice:
            jmp mainLoop
    finish:
        pop rbx
        ret

;rdi - value to hold character
;retrieve a single character from the buffer as described in the buffer I/O algorithm. 
; Store thecharacter into a pass by reference argument.  
;The buffer variables and file descriptor may be accessed globally.  
;Return 1 if a character was retrieved succesfully, 
;0 if there are no more characters to retrieve, 
;and -1 if an error occurred during the read system service call.
global getWordCountAndAverage
getWordCountAndAverage:
    mov r8, qword[special] ;store value into regs
    mov r9, qword[wordNumber]
    mov r10, qword[letter]
    mov rax, 0
    mov r11, r8 ;store char
    mov r11, 0
    mov rdx, 0
    checkSpace:
        cmp byte[value], ' ' ;check space
        jne findChar  ;if not space -> char
        je whiteSpace 
        cmp byte[value], 9 ;check tab
        jne findChar
        je whiteSpace 
        cmp byte[value], 10 ;check linefeed
        jne findChar ;if not space -> char
        je whiteSpace 
        cmp byte[value], 12 ;form feed
        jne findChar
        je whiteSpace 
        cmp byte[value], 13 ;check for carriage return
        jne findChar
        je whiteSpace 
    whiteSpace:
        cmp r8, 0  
        je doneFind
        inc r9 ;increase words if there is whitespacec
        jmp doneFind
    findChar:
        cmp byte[value], ' ' ;check space
        je whiteSpace
        cmp byte[value], 10 ;check linefeed in case of CRLF
        je whiteSpace
        cmp byte[value], 39 ;for '
        je specialCharacter
        cmp byte[value], '-'
        je specialCharacter
        mov r11 ,1
        cmp byte[value], 65 ;'A'
        jl doneFind
        cmp byte[value], 122 ;'z'
        jg doneFind
        inc r10 ;increase letter read
        jmp doneFind

    specialCharacter:
        inc rax ;increase special char read
        jmp doneFind
    doneFind:
        mov qword[wordNumber], r9 
        sub qword[wordNumber], rax
        mov qword[letter], r10
        mov qword[special], r11
        ret

;	Converts a signed 32 bit integer to a null terminated string representation
;	Argument 1: 32 bit integer
;	Argument 2: Address to a string (12 characters maximum)
%macro int64ToString 2
	mov rcx, 0 ; characters written
	
	mov rax, %1
	; Check for negative value
	cmp rax, 0
	jge %%nonNegativeValue
		mov byte[%2 + rcx], '-' 
		mov rbx, -1
		imul rbx
		inc rcx
	%%nonNegativeValue:

	;	Calculate digits in reverse order
	mov r10, 10
	mov rbx, 0 ; push count
	%%pushLoop:
		cdq
		idiv r10
		
		; Store digits onto stack
		push rdx
		inc rbx
	cmp rax, 0
	jne %%pushLoop

	%%writeLoop:
		pop rdx
	
		; Convert remainder to digit character
		add dl, '0'
	
		mov byte[%2 + rcx], dl
		
		inc rcx
		dec rbx
	cmp rbx, 0
	jne %%writeLoop

	; Null terminate string
	mov byte[%2 + rcx], NULL
%endmacro

global checkCommandLine
;rdi - argc (arg count)
;rsi - argv
;check and convert the command line arguments.
checkCommandLine:
    push r9
    ;check for argc
    cmp rdi, 1 
    je oneArgument ;rdi == 1
    jne continue
    continue:
        cmp rdi, 2 
        jb tooMany ;if rdi < 2
        je noEcho
        cmp rdi, 3
        ja tooMany ;if rdi > 3
        je haveEcho ;if rdi == 3

    noEcho:
        mov r10d, 0 
        mov dword[echoOptions], r10d
        jmp openFile
    openFile:
        mov rax, SYS_OPEN ;file open for reading
        mov rdi, qword[rsi + 8] ; name of the file
        mov r9, qword[rsi + 8]
        mov rsi, O_RDONLY ;read only access to the file
        syscall ;call for kernel

        cmp rax, 0  ;check for sucess  
        jl cantOpen ;rax < 0

        ;otherwise ,rax, fileDesc
        mov qword[fileDesc], rax ;save if can open
        jmp correctCase

    cantOpen:
        mov rdi, errorOpen
        call printString
        mov rdi, r9
        call printString
        mov rdi, errorOpen2
        call printString
        jmp errorCase

    haveEcho:
        mov r10d, 1
        mov dword[echoOptions], r10d
        ;check for flags -W 
        mov rcx, qword[rsi + 16] ;2nd pos so +8
        cmp byte[rcx], '-'
        jne notEcho
        cmp byte[rcx + 1], 'e'
        jne notEcho
        cmp byte[rcx + 2], 'c'
        jne notEcho
        cmp byte[rcx + 3], 'h'
        jne notEcho
        cmp byte[rcx + 4], 'o'
        jne notEcho
        cmp byte[rcx + 5], NULL
        jne notEcho
        jmp openFile

    notEcho:
        mov rdi, invalid
        call printString
        jmp errorCase

    oneArgument:
        mov rdi, oneArgu1
        call printString
        mov rdi, oneArgu2
        call printString
        jmp errorCase

    tooMany:
        mov rdi, manyErr
        call printString
        jmp errorCase

    errorCase:
        mov rax, -1
        jmp done

    correctCase:
        
        mov rax, 1 
        jmp done

    done:
        pop r9
        ret
global main
main:
    call checkCommandLine ;call to check command line
    cmp rax, 1 ;if 1 then it is good 
    jne endProgram ;error
    cmp dword[echoOptions], 1 ;check to see if need to echo or not
    je printHeader
    jne noPrint

    printHeader: ;this case is no echo
        mov rdi, valid
        call printString
        jmp printOut
    printOut: ;echo option
        mov rdi, value
        call getCharacter ;call function to get char

        cmp rax, 1 ;if it's 1 then good. otherwise bad
        jne final

        mov rdi, value ;print out each char until eof
        call printString

        mov rdi, wordNumber ;pass by reference
        mov rsi, average
        call getWordCountAndAverage ;call function to count words
        jmp printOut
        
    noPrint: ;no echo then no need to print out the file
        mov rdi, value
        call getCharacter

        cmp rax, 1 
        jne final

        mov rdi, wordNumber
        mov rsi, average
        call getWordCountAndAverage
        jmp noPrint

    final: ;print out result
        mov rdi, newline
        call printString

        mov rdi, newline
        call printString

        mov rdi, tempWord ;pass to print out the template for result
        call printString
        int64ToString qword[wordNumber], strWord ;call macros to convert
        mov rdi, strWord 
        call printString ;call to print out result

        mov rdi, newline
        call printString

        mov rdi, tempAverage ;pass to print out the template for result
        call printString

        ;calculate work for average
        mov rax, qword[letter]
        cqo  
        idiv qword[wordNumber]
        mov qword[average], rax

        int64ToString qword[average], strAverage ;call macros to convert
        mov rdi, strAverage ;call to print out result
        call printString
        
        jmp endProgram
    
endProgram:
    mov rdi, newline
    call printString
    mov rax, SYS_EXIT
    mov rdi, EXIT_SUCESS
    syscall