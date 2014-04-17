#include <unistd.h>
#include <termios.h>  //Put with other include statements
#include <cstdio>  
#include <cstdlib> 
#include <fcntl.h>
#include <math.h>
#include <cstring>

using namespace std;



int main( int argc, char *argv[] )
{
    struct termios initial_settings, new_settings;
    int counter = 1;
    bool flag;
    int inFile, linesRead, readRtn;
    char inChar[1], uInput[1];

        tcgetattr(fileno(stdin), &initial_settings);
        new_settings=initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        
	if (tcsetattr(fileno(stdin), TCSANOW, &new_settings)!=0)
        {
             write( 1, "could not set attributes\n", 25);
             return -1;
        }

	if ( argc == 1 )	//no command line arguements profided
	{
   	     write( 1, "No command line arguements provided\n", 36 );
	}
	else
	{
	    while ( counter < argc )
        {
            inFile = open( argv[counter], O_RDONLY );
            if (inFile == -1)
            {
                write( 1, "::::::::::::::::::::::::::::::\nThe following file was not found: ", 65);
                write( 1, ("%s", argv[counter]), ( strlen( argv[counter]) ) );
                write( 1, "\n::::::::::::::::::::::::::::::\n", 32);
                flag = 1;
            //wait for user to input space
                while ( flag )
                {
                    read( 0, uInput, 1);

                    if ( uInput[0] == ' ' )
                        flag = 0;
                    if ( uInput[0] == 'q' || uInput[0] == 'Q' )
                    {
                        tcsetattr(fileno(stdin), TCSANOW, &initial_settings); 
                        return 0;
                    }
                }
            }
            else
            {
                if ( argc > 2 )     //if more than one file, print file id header
                {
                                    while ( flag )
                {
                    read( 0, uInput, 1);

                    if ( uInput[0] == ' ' )
                        flag = 0;
                    if ( uInput[0] == 'q' || uInput[0] == 'Q' )
                    {
                        tcsetattr(fileno(stdin), TCSANOW, &initial_settings); 
                        return 0;
                    }
                }
                    write( 1, "::::::::::::::::::::::::::::::\n", 31);
                    write( 1, ("%s", argv[counter]), ( strlen( argv[counter]) ) );
                    write( 1, "\n::::::::::::::::::::::::::::::\n", 32);
                                            flag = 1;
                        //wait for user to input space
                        while ( flag )
                        {
                            read( 0, uInput, 1);

                            if ( uInput[0] == ' ' )
                                flag = 0;
                            if ( uInput[0] == 'q' || uInput[0] == 'Q' )
                            {
                                tcsetattr(fileno(stdin), TCSANOW, &initial_settings); 
                                return 0;
                            }
                        }  
                }
                linesRead = 0;
                while ( (readRtn = read( inFile, inChar, 1 ) != 0) )
                {
                    if ( inChar[0] == '\n')
                        linesRead += 1;
                    write( 1, inChar, 1 );
                    if ( linesRead == 20 )
                    {
                        flag = 1;
                        //wait for user to input space
                        while ( flag )
                        {
                            read( 0, uInput, 1);

                            if ( uInput[0] == ' ' )
                                flag = 0;
                            if ( uInput[0] == 'q' || uInput[0] == 'Q' )
                            {
                                tcsetattr(fileno(stdin), TCSANOW, &initial_settings); 
                                return 0;
                            }
                        }    
                        linesRead = 0;
                    }
                }
                close( inFile );
            }
            counter += 1;
        }   
	}  
    tcsetattr(fileno(stdin), TCSANOW, &initial_settings); 
	return 0;
}
