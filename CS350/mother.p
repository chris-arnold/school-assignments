%P.761, programming question 1.
parent(jim, sally).
parent(mary, sally).
parent(craig, dan).
parent(sally, holly).
parent(sally, david).

male(jim).
male(craig).
male(dan).
male(david).
female(mary).
female(sally).
female(holly).

mother(X,Y) :- parent(X,Y), female(X).

%adding sister structure.

sister(X,Y) :- parent(Z,X), parent(Z,Y), female(X).