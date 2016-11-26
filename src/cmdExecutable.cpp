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
 
    unsigned int lastPos = 0;

    for ( ; args[lastPos] != '\0'; lastPos++ ){}
    lastPos--;
    

    // checks if the first input is either test or the alias for test [
    // if there is a [, it checks if there is a closing bracket 
    // One way of achieving this is to check if the [ ] is overloaded with 
    // arguments
    if ( strcmp( executable, "test" ) == 0 || strcmp( executable, "[" ) == 0)
    {
        int argNum = 0;
        while (args[argNum] != NULL)
        {
            argNum++;
        }

        if ((executable[0] == '[' && argNum == 4) 
                || (strcmp(executable, "test") == 0 && argNum == 3) )
        {
            if (strcmp(args[1], "-e") != 0 && strcmp(args[1], "-f") != 0 
                    && strcmp(args[1], "-d") != 0)
            {
                cout << "Error: unexpected argument '" << args[1] << "'" 
                    << endl;

                return false;
            }
        }
        else if ((executable[0] == '[' && (argNum > 4 || argNum < 3)) 
                || (strcmp(executable, "test") == 0 && (argNum < 2 || 
                        argNum > 3)) )
        {
            cout << "Error: unexpected number of arguments" << endl;
            return false;
        }

        if ( executable[0] == '[' )
        {
            if ( strcmp( args[ lastPos], "]") != 0 )
            {
                cout << "Error: missing ']' " << endl;

                return false;
            }   
        } 


       
        struct stat sb;

        //int pathLocation = 1;
        bool exist = false;
        bool exist2 = false;

        string temp;

        //cout << args[1] << endl;
        temp.append( args[1] );

        // defualt argument ( -e ) if exist
        if ( temp[0] != '-' )
        {   
            //cout << args[pathLocation] << endl;

            exist = ( stat( args[1], &sb ) == 0 );

            if ( exist )
                cout << "(True)" << endl;

            else
                cout << "(False)" << endl;

            return exist;
        }

        // this section is for arguemetns -e -f -d
        else
        {

            exist = ( stat( args[2], &sb ) == 0 );

            if ( exist )
            {
                if ( temp[1] == 'e' )
                {
                    cout << "(True)" << endl;
                    return exist;
                }

                // regular file
                else if ( temp[1] == 'f' )
                    exist2 = S_ISREG( sb.st_mode );

                // directory 
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

    else if ( strcmp( executable, "cd" ) == 0 )
    {

        int status;
        // getenv setenv - PWD OLDPWD
        //cout << args[1] << endl;

        char* location = args[1];
 
        char* tempLocation = getenv( "PWD" );

        if( args[1] == '\0' )
        {
            //cout << " empty " << endl;
            location = getenv( "HOME" );
        } 

        else if ( strcmp( args[1], "-" ) == 0  )
        {
            //cout << " - " << endl;
            location = getenv( "OLDPWD" );
        }

        status = chdir( location );
 
        if ( status == 0 )
        {
            if ( args[1] != NULL )
            {
                if ( strcmp( args[1], ".." ) == 0 )
                {
                    char *buf;
                    long size = 100;
                    buf = (char *)malloc((size_t)size);
                    setenv( "PWD", getcwd( buf, 100 ), 1 );
                }

                else
                    setenv( "PWD", location, 1 );

            }

            else
                setenv( "PWD", location, 1 );

            setenv( "OLDPWD", tempLocation, 1 );
        }

        // FOR DEBUGGING
        //cout << "\tPWD: " <<  getenv( "PWD" ) << endl;
        //cout << "\tOLDPWD: " << getenv( "OLDPWD" ) << endl;

        return true;
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
