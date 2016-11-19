#include "cmdExecutable.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
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

cmdExecutable::~cmdExecutable()
{
    int i = 0;
    while (args[i] != 0)
    {
        delete args[i];
    }
}

bool cmdExecutable::execute()
{
    // responsible for preventing the seg fault
    // that occurs when || follows right after ;
    // when it occurs, within main, the executable 
    // becomes null
    if ( executable == NULL )
    {
        return true;
    }
 

    if ( strcmp( executable, "test" ) == 0 || strcmp( executable, "[" ) == 0)
    {
        //cout << "input is test" << endl;

        struct stat sb;

        int pathLocation = 1;
        bool exist = false;
        bool exist2 = false;

        string temp;

        temp.append( args[1] );

        if ( temp[0] != '-'  || temp[1] == 'e' )
        {
            if ( temp[1] == 'e' )
                pathLocation = 2;


            exist = ( stat( args[pathLocation], &sb ) == 0 );

            if ( exist )
                cout << "(True)" << endl;

            else
                cout << "(False)" << endl;

            return exist;
        }

        else
        {

            exist = ( stat( args[2], &sb ) == 0 );

            if ( exist )
            {
               if ( temp[1] == 'f' )
                   exist2 = S_ISREG( sb.st_mode );

               else if ( temp[1] == 'd' )
                   exist2 = S_ISDIR( sb.st_mode );

               if ( exist2 )
                   cout << "(True)" << endl;

               else
                   cout << "(False)" << endl;

               return exist2;
            }

            else
            {
                cout << "(False)" << endl;

                return exist;
            }

        }


    }
    // if the current command is exit
    // the following with exit the rshell

    
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
