#include <iostream>
#include <stack>
using namespace std;

#define LEFT 1
#define RIGHT 2

/* used in comparison from right operator to left operator without brackets*/
const char Order[6][6] = {
//	 +	  -	   *	/	 (	  )
	'<', '<', '<', '<', '!', '!',//  +

	'<', '<', '<', '<', '!', '!',//  -

	'>', '>', '<', '<', '!', '!',//  *

	'>', '>', '<', '<', '!', '!',//  /

	'<', '<', '<', '<', '<', '=',//  (

	'>', '>', '>', '>', '!', '!' //  )
};

/* used in comparison from right operator to left operator */
const char OrderRight[6][6] = {
//	 +	  -	   *	/	 (	  )
	'>', '<', '<', '<', '!', '!',//  +

	'<', '<', '<', '<', '!', '!',//  -

	'>', '>', '>', '<', '!', '!',//  *

	'>', '>', '<', '<', '!', '!',//  /

	'<', '<', '<', '<', '<', '=',//  (

	'>', '>', '>', '>', '!', '!' //  )
};

/* used in comparison from left operator to right operator */
const char OrderLeft[6][6] = {
//	 +	  -	   *	/	 (	  )
	'>', '>', '<', '<', '!', '!',//  +

	'>', '>', '<', '<', '!', '!',//  -

	'>', '>', '>', '>', '!', '!',//  *

	'>', '>', '>', '>', '!', '!',//  /

	'<', '<', '<', '<', '<', '=',//  (

	'>', '>', '>', '>', '!', '!' //  )
};

struct opNode {
	stack<unsigned int> indexLeft;
	stack<unsigned int> indexRight;
	char op;
	opNode *leftchild;
	opNode *rightchild;
	opNode ( char op ) : op ( op ) {}
	opNode ( stack<unsigned int> indexLeft, stack<unsigned int> indexRight, char op ) : indexLeft ( indexLeft ),
		indexRight ( indexRight ), op ( op ) {}
};

class ExpressionOptimize {
public:
	ExpressionOptimize() {}

	bool run() {
		getExpression();
		if ( !bracketsValid() || !operandValid() )
			return false;
		bracketsOptimize();
		cout << this->expression;
		return true;
	}

	bool run ( string expression ) {
		getExpression ( expression );
		if ( !bracketsValid() || !operandValid() )
			return false;
		bracketsOptimize();
		cout << this->expression << endl;
		return true;
	}

private:
	void getExpression ( string str ) {
		expression = "";
		for ( unsigned int i = 0; i < str.length(); i++ ) {
			if ( str[i] == ' ' || str[i] == '\t' )
				continue;
			expression.append ( 1, str[i] );
		}
	}

	void getExpression() {
		expression = "";
		char ch = '\0';
		cout << "please input an expression sequence:" << endl;
		while ( ch != '\n' ) {
			if ( ch == ' ' || ch == '\t' )
				continue;
			expression.append ( 1, ch );
			cin >> ch;
		}
	}

	bool bracketsValid() {
		stack<char> brackets;
		char ch;
		unsigned int i = 0;
		while ( i < expression.length() ) {
			ch = expression[i++];
			if ( ch == '(' )
				brackets.push ( ch );
			else if ( ch == ')' ) {
				if ( !brackets.empty() )
					brackets.pop();
				else
					return false;
			}
		}
		return brackets.empty();
	}

