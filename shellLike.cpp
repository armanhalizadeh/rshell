#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <linux/wait.h>
#include <linux/types.h>

using namespace std;


void printPrompt( );

int main( )
{
    int maxSize = 30;
    char theString[maxSize];
    char *theUser;
    char nameAndLocation[maxSize];
    char *tok;
    string shellPrompt = "$ - ";
    string exitFlag = "ok";
    string command;

    while ( command != "exit" )
    {
        cout.flush( );
        printPrompt( );
        //fgets( theString, maxSize, stdin );
        cin.getline( theString, maxSize );

        while ( strcmp( theString, "\0") == 0 )
        {
            printPrompt( );
            cin.getline( theString, maxSize );
            cin.clear( );
            cin.sync( );
        }

        tok = strtok( theString, " ");
        command = tok;

        if ( command == "ls" )
        {
            pid_t pid = fork( );

            if ( pid == 0 )
                execl( "/bin/ls", "ls", (char *) 0 );
        }

        cin.clear( );
        cin.sync( );
        cout.flush( );
        //usleep( 1 );
    }

    return 0;
}

void printPrompt( )
{
    int maxSize = 30;

    char *theUser;
    char hostAndLocation[maxSize];

    theUser = getlogin( );
    gethostname( hostAndLocation, maxSize );


    cout << theUser << '@' << hostAndLocation << ": ";

}
