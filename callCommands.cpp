#include <iostream>
#include <unistd.h>


using namespace std;

int main( )
{
    //cout << "Before" << endl;

    int pid = fork( );

    //cout << pid << endl;

    if ( pid == 0 )
        execl( "/bin/ls", "ls", (char *) 0 );

    //cout << "done" << endl;

    return 0;
}
