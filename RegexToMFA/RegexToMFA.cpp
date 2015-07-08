#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//used for generate the NFA queue
struct NFA_Node {
    int begin;
    string regex;
    int end;
};

//used for generate the DFA queue and the MFA queue
struct DFA_Node {
    int begin;
    char metach;
    int end;
};

//used in generate the DFA queue
struct State_Node {
    vector<int> state_set;
    bool isEnd;
};

/**
 * @class RegexToMFA
 * @author Zhi
 * @date 08/07/2015
 * @file RegexToMFA.cpp
 * @brief this is the core component for an auto generator of lexical analyzer
 * which transforms the regular expression to NFA, then DFA and to MFA at the end.
 */

class RegexToMFA {
public:
    RegexToMFA ( string regex ) {
        this->regex = regex;
    }

    int analyse() {
        //int[5][5] a = new int*[5];
        int a = 0;
        return a;
    }

private:
    queue<NFA_Node> nfa;
    queue<DFA_Node> dfa;
    vector<State_Node> states;
    string regex;
};
