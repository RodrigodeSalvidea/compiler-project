#ifndef ERROR_REPORTING
#define ERROR_REPORTING
#include <stdio.h>



typedef unsigned int LineNumber;
typedef unsigned int Position;
typedef unsigned int CompilerErrorNumber;


typedef struct s_ErrorInformation{
	LineNumber line;
	Position position;
	CompilerErrorNumber error;	
	char *message;
} ErrorInformation;


typedef struct s_ErrorListNode{
	struct s_ErrorListNode *next;
	ErrorInformation *data;
} ErrorListNode;
typedef struct s_ErrorList{
	ErrorListNode *head;
	ErrorListNode *tail;
} ErrorList;
ErrorList *initErrorList();
void reportCompilerError(ErrorList *list, ErrorInformation *e);
void showCompilerErrors(ErrorList *list, char *path, FILE * sourceFile);
void freeErrorList(ErrorList *list);
#endif
