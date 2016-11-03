#!/bin/sh

echo multiple commands

./bin/rshell<<EOF
pwd && uname && date || dmesg || touch me
mkdir test && rm -rf test && ls && date || pwd && rm me
exit
EOF

