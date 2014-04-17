%Fox and goose cant be alone

%Goose and beans can't be alone

reverse_print_list([]).
reverse_print_list([H|T]):-
     reverse_print_list(T), nl, write(H).

solve(Node):-
    dfs([], Node, Solution),
    reverse_print_list(Solution).

dfs(Path, Node, [Node|Path]):-
    Node = state(left(0,0,0), right(1,1,1), 0, 0).

dfs(Path, Node, Sol):-
   move(Node, Node1),
   write(Node), write(' ---- '), write(Node1), nl,
   not(member(Node1, Path)),
   dfs([Node|Path], Node1, Sol).


%valid states:
valid(0,1,0).
valid(0,0,1).
valid(0,0,0).
valid(1,0,0).
valid(1,1,1).
valid(1,0,1).


%valid moves

%state(left(F,G,B), right(F,G,B), X).	X = 0 L-R	X = 1 R-L

%move fox
move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl1,Gl1,Bl1), right(Fr1,Gr,Br), X1, Boat1)) :- Gl1 is Gl, Bl1 is Bl,
	( 
	  Boat = 1 -> Fl1 is 1; 
	  Boat = 2 -> Gl1 is 1; 
	  Boat = 3 -> Bl1 is 1), Boat1 is 0,
	X = 0, Fl = 1, Fr = 0,
	Fl1 is 0, Boat is 1, X1 is 1, 
	valid(Fl1,Gl1,Bl1), valid(Fr1,Gr,Br).

move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl,Gl,Bl), right(Fr1,Gr1,Br1), X1, Boat1)) :- Gr1 is Gr, Br1 is Br,
	( Boat = 1 -> Fr1 is 1; 
	  Boat = 2 -> Gr1 is 1; 
	  Boat = 3 -> Br1 is 1), Boat1 is 0,
	X = 1, Fr = 1, Fl = 0,
	Fr1 is 0, Boat is 1, X1 is 0, 
	valid(Fl,Gl,Bl), valid(Fr1,Gr1,Br1).

%move Goad
move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl1,Gl1,Bl1), right(Fr,Gr1,Br), X1, Boat1)) :- Fl1 is Fl, Bl1 is Bl,
	( Boat = 1 -> Fl1 is 1; 
	  Boat = 2 -> Gl1 is 1; 
	  Boat = 3 -> Bl1 is 1), Boat1 is 0,
	X = 0, Gl = 1, Gr = 0,
	Gl1 is 0, Boat is 2, X1 is 1,
	valid(Fl1,Gl1,Bl1), valid(Fr,Gr1,Br).

move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl,Gl,Bl), right(Fr1,Gr1,Br1), X1, Boat1)) :- Fr1 is Fr, Br1 is Br,
	( Boat = 1 -> Fr1 is 1; 
	  Boat = 2 -> Gr1 is 1; 
	  Boat = 3 -> Br1 is 1), Boat1 is 0,
	X = 1, Gr = 1, Gl = 0,
	Gr1 is 0, Boat is 2, X1 is 0, 
	valid(Fl,Gl,Bl), valid(Fr1,Gr1,Br1).

%move beans
move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl1,Gl1,Bl1), right(Fr,Gr,Br1), X1, Boat1)) :- Fl1 is Fl, Gl1 is Gl,
	( 
	  Boat = 1 -> Fl1 is 1; 
	  Boat = 2 -> Gl1 is 1; 
	  Boat = 3 -> Bl1 is 1), Boat1 is 0,
	X = 0, Bl = 1, Br = 0,
	Bl1 is 0, Boat is 3, X1 is 1,
	valid(Fl1,Gl1,Bl1), valid(Fr,Gr,Br1).

move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl,Gl,Bl), right(Fr1,Gr1,Br1), X1, Boat1)) :- Fr1 is Fr, Gr1 is Gr,
	( Boat = 1 -> Fr1 is 1; 
	  Boat = 2 -> Gr1 is 1; 
	  Boat = 3 -> Br1 is 1), Boat1 is 0,
	X = 1, Br = 1, Bl = 0,
	Br1 is 0, Boat is 3, X1 is 0, 
	valid(Fl,Gl,Bl), valid(Fr1,Gr1,Br1).

%move just boat
move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X1), Boat) :- X = 1, X1 is 0.
move(state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X, Boat), state(left(Fl,Gl,Bl), right(Fr,Gr,Br), X1), Boat) :- X = 0, X1 is 1.


not(P):- P, !, fail; true.
