#ifndef SCOPE_DEFINITIONS
#define SCOPE_DEFINITIONS




#include <string.h>
#include <stdlib.h>
#include <../include/logging.h>
#include "./parser.h"
#include <stdbool.h>
#define MIN_SCOPE_BUFFER_LENGTH 0x10
#define NAME_ALREADY_DEFINED_IN_SCOPE 0x00000001


Scope *initializeScope();
void freeScope( Scope *scope );
int defineInScope( Scope *scope, char *string, size_t stringLen );
Scope *searchScope( Scope *scope, char *string );
#endif
