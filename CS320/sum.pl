sum([], 0).
sum([H|T],Sum) :- sum(T, Subsum), Sum is Subsum + H.
