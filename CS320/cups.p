%three cups, sizes 3, 5, 8. Goal: 4 in the larger two. Largest begins full.

reverse_print_list([]).
reverse_print_list([H|T]):-
     reverse_print_list(T), nl, write(H).

solve(Node):-
    dfs([], Node, Solution),
    reverse_print_list(Solution).

dfs(Path, Node, [Node|Path]):-
    Node = state(0,4,4).

dfs(Path, Node, Sol):-
   move(Node, Node1),
   write(Node), write(' ---- '), write(Node1), nl,
   not(member(Node,Path)),
   not(member(Node1, Path)),
   dfs([Node|Path], Node1, Sol).

%%Operations
% Valid moves defined here.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- X + Y =< 5, Y1 is X + Y, X1 is 0, Z1 is Z.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- X + Y > 5, Y1 is 5, X1 is X + Y - 5, Z1 is Z.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- X + Z =< 8, Z1 is X + Z, X1 is 0, Y1 is Y.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- X + Z > 8, Z1 is 8, X1 is X + Z - 8, Y1 is Y.

move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Y + Z =< 8, Z1 is Y + Z, Y1 is 0, X1 is X.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Y + Z > 8, Z1 is 8, Y1 is Y + Z - 8, X1 is X.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Y + X =< 3, X1 is X + Y, Y1 is 0, Z1 is Z.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Y + X > 3, X1 is 3, Y1 is X + Y - 3, Z1 is Z.

move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Z + Y =< 5, Y1 is Z + Y, Z1 is 0, X1 is X.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Z + Y > 5, Y1 is 5, Z1 is Z + Y -5, X1 is X.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Z + X =< 3, X1 is Z + X, Z1 is 0, Y1 is Y.
move( state(X,Y,Z), state(X1,Y1,Z1) ) :- Z + X > 3, X1 is 3, Z1 is Z + X -3, Y1 is Y.

not(P):- P, !, fail; true.
