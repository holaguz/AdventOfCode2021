/* https://adventofcode.com/2021/day/5/ */

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <cassert>

using namespace std;
using mat = vector<vector<int>>;

struct point2d{
    int x;
    int y;
};

template<typename T> void print(const T& t){
    cerr << t;
}

template<typename T> void print(const vector<T>& vec){
    std::cerr << "[";
    for(const auto& value: vec){
        print(value);
        cerr << ' ';
    }
    std::cerr << "]" << std::endl;
}

void print(const point2d& p){
    fprintf(stderr, "[%d, %d]", p.x, p.y);
}


int main(){
    int mats;
    cin >> mats;
    vector<array<point2d, 2>> points(mats);

    int maxN = 0;

    for(auto& p: points){
        scanf("%d,%d -> %d,%d", &p[0].x, &p[0].y, &p[1].x, &p[1].y); // 0,9 -> 5,9
        if(p[0].x > p[1].x)
            swap(p[0], p[1]);
        maxN = max(maxN, p[0].x);
        maxN = max(maxN, p[0].y);
        maxN = max(maxN, p[1].x);
        maxN = max(maxN, p[1].y);
    }

    maxN++;

    cerr << maxN << endl;

    mat prefix_x(maxN, vector<int>(maxN, 0));
    mat prefix_y(maxN, vector<int>(maxN, 0));
    mat solved(maxN, vector<int>(maxN, 0));

    for(const auto& line: points){
        auto [p0, p1] = line;

        if(p0.x == p1.x && p0.y != p1.y){ // line on the y axis
            auto beg = min(p0.y, p1.y);
            auto end = max(p0.y, p1.y);
            prefix_y[beg][p0.x]++;
            if(end+1 < maxN) prefix_y[end+1][p0.x]--;
        }

        else if(p0.y == p1.y && p0.x != p1.x){ // line on the x axis
            auto beg = min(p0.x, p1.x);
            auto end = max(p0.x, p1.x);
            prefix_x[p0.y][beg]++;
            if(end+1 < maxN) prefix_x[p0.y][end+1]--;
        }

        else{ // To solve the first part of the puzzle, comment this statement
            if(p0.x > p1.x)
                swap(p0, p1);

            //p0 is the leftmost point
            auto delta = p1.x - p0.x;
            auto deltay = max(p0.y, p1.y) - min(p0.y, p1.y);
            assert(delta == deltay);

            for (int i = 0; i <= delta; ++i){
                if (p0.y > p1.y)                        // goes up
                    solved[p0.y - i][p0.x + i] += 1;
                else                                    // goes down
                    solved[p0.y + i][p0.x + i] += 1;
            }
        }
    }

    for (int i = 0; i < maxN; ++i)
    for (int j = 1; j < maxN; ++j)
    {
        prefix_x[i][j] += prefix_x[i][j - 1];
        prefix_y[j][i] += prefix_y[j - 1][i];
    }

    long long ans = 0;
    for (int i = 0; i < maxN; ++i)
    for (int j = 0; j < maxN; ++j)
    {
        solved[j][i] += prefix_y[j][i] + prefix_x[j][i];
        ans += (solved[j][i] >= 2);
    }

    //print(solved);
    cout << ans << endl;
}