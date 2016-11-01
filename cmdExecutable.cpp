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
  while (command != NULL)
  {
    args.push_back(command);
    command = strtok(NULL, " ");
  }
}

bool cmdExecutable::execute()
{
  cout << executable;
  for (int i = 0, n = args.size(); i < n; i++)
  {
    cout << ' ' << args.at(i);
  }
  cout << endl;

    // to remove - jonathan
    // Hard coded example
    // need to find a way to get argv to be of char * const
    char *const tmp[] = { "testing", NULL};

    pid_t pid = fork( );

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
        execvp( executable, tmp );

    // may have to change to wait( )
    waitpid( pid, NULL, 0 );


  return true;
}
