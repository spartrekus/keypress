
//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__) //linux
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__) 
#define MYOS 4  // freebsd
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <stdlib.h>
#include <string.h>
#include <termios.h>


///////////////
char* scan_line( char* buffer, int buffer_size) 
{
   char* p = buffer;
   int count = 0;
   do {
       char c;
       scanf("%c", &c); // scan a single character
       // break on end of line, string terminating NUL, or end of file

       if (c == '\r' || c == '\n' || c == 0 || c == EOF) 
       {
           *p = 0;
           break;
       }

       *p++ = c; // add the valid character into the buffer
   } while (count < buffer_size - 1);  // don't overrun the buffer
   // ensure the string is null terminated
   buffer[buffer_size - 1] = 0;
   return buffer;
}



static struct termios oldt;

void restore_terminal_settings(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void enable_waiting_for_enter(void)
{
    tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
    struct termios newt;

    /* Make terminal read 1 char at a time */
    tcgetattr(0, &oldt);  /* Save terminal settings */
    newt = oldt;  /* Init new settings */
    newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
    tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
    atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}


int main( int argc, char *argv[])
{
    char string[PATH_MAX];
    int key = 0;
    ///////////////
    if ( argc == 2)
    if ( strcmp( argv[1] , "input" ) ==  0 ) 
    {
       strncpy( string, "" , PATH_MAX );
       printf("Enter a string: ");
       scan_line( string , PATH_MAX);
       printf("got: \"%s\"\n\n", string );
       return 0;
    }

    printf("-= KeyPress =-\n");


    int ch;
    disable_waiting_for_enter();
    /* Key reading loop */
    while (1) {
        ch = getchar();
        if (ch == 'Q') return 0;  /* Press 'Q' to quit program */
        if (ch == 'q') return 0;  /* Press 'Q' to quit program */

        if (ch == ':') 
        {
            enable_waiting_for_enter();
            strncpy( string, "" , PATH_MAX );
            printf("Enter a string: ");
            scan_line( string , PATH_MAX);
            printf("got: \"%s\"\n", string );
            disable_waiting_for_enter();
        }
        else 
          printf("You pressed %c\n", ch);
    }

    return 0;
}




