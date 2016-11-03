#!/bin/sh

echo "Single command test"
echo 

./bin/rshell<<EOF
pwd
date
echo hey
echo bye
mkdir temp
ls
ls -la
rm -rf temp
touch temp2
mv temp ../
cat >> temp3
echo fini
echo entering in bash
bash
exit
exit
EOF

echo
echo "Done"
echo
