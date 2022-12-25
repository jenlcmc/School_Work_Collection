/**
 * 1/Write a Prolog program to display the distances traveled by each of the following 
vehicles, given their speeds and time on a fictional race track.
if vehicle is ford then speed is 100 and time is 20 then distance is 2000
ford, speed=100, time=20
chevy, speed=105, time=21
dodge, speed=95, time=24
volvo, speed=80, time=24
It will take the name of the vehicle and calculate the distance traveled.
Output should look something like the following:
| ?- distance(chevy).
Distance traveled by chevy was 2205
*/

distance(Vehicle) :-
    speed(Vehicle, Speed),
    time(Vehicle, Time),
    Distance is Speed * Time,
    write('Distance traveled by '), write(Vehicle), write(' was '), write(Distance), nl.

speed(ford, 100). % speed of ford is 100
speed(chevy, 105).
speed(dodge, 95).
speed(volvo, 80).

time(ford, 20).
time(chevy, 21).
time(dodge, 24).
time(volvo, 24).

/**
 * 2/Write a Prolog program to display a list of all combinations/permuation of an ice cream cone with strawberry, 
chocolate, and vanilla scoops. 
Output should look something like the following:
| ?- ice_cream(strawberry, chocolate, vanilla).
*/
ice_cream(Scoop1, Scoop2, Scoop3) :-
    write('Ice cream cone with '), write(Scoop1), write(', '), write(Scoop2), write(', and '), write(Scoop3), nl.




/**
 * Write a prolog program to solve the 
following puzzle: 
There is a monkey at the door into a 
room.  In the middle of the room a 
banana is hanging from the ceiling.  The 
monkey is hungry and wants to get the 
banana, but he can not stretch high 
enough from the floor.  At the window 
of the room there is a box the monkey 
can use.  The monkey can perform the following actions: walk on the floor, climb the 
box, push the box around (if the monkey is at the box), grasp the banana if standing on 
the box directly under the banana.  Can the monkey get the banana? 
Output:
| ?- getfood(state(atdoor,atwindow,onfloor,hasnot)).
 Monkey is at the door.
----------------------------------------
-> Monket pos: atdoor, middle, atwindow (H)
-> box pos: atdoor, middle, atwindow
-> Monkey pos: onbox, onfloor (V)
-> has banana: has, hasnot
-> inital state: state(monkey pos(H), box pos, monkey pos(V), has banana)
->Goal: state(middle, middle, onbox, has)
----------------------------------------
-> graps only if onbox and at middle 
-> climb only if onfloor and at box pos (V)
-> push only if at bos pos
-> walk only if to new pos (H)
*/

perform(
    graps,
    state(middle, middle, onbox, hasnot),
    state(middle, middle, onbox, has)
).

perform(
    climb,
    state(MP, BP, onfloor, H),
    state(MP, BP, onbox, H)
).

perform(
    pushbox,
    state(P1, P1, onfloor, H),
    state(P2, P2, onfloor, H)
).

perform(
    walk,
    state(P1, BP, onfloor, H),
    state(P2, BP, onfloor, H)
).

getfood(state(_,_,_,has)).


getfood(S1) :-
    perform(Act, S1, S2),
    write(' In '), write(S1), nl,
    write(' try '), write(Act), nl,
    write(' now '), write(S2), nl,
    getfood(S2).

gf :- getfood(state(atdoor,atwindow,onfloor,hasnot)).