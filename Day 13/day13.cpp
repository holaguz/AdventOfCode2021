/* https://adventofcode.com/2021/day/13 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <typename T>
using matrix = vector<vector<T>>;
using pi = pair<int, int>;

char buffer[256];

template<typename ...Args>
void Debug(Args ...args){
    #ifdef NDEBUG
    fprintf(args...);
    #endif
}

void printMat(const matrix<bool>& mat) {
    for(const auto& row: mat){
        for(const auto& val: row)
            cout << (val ? '#' : '.' ) << ' ';
        cout << endl;
    }
}

int main(){
    int x, y;
    int cols = 0, rows = 0;
    vector<pi> dots;
    vector<pi> folds;
    bool first_run = true;
    while( 2 == scanf("%d,%d\n", &x, &y))
        dots.emplace_back(x, y);

    while(2 == scanf("%*s %*s %c=%d\n", buffer, &x)){
        if(buffer[0] == 'y')
            folds.emplace_back(x, true);
        else if(buffer[0] == 'x')
            folds.emplace_back(x, false);
        else
            assert(false);
    }

    // Sorting pairs by default sorts them by the first parameter.
    // This custom predicate allows us to sort them by the second parameter (y coordinate)
    auto sort_by_second = [](const pi &a, const pi &b)
    {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    };

    for(const auto& [line, foldAlongY] : folds){
        Debug(stderr, "Folding on line %d along %c axis\n", line, (foldAlongY ? 'y' : 'x'));
        if(foldAlongY){
            sort(dots.begin(), dots.end(), sort_by_second);
            for(auto& dot: dots){
                if(dot.second < line)
                    continue;
                Debug(stderr, "[%d, %d] -> ", dot.first, dot.second);
                dot.second = line -(dot.second - line);
                Debug(stderr, "[%d, %d]\n", dot.first, dot.second);
                assert(dot.second >= 0);
            }
        }
        else{
            sort(dots.begin(), dots.end());
            for(auto& dot: dots){
                if(dot.first < line)
                    continue;
                Debug(stderr, "[%d, %d] -> ", dot.first, dot.first);
                dot.first = line -(dot.first - line);
                Debug(stderr, "[%d, %d]\n", dot.first, dot.first);
                assert(dot.first >= 0);
            }
        }

        // Remove duplicates
        set<pi> uniques;
        for(auto& dot: dots)
            uniques.insert(dot);
        dots.clear();
        cols = 0, rows = 0;
        for(auto& dot: uniques){
            dots.push_back(dot);
            cols = dot.first  > cols ? dot.first : cols;
            rows = dot.second > rows ? dot.second : rows;
        }

        if(first_run){
            first_run = false;
            cout << "Part 1: " << dots.size() << endl;
        }
    }

    auto mat = matrix<bool>(rows + 1, vector<bool>(cols + 1, false));
    for(auto& [x, y] : dots)
        mat[y][x] = true;

    cout << "Part 2: the answer is the code below" << endl;
    printMat(mat);
}
