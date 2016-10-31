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

using namespace std;

void printPrompt( );
void getInput( char & );
void parser( char *, char * );
bool cmd( );

int main( )
{
    int maxSize = 30;
    char theString[maxSize];
    char *input[maxSize];
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
            cin.getline( theString, maxSize );
            cin.clear( );
            cin.sync( );
        }

        //pid_t pid = fork( );

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

        cin.clear( );
        cin.sync( );
        cout.flush( );
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

void parser( char *getLine, char *theInput )
{
    char *tok;
    tok = strtok( getLine, " ");
    string command;

    while ( tok != NULL )
    {
        command = tok;
    }
        //
}

bool cmd( )
{

}
