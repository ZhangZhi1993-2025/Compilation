#include <iostream>
#include <lexicalType.h>
#include <vector>
using namespace std;

class LexicalAnalyzer {
public:
	LexicalAnalyzer ( string sourceCode ) {

	}
	LexicalAnalyzer ( FILE *fp ) {

	}
	vector<Object> Next() {
		vector<Object> a;
		a.push_back ( 2 );
		return a;
	}
private:
	string sourceCode;
	unsigned int index;
};

int main() {
	return 0;
}
