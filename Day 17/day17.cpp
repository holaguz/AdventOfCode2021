/* https://adventofcode.com/2021/day/17 */

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int main(){
    char buffer[512];
    pair<int, int> bound_x, bound_y;

    scanf("%*s %*s x=%d..%d, y=%d..%d\n",
        &bound_x.first, &bound_x.second,
        &bound_y.first, &bound_y.second);

    auto max_height = abs(bound_y.first) * (abs(bound_y.first) - 1) / 2;
    cout << "Part 1: " << max_height << endl; // Trust me

    /* Part 2: Count the distinct pairs of velocities that will reach the trench eventually */
    auto triangular = [](int x) { return x * (x + 1) / 2; };

    map<int, set<int>> possible_x;
    map<int, set<int>> possible_y;
    set<int> special;

    int lb = abs(bound_y.first) + 10;

    /* Count distinct y velocities and store them by the number of steps taken to reach the trench */
    for (int i = lb; i >= bound_y.first; --i){
        auto pos = 0;
        for (int j = i; pos >= bound_y.first; j--){
            auto n_steps = i - j + 1;
            pos += j;
            if(pos >= bound_y.first && pos <= bound_y.second){
                possible_y[n_steps].insert(i);
            }
        }
    }

    /* Idem for x velocities */
    /* Velocities that reach zero while inside the trench are valid for 
    any number of steps greater than or equal to the initial velocity */
    int threshold = 1e9;
    for (int i = 1; i <= bound_x.second; ++i){
        /* We treat the velocities that drop to zero inside the trench as a special case */
        if(triangular(i) >= bound_x.first && triangular(i) <= bound_x.second){
            special.insert(i);
            threshold = min(threshold, i);
        }

        auto pos = 0;
        for (int j = i; pos <= bound_x.second; --j){
            auto n_steps = i - j + 1;
            pos += j;
            if(pos >= bound_x.first && pos <= bound_x.second){
                possible_x[n_steps].insert(i);
            }
        }
    }

    set<pair<int, int>> values;
    for(const auto& [steps, y_velocities] : possible_y){
        for(const auto& x_vel: possible_x[steps])
        for(const auto& y_vel: y_velocities)
            values.emplace(x_vel, y_vel);
    }

    auto ub = possible_y.rbegin()->first;

    for (int i = threshold; i <= ub; ++i){
        for(const auto& y_vel: possible_y[i])
        for(const auto& x_vel: special)
            values.emplace(x_vel, y_vel);
    }

    // 5945
    cout << "Part 2: " << values.size() << endl;
}