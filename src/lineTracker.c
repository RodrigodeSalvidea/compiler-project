#include "./lineTracker.h"
#include "../include/logging.h"

LineTable *initLineTable(size_t lines){
	LineTable *lt = (LineTable *) malloc(sizeof(LineTable));
	if (!lt){
		CHECK_MALLOC_ERRORS;
	}
	lt -> indexes = malloc(lines * sizeof(int) );
	lt -> length = 1; 
	lt -> size = lines;
	lt -> indexes[0] = 0;
	lt -> lineIndex = 0;
	return lt;
}

void freeLineTable(LineTable *lineTable){
	free(lineTable -> indexes);
	free(lineTable);
}

void nextLine(LineTable *lineTable){
	lineTable -> length++;
	lineTable -> indexes[lineTable -> length - 1] = lineTable -> indexes[lineTable -> length - 2];
}

void nextToken(LineTable *lineTable){
	lineTable -> indexes[lineTable -> length - 1]++;
}

//find highest index with a value leq target
//
int nextTokenIndex(LineTable *lineTable, int *position){
	lineTable -> tokenIndex++;
	(*position)++;
	while (lineTable -> tokenIndex > lineTable -> indexes[lineTable -> lineIndex] ){
		lineTable -> lineIndex++;
		*position = 0;
	}
	
	return lineTable -> lineIndex;
}
