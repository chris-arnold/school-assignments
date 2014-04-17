largest([], 0).
largest([H|T],Max) :- largest(T,Tmax), Max is max(H, Tmax).
