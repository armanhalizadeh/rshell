# rshell

## Overview

This repository contains a c++ program that mimics a simple command shell called **rshell**. It is able to execute programs within `/bin/`.
The simple shell also uses connectors to string commands together.

The avaliable connectors are the following: `&&`, `||`, and `;`.

The rshell works with the following input format
    
    command = executable [ argumentList ] [ connector cmd ]
    connector = && or || or ;

Example: 

    ls -la && date; echo Done!

There are are total of three executables in the example; `ls`, `date`, and `echo`.
the ls command will list the files in the working directory. The arugment list for ls
is `l` and `a`. The `l` argument will print the output in a long listing format. While
the `a` argument will print all files in the working directory such as invisible files.

The `date` command will print the current date. And the `echo` command will print out its argument
which in this case is the string `Done!`.

The connector `&&` acts as an AND. If the exectable to the left of `&&` executes correctly then
the executable to the right of the connector will also execute regardless if it executes correctly
or not. For the `||` connector the executable to the right of it will only execute if the exectuable
before the connector fails. Lastly the `;` connector acts as a breakpoint. Any of the executables 
will run regardless of its status.


## Bugs

In the following input
    ls && #pwd
or
    ls || #pwd

the **rshell** enters into a input mode in which the prompt becomes
    >

In the actual standard bash the same result occurs. We are unsure if this is 
the intended result of the command. In order to escape this mode the user needs
to input `ctrl+c`.


Another bug is spaces of more than between connectors

    ls &&   ||

will result in a segmentation fault

One input possibility we overlooked is the following

    ls ||
    ls &&

in which the is now executable to follow after the connector
as a result there is a segmentation fault.

The expected output for `ls &&` however in the actual shell enters into an input mode
