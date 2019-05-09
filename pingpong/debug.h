#ifndef DEBUG_H
#define DEBUG_H

#ifndef NDEBUG
#  define DEBUG(msg, ...)   Serial.print(msg, ##__VA_ARGS__)
#  define DEBUGLN(msg, ...) Serial.println(msg, ##__VA_ARGS__)
#  define DEBUGW(msg, len)  Serial.write(msg, len)
#else
#  define DEBUG(msg, ...)   do {} while (0)
#  define DEBUGLN(msg, ...) do {} while (0)
#  define DEBUGW(msg, len)  do {} while (0)
#endif


#endif
