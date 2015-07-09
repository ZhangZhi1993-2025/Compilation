#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//used for generate the NFA queue
struct NFA_Node {
    int begin;
    string regex;
    int end;
    NFA_Node ( int b, int e, string r ) : begin ( b ), regex ( r ), end ( e ) {}
};

//used for generate the DFA queue and the MFA queue
struct DFA_Node {
    int begin;
    char meta_ch;
    int end;
    DFA_Node ( int b, int e, char meta ) : begin ( b ), meta_ch ( meta ), end ( e ) {}
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

    int** analyse() {
        makeNFA();
        makeDFA();
        makeMFA();
        int **a = NULL;
        return a;
    }

private:

    void makeNFA() {
        bool isMeta = false;
        while ( !isMeta ) {

        }
    }

    string* split ( string regex ) {
        return NULL;
    }

    void makeDFA() {

    }

    void makeMFA() {

    }

private:
    queue<NFA_Node> nfa;
    queue<DFA_Node> dfa;
    vector<State_Node> states;
    string regex;
};
