#include <stdbool.h>
#include <fcntl.h>
#include <assert.h>
#ifndef NEXTCHAR_DEFINITIONS
#define NEXTCHAR_DEFINITIONS
#define BUFFER_LENGTH 0x1000
void nextChar(int inFD, char *char_ptr);
void rollBack();
#endif
