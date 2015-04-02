#ifndef _RESOURCE_H
#define _RESOURCE_H

using namespace std;

union varType {
	char ch;
	short sint;
	int i;
	unsigned int ui;
	unsigned char uc;
	unsigned short us;
	long l;
	float f;
	double d;
	int strIndex[2];
};

static string strPool = "";		//a constant pool for character pool

static string keyWords[19] = {
	"main", "if", "else", "while", "break", "continue", "switch", "case", "default", "return",
	"goto", "void", "int", "float", "double", "char", "unsigned", "long", "short"
};

/* end of file */
#define ENDOFFILE 0

/* key words */
#define MAIN 1
#define IF 2
#define ELSE 3
#define WHILE 4
#define BREAK 5
#define CONTINUE 6
#define SWITCH 7
#define CASE 8
#define DEFAULT 9
#define RETURN 10
#define GOTO 11

/* value type */
#define VOID 12
#define INT 13
#define FLOAT 14
#define DOUBLE 15
#define CHAR 16
#define UNSIGNED 17
#define LONG 18
#define STRING 19
#define SHORT 20

/* operator */
#define ADD 100
#define SUB 101
#define MUL 102
#define DIV 103
#define AND 104
#define OR 105
#define NOT 106
#define EQUAL 107
#define LARGER 108
#define SMALLER 109
#define EQUAL_LARGER 110	//	'>='
#define EQUAL_SMALLER 111	//	'<='
#define BITOR 120
#define BITAND 121

/* bounds symbol */
#define LBRACE 112			//	'{'
#define RBRACE 113			//	'}'
#define LINDEX 114			//	'['
#define RINDEX 115			//	']'
#define LBRACKET 116		//	'('
#define RBRACKET 117		//	')'
#define SEMICOLON 118		//	';'
#define COMMA 119			//	','

/* identity symbol */
#define VAR 200

static string error[3] = {
	"the source code has illegal variables", "is an unrecognized identity",
	"the string does not end correctly"
};

#endif	/* _RESOURCE_H */
