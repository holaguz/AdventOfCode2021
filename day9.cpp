/* https://adventofcode.com/2021/day/9 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;
using ll = long long;

template <typename T>
using matrix =vector<vector<T>>;

struct Node{
    unordered_set<Node *> adj;
    int height;
    int size = 1;
};

unordered_set<Node *> vis;
char s[128];

int dfs(Node* u){
    if(vis.count(u))
        return 0;
    vis.insert(u);

    for(auto& next: u->adj)
        if(next->height != 9 && next->height > u->height){
            u->size += dfs(next);
            next->size = u->size;
        }
    return u->size;
}

int main(){
    matrix<int> input;
    ll ans = 0;

    while(1 == scanf("%s\n", s)){
        vector<int> row;
        for (auto c = &s[0]; *c != '\0'; ++c)
            row.emplace_back(*c - '0');
        input.push_back(row);
    }

    const int rows = input.size();
    const int cols = input.back().size();

    /* Part 1 */
    auto check = [&](int r, int c)
    {
        const auto &this_cell = input[r][c];
        bool test = true;
        if(r > 0)
            test &= (this_cell < input[r - 1][c]);
        if(r < rows - 1)
            test &= (this_cell < input[r + 1][c]);
        if(c > 0)
            test &= (this_cell < input[r][c - 1]);
        if(c < cols - 1)
            test &= (this_cell < input[r][c + 1]);
        return test;
    };

    ans = 0;
    for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
        if(check(i, j))
            ans += (input[i][j] + 1);

    // 516
    cout << "Part 1: " << ans << endl;

    /* Part 2 */
    matrix<Node *> nodes(rows, vector<Node *>(cols));
    vector<Node *> flat_nodes;

    for(auto& u: nodes)
    for(auto& v: u){
        v = new Node{};
        flat_nodes.push_back(v);
    }


    for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
    {
        auto this_node = nodes[i][j];
        this_node->height = input[i][j];

        auto left   = (i > 0);
        auto right  = (i < rows - 1);
        auto up     = (j > 0);
        auto down   = (j < cols - 1);

        if(left)    this_node->adj.insert(nodes[i - 1][j]);
        if(right)   this_node->adj.insert(nodes[i + 1][j]);
        if(up)      this_node->adj.insert(nodes[i][j - 1]);
        if(down)    this_node->adj.insert(nodes[i][j + 1]);
    }

    sort(flat_nodes.begin(), flat_nodes.end(),  // Sort the nodes by height
    [](Node* a, Node* b){
        return a->height < b->height;
    });

    vector<int> sizes;
    for(auto& node: flat_nodes)
        sizes.push_back(dfs(node));

    sort(sizes.rbegin(), sizes.rend());

    ans = 1;
    for (int i = 0; i <= 2; ++i){
        fprintf(stderr, "Basin %d: %d\n", i + 1, sizes[i]);
        ans *= sizes[i];
    }

    // 1023660
    cout << "Part 2: " << ans << endl;
}