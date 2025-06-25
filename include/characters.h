/*
 *
 * Character classes:    whitespace  illegal  alphanumeric  semicolon  quotation single quote  backtick  backslash  period
 * 						   |
 * 					      -----------------
 * 					      |		      |
 * 					      alphabetical    digits	   
 *
 * */

/*if enums are basically 32 bit integers, it makes sense to define tags
 *literal + 3 tiers of hierarchy.
 *
 * 	[literal] [tier 3] [tier 2] [ tier 1 ]
 * 	most generic information should be used first
 *number structure:
 * [  ][  ][][ char literal ]
 *
 *
*/



enum e_characterClasses {
	PUNCTUATION,
	WHITESPACE,
	ALPHANUMERIC,
	ILLEGAL
}
enum e_alphanumericSubclasses {
	ALPHABETICAL,
	NUMERICAL
}
enum e_bracesSubclasses {
	LEFT,
	RIGHT
}
