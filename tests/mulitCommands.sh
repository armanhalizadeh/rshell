#!/bin/sh

echo multiple commands

../bin/rshell<<EOF

pwd && uname && date || dmesg || touch me
exit
EOF

