reverse_print_list([]).
reverse_print_list([H|T]):-
     reverse_print_list(T), nl, write(H).

solve(Node):-
    dfs([], Node, Solution),
    reverse_print_list(Solution).

dfs(Path, Node, [Node|Path]):-
    Node = GOAL_NODE.

dfs(Path, Node, Sol):-
   move(Node, Node1),
   write(Node), write(' ---- '), write(Node1), nl,
   not(member(Node1, Path)),
   dfs([Node|Path], Node1, Sol).
