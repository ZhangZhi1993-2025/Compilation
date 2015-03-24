#ifndef _LEXICALTYPE_H
#define _LEXICALTYPE_H

/* main function */
#define MAIN 1

/* key words */
#define IF 2
#define ELSE 3
#define WHILE 4
#define BREAK 10
#define CONTINUE 11
#define SWITCH 29
#define CASE 30
#define DEFAULT 31
#define RETURN 9

/* value type */
#define VOID 5
#define INT 6
#define DOUBLE 7
#define CHAR 8

/* operator */
#define ADD 12
#define SUB 13
#define MUL 14
#define DIV 15
#define AND 16
#define OR 17
#define NOT 32
#define EQUAL 18
#define LARGER 19
#define SMALLER 20
#define EQUAL_LARGER 21		//	'>='
#define EQUAL_SMALLER 22	//	'<='

/* bound symbol */
#define LBRACE 23			//	'{'
#define RBRACE 24			//	'}'
#define LINDEX 33			//	'['
#define RINDEX 34			//	']'
#define LBRACKET 25			//	'('
#define RBRACKET 26			//	')'
#define SEMICOLON 27		//	';'
#define COMMA 28			//	','

/* identity */
#define IDENT 100

#endif	/* _LEXICALTYPE_H */
