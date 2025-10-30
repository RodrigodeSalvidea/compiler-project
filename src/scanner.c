#include "./scanner.h"
#include "./stateStack.h"
#include "../include/logging.h"
#include "./transitions.h"


int scan(int inFD, int outFD, int stringOut){
  char *k_break = "break"; int const breakLen = 5;
  char *k_char = "char"; int const charLen = 4;
  char *k_continue = "continue"; int const continueLen = 8;
  char *k_case = "case"; int const caseLen = 4;
  char *k_do = "do"; int const doLen = 2;
  char *k_double = "double"; int const doubleLen = 6;
  char *k_default = "default"; int const defaultLen = 7; 
  char *k_enum = "enum"; int const enumLen = 4;
  char *k_else = "else"; int const elseLen = 4;
  char *k_float = "float"; int const floatLen = 5;
  char *k_for = "for"; int const forLen = 3;
  char *k_goto = "goto"; int const gotoLen = 4;
  char *k_if = "if"; int const ifLen = 2;
  char *k_int = "int"; int const intLen = 3;
  char *k_long = "long"; int const longLen = 4;
  char *k_register = "register"; int const registerLen = 8;
  char *k_return = "return"; int const returnLen = 6;
  char *k_short = "short"; int const shortLen = 5;
  char *k_unsigned = "unsigned"; int const unsignedLen = 8;
  char *k_sizeof = "sizeof"; int const sizeofLen = 6;
  char *k_static = "static"; int const staticLen = 6;
  char *k_struct = "struct"; int const structLen = 6;
  char *k_switch = "switch"; int const switchLen = 6;
  char *k_union = "union"; int const unionLen = 5;
  char *k_void = "void"; int const voidLen = 4;
  char *k_while = "while"; int const whileLen = 5;

  char c;  
  char charVal;
  transition t;
  unsigned int intVal = 0;
  double floatVal;
  double floatPlace;
  Sign sign = POSITIVE;
  StateStack s;
  StateStack *stack = &s;
  unsigned int stringIndex = 0;
  char stringBuffer[STRING_BUFFER_LENGTH];
  initialize_stateStack(stack);
  push(stack, 0);
  State state;
  Monad m;
  off_t offset = 0;

  state_initial: 
    nextChar(inFD, &c);
    t = transitionTable(c);
    push(stack,STATE_INITIAL); 
    m.type = EMPTY_TOKEN;
//    assert(t != TRANSITION_ERROR);
    switch(c){
	case '0':
		goto state_one_zero;
        case 'b':
		goto state_k_break;
	case 'c':
	        goto state_k_c;
	case 'd':
		goto state_k_d;
	case 'e':
		goto state_k_e;
	case 'f':
		goto state_k_f;
	case 'g':
		goto state_k_goto;
	case 'i':
		goto state_k_i;
	case 'l':
		goto state_k_long;
	case 'r':
		goto state_k_re;
	case 's':
		goto state_k_s;
	case 'u':
		goto state_k_u;
	case 'v':
		goto state_k_void;
	case 'w':
		goto state_k_while;
	case '\'':
		goto state_init_char;
	case '+':
		goto state_accept_plus;
	case '-':
		goto state_accept_minus;
	case '"':
		goto state_init_string;
	case '.':
		goto state_accept_fullstop;
	case ',':
		goto state_accept_comma;	
	case ';':
		goto state_accept_semicolon;
	case '=':
		goto state_accept_assign;
	case '!':
		goto state_accept_not;
	case '<':
		goto state_accept_lessthan;
	case '>':
		goto state_accept_greaterthan;
	case ':':
		goto state_accept_colon;
	case '|':
		goto state_accept_bitor;
	case '&':
		goto state_accept_bitand;
	case '%':
		goto state_accept_mod;
	case '(':
		goto state_accept_lparen;
	case ')':
		goto state_accept_rparen;
	case '[':
		goto state_accept_lsquare;
	case ']':
		goto state_accept_rsquare;
	case '{':
		goto state_accept_lcurly;
	case '}':
		goto state_accept_rcurly;
	case '~':
		goto state_accept_complement;
	case '^':
		goto state_accept_xor;
	case '/':
		goto state_accept_fslash;
	case '*':
		goto state_accept_star;
	case '?':
		goto state_accept_question;
	case -1:
		delete_stateStack(stack);
		return 0;
	default:
		if (ALPHA_BIT & t)
			goto state_accept_name;
		if (DECIMAL_BIT & t)
			goto state_accept_decimal;
		if (WHITESPACE_BIT & t)
			goto state_initial;
		LOG("scanner encountered an error: undefined transition from the initial state");
		goto state_initial;
    }
  state_error:
   do{
    state = pop(stack);
    rollBack(); 
    }while(!(state & ACCEPTING) && state != STATE_INITIAL);
   if (state == STATE_INITIAL){
	   nextChar(inFD, &c);
   	   goto state_initial;
   }
   switch(m.type){
	case INT_TOKEN:
		m.value.intVal =  intVal;
		m.size = sizeof(long);
		intVal = 0;
		break;
	case FLOAT_TOKEN:
		m.value.floatVal =  (intVal  + floatVal);
		m.size = sizeof(double);
		intVal = 0;
		floatVal = 0.0;
		floatPlace = 1.0;

		break;
	case NAME_TOKEN:
		write(stringOut, stringBuffer, stringIndex);
		m.value.offset = offset;
		m.size = stringIndex;
		offset += stringIndex;
		stringIndex = 0;
		break;
	case STRING_TOKEN:
		write(stringOut, stringBuffer + 1, stringIndex - 1);
		m.value.offset = offset;
		m.size = stringIndex - 1;
		offset += stringIndex - 1;
		stringIndex = 0;
		break;
	default:
		stringIndex = 0;
		m.size = 1;
   }
	if (m.type != EMPTY_TOKEN)   
   		write(outFD, &m, sizeof(Monad));
  goto state_initial;
  //TODO: add keyword states
    //
  state_k_break:
  //testing for keyword break
  m.type = NAME_TOKEN;
  do{
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    stringBuffer[stringIndex] = c;
    nextChar(inFD, &c);
  }while(c == k_break[++stringIndex]);
   if (stringIndex == breakLen)
	   m.type = BREAK_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT  | DECIMAL_BIT ) & t )
	   goto state_accept_name;
   goto state_error;
   state_k_c:
   m.type = NAME_TOKEN;
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex++] = c;
   nextChar(inFD, &c);
   switch(c){
	   case 'a':
		   goto state_k_case;
	   case 'h':
		   goto state_k_char;
	   case 'o':
		   goto state_k_continue;
	   default:
		   t = transitionTable(c);
		   if (ALPHA_BIT & t || DECIMAL_BIT & t)
			   goto state_accept_name;
		   goto state_error;
   }
   state_k_case:
   m.type = NAME_TOKEN;
   do{
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    stringBuffer[stringIndex] = c;
    nextChar(inFD, &c);
   }while(c == k_case[++stringIndex]);
   if (stringIndex == caseLen)
	   m.type = CASE_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
	   goto state_accept_name;
   goto state_error;

   state_k_continue:
   do{
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    stringBuffer[stringIndex] = c;
    nextChar(inFD, &c);
   }while(c == k_continue[++stringIndex]);
   if (stringIndex == continueLen)
	   m.type = CONTINUE_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
	   goto state_accept_name;
   goto state_error;

   state_k_char:
   m.type = NAME_TOKEN;
   do{
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    stringBuffer[stringIndex] = c;
    nextChar(inFD, &c);
    }while(c == k_char[++stringIndex]);
   if (stringIndex == charLen)
       m.type = CHAR_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
	  goto state_accept_name;
  goto state_error;

  state_k_d:
  m.type = NAME_TOKEN;
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
   case 'e':
	   goto state_k_default;
   case 'o':
	   goto state_k_do;
   default:
	   if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
		   goto state_accept_name;
	   goto state_error;
  }
  state_k_do:
  m.type = DO_KEYWORD_TOKEN;
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
   case 'u':
	   goto state_k_double;
   default:
	   t = transitionTable(c);
	   if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
		   goto state_accept_name;
	   goto state_error;
  }
 state_k_double:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_double[++stringIndex]);
  if (stringIndex == doubleLen)
	m.type = DOUBLE_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
	 goto state_accept_name;
  goto state_error; 
 state_k_default:  
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_default[++stringIndex]);
  if(stringIndex == defaultLen)
	  m.type = DEFAULT_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
	  goto state_accept_name;
  goto state_error;
 state_k_e:
 m.type = NAME_TOKEN;
 clear(stack);
 push(stack, STATE_ACCEPT_NAME);
 stringBuffer[stringIndex++] = c;
 nextChar(inFD, &c);
 switch(c){
	 case 'l':
		 goto state_k_else;
         case 'n':
		 goto state_k_enum;
	 default:
		 t = transitionTable(c);
		 if ((ALPHA_BIT | DECIMAL_BIT) & t)
			 goto state_accept_name;
 		goto state_error;
 }
 state_k_else:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_else[++stringIndex]);
  if (stringIndex == elseLen)
          m.type = ELSE_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
          goto state_accept_name;
  goto state_error;

 state_k_enum:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_enum[++stringIndex]);
  if (stringIndex == enumLen)
	  m.type = ENUM_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
	  goto state_accept_name;
  goto state_error;
 state_k_f:
  m.type = NAME_TOKEN;
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
    case 'o':
	    goto state_k_for;
    case 'l':
	    goto state_k_float;
    default:
	    t = transitionTable(c);
	    if ((ALPHA_BIT | DECIMAL_BIT) & t)
		    goto state_accept_name;
	    goto state_error;
  }
 state_k_for:
  do{
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex] = c;
  nextChar(inFD, &c);
  }while(c == k_for[++stringIndex]);
  if (stringIndex = forLen)
	  m.type = FOR_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
	  goto state_accept_name;
  goto state_error;
 state_k_float:
  do{
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex] = c;
  nextChar(inFD, &c);
  }while(c == k_float[++stringIndex]);
  if (stringIndex = floatLen)
          m.type = FLOAT_KEYWORD_TOKEN;
  t = transitionTable(c);
  if((ALPHA_BIT | DECIMAL_BIT) & t)
          goto state_accept_name;
  goto state_error;
 state_k_i:
  m.type = NAME_TOKEN;
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
   case 'f':
	   goto state_k_if;
   case 'n':
	   goto state_k_int;
   default:
	   t = transitionTable(c);
	   if ((ALPHA_BIT | DECIMAL_BIT) & t)
		   goto state_accept_name;
	   goto state_error;
  }
 state_k_if:
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  m.type = IF_KEYWORD_TOKEN;
  nextChar(inFD, &c);
  t = transitionTable(c);
  if ((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
  goto state_error;
  
  state_k_int:
  do{
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex] = c;
  nextChar(inFD, &c);
  }while(c == k_int[++stringIndex]);
  if (stringIndex == intLen)
	m.type = INT_KEYWORD_TOKEN;
  t = transitionTable(c);
  if ((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
  goto state_error;
 state_k_long:
 do{
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex] = c;
  nextChar(inFD, &c);
 }while(c == k_long[++stringIndex]);
  if (stringIndex == longLen)
	m.type = LONG_KEYWORD_TOKEN;
  t = transitionTable(c);
  if ((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
  goto state_error;
 
  state_k_re:
  m.type = NAME_TOKEN;
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_register[++stringIndex] && (stringIndex < 2));
  switch(c){
   case 'g': 
   	goto state_k_register;
   case 't':
        goto state_k_return;
   default:
        t = transitionTable(c);
	if ((ALPHA_BIT | DECIMAL_BIT) & t)
	  goto state_accept_name;
	goto state_error;
  }

  state_k_register:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_register[++stringIndex]);
   if (stringIndex == registerLen)
	m.type = REGISTER_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
   goto state_error;

  state_k_return:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_return[++stringIndex]);
   if (stringIndex == returnLen)
        m.type = RETURN_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
        goto state_accept_name;
   goto state_error;
   
   state_k_s:
   m.type = NAME_TOKEN;
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex++] = c;
   nextChar(inFD, &c);
   switch(c){
     case 'i':
	     goto state_k_sizeof;
     case 't':
	     goto state_k_st;
     case 'w':
	     goto state_k_switch;
     default:
	     t = transitionTable(c);
	     if ((ALPHA_BIT | DECIMAL_BIT) & t)
		     goto state_accept_name;
	     goto state_error;
   }
  state_k_sizeof:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_sizeof[++stringIndex]);
   if( stringIndex == sizeofLen )
	m.type = SIZEOF_KEYWORD_TOKEN;
   t = transitionTable(c);
   if((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
   goto state_error;

  state_k_switch:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_switch[++stringIndex]);
   if ( stringIndex == switchLen )
	m.type = SWITCH_KEYWORD_TOKEN;
   t = transitionTable(c);
   if((ALPHA_BIT | DECIMAL_BIT) & t)
	goto state_accept_name;
   goto state_error;
   state_k_st:
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    stringBuffer[stringIndex++] = c;
    nextChar(inFD, &c);
    switch(c){
    case 'a':
	    goto state_k_static;
    case 'r':
            goto state_k_struct;
    default:
	    t = transitionTable(c);
	    if ((ALPHA_BIT | DECIMAL_BIT) & t)
		    goto state_accept_name;
	    goto state_error;
    }
  state_k_static:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_static[++stringIndex]);
   if ( stringIndex == staticLen )
        m.type = STATIC_KEYWORD_TOKEN;
   t = transitionTable(c);
   if((ALPHA_BIT | DECIMAL_BIT) & t)
        goto state_accept_name;
   goto state_error;
  state_k_struct:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_struct[++stringIndex]);
   if ( stringIndex == structLen )
        m.type = STRUCT_KEYWORD_TOKEN;
   t = transitionTable(c);
   if((ALPHA_BIT | DECIMAL_BIT) & t)
        goto state_accept_name;
   goto state_error;
  state_k_goto:
  m.type = GOTO_KEYWORD_TOKEN;
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
  }while(c == k_goto[++stringIndex]);
   if(c == gotoLen)
	   m.type = GOTO_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
	   goto state_accept_name;
   goto state_error;
  state_k_u:
  m.type =NAME_TOKEN;
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
    case'n':
       goto state_k_un;
    default:
       t = transitionTable(c);
       if ((ALPHA_BIT | DECIMAL_BIT) & t)
	       goto state_accept_name;
       goto state_error;
  }
  state_k_un:
  clear(stack);
  push(stack, STATE_ACCEPT_NAME);
  stringBuffer[stringIndex++] = c;
  nextChar(inFD, &c);
  switch(c){
     case 'i':
	     goto state_k_union;
     case 's':
	     goto state_k_unsigned;
     default:
	     t = transitionTable(c);
	     if ((ALPHA_BIT | DECIMAL_BIT) & t)
		     goto state_accept_name;
	     goto state_error;
  }
  state_k_union:
  do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
   }while(c == k_union[++stringIndex]);
   if (stringIndex == unionLen)
	   m.type = UNION_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
	   goto state_accept_name;
   goto state_error;

  state_k_unsigned:
   do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
   }while(c == k_unsigned[++stringIndex]);
   if (stringIndex == unsignedLen)
           m.type = UNSIGNED_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
           goto state_accept_name;
   goto state_error;
  state_k_void:
   do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
   }while(c == k_void[++stringIndex]);
   if (stringIndex == voidLen)
           m.type = VOID_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
           goto state_accept_name;
   goto state_error;
  state_k_while:
   do{
   clear(stack);
   push(stack, STATE_ACCEPT_NAME);
   stringBuffer[stringIndex] = c;
   nextChar(inFD, &c);
   }while(c == k_while[++stringIndex]);
   if (stringIndex == whileLen)
           m.type = WHILE_KEYWORD_TOKEN;
   t = transitionTable(c);
   if ((ALPHA_BIT | DECIMAL_BIT) & t)
           goto state_accept_name;
   goto state_error;

  state_one_zero:
    nextChar(inFD, &c);
    clear(stack);
    push(stack, STATE_ONE_ZERO);
    m.type = INT_TOKEN;
    t = transitionTable(c);
    assert(t != TRANSITION_ERROR);
    switch(c){
	case '0':
		goto state_leading_zeros;
	case 'b':
	case 'B':
		goto state_init_binary;
	case 'x':
	case 'X':
		goto state_init_hex;
	case '.':
		goto state_init_dec_float;
	default:
	        if (OCTAL_BIT & t)
			goto state_accept_octal;
		if (DECIMAL_BIT & t)
			goto state_accept_decimal;
		goto state_error;
	
    }

  state_leading_zeros:
    nextChar(inFD, &c);
    clear(stack);
    push(stack, STATE_LEADING_ZEROS);
    t = transitionTable(c);
    m.type = INT_TOKEN;
    assert(t != TRANSITION_ERROR);
    switch(c){
	case '0':
		goto state_leading_zeros;
	case '.':
		goto state_init_dec_float;
	default:
		if (OCTAL_BIT &  t)
			goto state_accept_octal;
		if (DECIMAL_BIT & t)
			goto state_accept_decimal;
		goto state_error;
    }

  state_init_binary:
    nextChar(inFD, &c);
    push(stack, STATE_INIT_BINARY);
    t = transitionTable(c);
    if (BINARY_BIT | t){
	goto state_accept_binary;
    }
    goto state_error;
  state_init_hex:
    nextChar(inFD, &c);
    push(stack, STATE_INIT_HEX);
    t = transitionTable(c);
    if (c == '.')
	    goto state_init_hex_float;
    if (HEX_CHAR | t)
    	goto state_accept_hex;
    goto state_error;
  state_accept_hex:
    clear(stack);
    push(stack, STATE_ACCEPT_HEX);
    intVal = intVal << 4;
    intVal+= matchHexChar(c);
    nextChar(inFD, &c);
    t = transitionTable(c);
    m.type = INT_TOKEN;
    if(t & HEX_BIT)
	goto state_accept_hex;
    if (c == '.')
	    goto state_init_hex_float;
    goto state_error;
  state_accept_octal:
    clear(stack);
    push(stack, STATE_ACCEPT_OCTAL);
    intVal = intVal << 3;
    intVal += (c - '0');
    nextChar(inFD, &c);
    t = transitionTable(c);
    m.type = INT_TOKEN;
    if (t & OCTAL_BIT)
	    goto state_accept_octal;
    goto state_error;
  state_accept_decimal:
    clear(stack);
    push(stack, STATE_ACCEPT_DECIMAL);
    intVal = intVal * 10;
    intVal += (c - '0');
    nextChar(inFD, &c);
    t = transitionTable(c);
    m.type = INT_TOKEN;
    if (DECIMAL_BIT & t)
	    goto state_accept_decimal;
    if (c == '.') 
	    goto state_init_dec_float;
    goto state_error;
  state_init_dec_float:
    push(stack, STATE_INIT_DEC_FLOAT);
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (DECIMAL_BIT & t)
	    goto state_accept_dec_float;
    goto state_error;
  state_init_hex_float:
    push(stack, STATE_INIT_HEX_FLOAT);
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (HEX_BIT & t)
	    goto state_accept_hex_float;
  state_accept_dec_float:
    clear(stack);
    push(stack, STATE_ACCEPT_DEC_FLOAT);
    floatPlace /= 10;
    floatVal+=(floatPlace * (c - '0'));
    m.type = FLOAT_TOKEN;
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (DECIMAL_BIT & t)
	    goto state_accept_dec_float;
    goto state_error;
  state_accept_hex_float:
    clear(stack);
    push(stack, STATE_ACCEPT_HEX_FLOAT);
    floatPlace /= 0x10;
    floatVal+=(floatPlace * matchHexChar(c));
    nextChar(inFD, &c);
    t = transitionTable(c);
    m.type = FLOAT_TOKEN;
    if (HEX_BIT & t)
	    goto state_accept_hex_float;
    nextChar(inFD, &c);
  state_init_string:
    push(stack, STATE_INIT_STRING); 
    if (stringIndex>= STRING_BUFFER_LENGTH){
      LOG("STRING  LITERAL IS TOO LONG...\n");
      stringIndex = 1;
    }
    stringBuffer[stringIndex++] = c;
    nextChar(inFD, &c);
    t = transitionTable(c);
    switch(c){
      case '"':
	      goto state_accept_string;
      case '\\':
	      goto state_escape_string;
      default:
	      if (REG_BIT & t)
		      goto state_init_string;
             goto state_error;	      
    }
   state_accept_string:    
    clear(stack);
    push(stack, STATE_ACCEPT_STRING);
    m.type = STRING_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
  state_escape_string:
    push(stack, STATE_ESCAPE_STRING);
    nextChar(inFD, &c);
    switch(c){
     case 'a':
	     stringBuffer[stringIndex++] = 0x07;
	     break;
     case 'b':
	     stringBuffer[stringIndex++] = 0x08;
	     break;
     case 'e':
	     stringBuffer[stringIndex++] = 0x1b;
	     break;
     case 'f':
	     stringBuffer[stringIndex++] = 0x0c;
	     break;
     case 'n':
	     stringBuffer[stringIndex++] = 0x0a;
	     break;
     case 't':
	     stringBuffer[stringIndex++] = 0x09;
	     break;
     case 'v':
	     stringBuffer[stringIndex++] = 0x0b;
	     break;
     case '\\':
	     stringBuffer[stringIndex++] = 0x5c;
	     break;
     case '\'':
	     stringBuffer[stringIndex++] = 0x27;
	     break;
     case '?':
	     stringBuffer[stringIndex++] = 0x3f;
	     break;
     case 'x':
	   //TODO: add logic for reading hec x numbersi;
	   goto state_init_hex_escape;
     default:
	     t = transitionTable(c);
	     //TODO add logic for reading octal numbers;
	     if(OCTAL_BIT & t)
		     goto state_first_octal_escape_dig;
	     goto state_error;

    }
   nextChar(inFD, &c);
   switch(c){
    case '\\': 
	    goto state_escape_string;
    case '"':
	    goto state_accept_string;
    default:
	    t = transitionTable(c);
	    if (REG_BIT & c)
		    goto state_init_string;
	    goto state_error;

   }
   goto state_init_string;
  state_first_octal_escape_dig:
    push(stack, STATE_FIRST_OCTAL_ESCAPE_DIG);
    charVal = (c - '0');
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (!(OCTAL_BIT & t))
	    goto state_error;
  state_second_octal_escape_dig:
    push(stack, STATE_SECOND_OCTAL_ESCAPE_DIG);
    charVal = charVal << 3;
    charVal = charVal | (c - '0');
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (!(OCTAL_BIT & t))
	    goto state_error;

  state_third_octal_escape_dig:  
    push(stack, STATE_THIRD_OCTAL_ESCAPE_DIG);
    charVal = charVal << 3;
    charVal = charVal | (c - '0');
    stringBuffer[stringIndex++] = charVal;
    charVal = 0;
    nextChar(inFD, &c);
    if (c == '"')
	    goto state_accept_string;
    t = transitionTable(c);
    if (REG_BIT & t)
	    goto state_init_string;
    goto state_error;
  state_init_hex_escape:
    push(stack, STATE_INIT_HEX_ESCAPE);
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (!(HEX_BIT & t))
	    goto state_error;
  state_first_hex_escape_dig:
    push(stack, STATE_FIRST_HEX_ESCAPE_DIG);
    charVal = (charVal << 4) | (char) matchHexChar(c);
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (!(HEX_BIT & t))
	    goto state_error;

  state_second_hex_escape_dig:
    push(stack, STATE_SECOND_HEX_ESCAPE_DIG);
    charVal = (charVal << 4) | (char) matchHexChar(c);
    stringBuffer[stringIndex++] = charVal;
    charVal = 0;
    nextChar(inFD, &c);
    switch(c){
	case '"':
	  goto state_accept_string;
	default:
	  if (REG_BIT & t)
		  goto state_init_string;
	  goto state_error;
    }

  state_accept_name:	
    clear(stack);
    push(stack, STATE_ACCEPT_NAME);
    m.type = NAME_TOKEN;
    if (stringIndex >= STRING_BUFFER_LENGTH){
	    LOG("name is too long...\n");
	    stringIndex = 0;
    }
    stringBuffer[stringIndex++] = c;
    nextChar(inFD, &c);
    t = transitionTable(c);
    if ((ALPHA_BIT & t) || (DECIMAL_BIT & t))
	    goto state_accept_name;
    goto state_error;

   state_accept_binary:
    clear(stack);
    push(stack, STATE_ACCEPT_BINARY);
    m.type = INT_TOKEN;
    intVal = (intVal << 1) + (c - '0');
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (BINARY_BIT & t)
	    goto state_accept_binary;
    goto state_error;

   state_accept_fullstop:
    clear(stack);
    push(stack, STATE_ACCEPT_FULLSTOP);
    m.type = FULLSTOP_TOKEN;
    nextChar(inFD, &c);
    t = transitionTable(c);
    if (DECIMAL_BIT & t){
	goto state_accept_dec_float;
    }
    goto state_error;

   state_accept_semicolon:
   clear(stack);
   push(stack, STATE_ACCEPT_SEMICOLON);
   m.type = SEMICOLON_TOKEN;
   nextChar(inFD, &c);
   goto state_error;
   
   state_accept_plus:
   clear(stack);
   push(stack, STATE_ACCEPT_PLUS);
   m.type = PLUS_TOKEN;
   nextChar(inFD, &c);
   switch(c){
	   case '=':
		   goto state_accept_plusequals;
           case '+':
		   goto state_accept_plusplus;
   	   default:
   		   goto state_error;
   }

   state_accept_plusplus:
     clear(stack);
     push(stack, STATE_ACCEPT_PLUSPLUS);
     m.type = PLUSPLUS_TOKEN;
     nextChar(inFD, &c);
     goto state_error;

   state_accept_plusequals:
     clear(stack);
     push(stack, STATE_ACCEPT_PLUSEQUALS);
     m.type = PLUSEQUALS_TOKEN;
     nextChar(inFD, &c);
     goto state_error;

  state_accept_minus:
    clear(stack);
    push(stack, STATE_ACCEPT_MINUS);
    m.type = MINUS_TOKEN;
    nextChar(inFD, &c);
    switch(c){
	case '=':
		goto state_accept_minusequals;
	case '-':
		goto state_accept_minusminus;
	case '>':
		goto state_accept_arrow;
	default: 
		goto state_error;
    }
   state_accept_arrow:
    clear(stack);
    push(stack, STATE_ACCEPT_ARROW);
    m.type = ARROW_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_minusminus:
    clear(stack);
    push(stack, STATE_ACCEPT_MINUSMINUS);
    m.type = MINUSMINUS_TOKEN;
    nextChar(inFD, &c);
    goto state_error; 
   state_accept_minusequals:
    clear(stack);
    push(stack, STATE_ACCEPT_MINUSEQUALS);
    m.type = MINUSEQUALS_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   
   state_accept_colon:
    clear(stack);
    push(stack, STATE_ACCEPT_COLON);
    m.type = COLON_TOKEN;
    nextChar(inFD, &c);
    goto state_error;   
   
   state_accept_assign:
    clear(stack);
    push(stack, STATE_ACCEPT_ASSIGN);
    m.type = ASSIGN_TOKEN;
    nextChar(inFD, &c);
    if (c == '=')
	    goto state_accept_equals;
    goto state_error;

   state_accept_equals:
    clear(stack);
    push(stack, STATE_ACCEPT_EQUALS);
    m.type = EQUALS_TOKEN;
    nextChar(inFD, &c);
    goto state_error;

   state_accept_nequals:
    clear(stack);
    push(stack, STATE_ACCEPT_EQUALS);
    m.type = NEQUALS_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_not:
    clear(stack);
    push(stack, STATE_ACCEPT_NOT);
    m.type = NOT_TOKEN;
    nextChar(inFD, &c);
    if (c == '=')
	    goto state_accept_nequals;
    goto state_error;
   state_accept_greaterthan:
    clear(stack);
    push(stack, STATE_ACCEPT_GREATERTHAN);
    m.type = GREATERTHAN_TOKEN;
    nextChar(inFD, &c);
    switch(c){
      case '=':
	      goto state_accept_geq;
      case '>':
	      goto state_accept_rightshift;
      default:
	      goto state_error;

    }
   state_accept_lessthan:
    clear(stack);
    push(stack, STATE_ACCEPT_LESSTHAN);
    m.type = LESSTHAN_TOKEN;
    nextChar(inFD, &c);
    switch(c){
      case '=':
	      goto state_accept_leq;
      case '<':
	      goto state_accept_leftshift;
      default:
	      goto state_error;

    }
   state_accept_leq:
    clear(stack);
    push(stack, STATE_ACCEPT_LEQ);
    m.type = LEQ_TOKEN;
    nextChar(inFD, &c);
    goto state_error; 
   state_accept_geq:
    clear(stack);
    push(stack, STATE_ACCEPT_GEQ);
    m.type = GEQ_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_bitor:
    clear(stack);
    push(stack, STATE_ACCEPT_BITOR);
    m.type = BITOR_TOKEN;
    nextChar(inFD, &c);
    if (c == '|')
	goto state_accept_logicalor;    
    goto state_error;
   state_accept_bitand:
    clear(stack);
    push(stack, STATE_ACCEPT_BITAND);
    m.type = BITAND_TOKEN;
    nextChar(inFD, &c);
    if (c == '&')
	    goto state_accept_logicaland;
    goto state_error;
   state_accept_logicalor:
    clear(stack);
    push(stack, STATE_ACCEPT_LOGICALOR);
    m.type = LOGICALOR_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_logicaland:
    clear(stack);
    push(stack, STATE_ACCEPT_LOGICALAND);
    m.type = LOGICALAND_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_lparen:
    clear(stack);
    push(stack, STATE_ACCEPT_LPAREN);
    m.type = LPAREN_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_rparen:
    clear(stack);
    push(stack, STATE_ACCEPT_RPAREN);
    m.type = RPAREN_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_lcurly:
    clear(stack);
    push(stack, STATE_ACCEPT_LCURLY);
    m.type = LCURLY_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_rcurly:
    clear(stack);
    push(stack, STATE_ACCEPT_RCURLY);
    m.type = RCURLY_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_lsquare:
    clear(stack);
    push(stack, STATE_ACCEPT_LSQUARE);
    m.type = LSQUARE_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
   state_accept_rsquare:
    clear(stack);
    push(stack, STATE_ACCEPT_RSQUARE);
    m.type = RSQUARE_TOKEN;
    nextChar(inFD, &c);
    goto state_error;
  state_accept_comma:
     clear(stack);
     push(stack, STATE_ACCEPT_COMMA);
     m.type = COMMA_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
  state_accept_complement:
     clear(stack);
     push(stack, STATE_ACCEPT_COMPLEMENT);
     m.type = COMPLEMENT_TOKEN;
     nextChar(inFD, &c);	
     goto state_error;
   state_accept_xor:
     clear(stack);
     push(stack, STATE_ACCEPT_XOR);
     m.type = XOR_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
   state_accept_mod:
     clear(stack);
     push(stack, STATE_ACCEPT_MOD);
     m.type = MOD_TOKEN;
     nextChar(inFD, &c);
     if (c == '=')
       goto state_accept_modequals;
     goto state_error;
    state_accept_modequals:
     clear(stack);
     push(stack, STATE_ACCEPT_MODEQUALS);
     m.type = MODEQUALS_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_accept_fslash:
     clear(stack);
     push(stack, STATE_ACCEPT_FSLASH);
     m.type = FSLASH_TOKEN;
     nextChar(inFD, &c);
     switch(c){
	case '/':
		goto state_linecomment;
	case '=':
		goto state_accept_fslashequals;
	case '*':
		goto state_multilinecomment;
	default:
		goto state_error;
    } 
    state_accept_fslashequals:
     clear(stack);
     push(stack, STATE_ACCEPT_FSLASHEQUALS);
     m.type = FSLASHEQUALS_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_linecomment:
     nextChar(inFD, &c);
     if (c == '\n')
	   goto state_initial;
     goto state_linecomment;
    
    state_multilinecomment:
     nextChar(inFD, &c);
     if (c == '*')
	     goto state_exit_multilinecomment;
     goto state_multilinecomment;

     state_exit_multilinecomment:
      nextChar(inFD, &c);
      switch(c){
	case '*':
		goto state_exit_multilinecomment;
	case '/':
		goto state_initial;
	default:
		goto state_exit_multilinecomment;
      }
    state_accept_star:
     clear(stack);
     push(stack, STATE_ACCEPT_STAR);
     m.type = STAR_TOKEN;
     nextChar(inFD, &c);
     if(c == '=')
	     goto state_accept_timesequals;
     goto state_error;
    state_accept_timesequals:
     clear(stack);
     push(stack, STATE_ACCEPT_TIMESEQUALS);
     m.type = TIMESEQUALS_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_accept_ampersand:
     clear(stack);
     push(stack, STATE_ACCEPT_AMPERSAND);
     m.type = AMPERSAND_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_accept_leftshift:
     clear(stack);
     push(stack, STATE_ACCEPT_LEFTSHIFT);
     m.type = LEFTSHIFT_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_accept_rightshift:
     clear(stack);
     push(stack, STATE_ACCEPT_RIGHTSHIFT);
     m.type = RIGHTSHIFT_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_accept_question:
     clear(stack);
     push(stack, STATE_ACCEPT_QUESTION);
     m.type = QUESTION_TOKEN;
     nextChar(inFD, &c);
     goto state_error;
    state_init_char:
     push(stack, STATE_INIT_CHAR);
     nextChar(inFD, &c);
     switch(c){
	case '\\':
		goto state_escape_char;
	case '\'':
		goto state_error;
	default:
		t = transitionTable(c);
		if (REG_BIT & c)
			goto state_regchar;
		goto state_error;

     }     
     state_regchar:
      push(stack, STATE_REGCHAR);
      charVal = c;
      nextChar(inFD, &c);
      if (c != '\'')
	goto state_error;
      goto state_accept_char;
     state_accept_char:
      clear(stack);
      push(stack, STATE_ACCEPT_CHAR);
      m.type = CHAR_TOKEN;
      m.value.intVal = charVal;
      charVal = 0;
      nextChar(inFD, &c);
      goto state_error;
     state_escape_char:
      push(stack, STATE_ESCAPE_CHAR);
      nextChar(inFD, &c);
      switch(c){
       case 'a':
	       charVal = 0x07;
	       break;
       case 'b':
	       charVal = 0x08;
	       break;
       case 'e':
	       charVal = 0x1b;
	       break;
       case 'f':
	       charVal = 0x0c;
	       break;
       case 'n':
	       charVal = 0x0a;
	       break;
       case 'r':
	       charVal = 0x0d;
	       break;
       case 't':
	       charVal = 0x09;
	       break;
       case 'v':
	       charVal = 0x0b;
	       break;
       case '\\':
	       charVal = 0x5c;
	       break;
       case '\'':
	       charVal = 0x22;
	       break;
       case '\"':
	       charVal = 0x22;
	       break;
       case 'x':
	       goto state_init_hex_char_escape;
       case '?':
	       charVal = 0x3f;
	       break;
       default:
	       t = transitionTable(c);
	       if ( OCTAL_BIT & t )
		       goto state_first_octal_char_escape;
      }
      nextChar(inFD, &c);
      if (c == '\'')
	      goto state_accept_char;
      goto state_error;
     state_first_octal_char_escape:
      push(stack, STATE_FIRST_OCTAL_CHAR_ESCAPE);
      charVal = (charVal << 3) + c - '0';
      nextChar(inFD, &c);
      t = transitionTable(c);
      if (!(OCTAL_BIT & t))
	      goto state_error;
     state_second_octal_char_escape:
      push(stack, STATE_SECOND_OCTAL_CHAR_ESCAPE);
      charVal = (charVal << 3) + c - '0';
      nextChar(inFD, &c);
      t = transitionTable(c);
      if (!(OCTAL_BIT & t))
	      goto state_error;
     state_third_octal_char_escape:
      push(stack, STATE_THIRD_OCTAL_CHAR_ESCAPE);
      charVal = (charVal << 3) + c - '0';
      nextChar(inFD, &c);
      if (c == '\'')
	      goto state_accept_char;
      goto state_error;
     state_init_hex_char_escape:
      push(stack, STATE_INIT_HEX_CHAR_ESCAPE);
      nextChar(inFD, &c);
      t = transitionTable(c);
      if (!(HEX_BIT & t))
	      goto state_error;
     state_first_hex_char_escape:
      push(stack, STATE_FIRST_HEX_CHAR_ESCAPE);
      charVal = (charVal << 4) + c;
      nextChar(inFD, &c);
      t = transitionTable(c);
      if (!(HEX_BIT & t))
	      goto state_error;
     state_second_hex_char_escape:
      push(stack, STATE_SECOND_HEX_CHAR_ESCAPE);
      charVal = (charVal << 4) + c;
      nextChar(inFD, &c);
      if (c == '\'')
	      goto state_accept_char;
      goto state_error;
}

