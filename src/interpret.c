#include "scanner.h"
#include <stdio.h>
#include <unistd.h>
#include "interpret.h"

void interpret(int inFD, int stringFD){
int r_status;
Monad m;
char stringBuffer[0x1000];
do{
  r_status = read(inFD, &m, sizeof(Monad));
  if (r_status < sizeof(Monad)){break;}
  switch(m.type){
	  case   INT_TOKEN:
		 printf("<int literal: %li>\n", m.value.intVal);
		 break; 
	  case   FLOAT_TOKEN:
                 printf("<float literal: %f>\n",m.value.floatVal);
	  case NAME_TOKEN:
		 read(stringFD, stringBuffer, m.size);
		 printf("<name token %.*s >\n", m.size, stringBuffer);
		 break;
	  case       STRING_TOKEN:
		 read(stringFD, stringBuffer, m.size);
		 printf("<string token %.*s >\n", m.size, stringBuffer);
		 
		 break;
	  case       EMPTY_TOKEN:
		 break;
	  case       FULLSTOP_TOKEN:
		 printf("<fullstop token . >\n");
		 break;
	  case       ASSIGN_TOKEN:
		 printf("<assignment token = >\n");
		 break;
	  case       COMMA_TOKEN:
		 printf("<comma token , >\n");
		 break;
	  case       PLUS_TOKEN:
		 printf("<plus token + >\n");
		 break;
	  case       MINUS_TOKEN:
                 printf("<plus token - >\n");
		 break;
	  case       STAR_TOKEN:
		 printf("<star token * >\n");
		 break;
	  case       FSLASH_TOKEN:
		 printf("<fslash token / >\n");
		 break;
	  case       MOD_TOKEN:
		 printf("<mod token %% >\n");
		 break;
	  case       PLUSEQUALS_TOKEN:
		 printf("<plusequals token += >\n");
		 break;
	  case       MINUSEQUALS_TOKEN:
		 printf("<minusequals token -=> \n");
		 break;
	  case       FSLASHEQUALS_TOKEN:
		 printf("<fslashequals token /= >\n");
		 break;
	  case       MODEQUALS_TOKEN:
		 printf("<modequals token %%= >\n");
		 break;
	  case       TIMESEQUALS_TOKEN:
		 printf("<timesequals token *= >\n");
		 break;
	  case       PLUSPLUS_TOKEN:
		 printf("<incrementer token ++ >\n");
		 break;
	  case       MINUSMINUS_TOKEN:
	    	printf("<decrementer token -- >\n");
 		break;
	  case       GREATERTHAN_TOKEN:
		printf("<greaterthen token > >\n");
		break;
	  case       LESSTHAN_TOKEN:
		printf("<lessthan token < >\n");
		break;
	  case       GEQ_TOKEN:
		printf("<geq token >= >\n");
		break;
	  case       LEQ_TOKEN:
		printf("<leq token <= >\n");
		break;
	  case       EQUALS_TOKEN:
		printf("equals token == >\n");
		break;
	  case    NEQUALS_TOKEN:
		printf("<nequals token != >\n");
		break;
	  case      SEMICOLON_TOKEN:
		printf("<semicolon token ; >\n");
		break;
	  case      COLON_TOKEN:
		printf("<colon token : >\n");
		break;
	  case      LPAREN_TOKEN:
		printf("< lparen token ( >\n");
		break;
	  case      RPAREN_TOKEN:
		printf("<rparen token ) >\n");
		break;
	  case      LSQUARE_TOKEN:
		printf("<lsquare token [ >\n");
		break;
           case      RSQUARE_TOKEN:
		printf("<rsquare token ] >\n");
		break;
	   case      LCURLY_TOKEN:
		printf("<lcurly token { >\n");
		break;
	   case      RCURLY_TOKEN:
		printf("<rcurly token }\n");
		break;
	   case      NOT_TOKEN:
		printf("<logical not token ! >\n");
		break;
	   case      BITOR_TOKEN:
		printf("<bitwise or token | >\n");
		break;
	   case      BITAND_TOKEN:
		printf("<bitwise and token & >\n");
		break;
	   case      LOGICALAND_TOKEN:
		printf("<logical and token && >\n");
		break;
	   case      LOGICALOR_TOKEN:
		printf("<logical or token || >\n");
		break;
	   case      COMPLEMENT_TOKEN:
		printf("<bitwise complement token ~ >\n");
		break;
	   case      XOR_TOKEN:
		printf("<xor token ^ >\n");
		break;
	   case      AMPERSAND_TOKEN:
		printf("<ampersand token & >\n");
		break;
	   case      LEFTSHIFT_TOKEN:
		printf("<leftshift token << >\n");
		break;
	   case      RIGHTSHIFT_TOKEN:
		printf("<rightshift token >> >\n");
		break;
	   case	     QUESTION_TOKEN:
		printf("<question token ? >\n");
		break;
	   case ARROW_TOKEN:
		printf("<arrow token -> >\n");
		break;
           case CHAR_TOKEN:
		printf("<char token %c >\n", (char) m.value.intVal);
		break;
           case BREAK_KEYWORD_TOKEN:
		printf("<break keyword token>\n");
		break;
	   case CASE_KEYWORD_TOKEN:
		printf("<case keyword token>\n");
		break;
	   case CHAR_KEYWORD_TOKEN:
		printf("<char keyword token>\n");
		break;
	   case CONTINUE_KEYWORD_TOKEN:
	        printf("<continue keyword token>\n");
		break;
	   case DO_KEYWORD_TOKEN:
		printf("<do keyword token>\n");
		break;
	   case DEFAULT_KEYWORD_TOKEN:
		printf("<default keyword token>\n");
		break;
	   case DOUBLE_KEYWORD_TOKEN:
		printf("<double keyword token>\n");
		break;
	   case ENUM_KEYWORD_TOKEN:
		printf("<enum keyword token>\n");
		break;	
	   case FLOAT_KEYWORD_TOKEN:
		printf("<float keyword token>\n");
		break;
	   case FOR_KEYWORD_TOKEN:
		printf("< for keyword token >\n");
		break;
	   case GOTO_KEYWORD_TOKEN:
		printf("< goto keyword token>\n");
		break;
	   case IF_KEYWORD_TOKEN:
		printf("< if keyword token>\n");
	        break;	
	   case INT_KEYWORD_TOKEN:
		printf("< int keyword token >\n");
	        break;	
	   case LONG_KEYWORD_TOKEN:
		printf("< long keyword token >\n");
		break;
	   case REGISTER_KEYWORD_TOKEN:
		printf("< register keyword token >\n");
		break;
	   case RETURN_KEYWORD_TOKEN:
		printf("< return keyword token >\n");
		break;
	   case SHORT_KEYWORD_TOKEN:
		printf("< short keyword token >\n");
	        break;	
	   case UNSIGNED_KEYWORD_TOKEN:
		printf("< unsigned keyword token>\n");
	        break;	
	   case SIZEOF_KEYWORD_TOKEN:
		printf("< sizeof keyword token>\n");
	        break;	
	   case STATIC_KEYWORD_TOKEN:
		printf("< static keyword token>\n");
	        break;	
	   case STRUCT_KEYWORD_TOKEN:
		printf("< struct keyword token>\n");
		break;
	   case SWITCH_KEYWORD_TOKEN:
		printf("< switch keyword token>\n");
		break;
	   case UNION_KEYWORD_TOKEN:
		printf("< union keyword token>\n");
		break;
	   case VOID_KEYWORD_TOKEN:
		printf("< void keyword token>\n");
		break;
	   case WHILE_KEYWORD_TOKEN:
		printf("< while keyword token>\n");
		break;
	   default:
		printf("<< !!!!unknown token!!! >>\n");
		break;
  }
  
}while(1);


}
