#include "./makeParserTokens.h"



void makeParseStream( int inFD, int outFD, int stringsFD ){
	Monad monad;
	size_t bytes_read;
	ParserToken parserToken;
	char* stringVal;


	while (1){
		bytes_read = read( inFD, &monad, sizeof(Monad) );	
		parserToken.val.intVal = 0;	
		if (bytes_read < sizeof( Monad )){
			if (bytes_read > 0)
				LOG("Error reading from input at makeParseStream\n");
			return;
		}
		if (monad.type == NAME_TOKEN || monad.type == STRING_TOKEN){
			stringVal = (char *) malloc( monad.size + 1 );
			if (!stringVal){
				CHECK_MALLOC_ERRORS;
				return;
			}
			read(stringsFD, stringVal, monad.size);
			stringVal[monad.size] = 0;
		}
		makeParserToken( &monad, &parserToken, stringVal );
		
		write(outFD, &parserToken, sizeof( parserToken ) );
	}
	parserToken.val.intVal = 0;
	parserToken.isTerminal = true;
	parserToken.symbol.terminal = PARSER_EOF_TOKEN;

	write(outFD, &parserToken, sizeof( parserToken ));
}



void makeParserToken( Monad *m, ParserToken *parserToken, char *stringVal){
	
	switch( m -> type){
		case INT_TOKEN:
			parserToken -> val.intVal = m -> value.intVal;
			parserToken -> isTerminal = true;
			parserToken -> symbol.terminal = PARSER_INT_TOKEN;
			break;

		case FLOAT_TOKEN:
			parserToken -> val.floatVal = m -> value.floatVal;
			parserToken -> isTerminal = true;
			parserToken -> symbol.terminal = PARSER_FLOAT_TOKEN;
			break;

		case NAME_TOKEN:
			parserToken -> val.stringVal = stringVal;
			parserToken -> symbol.terminal = PARSER_NAME_TOKEN;
			parserToken -> isTerminal = true;	
			break;

		case STRING_TOKEN:
			parserToken -> val.stringVal = stringVal;
			parserToken -> symbol.terminal = PARSER_STRING_TOKEN;
			parserToken -> isTerminal = true;	
			break;

		case FULLSTOP_TOKEN:
			parserToken -> symbol.terminal = PARSER_FULLSTOP_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case ASSIGN_TOKEN:
			parserToken -> symbol.terminal = PARSER_ASSIGN_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case COMMA_TOKEN:
			parserToken -> symbol.terminal = PARSER_COMMA_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case PLUS_TOKEN:
			parserToken -> symbol.terminal = PARSER_PLUS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case MINUS_TOKEN:
			parserToken -> symbol.terminal = PARSER_MINUS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case STAR_TOKEN:
			parserToken -> symbol.terminal = PARSER_STAR_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case FSLASH_TOKEN:
			parserToken -> symbol.terminal = PARSER_FSLASH_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case MOD_TOKEN:
			parserToken -> symbol.terminal = PARSER_MOD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case PLUSEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_PLUSEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case MINUSEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_MINUSEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case FSLASHEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_FSLASHEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case MODEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_MODEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case TIMESEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_TIMESEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case PLUSPLUS_TOKEN:
			parserToken -> symbol.terminal = PARSER_PLUSPLUS_TOKEN;
			parserToken -> isTerminal = true;
			break;
			
		case MINUSMINUS_TOKEN:
			parserToken -> symbol.terminal = PARSER_MINUSMINUS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case GREATERTHAN_TOKEN:
			parserToken -> symbol.terminal = PARSER_GREATERTHAN_TOKEN;
			parserToken -> isTerminal = true;
			break;
			
		case LESSTHAN_TOKEN:
			parserToken -> symbol.terminal = PARSER_LESSTHAN_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case GEQ_TOKEN:
			parserToken -> symbol.terminal = PARSER_GEQ_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LEQ_TOKEN:
			parserToken -> symbol.terminal = PARSER_LEQ_TOKEN;
			parserToken -> isTerminal = true;
			break;
			
		case EQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_EQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case NEQUALS_TOKEN:
			parserToken -> symbol.terminal = PARSER_NEQUALS_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case SEMICOLON_TOKEN:
			parserToken -> symbol.terminal = PARSER_SEMICOLON_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case COLON_TOKEN:
			parserToken -> symbol.terminal = PARSER_COLON_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LPAREN_TOKEN:
			parserToken -> symbol.terminal = PARSER_LPAREN_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case RPAREN_TOKEN:
			parserToken -> symbol.terminal = PARSER_RPAREN_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LSQUARE_TOKEN:
			parserToken -> symbol.terminal = PARSER_LSQUARE_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case RSQUARE_TOKEN:
			parserToken -> symbol.terminal = PARSER_RSQUARE_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LCURLY_TOKEN:
			parserToken -> symbol.terminal = PARSER_LCURLY_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case RCURLY_TOKEN:
			parserToken -> symbol.terminal = PARSER_RCURLY_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case NOT_TOKEN:
			parserToken -> symbol.terminal = PARSER_NOT_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case BITOR_TOKEN:
			parserToken -> symbol.terminal = PARSER_BINOR_TOKEN;
			parserToken -> isTerminal = true;
			break;
			
		case BITAND_TOKEN:
			parserToken -> symbol.terminal = PARSER_BINAND_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LOGICALAND_TOKEN:
			parserToken -> symbol.terminal = PARSER_LOGICALAND_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case COMPLEMENT_TOKEN:
			parserToken -> symbol.terminal = PARSER_COMPLEMENT_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case XOR_TOKEN:
			parserToken -> symbol.terminal = PARSER_XOR_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LEFTSHIFT_TOKEN:
			parserToken -> symbol.terminal = PARSER_LEFTSHIFT_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case RIGHTSHIFT_TOKEN:
			parserToken -> symbol.terminal = PARSER_RIGHTSHIFT_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case QUESTION_TOKEN:
			parserToken -> symbol.terminal = PARSER_QUESTION_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case ARROW_TOKEN:
			parserToken -> symbol.terminal = PARSER_ARROW_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case CHAR_TOKEN:
			parserToken -> symbol.terminal = PARSER_CHAR_TOKEN;
			parserToken -> val.intVal = m -> value.intVal;
			parserToken -> isTerminal = true;
			break;

		case DO_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_DO_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case DEFAULT_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_DEFAULT_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case DOUBLE_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_DOUBLE_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case ELSE_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_ELSE_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case ENUM_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_ENUM_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case FLOAT_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_FLOAT_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case FOR_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_FOR_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case GOTO_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_GOTO_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case IF_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_IF_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case INT_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_INT_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case LONG_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_LONG_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case CHAR_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_CHAR_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case RETURN_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_RETURN_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case SHORT_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_SHORT_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case UNSIGNED_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_UNSIGNED_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case SIZEOF_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_SIZEOF_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case STRUCT_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_STRUCT_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case SWITCH_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_SWITCH_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case UNION_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_UNION_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case VOID_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_VOID_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;

		case WHILE_KEYWORD_TOKEN:
			parserToken -> symbol.terminal = PARSER_WHILE_KEYWORD_TOKEN;
			parserToken -> isTerminal = true;
			break;
		case EOF_TOKEN:
			parserToken -> symbol.terminal = PARSER_EOF_TOKEN;
			parserToken -> isTerminal = true;
			break;
		case AMPERSAND_TOKEN:
		case REGISTER_KEYWORD_TOKEN:
		case STATIC_KEYWORD_TOKEN:

		default: 
			dprintf( 2, "Token type is undefined for some token...\n");

	}
}
