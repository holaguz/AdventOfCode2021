/* https://adventofcode.com/2021/day/8/ */
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;

using vs = vector<string>;

const unordered_map<string, int> from_seven{
    {"cf", 1},
    {"acdeg", 2},
    {"acf", 7},
    {"bcdf", 4},
    {"abcdefg", 8},
    {"abcefg", 0},
    {"acdfg", 3},
    {"abdfg", 5},
    {"abdefg", 6},
    {"abcdfg", 9},
};

long long countEasyDigits(const vector<string>& input){
    long long ans = 0;
    for(const auto& s: input){
        for(auto v: {2, 3, 4, 7})
            if(s.size() == v)
                ans++;
    }
    return ans;
}

string substract(string lhs, string rhs){
    cerr << "Substracting " << lhs << " and " << rhs << " -> ";
    set<char> ret;
    for(auto c: lhs)
        ret.insert(c);
    for(auto c: rhs)
        ret.extract(c);

    string ans;
    for(auto c: ret){
        ans += c;
    }
    cerr << ans << endl;
    return ans;
}

string intersect(string lhs, string rhs){
    cerr << "Intersecting " << lhs << " and " << rhs << " -> ";

    string ans;
    vector<bool> l(256, false);

    for(auto c: lhs)
        l[c] = true;

    for(auto c: rhs){
        if(true == l[c])
            ans += c;
    }

    cerr << ans << endl;
    return ans;
}

unordered_map<char, char> guess(vs samples){
    vector<char> map(256);
    string one, four, seven, eight;
    vs len6, len5;
    for(auto& s: samples){
        if(s.size() == 2)
            one = s;
        if(s.size() == 3)
            seven = s;
        if(s.size() == 4)
            four = s;
        if(s.size() == 5)
            len5.push_back(s);
        if(s.size() == 6)
            len6.push_back(s);
        if(s.size() == 7)
            eight = s;
    }

    cerr << "One " << one << endl;
    cerr << "Four " << four << endl;
    cerr << "Seven " << seven << endl;
    cerr << "Eight " << eight << endl;
    cerr << endl;

    cerr << "1: Find 'a'" << endl;
    string encoded_a = substract(seven, one);
    assert(encoded_a.size() == 1);
    cerr << endl;

    cerr << "2: Find 'b'" << endl;
    string b_and_d = substract(four, one);
    string a_and_b_and_f_and_g = intersect(len6[0], intersect(len6[1], len6[2]));

    string encoded_b = intersect(b_and_d, a_and_b_and_f_and_g);
    assert(encoded_b.size() == 1);
    cerr << endl;

    cerr << "3: Find 'd'" << endl;
    string encoded_d = substract(b_and_d, encoded_b);
    assert(encoded_d.size() == 1);
    cerr << endl;

    cerr << "4: Find 'g'" << endl;
    string a_and_d_and_g = intersect(len5[0], intersect(len5[1], len5[2]));
    string d_and_g = substract(a_and_d_and_g, encoded_a);
    string encoded_g = substract(d_and_g, encoded_d);
    assert(encoded_g.size() == 1);
    cerr << endl;

    cerr << "5: Find 'f'" << endl;
    string encoded_f = substract(a_and_b_and_f_and_g, encoded_a + encoded_b + encoded_g);
    assert(encoded_f.size() == 1);
    cerr << endl;

    cerr << "6: Find 'c'" << endl;
    string encoded_c = substract(one, encoded_f);
    assert(encoded_c.size() == 1);
    cerr << endl;

    cerr << "7: Find 'e'" << endl;
    string encoded_e = substract(eight,
                                 encoded_a + encoded_b + encoded_c + encoded_d + encoded_f + encoded_g);
    assert(encoded_e.size() == 1);
    cerr << endl;

    return {
        {encoded_a[0], 'a'},
        {encoded_b[0], 'b'},
        {encoded_c[0], 'c'},
        {encoded_d[0], 'd'},
        {encoded_e[0], 'e'},
        {encoded_f[0], 'f'},
        {encoded_g[0], 'g'},
    };
}

/**
 * NOTE:
 * You can find the steps I took for figuring out the algo on a txt file inside this repo.
 * Substract (a, b) means removing all the symbols in b from a
 * Insertect is just the regular set intersection
 * 
 * WARNING:
 * This solution spits a lot of debugging info to the standard error output.
 * You can comment those lines out, or dump the error stream to either /dev/null or NUL if you are running Unix or Windows.
 *
 * On Unix: ./day8   < input8.txt 2>/dev/null
 * On Wind: day8.exe < input8.txt 2>NUL
 *
 * A little about performance:
 *
 * A lot of the functions do pass by value and not by const ref, thus making unnecessary copies.
 * Some of the middle steps on the guess() fn can be deleted. I just tried to be verbose to get 
 * this ugly puzzle done.
 */

int main(){

    // Just to be sure I know the alphabet
     for(auto [k, _] : from_seven){
        assert(is_sorted(k.begin(), k.end()));
    }

    int n; cin >> n;
    long long ans;
    vector<vs> samples(n, vs(10));
    vector<vs> input(n, vs(4));

    for (int i = 0; i < n; ++i){
        for (auto &s : samples[i])
            cin >> s;
        scanf(" | ", nullptr);
        for(auto& i: input[i])
            cin >> i;
    }

    /* ------------ Part 1 ------------ */
    ans = 0;
    for(const auto& i: input)
        ans += countEasyDigits(i);

    cout << "Part 1: " << ans << endl;

    /* ------------ Part 2 ------------ */
    ans = 0;

    for (int i = 0; i < n; ++i){
        int ret = 0;
        auto symbol_map = guess(samples[i]);

        for(auto& [k, v] : symbol_map){
            cerr << k << ", " << v;
            cerr << endl;
        }

        for(auto& v: input[i]){
            cerr << v << " -> ";
            for(auto& c : v)
                c = symbol_map.at(c);

            sort(v.begin(), v.end());
            cerr << v << " -> ";
            ret *= 10;
            ret += from_seven.at(v);
            cerr << from_seven.at(v) << endl;
        }
        ans += ret;
    }

    cout << "Part 2: " << ans << endl;
}