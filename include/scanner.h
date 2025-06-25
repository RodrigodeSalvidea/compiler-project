#include <stdio.h>
#define BUFFER_LENGTH 0x1000
/* 	Character classes: whitespace: /t, /n, /s
 *  	SemiColon
 *  	Exclamation Point
 *  	Parenthesis(Left and Right)
 *  	Square Braces(Left and Right)
 *  	Curly Braces(Left and Right)
 *	ampersand
 *	pipe
 *	alphanumeric
 *	alphabetical
 *	numerical
 *	Arith
 *
 *
 *	keywords: 
 *		break, case, char, const, auto, short, struct, double, int,
 *		else, enum, float, continue, sizeof, switch, default, extern,
 *		for, do, goto, if, typedef, union, void, static, signed, long,
 *		register, return unsigned, volatile
 *
*/
/*Open the file. do some error checking, return a file descriptor*/


enum Word {
	//keywords:
	INT,
	CASE,
	CHAR,
	CONST,
	AUTO,
	SHORT,
	STRUCT,
	DOUBLE,
	INT,
	ELSE,
	ENUM, 
	FLOAT,
	CONTINUE,
	SIZEOF,
	SWITCH,
	DEFAULT,
	EXTERN,
	FOR,
	DO,
	GOTO,
	IF,
	TYPEDEF,
	UNION,
	VOID,
	STATIC,
	SIGNED,
	LONG,
	REGISTER,
	RETURN,
	UNSIGNED,
	VOLATILE,
	//identifiers:
	IDENTIFIER,
	//value types:
	INTEGER_VALUE,
	FLOATING_POINT_VALUE,
	CHARACTER_VALUE,
	STRING_VALUE,
	POINTER_VALUE,
	//punctuation 
	PARENTHESIS_LEFT,
	PARENTHESIS_RIGHT,
	SQUARE_LEFT,
	SQUARE_RIGHT,
	CURLY_LEFT,
	CURLY_RIGHT
	SEMICOLON,
	PERIOD,
	//operators
	///bitwise operators	
	BITWISE_OR,
	BITWISE_AND,
	BITWISE_XOR,
	BITWISE_COMPLEMENT,
	////boolean operators
	BOOLEAN_OR,
	BOOLEAN_AND,
	BOOLEAN_XOR,
	BOOLEAN_NOT,
	////arithmetic operators
	PLUS,
	MINUS,
	MULT,
	MOD,
	////pointer operators
	DEREF,
	//identifier specific operators
	ADDRESSOF,
	
	
};
struct Moneme {
	char* literal;
	int length;
	enum Word speech_type;
};


int beginScanning();
/*return the next block of size BUFFER_LENGTH*/
char* readBlock();
/**/


