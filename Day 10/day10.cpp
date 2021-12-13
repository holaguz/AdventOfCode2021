/* https://adventofcode.com/2021/day/10 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;
using ll = long long;

const map<char, char> dict = {
    {'{', '}'},  {'}', '{'},
    {'<', '>'},  {'>', '<'},
    {'(', ')'},  {')', '('},
    {'[', ']'},  {']', '['}
};

const map<char, int> score_1 = {
    {')', 3},       {']', 57},
    {'}', 1197},    {'>', 25137}
};

const map<char, int> score_2 = {
    {')', 1},   {']', 2},
    {'}', 3},   {'>', 4},
};

char buffer[256];

int main(){
    ll ans = 0;
    vector<string> input;
    vector<string> missing;
    while( 1 == scanf("%s \n", buffer) )
        input.push_back(buffer);

    const int n = input.size();

    for(int i = 0; i < n; ++i){
        stack<char> stk;
        char erc = 0;

        for(auto c: input[i]){
            if(c == '{' || c == '[' || c == '<' || c == '(')
                stk.push(dict.at(c));
            else
                if(stk.top() != c)
                    erc = c;
                else
                    stk.pop();

            if(erc != 0){
                ans += score_1.at(erc);
                break;
            }
        }

        if(erc == 0){
            string s;
            while( false == stk.empty() )
                s.push_back(stk.top()), stk.pop();
            missing.push_back(s);
        }
    }

    // 388713
    cout << "Part 1: " << ans << endl;

    /* Part 2 */
    vector<ll> answers;

    for(const auto& s: missing){
        ll score = 0;
        for(auto& c: s){
            score *= 5;
            score += score_2.at(c);
        }
        answers.push_back(score);
    }

    sort(answers.begin(), answers.end());
    // 3539961434
    cout << "Part 2: " << answers.at( answers.size()/2 ) << endl;
}
