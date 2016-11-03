#!/bin/sh

./bin/rshell<<EOF
./singleCommands.sh
./multiCommands.sh
./commentCommands.sh
./complicatedCommands.sh
./doesntexist.sh && ./singleCommands.sh
exit
EOF
