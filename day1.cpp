/* https://adventofcode.com/2021/day/1 */
#include <iostream>

int main(){
    const int n = 2000;
    int prev = 0, ans = 0, value;

    for (int i = 0; i < n; ++i){
        std::cin >> value;
        if(i && value > prev)
            ans++;
        prev = value;
    }
    std::cout << ans;
}