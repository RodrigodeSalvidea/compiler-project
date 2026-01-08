#include <scope.h>



Scope *initializeScope(){
	Scope *scope = (Scope *) malloc( sizeof(Scope) );
	if (!scope){
		CHECK_MALLOC_ERRORS;
	}
	scope -> variables = (Variable *) malloc( sizeof( Variable ) * MIN_SCOPE_BUFFER_LENGTH );
	scope -> parentScope = NULL;
	scope -> length = 0;
	scope -> maxLength = MIN_SCOPE_BUFFER_LENGTH;
	if (!scope -> variables){
		CHECK_MALLOC_ERRORS;
	}
	return scope;
}


int defineInScope( Scope *scope, char *string, size_t stringLen ){
	char *newName;

	for(int i = 0; i < scope -> length; i++){
		if (!strcmp(string, scope -> variables[i].name))
			return NAME_ALREADY_DEFINED_IN_SCOPE;	
		}
	
	if ( scope -> length == scope -> maxLength - 1){
		int newLength = 2 * scope -> maxLength;
		Variable* newBuff = (Variable*) malloc( sizeof( Variable ) * newLength );
		if (!newBuff){
			CHECK_MALLOC_ERRORS;
		}	
		memcpy(newBuff, (void *) scope -> variables, (size_t) (sizeof( Variable ) * scope -> length));
		free(scope -> variables);
		scope -> variables = newBuff;
		scope -> maxLength = newLength;
	}
	
	newName = malloc( sizeof(char) * (stringLen + 1));
	if (newName){
		CHECK_MALLOC_ERRORS;
	}
	strncpy(newName, string, stringLen);
	newName[stringLen] = 0;
	Variable var;
	var.resolved = false;
	var.name = newName;
	scope -> variables[ scope -> length ] = var;
	scope -> length++;
	return 0;
}

Scope* searchScope( Scope *scope, char *string ){
	int index;
	

	for( index = 0; index < scope -> length; index++ ){
		if ( !strcmp( string, scope -> variables[index].name) ){
			return scope;
		}
	}
	if ( scope -> parentScope ){
		return searchScope( scope -> parentScope, string );
	}
	return NULL;
}

void freeScope( Scope *scope ){
	int index;
	for( index = 0; index < scope -> length; index++ ){
		free( scope -> variables[ index ].name );
	}
			
	free( scope -> variables );
}
