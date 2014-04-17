final([Final], Final).
final([_|T], Final) :- final([T], Final).

other([H|T], Last) :- reverse([H|T]), Last is H.