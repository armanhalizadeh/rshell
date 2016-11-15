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

        cmdBase* head = parse(userInput);

        //head->execute( );
        //delete head;
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

    //if user entered nothing
    //print the prompt and wait for user input
    //checks for syntax error when the connectors
    //are the first inputs 
    while ( temp.empty( ) || temp[0] == '&' ||
            temp[0] == '|' || temp[0] == ';')
    {
        if (temp[0] == '&' || temp[0] == '|' || temp[0] == ';')
        {
            cout << "syntax error near unexpected token '"
                << temp[0];

            if ( temp[0] != ';' )
                cout << temp[1] << "'" << endl;
            else
                cout << "'" << endl;

        }

        printPrompt();
        getline( cin, temp );
    }

    if ( temp.find("&& ||") != std::string::npos )
    {
        cout << "syntax error near unexpected token ||" << endl;

        printPrompt( );
        getline( cin, temp );
    }

    else if ( temp.find( "|| &&" ) != std::string::npos )
    {
        cout << "syntax error near unexpected token &&" << endl;
        printPrompt( );
        getline( cin, temp );
    }

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
        if (wrdPtr == "&&" || wrdPtr == "||" || wrdPtr == ";") {
            if (wrdPtr == "(")
            {

            }
            else if (wrdPtr == ";")
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
}


