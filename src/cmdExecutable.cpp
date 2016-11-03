#include "cmdExecutable.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

// Placing the tokens to char*
cmdExecutable::cmdExecutable(char* command)
{

    executable = strtok(command, " ");
    command = strtok(NULL, " ");

    args[0] = executable;

    int i = 1;

    while (command != NULL)
    {
        args[i] = command;

        command = strtok(NULL, " ");

        i++;
    }

    //putting NULL at the end of args
    //necessary for execvp
    args[i] = NULL;
}

//cmdExecutable::~cmdExecutable()
//{}

bool cmdExecutable::execute()
{

    // if the current command is exit
    // the following with exit the rshell

    cout << "inside execute" << endl;

    // responsible for preventing the seg fault
    // that occurs when || follows right after ;
    // when it occurs, within main, the executable 
    // becomes null
    if ( executable == NULL )
    {
        return true;
    }

    // responsible for exiting the rshell
    // whenever the input is exit or exit is 
    // called through the connectors
    else if (strcmp(executable, "exit") == 0)
    {
        exit(0);
    }

    // forks the process. Allows the executable
    // to take process while the "rshell" waits 
    // for the fork process
    pid_t pid = fork( );

    int status;

    // first arguement is the command
    // second argument is a pointer to an array of pointers to
    // null terminated null-terminated characters

    //cout << "Executable: " << executable << endl;

    if ( pid == 0 )
    {
        execvp( executable, args );

        //if command does not successfully run
        string execvpFail = string(executable);

        execvpFail += " failed";

        perror( execvpFail.c_str() );

        exit(EXIT_FAILURE);
    }

    else if( pid < 0 )
    {
        perror( "fork failed" );
    }

    else
    {
        // waits for the process to end
        waitpid(pid, &status, 0);
    }

    if (status != 0 )
    {
        return false;
    }

    else
    {
        return true;
    }
}
