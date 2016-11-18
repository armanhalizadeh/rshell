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
vector<char*> infixToPostfix(list<char*> vInfix);
int priority(char*);

int main()
{
    while(true)
    {
        printPrompt();

        char* userInput = getInput();

        cmdBase* head = parse(userInput);
        
        head->execute( );
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
        char* temp = new char[2];
        temp[0] = ';';
        temp[1] = '\0';
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
        char* cmdPtr2 = strtok(NULL, "");
        if (cmdPtr2 != NULL)
        {
           cmdPtr2 += 1;
           *it = cmdPtr;
           char* temp = new char[3];
           temp[0] = '&';
           temp[1] = '&';
           temp[2] = '\0';
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
               vInfix.insert(it, temp);
               vInfix.insert(it, cmdPtr2);
           }
        }
    }

    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        cmdPtr = strtok(*it, "|");
        char* cmdPtr2 = strtok(NULL, "");
        if (cmdPtr2 != NULL)
        {
           cmdPtr2 += 1;
           *it = cmdPtr;
           char* temp = new char[3];
           temp[0] = '|';
           temp[1] = '|';
           temp[2] = '\0';
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
               vInfix.insert(it, temp);
               vInfix.insert(it, cmdPtr2);
           }
        }
    }
 
    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        char* c = *it;
        int i = 0;
        while (c[i] == ' ')
        {
            i++;
        }
        if (c[i] == '(')
        {
           char* temp = new char[2];
           temp[0] = '(';
           temp[1] = '\0';
           vInfix.insert(it, temp);
           c[i] = '\0';
           c += i + 1;
           *it = c;
           it--;
        }
    }

    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        char* c =  strpbrk(*it, ")");
        if (c != NULL)
        {
            c[0] = '\0';
            int i = 1;
            while (c[i] == ' ')
            {
                i++;
            }
            if (c[i] != '\0')
            {
                c += i;
                it++;
                if (it == vInfix.end())
                {
                    it--;
                    vInfix.push_back(c);
                    it++;
                }
                else
                {
                    vInfix.insert(it, c);
                }
                it--;
            }
            char* temp = new char[2];
            temp[0] = ')';
            temp[1] = '\0';
            it++;
            if (it == vInfix.end())
            {
                it--;
                vInfix.push_back(temp);
                it++;
            }
            else
            {
                vInfix.insert(it, temp);
            }
        }
    }

        vector<char*> vPostfix = infixToPostfix(vInfix);
    stack<cmdBase*> cmdStack;
    for (int i = 0, n = vPostfix.size(); i < n; i++)
    {
        cmdBase* temp;
        if (strcmp(vPostfix.at(i), "&&") == 0) 
        {
            cmdBase* right = cmdStack.top();
            cmdStack.pop();
            cmdBase* left = cmdStack.top();
            cmdStack.pop();
            temp = new cmdAnd(left, right);
        }
        else if (strcmp(vPostfix.at(i), "||") == 0) 
        {
            cmdBase* right = cmdStack.top();
            cmdStack.pop();
            cmdBase* left = cmdStack.top();
            cmdStack.pop();
            temp = new cmdOr(left, right);
        }
        else if (strcmp(vPostfix.at(i), ";") == 0) 
        {
            cmdBase* right = cmdStack.top();
            cmdStack.pop();
            cmdBase* left = cmdStack.top();
            cmdStack.pop();
            temp = new cmdSemi(left, right);
        }
        else
        {
            temp = new cmdExecutable(vPostfix.at(i));
        }
        cmdStack.push(temp);
    }

    return cmdStack.top();
}

vector<char*> infixToPostfix(list<char*> vInfix)
{
    stack<char*> cntrStack;
    vector<char*> vPostfix;
    char* wrdPtr;
    for (list<char*>::iterator it = vInfix.begin(); it != vInfix.end(); it++)
    {
        wrdPtr = *it; 
        if (strcmp(wrdPtr, "&&") == 0 || strcmp(wrdPtr, "||") == 0 
            || strcmp(wrdPtr, ";") == 0 || strcmp(wrdPtr, "(") == 0
            || strcmp(wrdPtr, ")") == 0) {
            if (strcmp(wrdPtr, "(") == 0)
            {
                cntrStack.push(wrdPtr);
            }
            else if (strcmp(wrdPtr, ")") == 0)
            {
                while (strcmp(cntrStack.top(), "(") != 0)
                {
                    vPostfix.push_back(cntrStack.top());
                    cntrStack.pop();
                }
                cntrStack.pop();
            }
            else
            {
                while (!cntrStack.empty() && priority(wrdPtr) 
                        <= priority(cntrStack.top()))
                {
                    if (strcmp(cntrStack.top(), "(") == 0)
                    {
                        break;
                    }
                    vPostfix.push_back(cntrStack.top());
                    cntrStack.pop();
                }
                cntrStack.push(wrdPtr);
            }
        }
        else
        {
            vPostfix.push_back(wrdPtr);
        }
    }
    while (!cntrStack.empty())
    {
        vPostfix.push_back(cntrStack.top());
        cntrStack.pop();
    }
    return vPostfix;
}

int priority(char* c)
{
    if (strcmp(c, "(") == 0)
    {
        return 3;
    }
    else if (strcmp(c, ";") == 0)
    {
        return 1;
    }
    return 2;
}
