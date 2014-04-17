married(i,w).
married(f,d).
father(i,s1),
father(i,d).
father(f,s2).
father(f,i).
mother(d,s2).
grandfather(i,s2).

grandfather(Z,X) :- brother(X,Y), grandfather(Z,Y).
brother(Y,Z) :- father(X,Y), father(X,Z).
grandfather(X,Y) :- father(X,Y), mother(Y,Z).
father_in_law(X,Z) :- father(X,Y), married(Y,Z).
grandfather(X,Z) :- father(X,Y), father(Y,Z).

