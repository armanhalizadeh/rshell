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

using namespace std;

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
                cout << " " << temp[1] << "'" << endl;
            else
                cout << "'" << endl;

        }

        printPrompt();
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
    char* command1 = strtok(input, "#"); //removes everything thats a comment

    command1 = strtok(command1, ";"); //finds first semicolon

    char* command2 = strtok(NULL, "\0");

    if (command2 != NULL) //if semicolon was found
    {
        if (command2[0] == '&' || command2[1] == '&' || 
                command2[0] == '|' || command2[1] == '|' 
                || command2[0] == ';')
        {
            cout  << "syntax error near unexpected token '"
                                  << command2[0] << "'" << endl;
            cmdExecutable* tmp = new cmdExecutable( NULL );
            return tmp;
        }
        //create semi connector by parsing left side and right side
        cmdSemi* tmp = new cmdSemi(parse(command1), parse(command2));
        return tmp;
    }
    else //no semicolon found
    {
        //tree must be built with last connector having highest priority
        char* lastAnd = strrchr(command1, '&'); //returns ptr to last &
        char* lastOr = strrchr(command1, '|'); //returns ptr to last |

        //if there is && but no || or if && is after ||
        if (lastAnd != '\0' && (lastOr == '\0' || strlen(lastAnd) 
                    < strlen(lastOr)))
        {
            //checks if two connectors are in a row and prints error if so
            if (lastAnd[-2] == '&' || lastAnd[-3] == '&' || 
                lastAnd[-1] == '|' || lastAnd[-2] == '|' 
                || lastAnd[-1] == ';' || lastAnd[-2] == ';')
            {
                cout  << "syntax error near unexpected token '"
                    << lastAnd[0] << "'" << endl;
                cmdExecutable* tmp = new cmdExecutable( NULL );
                return tmp;
            }
        

            lastAnd[-1] = '\0'; //make last && into NULL
            lastAnd[0] = '\0';

            command2 = &lastAnd[1]; //set right side to after last &
            
               

            cmdAnd* tmp = new cmdAnd(parse(command1), parse(command2));

            return tmp;
        }

        //if there is || but no && or if || is after &&
        else if (lastOr != '\0' && (lastAnd == '\0' 
                    || strlen(lastOr) < strlen(lastAnd)))
        {
            //checks if two connectors are in a row and prints error if so
            if (lastOr[-1] == '&' || lastOr[-2] == '&' || 
                lastOr[-2] == '|' || lastOr[-3] == '|' 
                || lastOr[-1] == ';' || lastOr[-2] == ';')
            {
                cout  << "syntax error near unexpected token '"
                    << lastOr[0] << "'" << endl;
                cmdExecutable* tmp = new cmdExecutable( NULL );
                return tmp;
            }
 
            
            lastOr[-1] = '\0'; //make last || into NULL
            lastOr[0] = '\0';

            command2 = &lastOr[1]; //set right side to after last |

            cmdOr* tmp = new cmdOr(parse(command1), parse(command2));

            return tmp;
        }

        //if no && or || commands found
        else //if (lastAnd == '\0' && lastOr == '\0')
        {
            cmdExecutable* tmp = new cmdExecutable(command1);
            return tmp;
        }
    }
}

int main()
{
    while(true)
    {
        printPrompt();

        char* userInput = getInput();

        cmdBase* head = parse(userInput);

        head->execute( );
        delete head;
    }
}
