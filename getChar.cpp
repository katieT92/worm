#include <iostream>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sgtty.h>
#include <curses.h>
#include <signal.h>

const int SEC_DELAY = 0;
const int USEC_DELAY = 800000;
static char lastc = ' ';
void die( void );
char get_char( void );

char get_char( )
{
     char	c;
     struct timeval tvec;
     fd_set rfds;

     tvec.tv_sec = SEC_DELAY;
     tvec.tv_usec = USEC_DELAY;
     FD_ZERO(&rfds);
     FD_SET(0, &rfds);

     int retval = select(1, &rfds, NULL, NULL, &tvec); // chooses the input
     if ( retval < 0 ) //if less than 0, it wsant able to read the character. something went wrong. we dont expect this.
	 die();
     
     if ( retval ) {
         if ( read(0, &c, 1) < 0) // reads just one character. if read reads something undesirble usually returns like -1 and the program does.
             die();
//         if( c == LEFT || c == RIGHT || c == UP || c == DOWN ) 
         lastc = c;
     }
     return( lastc );
}

void die( void )
{
     signal( SIGINT, SIG_IGN );
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     endwin();
     exit( 1 );
}
