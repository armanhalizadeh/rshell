#!/bin/bash

./bin/rshell<<EOF
(echo A)
((echo A))
echo A && (echo B)
(echo A) && echo B
(echo A) && (echo B)
((echo A) && (echo B))
echo A || (echo B)
(echo A) || echo B
(echo A) || (echo B)
(echo A);
(echo A;)
(echo A); echo B
echo A; (echo B)
(echo A); (echo B)
(echo A && echo B)
(echo A && echo B) || echo C
(echo A && echo B) || (echo C && echo D)
echo A && echo B || (echo C && echo D)
(echo A && echo B; echo C) || (echo D)
exit
EOF

echo done

