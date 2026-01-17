#include "parser.h"
#include "makeParserTokens.h"





void debugParseTreeR( ParserTreeNode *root, int outFD, int level, char *tokenTypeNames[ 2 ][ NUM_TERMINALS > NUM_NONTERMINALS ? NUM_TERMINALS : NUM_NONTERMINALS]){

	int i;
	i = 0;
	dprintf(outFD,"\n");
	while (i < level){
		dprintf(outFD, "|");
		i++;
	};
	
	dprintf(outFD, "{\n");
	i = 0;
	while( i < level ){
		dprintf(outFD, "|");
		i++;
	};
	dprintf(outFD, "--- %s ---", tokenTypeNames[ !(root -> token -> isTerminal) ][ root -> token -> symbol.terminal ]);
	i = 0;
	//dprintf(outFD, "\n");
	while (i < root -> numChildren){
		debugParseTreeR(root -> children[i], outFD, level + 1, tokenTypeNames);
		i += 1;
	}
	dprintf(outFD, "\n");
	i = 0;
	while( i < level ){
		dprintf(outFD, "|");
		i++;
	};



	dprintf(outFD, "}");
//Token Type: token type
//value - none
//name
	
}
void debugParseTree( ParserTreeNode *root, int outFD){
	
	debugParseTreeR( root, outFD, 0, tokenNameTable );
	dprintf(outFD,"\n");
}


void shrinkTree(ParserTreeNode *root){
	ParserTreeNode *temp;
	int i;
	
	if (root -> token -> isTerminal){
		return;
	}
	i = 0;
	while( i < root -> numChildren){
		shrinkTree( root -> children[i] );
		i++;
	}
	if ( root -> numChildren == 1 ){
		free( root -> token );
		root -> token = root -> children[0] -> token;
		root -> numChildren  = root -> children[0] -> numChildren;	
		temp = root -> children[0];
		memcpy(root -> children, temp -> children, sizeof(ParserTreeNode*) * root -> numChildren);
		free(temp);
	}

}	


void debugStack( ParserStackNode *stack ){
	if (!stack){
		return;
	}
	debugParseTree(stack -> token, 2);
	dprintf(2, "------ state %d ------\n", stack -> state);
	debugStack(stack -> last);
}



ParserTreeNode *makeParseTree( FILE *inFile, FILE *stringFile, LineTable *lineTable, ErrorList *errorList ){
	Monad monad;
	size_t bytes_read;
	ParserToken *parserToken;
	char* stringVal;
	Rule rule;
	int ruleSize;
	ParserStackNode *stack;
	ParserStackNode *stackNode;
	ParserStackNode *temp;
	ParserToken *leftSideToken;
	ParserTreeNode *parentNode;
	ParserTreeNode *childNode;
	ParserState state;
	Action action;
	int lineNumber;
	int position;


	stack = 0x0;
	state = 0;
	action = 0x0;
	signed int ruleIndex;
	bool rightIsEmpty;

	rightIsEmpty = true;
	position = 0;

	

	int check_malloc_errors(){
		CHECK_MALLOC_ERRORS;
		return 0;
	}	
	

	while ( !(ACCEPT & action) ){
		if ( rightIsEmpty ){
			bytes_read = fread(&monad, sizeof( Monad ), 1, inFile);// )// inFD, &monad, sizeof(Monad) );	
			if (bytes_read <  1){
				if (bytes_read > 0)
					LOG("Error reading from input at makeParseStream\n");
					
				monad.type = EOF_TOKEN;
			}
			if (monad.type == NAME_TOKEN || monad.type == STRING_TOKEN){
				stringVal = (char *) malloc( monad.size + 1 );
				if (!stringVal){
					check_malloc_errors();
					return parentNode;
				}
				fread(stringVal, sizeof(char), monad.size, stringFile);// ) //stringVal, stringsFD, stringVal, monad.size);
				stringVal[monad.size] = 0;
			}
			parserToken = (ParserToken *) malloc( sizeof(ParserToken) );
			parserToken -> val.intVal = 0;	
			makeParserToken( &monad, parserToken, stringVal );
			lineNumber = nextTokenIndex( lineTable, &position );
			rightIsEmpty = false;
		}
		action = actionTable[ state ][ parserToken -> symbol.terminal ];
		if (action == UNDEFINED){
			ErrorInformation ei;
			ei.error = 0200;
			ei.message =  "Symbol not expected by parser. Parser can not continue parsing with this symbol in place\n";
			ei.line = lineNumber;
			ei.position = position;
			reportCompilerError(errorList, &ei);
			//debugParserToken(parserToken);
		/*:wq

			dprintf(2, "current state: %d\n", state);
			dprintf(2, "--- %s ---\n", tokenNameTable[ !(parserToken -> isTerminal) ][ parserToken -> symbol.terminal ]);
			dprintf(2, "stack::\n");
			debugStack( stack );//debugParseTree(parentNode, 2);
				*/
			free( parserToken );
			return 0x0;
		}	
		if (action & SHIFT){
			parentNode = (ParserTreeNode *) malloc ( sizeof(ParserTreeNode) );
			parentNode || check_malloc_errors();
			stackNode = (ParserStackNode *) malloc( sizeof(ParserStackNode) );
			stackNode || check_malloc_errors();


			parentNode -> numChildren = 0x0;
			parentNode -> token = parserToken;

			stackNode -> state = state;
			stackNode -> last = stack;
			stackNode -> token = parentNode;
			stack = stackNode;			
			state = action & ~SHIFT;
			rightIsEmpty = true;
		}
		if (action & REDUCE || action & ACCEPT){
			rule = action & ~(ACCEPT | REDUCE);
			ruleSize = ruleSizes[ rule ];
			leftSideToken = (ParserToken *) malloc( sizeof(ParserToken) );
			leftSideToken ? 1 : check_malloc_errors();

			leftSideToken -> isTerminal = false;
			leftSideToken -> symbol.nonTerminal = reductions[ rule ];
			leftSideToken -> val.intVal = 0xcafebabe;			
			parentNode = (ParserTreeNode *) malloc( sizeof(ParserTreeNode) );
			parentNode ? 1 : check_malloc_errors();
			parentNode -> token = leftSideToken;
			parentNode -> numChildren = ruleSize;
			for( ruleIndex =  ruleSize - 1; ruleIndex > -1;  ruleIndex--){
				childNode = stack -> token;
				state = stack -> state;
				temp = stack -> last;
				free(stack);
				stack = temp;
				parentNode -> children[ ruleIndex ] = childNode;
				
			}


			


			stackNode = (ParserStackNode *) malloc( sizeof(ParserStackNode) ); 
			stackNode ? 1 : check_malloc_errors();
			stackNode -> state = state;
			stackNode -> last = stack;
			stackNode -> token = parentNode;
			stack = stackNode;
			state = gotoTable[ state ][ leftSideToken -> symbol.nonTerminal ];

		}	
	}

	

	


	shrinkTree(parentNode);
	return parentNode;
}


struct s_AbstractSyntaxTree{


}


AbstractSyntaxTree *makeAST( ParserTreeNode *root){





}



