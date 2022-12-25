#lang racket

;; Project #11

; -----
;  Predicates - iseven? or isodd?
; return a true if the argument, an atom, is even. Return false otherwise.
; use modulo function to determine if the number is even or odd.
; -----
(define (iseven? n)
  ; if n is 0, then it is even then return true
  (if (= (modulo n 2) 0)
      #t
      #f))

; -----
(define (isodd? n)
  ; if n is 0, then it is even then return false
  (if (= (modulo n 2) 0)
      #f
      #t))

(newline)
(display "Even Tests -> (iseven? atm) \n")
(iseven? 10)
(iseven? 21)
(iseven? 50)
(iseven? 97)
(newline)

(display "Odd Tests -> (isodd? atm) \n")
(isodd? 10)
(isodd? 21)
(isodd? 50)
(isodd? 97)
(newline)

; -----
;  Multiply all numbers in a list, including sublists.
;  [i.e.,   (product '(1 2 3) = 6 ]
; [i.e.,   (product '(1 2 (3 4)) = 24 ]
; no use of built-in functions like car or cdr
; using first and last instead of car and cdr
; -----
(define (prod lst)
  ; if the list is empty, then return 1
  (if (null? lst)
      1
      ; if the first element is a list, then multiply the first element
      ; with the product of the rest of the list
      (if (list? (first lst))
          (* (prod (first lst)) (prod (rest lst)))
          ; if the first element is not a list, then multiply the first element
          ; with the product of the rest of the list
          (* (first lst) (prod (rest lst))))))


(display "Product Tests -> (prod lst) \n")
(prod '(2 3 4 5))
(prod '(10 20 30))
(prod '(2 3 (2 3) 4 5))
(prod '(2 2 2 2))
(prod '(2 2 (2 2 (2 2 2) 2)))
(prod '())
(newline)

; -----
;  Multiply each element of a list by n.
;  [i.e.,   (lstmul 2 '(2 3 4)) = (list 4 6 8)]
;  [i.e., (lstmul 2 '(1 2 (3 4))) = (list 2 4 (list 6 8)) ]
; no use of built-in functions cdr and car (use first and rest instead)
; -----
(define (lstmul n lst)
  ; if the list is empty, then return an empty list
  (if (null? lst)
      '()
      (if (list? (first lst)) ; if the first element is a list
          (cons (lstmul n (first lst)) (lstmul n (rest lst))) ; multiply the first element
          (cons (* n (first lst)) (lstmul n (rest lst)))))) ; multiply the rest of the list


(display "List Multiplication Tests -> (lstmul lst) \n")
(lstmul 2 '(2 3 4))
(lstmul 5 '(2 4 6 8))
(lstmul 2 '(1 2 (3 4)))
(lstmul 10 '(10 20 30 40))
(lstmul 2 '(100 200 (300 400)))
(lstmul 2 '(1 2 (3 4 (5 6) (7 8) 9) 10 (11) 12))
(lstmul 12 '())
(lstmul 10 '(10 20 (10 20) 30 40))
(lstmul 2 '(2 4 (2 4) 2 4 (2 2 (2 2)) 2 4))
(newline)

; -----
;  Sum numbers in a list, including sublists
;  [i.e.,   (sumlist '(2 3 4) = 9 ]
; [i.e., (sumlist '(1 2 (2 3) 4)) = 12 ]
; no use of built-in functions
; use first and last instead of car and cdr
; -----
(define (sumlist lst)
  ; if the list is empty, then return 0
  (if (null? lst)
      0
      (if (list? (first lst)) ; if 1st elem is list
          ; then add the first element with the sum of the rest of the lis
          (+ (sumlist (first lst)) (sumlist (rest lst)))
          (+ (first lst) (sumlist (rest lst))))))

(display "Sum List Tests -> (sumlist lst) \n")
(sumlist '(1 2 3 4 5 6 7 8 9))
(sumlist '(1 2 (2 3) 4))
(sumlist '(100 200 300 400 4 3 2 1))
(sumlist '(1 2 (3 4 (5 6 (7 8 (9 10) 11)) 12) 13 14))
(sumlist '())
(newline)

; -----
;  Length of a list.
;  [i.e.,   (len '(1 2 3 4 5 6 7 8)) = 8 ]
; [i.e., (len '(7 9 (1 4) 2)) = 5 ]
; no use of built-in functions
; use first and last instead of car and cdr
; because it is only for lists (that are not empty).
; we will need to modify the code to work with empty lists.
; -----
(define (len lst)
  ; if the list is empty, then return 0
  (if (null? lst)
      0
      (if (list? (first lst))
          (+ (len (first lst)) (len (rest lst)))
          (+ 1 (len (rest lst))))))


(display "Length Tests -> (len lst) \n")
(len '(1 2 3 4 5 6 7 8))
(len '(4))
(len '(7 9 1 4 2))
(len '(7 9 (1 4) 2))
(len '(1 1 (1 1 (1 1 1) 1 ) 1 (1 1 1)))
(len '())
(newline)

; -----
;  Average of list.
; returns average of a list, including sublists (use the previous functions).
;   [i.e., (average '(1 (2) 3 (4 5 (6 7) 8 (9) 10))) = 5.5 ]
;  [i.e.,   (average '(4 5 6 7 8)) = 6 ]
; [i.e., ((average '()) = 0 ]
; no use of built-in functions
; -----
(define (average lst)
  ; if the list is empty, then return 0
  (if (null? lst)
      0
      ; if it not empty then divide the sum of the list by the length of the list
      (/ (sumlist lst) (len lst))))


(display "Average Tests -> (average lst) \n")
(average '(4 5 6 7 8))
(average '(1 (2) 3 (4 5 (6 7) 8 (9) 10)))
(average '(21 32 46 51 69))
(average '(111 222 333))
(average '(3))
(average '())
(average '(4 5 (6 7) 8))
(average '(2 2 (4 4) 2 (4 2 (4 2) 2 4) 4))
(newline)

; -----
;  Flatten the list
;  [i.e.,   (flatten '(1 2 (3 4 (5 6)))) = (list 1 2 3 4 5 6) ]
;  [i.e.,   (flatten '(a ((c d) f) d)) = (list a c d f d) ]
; [(flatten '(a (((d f g)) e) h)) = (list a d f g e h) ]
; [i.e.,   (flatten '()) = '() ]
; it will need to deal with both numbers and symbols or characters
; and when a list is empty, it should return an empty list
; no use of built-in functions cdr and car (use first and rest instead)
; -----
(define (flatten lst)
  ; if the list is empty, then return an empty list
  (if (null? lst)
      '()
      (if (list? (first lst))
          (append (flatten (first lst)) (flatten (rest lst)))
          (cons (first lst) (flatten (rest lst))))))


(display "Flatten Lists Tests -> (flatten lst) \n")
(flatten '(1 2 (3 4 (5 6))))
(flatten '(1 2 (3 4 (5 6) 7 8 (9 10) 11 (12) 13 14) 15 16))
(flatten '(a ((c d) f) d))
(flatten '(a (((d f g)) e) h))
(flatten '())
(flatten '(1 1 (1 1 (1 1 1) 1 ) 1 (1 1 1)))
(newline)

; -----
;  Reverse all items in a list.
;  [i.e.,   (rvlst '(2 3 4 5)) = (list 5 4 3 2) ]
; [i.e., (rvlst '(1 2 (3 4) (5 6) 7 8)) = (list 8 7 (list 6 5) (list 4 3) 2 1) ]
; [i.e., (rvlst '()) = '() ]
; no use of built-in functions car and cdr
; it will need to reverse the sublists inside the list
; and maintain the order of the items in the list
; so we will need to reverse the list and check if it has sublists
; if it is then we will reverse the sublist and continue to reverse the list
; and it will need to be in order of the original list
; -----
(define (rvlst lst)
  ; if the list is empty, then return an empty list
  (if (null? lst)
      '()
      (if (not (list? (first lst)))
          (append (rvlst (rest lst)) (list (first lst)))
          (append (rvlst (rest lst)) (list (rvlst (first lst)))))))


(display "Reverse List Tests -> (revlst lst) \n")
(rvlst '(1 2 3 4 5 6))
(rvlst '(1 2 (3 4) (5 6) 7 8))
(rvlst '(9 87 6 5 4 3 2 1))
(rvlst '(10 20 30 40))
(rvlst '())
(rvlst '(9 8 (7 6 (5 4) 3) 2 1))
(newline)

; -----
;  Remove first occurance of item from a list.
;  [i.e.,   (rmFirstOcc 3 '(2 3 4 3)) = (list 2 4 3) ]
; [i.e., (rmFirstOcc 5 '(1 2 (3 4 (5) 6))) = (list 1 2 (list 3 4 empty 6)) ]
; no use of built-in functions
; without using cdr and car
; -----
(define (rmFirstOcc item lst)
  ; if the list is empty, then return empty list
  (if (null? lst)
      '()
      ; if the first item in the list is equal to the item we want to remove
      ; then return the rest of the list
      (if (equal? (first lst) item)
          (rest lst)
          ; if the first item in the list is a list
          ; then use append to return a new list
          (if (list? (first lst))
              (append (list (rmFirstOcc item (first lst))) (rmFirstOcc item (rest lst)))
              (cons (first lst) (rmFirstOcc item (rest lst)))))))


(display "Remove First Occurance of Item from List Tests -> (rmFirstOcc lst) \n")
(rmFirstOcc 3 '(2 3 4 3))
(rmFirstOcc 18 '(12 14 87 12 18))
(rmFirstOcc 5 '(1 2 (3 4 (5) 6)))
(rmFirstOcc 3 '(2 3 4 3))
(rmFirstOcc 9 '(1 3 5 7 9 11 13))
(rmFirstOcc 3 '(4 7 (5 2) (8 1) (9 2 (3 1))))
(rmFirstOcc 8 '(0 2 (4 6 (8 10) 12) 14 16))
(rmFirstOcc 10 '())
(rmFirstOcc 50 '(10 (20 (30 (40 (50 60) 70) 80) 90) 100))
(newline)

; -----
(define (minimum lst)
  ; if the list is empty, then return empty list
  (if (null? lst)
      '()
      ;check for number
      (if (number? (first lst))
          ; check for null list
          (if (null? (rest lst))
              (first lst)
              ;compare to find min
              (if (< (first lst) (minimum (rest lst)))
                  (first lst)
                  (minimum (rest lst))))
          ; if it is character or symbol then check null agains
          (if (null? (rest lst))
              ; if it is then return the first element
              (minimum (first lst))
              ; if not then we need to compare the first element with the minimum of the rest of the list
              (if (< (minimum (first lst)) (minimum (rest lst)))
                  (minimum (first lst))
                  (minimum (rest lst)))))))

(display "Minimum Item in List Tests -> (minimum lst) \n")
(minimum '(5 4 3 2 1))
(minimum '((2 3) 7 5 (6 1)))
(minimum '(5 2 7))
(minimum '(4121 3532 5522))
(minimum '((9 8) 1))
(minimum '(26 18 (27 21 19 (12 21 (7 10) 15) 17)))
(minimum '(12 15 12 (71 34 (51 9)) 61))
(minimum '(21 15 (71 34 (51 (37 4)) 61) 32 41 18))
(minimum '())
(newline)

; -----
; Insertion Sort
;  [i.e.,   (insertion-sort '(9 1 8 2 7 3 6 4 5)) = (1 2 3 4 5 6 7 8 9) ]
; no use of built-in functions
; no use cdr and car
; -----
(define (insertion-sort lst)
  ; if the list is empty, then return empty list
  (if (null? lst)
      '()
      ; if it not empty then use insert to return a new list by inserting the first element of the list
      (insert (first lst) (insertion-sort (rest lst)))))

;helper function with help of funcion we wrote earlier
(define (insert item lst)
  ; if the list is empty, then return empty list
  (if (null? lst)
      (list item)
      ; if the item is less than the first element of the list
      ; then return a new list with the item and the rest of the list
      (if (< item (first lst))
          (cons item lst)
          ; if the item is greater than the first element of the list
          ; then return a new list with the first element of the list and the rest of the list
          (cons (first lst) (insert item (rest lst))))))

(display "Insertion Sort Tests -> (insertion-sort lst) \n")
(insertion-sort '(5 9 8 4 2))
(insertion-sort '(5 9 2))
(insertion-sort '(5 9 1 2))
(insertion-sort '(12 7 3 5 9 11 1 8 10 4 2 6 12 1))
(newline)

; -----
;  Sqaure program.
;  Read a number from the user and output its value squared and cubed.
;  Note, uses built-in (read) function
; -----
(define (sqr-and-cube)
  (display "---------------------------------------------------")
  (newline)

  (display "Square and Cube Program.")
  (newline)
  (display "Give me a number, and I'll compute its square and cube.")
  (newline)
  (newline)
  (display "Number: ")
  (define num (read))
  (newline)
  (display "The square of ")
  (display num)
  (display " is ")
  (display (* num num))
  (newline)
  (display "The cube of ")
  (display num)
  (display " is ")
  (display (* num num num))
  (newline))

(sqr-and-cube)

; -----
;  Simple list stats program.
;  Read a list from the user and compute the
;  length, sum, and average.
;  Note, also uses built-in (read) function
;  Also sorts lists and displays.
; You do not need to handle invalid/incorrect input.
; Should use many of the previously defined functions (from above as needed).
; -----
(define (liststats)
  (newline)
  (newline)
  (display "List: ")
  (define lst (read))
  (newline)
  (newline)
  (display "---------------------------------------------------")
  (newline)

  (display "List Stats Program.")
  (newline)
  (newline)

  (display "length: ")
  (display (length lst))
  (newline)
  (display "average: ")
  (display (average lst))
  (newline)
  (display "minimum: ")
  (display (minimum lst))
  (newline)
  (display "sum: ")
  (display (sumlist lst))
  (newline)
  (display "product: ")
  (display (prod lst))
  (newline)
  (newline)
  (display "unsorted list: ")
  (newline)
  (display lst)
  (newline)
  (display "sorted list: ")
  (newline)
  (display (insertion-sort lst))
  (newline)
  )


(liststats)
