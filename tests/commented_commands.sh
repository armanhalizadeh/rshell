#!/bin/sh

echo "Commands with comments"

#line 10 should output #pwd && ls
./bin/rshell<<EOF
echo echo testing testing
echo #pwd && ls
echo "#pwd && ls"
pwd || ls; date && uname; #pwd; echo work!
ls; ls -a; ls -l; pwd && #uname
exit
EOF

echo Done
echo
