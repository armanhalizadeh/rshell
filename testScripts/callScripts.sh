#!/bin/sh

../bin/rshell<<EOF

./singleCommands.sh
./multiCommands.sh
./comments.sh
./complicated.sh
./doesntexist.sh && ./singleCommands.sh
exit
EOF
