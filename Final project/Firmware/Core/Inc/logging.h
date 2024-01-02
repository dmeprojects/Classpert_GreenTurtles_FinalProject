/*
 * logging.h
 *
 *  Created on: Jan 2, 2024
 *      Author: nick_
 */

#ifndef INC_LOGGING_H_
#define INC_LOGGING_H_

#include "terminalColorCodes.h"

#define LIBRARY_LOG_NAME "logging"

#define log(message) printLog message

/* Check if LIBRARY_LOG_NAME macro has been defined. */
#if !defined( LIBRARY_LOG_NAME )
    #error "Please define LIBRARY_LOG_NAME for the library."
#endif

#if LIBRARY_LOG_LEVEL == LOG_INFO
#define LogError( ... )		log( (SERIAL_BRIGHT_RED_CHARS) ); log( ("ERROR: ") );log( (LIBRARY_LOG_NAME) ); log( ("-> ") ); log( ( __VA_ARGS__ ) ); log( ("\r\n") )
#define LogInfo( ... )		log( (SERIAL_BRIGHT_GREEN_CHARS) ); log(("INFO: "));log( (LIBRARY_LOG_NAME) ); log( ("-> ") ); log( ( __VA_ARGS__ ) ); log(("\r\n"))
#define	LogDebug( ... )		log( (SERIAL_DEFAULT_COLORS) ); log(("DEBUG: "));log( (LIBRARY_LOG_NAME) ); log( ("-> ") ); log( ( __VA_ARGS__ ) ); log(("\r\n"))
#define	LogWarn( ... )		log( (SERIAL_BRIGHT_YELLOW_CHARS) ); log(("WARNING: "));log( (LIBRARY_LOG_NAME) ); log( ("-> ") ); log( ( __VA_ARGS__ ) );; log(("\r\n"))

#endif

void printLog (const char * pc, ...);



#endif /* INC_LOGGING_H_ */
