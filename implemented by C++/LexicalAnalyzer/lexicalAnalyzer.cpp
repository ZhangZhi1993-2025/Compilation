#include <iostream>
#include <resource.h>
#include <tuple>
using namespace std;

class LexicalAnalyzer {
public:
	LexicalAnalyzer() {}

	LexicalAnalyzer ( string sourceCode ) {
		this->sourceCode = sourceCode;
		currentIndex = 0;
		row = col = 0;
	}

	LexicalAnalyzer ( FILE *fp ) {
		currentIndex = 0;
		row = col = 0;
	}

	pair<int, varType> Next() {
		pair<int, varType> p;
		varType var;
		unsigned int startIndex = 0;
		char ch = '\0';
		short sint = 0;
		int i = 0;
		float f = 0.0f;
		double d = 0.0;
		while ( currentIndex < sourceCode.length() ) {

			/* skip the space,tab and enter symbols */
			while ( sourceCode[currentIndex] == ' ' ) {
				currentIndex++;
				col++;
			}
			while ( sourceCode[currentIndex] == '\t' ) {
				currentIndex++;
				col += 4;
			}
			while ( sourceCode[currentIndex] == '\n' ) {
				currentIndex++;
				row++;
				col = 0;
			}

			/* pattern recognition */

			startIndex = currentIndex;

			//variable or key words
			if ( isLetter ( sourceCode[currentIndex] ) || sourceCode[currentIndex] == '_' ) {
				currentIndex++;
				col++;
				while ( isLetter ( sourceCode[currentIndex] ) || isDigit ( sourceCode[currentIndex] ) ||
				        sourceCode[currentIndex] == '_' ) {
					currentIndex++;
					col++;
				}
				//judge if the word is a key word
				unsigned int num = isKeyWords ( sourceCode.substr ( startIndex, currentIndex - startIndex ) );
				if ( num == 0 ) {	//variable
					unsigned int start = strPool.length();
					strPool += sourceCode.substr ( startIndex, currentIndex - startIndex );
					unsigned int end = start + currentIndex - startIndex;
					var.strIndex[0] = start;
					var.strIndex[1] = end;
					p = make_pair ( VAR, var );
					return p;
				} else {	//key words
					var.ch = ch;
					p = make_pair ( num, var );
					return p;
				}
			}

			//constants
			if ( isDigit ( sourceCode[currentIndex] ) ) {
				currentIndex++;
				col++;
				while ( isDigit ( sourceCode[currentIndex] ) ) {
					currentIndex++;
					col++;
				}
				if ( sourceCode[currentIndex] == '.' ) {
					currentIndex++;
					col++;
					bool flag = false;
					while ( isDigit ( sourceCode[currentIndex] ) ) {
						flag = true;
						currentIndex++;
						col++;
					}
					if ( flag ) {
						//double constant
						d = strToDouble ( sourceCode.substr ( startIndex, currentIndex - startIndex ) );
						var.d = d;
						p = make_pair ( DOUBLE, var );
						return p;
					} else
						//throw an exception where the source code has illegal identities
						throw tuple<int, int, int, string> ( row, col, 0, sourceCode.substr
						                                     ( startIndex, currentIndex - startIndex ) );
				} else {
					//int constant
					i = strToInt ( sourceCode.substr ( startIndex, currentIndex - startIndex ) );
					var.i = i;
					p = make_pair ( INT, var );
					return p;
				}
			}

			//other symbols
			switch ( sourceCode[currentIndex] ) {
				case '"':

				case '+':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( ADD, var );
					break;
				case '-':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( SUB, var );
					break;
				case '*':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( MUL, var );
					break;
				case '/':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( ADD, var );
					break;
				case '|':
					currentIndex++;
					col++;
					if ( sourceCode[currentIndex] == '|' ) {
						currentIndex++;
						col++;
						var.ch = ch;
						p = make_pair ( OR, var );
						break;
					} else {
						var.ch = ch;
						p = make_pair ( BITOR, var );
						break;
					}
				case '&':
					currentIndex++;
					col++;
					if ( sourceCode[currentIndex] == '&' ) {
						currentIndex++;
						col++;
						var.ch = ch;
						p = make_pair ( AND, var );
						break;
					} else {
						var.ch = ch;
						p = make_pair ( BITAND, var );
						break;
					}
				case '>':
					currentIndex++;
					col++;
					if ( sourceCode[currentIndex] == '=' ) {
						currentIndex++;
						col++;
						var.ch = ch;
						p = make_pair ( EQUAL_LARGER, var );
						break;
					} else {
						var.ch = ch;
						p = make_pair ( LARGER, var );
						break;
					}
				case '<':
					currentIndex++;
					col++;
					if ( sourceCode[currentIndex] == '=' ) {
						currentIndex++;
						col++;
						var.ch = ch;
						p = make_pair ( EQUAL_SMALLER, var );
						break;
					} else {
						var.ch = ch;
						p = make_pair ( SMALLER, var );
						break;
					}
				case '{':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( LBRACE, var );
					break;
				case '}':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( RBRACE, var );
					break;
				case '(':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( LBRACKET, var );
					break;
				case ')':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( RBRACKET, var );
					break;
				case '[':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( LINDEX, var );
					break;
				case ']':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( RINDEX, var );
					break;
				case '=':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( EQUAL, var );
					break;
				case ';':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( SEMICOLON, var );
					break;
				case ',':
					currentIndex++;
					col++;
					var.ch = ch;
					p = make_pair ( COMMA, var );
					break;
				default:
					throw tuple<int, int, int, string> ( row, col, 0, sourceCode.substr
					                                     ( startIndex, currentIndex - startIndex ) );
			}
		}

		/* end of file */
		var.ch = ch;
		p = make_pair ( ENDOFFILE, var );
		return p;
	}

private:
	bool isLetter ( char ch ) {
		return ( ch - 'a' >= 0 && ch - 'z' <= 0 ) || ( ch - 'A' >= 0 && ch - 'Z' <= 0 );
	}

	bool isDigit ( char ch ) {
		return ch - '0' >= 0 && ch - '9' <= 0;
	}

	unsigned int isKeyWords ( string str ) {
		for ( unsigned int i = 0; i < 16; i++ ) {
			if ( str == keyWords[i] )
				return i + 1;
		}
		return 0;
	}

	int strToInt ( string str ) {
		int result = 0;
		int current = 0;
		unsigned int index = 0;
		while ( index <= str.length() ) {
			current = str[index] - '0';
			result = result * 10 + current;
			index++;
		}
		return result;
	}

	double strToDouble ( string str ) {
		double integerPart = 0;
		double demicalPart = 0;
		double current = 0;
		unsigned int index = 0;
		while ( str[index] != '.' ) {
			current = str[index] - '0';
			integerPart = integerPart * 10 + current;
			index++;
		}
		index = str.length() - 1;
		while ( str[index] != '.' ) {
			current = str[index] - '0';
			current = current / 10;
			demicalPart = demicalPart / 10 + current;
			index--;
		}
		return integerPart + demicalPart;
	}

private:
	string sourceCode;
	unsigned int currentIndex;
	unsigned row;		//locate the row of the wrong cause
	unsigned col;		//locate the column of the wrong cause
};

int main() {
	try {
		LexicalAnalyzer la;
		return 0;
	} catch ( tuple<int, int, int, string> t ) {

	}
}
