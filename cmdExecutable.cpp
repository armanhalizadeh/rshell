#include "cmdExecutable.h"
#include <iostream>

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
  return true;
}
