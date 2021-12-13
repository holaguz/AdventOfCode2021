/* https://adventofcode.com/2021/day/2 */
#include <iostream>
#include <cassert>
#include <string>

int main(){
    const int n = 1000;
    int x = 0, y = 0, amount;
    std::string move;
    for (int i = 0; i < n; ++i){
        std::cin >> move >> amount;
        if(move == "forward")
            x += amount;
        else if(move == "up")
            y -= amount;
        else if(move == "down")
            y += amount;
        else
            assert(false);
    }
    std::cout << x * y << std::endl;
}