/* https://adventofcode.com/2021/day/11 */
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstring>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

template <typename T>
using matrix = vector<vector<T>>;

char buffer[256];

void printMat(const matrix<int> &m){
    for(auto& r: m){
        for(auto& c: r)
            cerr << c;
        cerr << endl;
    }
}

vector<pi> getNeighbors(const matrix<int>& mat, const int x, const int y){
    const int rows = mat.size();
    const int cols = mat.back().size();

    bool up = (y > 0);
    bool down = (y < rows - 1);

    bool left = (x > 0);
    bool right = (x < cols - 1);

    vector<pi> neigh;

    if(up)              neigh.emplace_back(x, y - 1);
    if(down)            neigh.emplace_back(x, y + 1);

    if(left)            neigh.emplace_back(x - 1, y);
    if(right)           neigh.emplace_back(x + 1, y);

    if(up && left)      neigh.emplace_back(x - 1, y - 1);
    if(up && right)     neigh.emplace_back(x + 1, y - 1);
    if(down && left)    neigh.emplace_back(x - 1, y + 1);
    if(down && right)   neigh.emplace_back(x + 1, y + 1);

    return neigh;
}

int tick(matrix<int>& mat){
    const int rows = mat.size();
    const int cols = mat.back().size();

    queue<pi> flash;
    set<pi> reset;

    for (int y = 0; y < rows; ++y)
    for (int x = 0; x < cols; ++x){
        mat[y][x]++;
        if(mat[y][x] >= 10){
            flash.push({y, x});
            reset.insert({y, x});
        }
    }

    while( false == flash.empty() ){
        auto [y, x] = flash.front();
        flash.pop();
        auto neighbors = getNeighbors(mat, x, y);

        for(const auto& [x, y] : neighbors){
            if(reset.end() != reset.find({y, x}))
                continue;

            mat[y][x]++;
            if(mat[y][x] >= 10){
                flash.push({y, x});
                reset.insert({y, x});
            }
        }
    }

    for(const auto& [y, x]: reset)
        mat[y][x] = 0;

    return reset.size();
}

int main(){
    matrix<int> input;
    ll ans = 0;
    ll ans2 = 0;
    bool all_flashed = false;
    while( 1 == scanf("%s\n", buffer) ){
        input.emplace_back();
        for (int i = 0; buffer[i]; ++i)
            input.back().emplace_back(buffer[i] - '0');
    }

    const int total = input.size() * input.back().size();
    const int times = 100;

    for (int i = 1; i <= times; ++i){
        auto flash_count = tick(input);
        ans += flash_count;

        if(flash_count == total){   // For Part 2
            ans2 = times;
            all_flashed = true;
        }

        cerr << "After step " << i << endl;
        printMat(input);
        cerr << endl;
    }

    //1697
    cout << "Part 1: " << ans << endl;

    if(false == all_flashed){
        ans2 = times + 1;
        while (tick(input) != total) ++ans2;
    }

    //344
    cout << "Part 2: " << ans2 << endl;
}
