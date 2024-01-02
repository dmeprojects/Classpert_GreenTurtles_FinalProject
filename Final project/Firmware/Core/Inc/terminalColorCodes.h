/*
 *  Defines for changing the colours in the serial terminal
 *
 *  info source:
 *
 *  https://xdevs.com/guide/color_serial/
 *
 *  https://en.wikipedia.org/wiki/ANSI_escape_code
 *
 */

#ifndef INCLUDE_TERMINALCOLORCODES_H_
#define INCLUDE_TERMINALCOLORCODES_H_


/*Use default color scheme*/
#define SERIAL_DEFAULT_COLORS "\033[0;39m"

/*Reset color codes*/
#define SERIAL_RESET_COLORS   "\033[m"

/*Foreground colors*/
#define SERIAL_GREEN_CHARS    "\033[0;32m"
#define SERIAL_RED_CHARS      "\033[0;31m"
#define SERIAL_WHITE_CHARS    "\033[0;37m"
#define SERIAL_YELLOW_CHARS   "\033[0;33m"
#define SERIAL_BLUE_CHARS     "\033[0;34m"
#define SERIAL_CYAN_CHARS     "\033[0;36m"
#define SERIAL_MAGNETA_CHARS  "\033[0;35m"


/*Bright foreground colors*/
#define SERIAL_BRIGHT_GREEN_CHARS      "\033[1;32m"
#define SERIAL_BRIGHT_RED_CHARS        "\033[1;31m"
#define SERIAL_BRIGHT_YELLOW_CHARS     "\033[1;33m"
#define SERIAL_BRIGHT_WHITE_CHARS      "\033[1;37m"
#define SERIAL_BRIGHT_BLUE_CHARS       "\033[1;34m"
#define SERIAL_BRIGHT_CYAN_CHARS       "\033[1;36m"
#define SERIAL_BRIGHT_MAGNETA_CHARS    "\033[1;35m"

/*Background colors*/
#define SERIAL_RED_BACKGROUND         "\033[0;41m"
#define SERIAL_GREEN_BACKGROUND       "\033[0;42m"
#define SERIAL_BLUE_BACKGROUND        "\033[0;44m"
#define SERIAL_MAGNETA_BACKGROUND     "\033[0;45m"
#define SERIAL_CYAN_BACKGROUND        "\033[0;46m"
#define SERIAL_WHITE_BACKGROUND       "\033[0;47m"
#define SERIAL_DEFAULT_BACKGROUND     "\033[0;49m"

/*Cursor functions*/
#define SERIAL_CLEAR_SCREEN            "\033[2J"
#define SERIAL_GOLINEUP                "\033[1A"
#define SERIAL_GOSIDEWAYS              "\033[10C"

/*
 * terminal cursor movement
 *
 *  puts("\033[2J");   // clear screen
 *  puts("\033[0;0H"); // set cursor to 0,0
 *  puts("\033[10B");  // move cursor down 10 lines
 *  puts("\033[5A");  // move cursor up 5 lines
 *
 * */

#endif /* INCLUDE_TERMINALCOLORCODES_H_ */



