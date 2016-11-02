#!/bin/sh

echo "complicated"

../bin/rshell<<EOF


date; ls -a && pwd || exit

exit

EOF

echo
echo "done"
echo
