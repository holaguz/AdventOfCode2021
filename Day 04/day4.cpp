/* https://adventofcode.com/2021/day/4 */
#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>
#include <unordered_set>
#include <array>
#include <vector>

using namespace std;
using ll = long long;
using mat = vector<vector<int>>;

int main(){
    int number_count;
    cin >> number_count;
    vector<int> numbers(number_count);
    for(auto& v: numbers) cin >> v;

    const int sz = 5;
    int mat_count;
    cin >> mat_count;

    auto boards = vector<mat>(mat_count, mat(sz, vector<int>(sz, 0)));

    map<int, vector<array<int, 3>>> where;

    for (int k = 0; k < mat_count; ++k){
        auto &board = boards[k];
        for (int j = 0; j < sz; ++j){
            for (int i = 0; i < sz; ++i){
                cin >> board[j][i];
                where[board[j][i]].push_back({k, i, j});
            }
        }
    }

    auto filled_rows = vector<vector<int>>(mat_count, vector<int>(sz));
    auto filled_cols = vector<vector<int>>(mat_count, vector<int>(sz));

    int last_lucky_number = 0;
    int winners_so_far = 0;
    int last_winner_board = 0;

    vector<bool> won(mat_count, false);

    for (int i = 0; i < numbers.size() && winners_so_far == 0; ++i){
    //for (int i = 0; i < numbers.size() && winners_so_far != mat_count; ++i){          // UNCOMMENT FOR PART TWO
        auto lucky = numbers[i];
        last_lucky_number = lucky;
        // get all the records that contain that number
        auto &record = where[lucky];
        for(auto& rec: record){
            auto [k, x, y] = rec;

            if(won[k])
                continue;

            boards[k][y][x] = -1;
            filled_cols[k][x]++;
            filled_rows[k][y]++;

            if(filled_cols[k][x] == sz || filled_rows[k][y] == sz){
                won[k] = true;
                last_winner_board = k;
                winners_so_far++;
            }
        }
    }

    ll ans = 0;
    auto& winner_board = boards[last_winner_board];
    for(const auto& col: winner_board){
        for(const auto& cell: col){
            cerr << cell << ",\t";
            ans += cell != -1 ? cell : 0;
        }
        cerr << '\n';
    }

    //7161 was wrong
    //32934 was wrong
    //21054 was wrong
    //4495 was correct. This took 11 tries lmao
    cout << ans * last_lucky_number << endl;
}