#ifndef PARSER_DEFINITIONS
#define PARSER_DEFINITIONS
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "./parser-tables.h"


union u_Symbol{
	Terminal terminal;
	NonTerminal nonTerminal;
};
typedef union u_Symbol Symbol;

union u_ExprValue{
	long intVal;
	double floatVal;
	char *stringVal;
};
typedef union u_ExprValue ExprValue;

typedef unsigned int ValueType;

struct s_ParserToken{
	bool isTerminal;
	Symbol symbol;
	ExprValue val;	
};
typedef struct s_ParserToken ParserToken;



struct s_Variable{
        char* name;
        ExprValue value;
        bool resolved;
};
typedef struct s_Variable Variable;

struct s_Scope{
        struct s_Scope *parentScope;
        Variable *variables;
        unsigned int length;
        unsigned int maxLength;
};
typedef struct s_Scope Scope;





enum e_PrimitiveValueType{
	PRIM_STRING_VALUE,
	PRIM_POINTER_VALUE,
	PRIM_INT_VALUE,
	PRIM_DOUBLE_VALUE
};
typedef enum e_PrimitiveValueType PrimitiveValueType;



struct s_ParserTreeNode{
	struct s_ParserTreeNode *children[8];
	ParserToken *token;
	int numChildren;
};
typedef struct s_ParserTreeNode ParserTreeNode;

typedef unsigned int ParserState;

struct s_ParserStackNode{
	struct s_ParserStackNode *last;
	ParserTreeNode *token;
	ParserState state;
};
typedef struct s_ParserStackNode ParserStackNode;

typedef unsigned int Rule;



ParserTreeNode *makeParseTree( int inFD, int stringFD );
void debugParseTree( ParserTreeNode *root, int outFD );

#endif
