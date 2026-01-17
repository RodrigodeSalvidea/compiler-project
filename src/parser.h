#ifndef PARSER_DEFINITIONS
#define PARSER_DEFINITIONS
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "./lineTracker.h"
#include "./parser-tables.h"
#include "./errors.h"

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



ParserTreeNode *makeParseTree( FILE *inFile, FILE *stringFile, LineTable *lineTable, ErrorList *ei );
void debugParseTree( ParserTreeNode *root, int outFD );
/** Abstract syntax tree types **/

struct s_StmtsTree{
	void *stmt;
	void *next;
};
typedef s_StmtsTree StmtsTree;





enum e_Type{
	TYPE_ENUM,
	TYPE_STRUCT,
	TYPE_UNION,
	TYPE_POINTER,
	TYPE_BUFFER, 
	TYPE_PRIMITIVE,
	TYPE_SIGNMOD	
};


enum e_Primitive{
	PRIMITIVE_INT,
	PRIMITIVE_LONG,
	PRIMITIVE_CHAR,
	PRIMITIVE_SHORT,
	PRIMITIVE FLOAT,
	PRIMITIVE_DOUBLE,
}

typedef enum e_Primitive Primitive;
typedef enum e_Type Type;

struct s_childType {
	void *child;
	Type childType;
};	
typedef struct s_childType ChildType;


struct s_EnumMembers{
	char *name;	
	void *next;
};
typedef struct s_EnumMember EnumMembers;


struct s_EnumTypeTree{
	EnumMembers members;		       
};
struct s_EnumTypeTree EnumTypeTree;


struct s_UnionTypeTree{
	size_t numChildren;
	ChildType *children;
};
typedef struct s_UnionTypeTree UnionTypeTree;


struct s_StructTypeTree{
	size_t numChildren;
	ChildType *children;
};
typedef struct s_StructTypeTree StructTypeTree;






enum e_ConditionalType{
	COND_DO_WHILE,
	COND_WHILE,
	COND_IF_ELSE,
	COND_IF
};
typedef e_ConditionalType ConditionalType;

struct s_ConditionalStatementTree{
	ConditionalType type;
	void *conditional;
	void *block;
};
typedef struct s_ConditionalStatementTree ConditionalStatementTree;





/** Expression tree nodes **/
enum e_ExpressionType{
	EXPRESSION_UNARY,
	EXPRESSION_BINARY,
	EXPRESSION_TERNARY,
	EXPRESSION_VALUE
};
typedef enum e_ExpressionType ExpressionType


struct s_ExpressionTree{
	ExpressionType type;	
	void *expression;
};
typedef s_ExpressionTree ExpressionTree;


struct s_UnaryExpressionTree{
	UnaryOperator op;
	ExpressionTree *child;
};
typedef struct s_UnaryExpressionTree UnaryExpressionTree;


struct s_BinaryExpressionTree{
	BinaryOperator op;
	ExpressionTree *left;
	ExpressionTree *right;
};
typedef struct s_BinaryExpressionTree BinaryExpressionTree;


struct s_TernaryExpressionTree{
	struct s_TernaryExpressionTree *head;
	ExpressionTree *left;
	ExpressionTree *right;
};
typedef s_TernaryExpressionTree TernaryExpressionTree;



struct s_Decl{
	TypeTree type;
	char *name;
};


struct s_functionCallTree{
	Decl *args
	char *name;
	int  numArgs;
};
typedef struct s_functionCallTree FunctionCallTree;





#endif
