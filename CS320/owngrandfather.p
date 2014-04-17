%%facts from the problem relevant to solution
male(myself).
male(myfather).
male(s1).
male(s2).
married(myself,widow).
married(myfather,daughter).
parent(widow,daughter).
parent(myfather,myself).
parent(widow,s1).
parent(father,s2).
parent(daughter,s2).
parent(myself,s1).
parent(myself,daughter).
parent(daughter,myself).

female(X) :- not(male(X)).

father(Parent,Child) :- parent(Parent,Child), male(Parent).

mother(Parent,Child) :- parent(Parent,Child), female(Parent).

sibling(Child,Child1) :- parent(Parent,Child), parent(Parent,Child1).

uncle(Uncle,Nephew) :- parent(Parent,Nephew), sibling(Parent,Uncle), male(Uncle).

grandparent(Grandparent,Grandchild) :- parent(Parent,Grandchild), parent(Grandparent,Parent).

parent_in_law(Parent,Child) :- parent(Partner,Child), married(Parent,Partner).

uncle_in_law(Uncle,Nephew) :- parent_in_law(Parent,Nephew), sibling(Parent,Uncle), male(Uncle).

sibling_in_law(Child,Child1) :- ( parent(Parent,Child1), parent_in_law(Parent,Child), Child \= Child1 ) ; ( parent(Parent,Child), parent_in_law(Parent,Child1), Child \= Child1).

grandparent_in_law(Grandparent,Grandchild) :- ( parent_in_law(Parent,Grandchild), parent(Grandparent,Parent)) ; ( parent(Parent,Grandchild), parent_in_law(Grandparent,Parent)) ; ( parent_in_law(Parent,Grandchild), parent_in_law(Grandparent,Parent)).

grandfather_in_law(Grandfather,Grandchild) :- grandparent_in_law(Grandfather,Grandchild), male(Grandfather).
