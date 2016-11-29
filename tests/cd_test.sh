#!/bin/bash

./bin/rshell << EOF
pwd
cd src
pwd
cd -
pwd
cd bin
pwd
cd ..
pwd
cd tests
pwd
cd
pwd
exit
EOF

echo Done

