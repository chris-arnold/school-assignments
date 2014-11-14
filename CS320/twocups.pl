move(s(X,Y),s(Z,5)) :- Z is X - (5 - Y), Z >= 0.
move(s(X,Y),s(Z,0)) :- Z is X + Y, Z =< 3.
move(s(X,Y),s(3,Z)) :- Z is Y - (3 - X), Z >=0.
move(s(X,Y),s(0,Z)) :- Z is X + Y, Z =< 5.

move(s(0,Y),s(3,Y)).
move(s(X,0),s(X,5)).
move(s(X,Y),s(X,0)) :- Y > 0.
move(s(X,Y),s(0,Y)) :- X > 0.

moves(Xs) :- moves([s(0,0)],Xs).
moves([s(X0,Y0)|T], [s(X1,4),s(X0,Y0)|T])
    :- move(s(X0,Y0),s(X1,4)), !.
moves([s(X0,Y0)|T],Xs) :-
    move(s(X0,Y0),s(X1,Y1)), 
    not(member(s(X1,Y1),[s(X0,Y0)|T])),
    moves([s(X1,Y1),s(X0,Y0)|T],Xs).

%?- moves(Xs), write(Xs), nl, fail.
