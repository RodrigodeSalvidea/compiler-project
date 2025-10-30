#include "transitions.h"
/*
 *		character classes
 *		error transition:
 *			- exclusixely exists for non-text ascii chars
 *
 *		regular chars: every character that could appear in a string (not double quotes, backslash or single quotes.
 *		
 *		decimal digits, octal digits and binary digits, hexadecimal digits;
 *
 *		
 *
 *
 *
 *
 *
 * */

transition transitionTable(char c){
	switch(c){
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		// invalid chars
		return TRANSITION_ERROR;
	case 9:
		return c | WHITESPACE_BIT | REG_BIT;
	case 10:
	case 11:
	case 12:
	case 13:
		//whitespace region
		return 	WHITESPACE_BIT  | c;
	case 14:
	case 15:
	case 16:
	case 17:	
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
		return TRANSITION_ERROR;
	case 32:
		return WHITESPACE_BIT | REG_BIT | c;
	case 33:
		return REG_BIT | c;
	case 34:
		return '\"';
	case 35:
	case 36:
		return REG_BIT | c;
	case 37:
		return '%';
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
		return REG_BIT | c;
		//decimal digits:
	case 48:
	case 49:
		return BINARY_CHAR | c;
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
		return OCTAL_CHAR | c;
	case 56:
	case 57:
		return DECIMAL_CHAR | c;
		//colon:
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
		return REG_BIT | c;
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
	case 70:
		return HEX_CHAR | ALPHA_CHAR | c;
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 82:
	case 83:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
		return ALPHA_CHAR | c;
	case 91:
		return REG_BIT | c;
	case 92:
		return c;
	case 93:
	case 94:
		return REG_BIT | c;
	case 95:
		return ALPHA_CHAR | c;
	case 96:
		return REG_BIT | c;
	case 97:
	case 98:
	case 99:
	case 100:
	case 101:
	case 102:
		return ALPHA_CHAR | c;
	case 103:
	case 104:
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
	case 110:
	case 111:
	case 112:
	case 113:
	case 114:
	case 115:
	case 116:
	case 117:
	case 118:
	case 119:
	case 120:
	case 121:
	case 122:
		return ALPHA_CHAR | c;
	case 123:
	case 124:
	case 125:
	case 126:
		return REG_BIT | c;
	case 127:
		return TRANSITION_ERROR;
	default:
	       	return TRANSITION_ERROR;
	}

}

