#include "cmdExecutable.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

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
  args[i] = NULL;
}

//cmdExecutable::~cmdExecutable()
//{}

bool cmdExecutable::execute()
{
    if (strcmp(executable, "exit") == 0)
    {
        exit(0);
    }
    
    // to remove - jonathan
    // Hard coded example
    // need to find a way to get argv to be of char * const
    //char *const tmp[] = { , NULL};

    pid_t pid = fork( );
    int status;

    // first arguement is the command
    // second argument is a pointer to an array of pointers to
    // null terminated null-terminated characters
    // An example: echo testing
    // executable - echo
    // tmp - testing
    // will print echo
    //
    // to do - checking if the executable failed ( returns -1 )

    if ( pid == 0 )
    {
        execvp( executable, args );
        //if command does not successfully run
        exit(EXIT_FAILURE);
    }

    else if( pid < 0 )
    {
        cout << "Error: fork failed" << endl;
    }

    else
    {    
        // may have to change to wait( )
        //waitpid(pid, &status, 0);
        while( wait( &status ) != pid ) ;
    }
    if (status != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
 }
