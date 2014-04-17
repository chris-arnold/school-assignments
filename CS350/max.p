max([], Max) :- Max is 0.
max([H|T], Max) :- max(T, Newmax), Max is max(H, Newmax).