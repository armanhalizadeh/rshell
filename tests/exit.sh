#!/bin/sh


./bin/rshell<<EOF
test tests/test_test.sh || exit
test -d tests || exit
test -d tests/ || exit
[ test/test.sh ] || exit
[ -f test/test.sh ] && exit
pwd && whoami || ( false && exit )
EOF

echo Done
echo