	bool operandValid() {
		if ( '+' == expression[0] || '-' == expression[0] || '*' == expression[0] || '/' == expression[0]
		        || ')' == expression[0] || '.' == expression[0] ) {
			return false;
		}
		char ch;
		unsigned int i = 0;
		while ( i < expression.length() ) {
			ch = expression[i++];
			if ( ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) &&
			        ( expression[i] == '+' || expression[i] == '-' ||
			          expression[i] == '*' || expression[i] == '/' ) )
				return false;
			else if ( ch == ')' &&
			          ( expression[i - 2] == '+' || expression[i - 2] == '-' ||
			            expression[i - 2] == '*' || expression[i - 2] == '/' || expression[i] == '(' ) )
				return false;
			else if ( ch == '(' &&
			          ( expression[i] == '+' || expression[i] == '-' ||
			            expression[i] == '*' || expression[i] == '/' || expression[i - 2] == ')' ) )
				return false;
			else if ( ch >= '0' && ch <= '0' &&
			          ( expression[i] == '(' || expression[i - 2] == ')' ) )
				return false;
		}
		return true;
	}

	void bracketsOptimize() {
		opNode *root = buildExpressionTree ( this->expression, 0 );
		opNode *node = root;
		bracketsOptimize ( node, '+', LEFT );
		deleteTreeNode ( root );
		unsigned int i = 0;
		while ( i < expression.length() ) {
			if ( expression[i] == '#' )
				expression = expression.erase ( i, 1 );
			else
				i++;
		}
	}

	opNode* buildExpressionTree ( string expression , unsigned int offset ) {		//divide and conquer
		char ch;
		unsigned int i = 0;
		unsigned int leftBound = 0;
		unsigned int rightBound = expression.length() - 1;
		stack<unsigned int> indexLeft;	//if the sub string has brackets at both edges,use indices to mark it
		stack<unsigned int> indexRight;	//same as above
		int pivot = -1;					//the partition of the sub string for two more shorter sub strings
		bool isSingleNum = true;		//the exit of the recursion
		while ( i < expression.length() ) {
			ch = expression[i++];
			if ( ch == '(' ) {
				unsigned int temp = i;
				stack<char> brackets;
				brackets.push ( '(' );
				while ( i < expression.length() ) {
					ch = expression[i++];
					if ( ch == '(' )
						brackets.push ( ch );
					else if ( ch == ')' ) {
						if ( !brackets.empty() ) {
							brackets.pop();
							if ( brackets.empty() )
								break;
						}
					}
				}
				if ( i == rightBound + 1 && temp == leftBound + 1 ) {
					i = temp;
					indexLeft.push ( offset + leftBound );
					indexRight.push ( offset + rightBound );
					leftBound++;
					rightBound--;
				}
			} else if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) {
				isSingleNum = false;		//if the sub string has at least one character on the above then
				if ( pivot == -1 ) {		//the recursion will not put an end
					pivot = i - 1;
					continue;
				}
				switch ( Order[charConvert ( ch )][charConvert ( expression[pivot] )] ) {
					case '>':
						break;
					case '<':
						pivot = i - 1;
						break;
					case '=':
						break;
					default:
						throw "expression invalid!";
				}
			}
		}
		offset = offset + indexLeft.size();
		opNode *node;
		if ( isSingleNum ) {
			if ( indexLeft.empty() )
				node = new opNode ( ')' ); //use ')' as the terminal operand because it has the highest priority
			else
				node = new opNode ( indexLeft, indexRight, ')' );
			node->leftchild = NULL;
			node->rightchild = NULL;
			return node;
		} else if ( indexLeft.empty() )
			node = new opNode ( expression[pivot] );
		else
			node = new opNode ( indexLeft, indexRight, expression[pivot] );

		node->leftchild = buildExpressionTree ( expression.substr ( leftBound, pivot - leftBound ), offset );
		node->rightchild = buildExpressionTree ( expression.substr
		                   ( pivot + 1, rightBound - pivot ), offset - indexLeft.size() + pivot + 1 );
		return node;
	}

	void bracketsOptimize ( opNode *node, char parOp, int type ) {
		if ( !node )
			return;
		if ( !node->indexLeft.empty() ) {
			if ( ( type == LEFT && OrderLeft[charConvert ( node->op )][charConvert ( parOp )] == '>' ) ||
			        ( type == RIGHT && OrderRight[charConvert ( node->op )][charConvert ( parOp )] == '>' ) ) {
				while ( !node->indexLeft.empty() ) {
					expression[node->indexLeft.top()] = '#';
					node->indexLeft.pop();
					expression[node->indexRight.top()] = '#';
					node->indexRight.pop();
				}
			}
		}
		bracketsOptimize ( node->leftchild, node->op , LEFT );
		bracketsOptimize ( node->rightchild, node->op, RIGHT );
	}

	void deleteTreeNode ( opNode *node ) {
		if ( !node )
			return;
		deleteTreeNode ( node->leftchild );
		deleteTreeNode ( node->rightchild );
		delete node;
	}

	int charConvert ( char op ) {
		switch ( op ) {
			case '+':
				return 0;
			case '-':
				return 1;
			case '*':
				return 2;
			case '/':
				return 3;
			case '(':
				return 4;
			case ')':
				return 5;
			default:
				throw "Exception";
		}
	}

private:
	string expression;		//sequence of expression
};

int main () {
	ExpressionOptimize eo;
	string str[3];
	str[0] = " ( ( 3 * ( 4 + 2 ) ) ) /( 3 - 5 )";
	str[1] = " ((4)) +  (    ((( 5 * 6 ) / ( 3 * 2 ))  )  ) ";
	str[2] = "2*(4*5)+6";
	for ( unsigned int i = 0; i < 3; i++ )
		eo.run ( str[i] );
	/*
	 * char ch = '\0';
	 * while ( ch != 'q' ) {
	 * if ( !eo.run() )
	 * cout << "expression invalid!" << endl;
	 * cin >> ch;
	 * }
	 */
	return 0;
}
