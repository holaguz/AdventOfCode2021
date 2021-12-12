/* https://adventofcode.com/2021/day/12 */
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
using namespace std;

map<string, vector<string>> adj;
char buffer[256];
int ans = 0;

bool is_small(const string& s){
    return (
        s != "start"    &&
        s != "end"      &&
        s[0] >= 'a'     &&
        s[0] <= 'z');
}

void dfs(const string& u, set<string> vis, bool two_times){
    if(is_small(u) && vis.count(u))
        if(two_times)
            return;
        else
            two_times = true;

    if(u == "end"){
        ans++;
        return;
    }

    vis.insert(u);
    auto next = adj[u];

    for(const auto& v: next){
        if(v == "start")
            continue;
        dfs(v, vis, two_times);
    }
}

/**
 * NOTE:
 * Passing the set by value is awful for performance.
 * If you want to add more paths you better download some additional RAM.
 */

int main(){

    while( 1 == scanf("%s\n", buffer) ){
        string u = buffer, v = buffer;
        auto index = u.find_first_of('-');
        u = u.substr(0, index);
        v = v.substr(index + 1);
        fprintf(stderr, "%s <-> %s\n", u.c_str(), v.c_str());

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ans = 0;
    dfs("start", {}, true);
    //3510
    cout << "Part 1: " << ans << endl;

    ans = 0;
    dfs("start", {}, false);
    //122880
    cout << "Part 2: " << ans << endl;
}
