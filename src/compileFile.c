#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "./scanner.h"
#include "./lineTracker.h"
#include "./interpret.h"
#include "./modes.h"
#include "./parser.h"
#include "./compileFile.h"
#include "./errors.h"


int compileFile( char *path, int lines, unsigned int mode){
	int pathLen;
	int stringOutputLen;
	int tokenOutputLen;
	char *scannerOutputPath;
	char *stringOutputPath;
	char *stringOutputExtension = ".strings";
	char *tokenOutputExtension = ".tokens";
	FILE *tokenOutputFile;
	FILE *stringOutputFile;	
	FILE *sourceFile;
	int sourceFD;
	char *create_file_flags;
	char *read_file_flags;
	LineTable *lineTable;
	ErrorList *errors;
	ParserTreeNode *parseTree;

	pathLen = strlen(path);
	tokenOutputLen = pathLen + strlen(tokenOutputExtension);
	stringOutputLen = pathLen + strlen(stringOutputExtension);

	scannerOutputPath = (char *) malloc( sizeof( char ) * (tokenOutputLen + 1) );
	strcpy( scannerOutputPath, path );
	strcat( scannerOutputPath, stringOutputExtension );
	
	stringOutputPath = (char *) malloc( sizeof( char ) * (stringOutputLen + 1) );
	strcpy( stringOutputPath, path );
	strcat( stringOutputPath, tokenOutputExtension );

	create_file_flags = "a";
	read_file_flags = "r";


	sourceFD = open( path, O_RDONLY );

	tokenOutputFile = fopen( scannerOutputPath, create_file_flags );
	stringOutputFile = fopen( stringOutputPath, create_file_flags );


	lineTable = initLineTable( lines );
	errors = initErrorList();


	scan( sourceFD, tokenOutputFile, stringOutputFile, lineTable);


	fclose(tokenOutputFile);
	fclose(stringOutputFile);	
	close(sourceFD);
	if (mode & VERBOSE){
		int inFD;
		int stringFD;
		inFD = open( scannerOutputPath, O_RDONLY );
		stringFD = open( stringOutputPath, O_RDONLY );
		interpret( inFD, stringFD );	
		close(inFD);
		close(stringFD);
	}

/************************************************************************************/
	tokenOutputFile = fopen(scannerOutputPath, "r");
	stringOutputFile = fopen(stringOutputPath, "r");

	parseTree = makeParseTree( tokenOutputFile, stringOutputFile, lineTable, errors);

	if (!parseTree){
		sourceFile = fopen(path, "r");
		showCompilerErrors(errors, path, sourceFile);
		fclose(sourceFile);
	}
	else if (VERBOSE & mode){
		debugParseTree(parseTree, 2);
	}
	/*****/
	fclose(tokenOutputFile);
	remove(scannerOutputPath);

	fclose(stringOutputFile);
	remove(stringOutputPath);
	

}
