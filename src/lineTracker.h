#ifndef LINETRACKER_DEFS
#define LINETRACKER_DEFS
#include <stddef.h>
#include <stdlib.h>

struct s_LineTable{
	int *indexes;
	int size;
	int length;
	int lineIndex;
	int tokenIndex;

};
typedef struct s_LineTable LineTable;

LineTable *initLineTable(size_t lines);

void freeLineTable( LineTable *lineTable );

void nextLine(LineTable *lineTable );

void nextToken( LineTable *lineTable );

int nextTokenIndex( LineTable *lineTable, int *position );


#endif
