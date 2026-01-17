#include "./errors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
ErrorList *initErrorList(){
	ErrorList *ei = (ErrorList *) malloc(sizeof(ErrorList));
	ei -> head = 0x0;
	ei -> tail = 0x0;
	return ei;
}

void reportCompilerError(ErrorList *list, ErrorInformation  *ei){
	ErrorInformation *errorInformation = (ErrorInformation *) malloc( sizeof(errorInformation) );
	ErrorListNode *node = ( ErrorListNode *) malloc( sizeof( ErrorListNode ) );

	errorInformation -> line = ei -> line;
	errorInformation -> position = ei -> position;
	errorInformation -> error = ei -> error;
	errorInformation -> message = ei -> message;



	node -> data = errorInformation;
	node -> next = 0x0;
	if (list -> tail)
		list -> tail -> next = node;
	
	
	list -> tail = node;
	

	if (!list -> head){
		list -> head = node;

	}

}
	



void showCompilerErrors(ErrorList *list, char *path, FILE *sourceFile){

	ErrorListNode *head = list -> head;

	while (head){
		int lineNo;
		size_t len;
		char *line;
		int line_read;
		int line_number;
		char *error_message;
		char *source_file_line;
		int position_number;
		lineNo = head -> data -> line;

		line_number = lineNo;
		position_number = head -> data -> position;
		error_message = head -> data -> message;

		

		


		len = 0;
		line_number = 0;				
		rewind(sourceFile);
		


		fprintf(stderr, "\nERROR in file %s at line %d token %d %s:\n", path, lineNo, position_number, error_message);
		
		while(line_number < lineNo - 1){
			line = NULL;
			line_read = getline(&line, &len, sourceFile);
			free(line);
			line_number++;
		}
		while( line_number < lineNo + 1 && line_read > -1 )	{
			line = NULL;
			line_read = getline(&line, &len, sourceFile);
			fprintf(stderr, "%d | > %s", line_number, line);
			free(line);
			line_number++;
		}

	       	head = head -> next;

	}

}

void freeErrorList( ErrorList *list ){
	ErrorListNode *head = list -> head;
	ErrorListNode *tail;

	while(head){
		free(head -> data);
		free(head -> data);
		tail = head -> next;
		free(head);
		head = tail;	
	}
	free(list);
}
