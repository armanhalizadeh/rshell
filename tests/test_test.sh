#!/bin/bash

./bin/rshell<<EOF

test -e makefile
test -e src
test -e hello
test makefile
test src
test hello
test -f makefile
test -f src
test -f hello
test -d makefile
test -d src
test -d hello
[ -e makefile ]
[ -e src ]
[ -e hello ]
[ makefile ]
[ src ]
[ hello ]
[ -f makefile ]
[ -f src ]
[ -f hello ]
[ -d makefile ]
[ -d src ]
[ -d hello ]
test src && echo hi
test hello && echo hi
test src || echo hi
test hello || echo hi
test src; test hello
test [ src
test -e src hello
[ [ src ]
[ src]
[ src
exit
EOF

echo done

