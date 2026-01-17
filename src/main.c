#include "./lineTracker.h"
#include <stdio.h>
#include "interpret.h"
#include <assert.h>
#include "../include/logging.h"
#include "./nextChar.h"
#include "./stateStack.h"
#include "./scanner.h"
#include "./parser.h"
#include "./compileFile.h"

#define INPUT_FILE "./sample_code/various-tokens"



int countLines(char *path){
	int count = 0;
	FILE *f = fopen(path, "r");
	if (!f){
		CHECK_OPEN_ERRORS(-1, INPUT_FILE);
	}
	int c = 'a';
	while (c > 0){
		c = fgetc(f);
		if (c == '\n'){
			count++;
		}
	}



	fclose(f);
	return count;
}

int main(int argc, char **argv){
	/*
	int inFD; int outFD;int stringOut;
	ParserTreeNode *parseTree;

	outFD = open(SCANNER_OUTPUT_FILE,O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
	CHECK_OPEN_ERRORS(outFD, SCANNER_OUTPUT_FILE);

	stringOut = open(STRING_OUT,O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
	CHECK_OPEN_ERRORS(stringOut, STRING_OUT);
	
	inFD = open(INPUT_FILE, O_RDONLY);
	CHECK_OPEN_ERRORS(inFD, INPUT_FILE);
	
	assert(inFD >= 0 && "input file is not open");
	assert(outFD >= 0 && "output file is not open");
	assert(stringOut >= 0 && "string output file is not open");

        scan(inFD, outFD, stringOut);
	
	close(outFD);
	close(inFD);
	close(stringOut);	
//----------------------------------------------//
//---------------------------------------------//

	inFD = open( SCANNER_OUTPUT_FILE, O_RDONLY );
	CHECK_OPEN_ERRORS( inFD, SCANNER_OUTPUT_FILE );
	outFD = open(PARSER_INPUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	CHECK_OPEN_ERRORS( inFD, PARSER_INPUT_FILE )
	stringOut = open( STRING_OUT, O_RDONLY );
	parseTree = makeParseTree( inFD, stringOut);
	CHECK_OPEN_ERRORS( stringOut, STRING_OUT );
	close(inFD);
	close(outFD);
	close(stringOut);


	debugParseTree( parseTree, 2);
	*/
	int lines;
	lines = countLines(INPUT_FILE);
	compileFile( INPUT_FILE, lines, VERBOSE );	


	return 0;

}
