//#include "../include/scanner.h"
#include "interpret.h"
#include <assert.h>
#include "../include/logging.h"
#include "./nextChar.h"
#include "./stateStack.h"
#include "./scanner.h"

#define OUTPUT_FILE "./scanner-output.txt"
#define STRING_OUT  "./output-strings.txt"
#define INPUT_FILE "/home/rodrigo/compiler-project/tests/input/various-tokens"

int main(int argc, char **argv){
	int inFD; int outFD;int stringOut;

	outFD = open(OUTPUT_FILE,O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
	CHECK_OPEN_ERRORS(outFD, OUTPUT_FILE);

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
	inFD = open(OUTPUT_FILE, O_RDONLY);
	CHECK_OPEN_ERRORS(inFD, OUTPUT_FILE);
        stringOut = open(STRING_OUT, O_RDONLY);
	CHECK_OPEN_ERRORS(inFD, STRING_OUT);
	interpret(inFD, stringOut);
	close(inFD);

}
