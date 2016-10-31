#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>

using namespace std;

void printPrompt( );
void getInput( char & );
void parser( char &, vector<string> *, char ** );
bool cmd( vector<string> ** );

int main( )
{
    int maxSize = 30;
    char theString[maxSize];
    char *input[maxSize];
    vector<string> coins;
    char *theUser;
    char nameAndLocation[maxSize];
    char *tok;
    string command;

    while ( command != "exit" )
    {
        cout.flush( );
        printPrompt( );
        getInput( *theString );

        //parser();
        //fgets( theString, maxSize, stdin );
        //cin.getline( theString, maxSize );

        while ( strcmp( theString, "\0") == 0 )
        {
            printPrompt( );
            getInput( *theString );
            //cin.getline( theString, maxSize );
            cin.clear( );
            cin.sync( );
        }


        parser( *theString, &coins, input );
        //cmd( coins );
                /*
        if ( command == "ls" )
        {
            pid_t pid = fork( );

            if ( pid == 0 )
                execl( "/bin/ls", "ls", (char *) 0 );

            waitpid( pid, NULL, 0 );
        }

        else if ( command == "pwd" )
        {
            pid_t pid = fork( );

            if ( pid == 0 )
                execl( "/bin/pwd", "pwd", (char *) 0);

            waitpid( pid, NULL, 0 );
        }

        else if ( command == "echo" )
        {
            pid_t pid = fork( );

            if ( pid == 0 )
                execl( "/bin/echo", "echo", (char *) 0 );

            waitpid( pid, NULL, 0 );
        }

        else if ( command == "date" )
        {
            pid_t pid = fork( );

            if ( pid == 0 )
                execl( "/bin/date", "date", (char *) 0 );

            waitpid( pid, NULL, 0 );
        }
        */

    }

    return 0;
}

void printPrompt( )
{
    int maxSize = 30;

    char *theUser;
    char *workingDir;
    char hostAndLocation[maxSize];

    theUser = getlogin( );
    //workingDir = getcwd( workingDir, 20 );
    gethostname( hostAndLocation, maxSize );

    cout << theUser << '@' << hostAndLocation << " $ ";

}

void getInput( char & getLine )
{
    fgets( &getLine, 30, stdin );
}

void parser( char & getLine, vector<string> * theInput, char ** thisOne )
{
    char *tok;
    vector<string> testingInput;
    tok = strtok( &getLine, " ");

    string temp(tok);
    string command;

    while ( tok != NULL )
    {
        theInput->push_back( tok );
        if ( tok != '\0' )
            cout << tok;

        *thisOne++ = tok;
        //*thisOne++;
        tok = strtok( NULL, " " );

    }

    /*
    for ( unsigned int i = 0; i < theInput->size( ); i++ )
    {
        cout << theInput->at(i) << endl;
    }
    */

    cout << "testing: " << **thisOne << " " << endl;
}

bool cmd( vector<string> ** commands )
{
    pid_t pid = fork( );

    //if ( pid == 0 )
       // execvp( **commands, commands );
}
