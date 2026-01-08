#ifndef MAKE_PARSER_TOKENS_DEFFS
#define MAKE_PARSER_TOKENS_DEFFS
#include "./scanner.h"
#include <stdlib.h>
#include "../include/logging.h"
#include "parser.h"

void makeParserToken( Monad *m, ParserToken *parserToken, char *stringVal);
void makeParseStream(int inFD, int outFD, int stringsFD);
#endif
