#include "cmdExecutable.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
  //cout << executable;
  //for (int i = 0, n = args.size(); i < n; i++)
  //{
  //  cout << ' ' << args.at(i);
  //}
  //cout << endl;

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
    }
    else if( pid < 0 )
    {
        cout << "Error: fork failed" << endl;
    }
    else
    {    
        // may have to change to wait( )
        waitpid(pid, &status, 0);
        //waitpid( pid, NULL, 0 );
    }
  return true;
}
