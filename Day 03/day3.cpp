/* https://adventofcode.com/2021/day/3 */
#include <iostream>
#include <bitset>
#include <vector>

int main(){
    int n;
    int gamma = 0, epsilon = 0;
    std::cin >> n;
    std::vector<int> count(64);
    std::vector<long long> input(n);
    long long max = 0;
    for(auto& v: input){
        std::cin >> v;
        max = v > max ? v : max;
    }

    int msb = 0;
    while(max){
        std::cerr << max << std::endl;
        max /= 10;
        msb++;
    }

    std::cerr << msb << std::endl;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < msb; ++j)
        {
            count[j] += (input[i] & 1);
            input[i] /= 10;
        }

        for (int i = 0; i < msb; ++i)
        {
            epsilon |= (2 * count[i] < n ? (1 << i) : 0);
        }

    gamma = (1 << msb) - epsilon - 1;
    std::cerr << epsilon << ' ' << gamma << std::endl;
    std::cout << gamma * epsilon << std::endl;
}