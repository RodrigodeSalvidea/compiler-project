#ifndef TRANSITION_DEFINITIONS
#define TRANSITION_DEFINITIONS
typedef unsigned int transition;
/*convention: */
#define TRANSITION_ERROR 0x0000
#define REG_BIT          0x8000
#define WHITESPACE_BIT   0x4000      //(reg | whitespace)
#define OCTAL_BIT        0x2000      //(reg | hex | decimal | octal)
#define DECIMAL_BIT      0x1000      //(reg | hex | decimal)
#define HEX_BIT		 0x0800
#define BINARY_BIT	 0x0400
#define ALPHA_BIT	 0x0200


#define OCTAL_CHAR (REG_BIT | DECIMAL_BIT | HEX_BIT | OCTAL_BIT)
#define DECIMAL_CHAR (REG_BIT | DECIMAL_BIT | HEX_BIT)
#define HEX_CHAR    (REG_BIT | HEX_BIT)
#define BINARY_CHAR (REG_BIT | HEX_BIT | DECIMAL_BIT | OCTAL_BIT | BINARY_BIT) 
#define ALPHA_CHAR  (REG_BIT | ALPHA_BIT)





transition transitionTable(char c);
#endif
