#!/bin/sh

echo "Commands with comments"

#line 10 should output #pwd && ls
./bin/rshell<<EOF
echo echo testing testing
echo #pwd && ls
echo "#pwd && ls"
ls; ls -a; ls -l; pwd && date #uname
exit
EOF

echo Done
echo
