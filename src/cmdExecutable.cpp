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

    // responsible for preventing the seg fault
    // that occurs when || follows right after ;
    // when it occurs, within main, the executable 
    // becomes null
    //
    // Maybe this check wont be needed anymore
    // need to further test out
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

// The following is how test command will work

/*
int main( )
{
    struct stat sb;
    
    string fileName = "test.txt";
    string dirName = "test";

    bool exist = false;
    bool exist2 = false;

    // checks if the file/directory exist
    // the string for a directory does not have to contain
    // an '/' at the end of it.
    // However, including it works perfectly fine to

    exist = ( stat( fileName.c_str( ), &sb ) == 0 );

    if ( exist )
        cout << "(True)" << endl;

    else
        cout << "(False)" << endl;

   
    // stat checks if something exist
    // when checking if its a regular file or a directory
    // there has to be a secondary check

    // -e checks if the file/directory exist ( line 21 )
    //
    // -f checks if the file/directory exist and is a regular file
    // -d checks if the file/directory exist and is a directory
    
    exist = ( stat( dirName.c_str( ), &sb ) == 0 );

    if ( exist )
    {
        exist2 = S_ISDIR( sb.st_mode );
        
        if ( exist2 )
            cout << "(True)" << endl;

        else
            cout << "(False)" << endl;
    }

    // S_ISREG - checking if its a regular file
    // S_ISDIR - checking if its a directory

    return 0;
}

*/
