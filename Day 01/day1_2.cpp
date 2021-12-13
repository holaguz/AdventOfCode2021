/* https://adventofcode.com/2021/day/1 */
#include <iostream>

int main(){
    const int n = 2000;
    int a[n];

    for (int i = 0; i < n; ++i)
        std::cin >> a[i];

    int prev = a[0] + a[1] + a[2];
    int ans = 0;

    for (int i = 3; i < n; ++i){
        int value = a[i] + a[i - 1] + a[i - 2];
        if(value > prev)
            ++ans;
        prev = value;
    }

    std::cout << ans << std::endl;
}