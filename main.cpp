#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "cmdAnd.h"
#include "cmdOr.h"
#include "cmdBase.h"
#include "cmdSemi.h"
#include "cmdExecutable.h"

using namespace std;

//takes in user input and returns the char*
char* getInput()
{
  //takes in user input as string w/ getline
  string temp;
  getline(cin, temp);

  //creates char array and sets it equal to string
  char* input = new char[temp.size()];
  for (int i = 0, n = temp.size(); i < n; i++)
  {
    input[i] = temp.at(i);
  }
  input[temp.size()] = '\0'; //adds NULL to end of char array
  return input;
}

cmdBase* parse(char* input)
{
  char* command1 = strtok(input, ";");
  char* command2 = strtok(NULL, "\0");
  if (command2 != NULL)
  {
    cmdSemi* tmp = new cmdSemi(parse(command1), parse(command2));
    return tmp;
  }
  else
  {
    char* lastAnd = strrchr(command1, '&');
    char* lastOr = strrchr(command1, '|');
    if there is && but no || or if && is after ||
    if (lastAnd[0] != '\0' && (lastOr[0] == '\0' || strlen(lastAnd) < strlen(lastOr)))
    {
      lastAnd[-1] = '\0';
      lastAnd[0] = '\0';
      command2 = &lastAnd[1];
      cmdAnd* tmp = new cmdAnd(parse(command1), parse(command2));
      return tmp;
    }
    else if (lastOr[0] != '\0' && (lastAnd[0] == '\0' || strlen(lastOr) < strlen(lastAnd)))
    {
      lastOr[-1] = '\0';
      lastOr[0] = '\0';
      command2 = &lastOr[1];
      cmdOr* tmp = new cmdOr(parse(command1), parse(command2));
      return tmp;
    }
    else if (lastAnd[0] == '\0' && lastOr[0] == '\0')
    {
      cmdExecutable* tmp = new cmdExecutable(command1);
      return tmp;
    }
  }
}

int main()
{
  char* userInput = getInput();
  cmdBase* head = parse(userInput);
}
