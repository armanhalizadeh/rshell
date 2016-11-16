#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include "cmdAnd.h"
#include "cmdOr.h"
#include "cmdBase.h"
#include "cmdSemi.h"
#include "cmdExecutable.h"
#include <vector>
#include <stack>
#include <list>
#include <iterator>

using namespace std;

void printPrompt();
char* getInput();
cmdBase* parse(char* input);
vector<char*> infixToPostfix(vector<char*> vInfix);

int main()
{
    while(true)
    {
        printPrompt();

        char* userInput = getInput();

        if ( userInput != NULL )
        {
            cmdBase* head = parse(userInput);

            //if ( head != NULL )
            //    head->execute( );

            delete userInput;
            delete head;
        }
    }
}

// prints the prompt for the user
// displays the user name and host name
void printPrompt()
{
    char *User;
    char host[30];

    User = getlogin( );
    gethostname( host, 30 );

    cout << User << "@" << host << "$ ";
}


//takes in user input and returns the char*
char* getInput()
{
    //takes in user input as string w/ getline
    string temp;

    getline(cin, temp);

    if ( temp.size( ) == 0 )
        return NULL;

    //creates char array and sets it equal to string
    char* input = new char[temp.size()];

    for (int i = 0, n = temp.size(); i < n; i++)
    {
        input[i] = temp.at(i);
    }

    input[temp.size()] = '\0'; //adds NULL to end of char array
    return input;
}

//creates tree of command connectors by parsing the entered line
cmdBase* parse(char* input)
{
    if ( input[0] == '\0' || input[0] == ';' )
        return NULL;

    list<char*> vInfix;
    char* cmdPtr;

    cmdPtr = strtok(input, ";");
    while (cmdPtr != NULL)
    {
        vInfix.push_back(cmdPtr);
        char* temp = new char[1];
        *temp = ';';
        vInfix.push_back(temp);
        cmdPtr = strtok(NULL, ";");
    }
    if (*vInfix.back() == ';')
    {
        vInfix.pop_back();
    }
    
    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        cmdPtr = strtok(*it, "&");
        char* cmdPtr2 = strtok(NULL, "&");
        while (cmdPtr2 != NULL)
        {
           *it = cmdPtr;
           char* temp = new char[2];
           temp[0] = '&';
           temp[1] = '&';
           it++;
           if(it == vInfix.end())
           {
               it--;
               vInfix.push_back(temp);
               vInfix.push_back(cmdPtr2);
               it++;
           }
           else
           {
               vInfix.insert(it++, temp);
               vInfix.insert(it, cmdPtr2);
           }
           cmdPtr = strtok(cmdPtr2, "&");
           cmdPtr2 = strtok(NULL, "&");
        }
    }
    
    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        cmdPtr = strtok(*it, "|");
        char* cmdPtr2 = strtok(NULL, "|");
        while (cmdPtr2 != NULL)
        {
           *it = cmdPtr;
           char* temp = new char[2];
           temp[0] = '|';
           temp[1] = '|';
           vInfix.insert(it++, temp);
           vInfix.insert(it++, cmdPtr2);
           cmdPtr = strtok(cmdPtr2, "&");
           cmdPtr2 = strtok(NULL, "&");
        }
 
    }

    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        cout << *it << endl;
    }

    /*fills v with every word
    wordPointer = strtok(input, " ");
    while(wordPointer != '\0')
    {
        vInfix.push_back(wordPointer);
        wordPointer = strtok(NULL, " ");
    }
    if (vInfix.back() == ";")
    {
        vInfix.pop_back();
    }*/

    //vector<char*> vPostfix = infixToPostfix(vInfix);

    cmdExecutable* t = new cmdExecutable(NULL);
    return t;
}

vector<char*> infixToPostfix(vector<char*> vInfix)
{
    stack<char*> cntrStack;
    vector<char*> vPostfix;
    char* wrdPtr;
    for (int i = 0, n = vInfix.size(); i < n; i++)
    {
        //TODO: FINISH PARSE
        wrdPtr = vInfix.at(i); 
        if ( ( strcmp( wrdPtr, "&&" ) == 0 ) || ( strcmp( wrdPtr, "||") == 0) 
                || ( strcmp( wrdPtr, ";") == 0 ) )
        {
            if ( strcmp( wrdPtr, "(") == 0 )
            {
                while ( !cntrStack.empty( ) )
                {
                    vPostfix.push_back(cntrStack.top());
                    cntrStack.pop( );
                }

            }

            else if ( strcmp( wrdPtr,";" ) == 0 )
            {
                while (!cntrStack.empty())
                {
                    vPostfix.push_back(cntrStack.top());
                    cntrStack.pop();
                }
            }

            else
            {
                while (!cntrStack.empty())
                {
                    vPostfix.push_back(cntrStack.top());
                    cntrStack.pop();
                }
            }
        }
    }

    return vPostfix;
}
    


